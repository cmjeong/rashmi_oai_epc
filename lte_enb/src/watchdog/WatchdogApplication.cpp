///////////////////////////////////////////////////////////////////////////////
//
// $Id: WatchdogApplication.cpp 27745 2010-06-30 12:56:50Z mmcternan $
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sys/types.h>
#include <inttypes.h>
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <errno.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "WatchdogApplication.h"
#include "ProcessGuardian.h"
#include "KickGuardian.h"
#include "BfinDog.h"
#include "SerialisationIds.h"
#ifdef BRDCM
#include "brcm_wd.h"
#include "brcm_syscalls.h"
#endif

#define BUFLEN                          512  //Max length of buffer
#define PORT                            6019   //The port on which to listen for incoming data
#define WD_TMR_INTERVAL                 5
#define WR_TMR_MAX_INTERVAL             10
#define KERNAL_WATCHDOG_TIMEOUT_VAL     120
#define KERNAL_WATCHDOG_MAX_TIMEOUT_VAL 300
#define WATCH_DOG                       27
#define POSTOFFICE                      1 
#define REGISTER_ENTITY_REQ             0x0801 /*REGISTER_ENTITY_REQ*/
#define MESSAGING_ROUTE_IND             0x0806 /*fix for ccpu00145040 */
#define POST_OFFICE_PORT                6000
#define WATCH_DOG_PORT                  6019 
int softTimeOut;
int hardTimeOut;
void die(const char *s)
{
    perror(s);
    exit(1);
}

extern "C" void alarm_wakeup (int i)
{
   WatchdogApplication::GetInstance().HandleTimerExpiry();
   WatchdogApplication::GetInstance().startTimer();
}

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

WatchdogApplication* WatchdogApplication::instance = NULL;

extern "C" void catchTerm(int v)
{
    printf("Received signal %u\n", v);
#ifdef BRDCM
    printf("Stopping BRDCM H/W WD as S/W watchdog is explicilty killed by signal %u \n", v);
    brcm_wd_stop();
#endif

    /* Indicate that we should exit */
    WatchdogApplication::GetInstance().m_exit = true;
}

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

WatchdogApplication::WatchdogApplication () :
    m_exit(false),
    m_dog(NULL),
    m_consecutiveMissedKicks(0)
{
   /*Registration Code*/
   u8 data[20];
   u32 sock, rc;
   struct sockaddr_in sin;
   u32 size;	
   u32 from=htonl(WATCH_DOG), to=htonl(POSTOFFICE);
   u32 serid, entity;

   size = 16;
   entity = htonl(WATCH_DOG);
   serid = htonl(REGISTER_ENTITY_REQ);


   /* compile the packet payload */
   memcpy(&data[0],  &from,  4);
   memcpy(&data[4],  &to,    4);
   memcpy(&data[8],  &serid, 4);
   memcpy(&data[12], &entity,4);

   /* send the payload to post office on localhost using udp */
   sock = socket(PF_INET, SOCK_DGRAM, 0);
   if (sock < 0) 
   {
      printf("could not create socket, errno=%d\n", errno);
   }

   memset(&sin, 0, sizeof(sin));
   sin.sin_family = AF_INET;
   sin.sin_port = htons(POST_OFFICE_PORT);
   inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);

   struct linger so_linger;
   so_linger.l_onoff = true;
   so_linger.l_linger = 0;
   setsockopt(sock, SOL_SOCKET, SO_LINGER, &so_linger, sizeof so_linger);

   struct sockaddr_in localInnerIpAddr;	
   localInnerIpAddr.sin_family = AF_INET;
   localInnerIpAddr.sin_port = htons(WATCH_DOG_PORT);
   inet_pton(AF_INET, "127.0.0.1", &localInnerIpAddr.sin_addr.s_addr);  
   bind(sock, (struct sockaddr *) &localInnerIpAddr, sizeof(struct sockaddr));

   rc = sendto(sock, data, size, 0, (const sockaddr *) &sin, sizeof(sin));
   if (rc != size) 
   {
      printf("packet send failed, errno=%d\n", errno);
   }
   close(sock);
}

WatchdogApplication::~WatchdogApplication ()
{
    instance = NULL;
}

WatchdogApplication &WatchdogApplication::GetInstance()
{
    if(instance == NULL)
    {
        instance = new WatchdogApplication();
    }

    return (*instance);
}

void WatchdogApplication::RemoveGuardian(Guardian *g)
{
    vector<Guardian*>::iterator vi;

    // Search the vector of guardians to remove from there
    for(vi = m_guardians.begin(); vi != m_guardians.end(); vi++)
    {
        if(*vi == g)
        {
            m_guardians.erase(vi);
            break;
        }
    }
}

void WatchdogApplication::startTimer()
{
  struct itimerval tout_val;
  tout_val.it_interval.tv_sec = 0;
  tout_val.it_interval.tv_usec = 0;
  tout_val.it_value.tv_sec = softTimeOut; /* set timer for softTimeOut seconds */
  tout_val.it_value.tv_usec = 0;
  setitimer(ITIMER_REAL, &tout_val,0);
  signal(SIGALRM,alarm_wakeup);
}

u32 WatchdogApplication::ThreadProcedure ()
{
    //Setting maximum priority
	struct sched_param p;
    p.sched_priority = sched_get_priority_max(SCHED_FIFO);
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &p);

    // Register handlers to catch 'normal' shutdown cases
    signal(SIGTERM, catchTerm);
    signal(SIGHUP, catchTerm);
    signal(SIGINT, catchTerm);

    // Creating the watchdog
    m_dog = new BfinDog();
	
	startTimer();
    // Loop, processing received messages
    MonitorMsgs();

    if(m_dog != NULL) delete m_dog;

    printf("Watchdog exiting\n");

    return(0);
}

void WatchdogApplication::MonitorMsgs()
{
    struct sockaddr_in si_me, si_other;
    int s,recv_len;
	unsigned int slen = sizeof(si_other);
    char buf[BUFLEN];
     
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
  
    struct linger so_linger;
    so_linger.l_onoff = true;
    so_linger.l_linger = 0;
    setsockopt(s, SOL_SOCKET, SO_LINGER, &so_linger, sizeof so_linger);
  
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
     
    //keep listening for data
    while(1)
    {
        fflush(stdout);
         
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
         
        //print details of the client/peer and the data received
        //printf("Received packet from %s:%d :%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));

        MessageHandler(buf);
        if(m_exit)
        {
           break;
        }
    }
}
void WatchdogApplication::MessageHandler (char *buf)
{
   u32 srcEntity = 0;
   u32 destEntity = 0;
   u32 msgType = 0;
   pid_t pid = 0;
   u32 len = 0;

   memcpy(&srcEntity,&buf[len],sizeof(srcEntity));
   srcEntity = ntohl(srcEntity);
   len += sizeof(srcEntity);

   memcpy(&destEntity,&buf[len],sizeof(destEntity));
   destEntity = ntohl(destEntity);
   len += sizeof(destEntity);

   memcpy(&msgType,&buf[len],sizeof(msgType));
   msgType = ntohl(msgType);
   len += sizeof(msgType);

   memcpy(&pid,&buf[len],sizeof(pid_t));
   pid = ntohl(pid);
   len += sizeof(pid_t);

   // Handle the message.
   switch(msgType)
   {
      case SERIALISATION_ID_WATCHDOG_ADD_PID_REQ:
         {
            u16 strlen;
            char name[50];
            memset(&name,'\0',50);
            memcpy(&strlen,&buf[len],sizeof(strlen));
            strlen = ntohs(strlen);
            len += sizeof(strlen);

            memcpy(name,&buf[len],strlen);
            name[strlen-1] = '\0';

            //printf("Received WATCHDOG_ADD_PID_REQ: msgType[%x] pid[%d] name[%s]\n", msgType, pid, name);
#ifdef BRDCM
	printf("\nInit. the BRDCM Hardware Watchdog");
	brcm_wd_kick_def_max_params();
#endif
            map<pid_t, ProcessGuardian *>::iterator i = m_pidguardians.find(pid);

            // Check if already in the map
            if(i == m_pidguardians.end())
            {
               ProcessGuardian *pg = new ProcessGuardian(pid, name);

               m_guardians.push_back(pg);
               m_pidguardians[pid] = pg;

               printf("Guardian added: %s\n", name);
            }
         }	
         break;

      case SERIALISATION_ID_WATCHDOG_KICK_REQ:
         {
            u16 softlimit;
            u16 hardlimit;

            memcpy(&softlimit,&buf[len],sizeof(softlimit));
            softlimit = ntohs(softlimit);
            len += sizeof(softlimit);

            memcpy(&hardlimit,&buf[len],sizeof(hardlimit));
            hardlimit = ntohs(hardlimit);
            len += sizeof(hardlimit);

            //printf("Received WATCHDOG_KICK_REQ: msgType[%x] pid[%d] softlimit[%d] hardlimit[%d]\n", msgType, pid, softlimit, hardlimit);
#ifdef BRDCM
            //brcm_wd_rearm();
#endif
            map<u32, KickGuardian *>::iterator i = m_kickguardians.find(pid);

            // Check if already in the map
            if(i != m_kickguardians.end())
            {
               // It is, just kick it
               i->second->Kick();
            }
            else
            {
               // It's new, create new object and store in list and map
               KickGuardian *kg = new KickGuardian(pid, softlimit, hardlimit);

               m_guardians.push_back(kg);
               m_kickguardians[pid] = kg;

               printf("Guardian added: %s\n", kg->ToString().c_str());
            }
         }
         break;

      case SERIALISATION_ID_WATCHDOG_REMOVE_PID_REQ:
         {
            map<pid_t, ProcessGuardian *>::iterator mi = m_pidguardians.find(pid);

            // Check if in the map
            if(mi != m_pidguardians.end())
            {
               Guardian *g = mi->second;

               // Remove from the map
               m_pidguardians.erase(mi);
               RemoveGuardian(g);

               printf("Guardian removed: %s\n", g->ToString().c_str());
               delete g;
            }
            else
            {
               printf("Unknown guardian: pid=%d\n",pid);
            }
         }
         break;

      case SERIALISATION_ID_WATCHDOG_KICK_STOP_REQ:
         {
            map<u32, KickGuardian *>::iterator mi = m_kickguardians.find(pid);

            // Check if in the map
            if(mi != m_kickguardians.end())
            {
               Guardian *g = mi->second;

               // Remove from the map
               m_kickguardians.erase(mi);
               RemoveGuardian(g);

               printf("Guardian removed: %s\n", g->ToString().c_str());
               delete g;
            }
            else
            {
               printf("Unknown guardian: id=%d\n",pid);
            }
         }
         break;
         /* ccpu00145040: message route type added. */
      case MESSAGING_ROUTE_IND:
         {
            /*DO Nothing*/
         }
         break;
      default:
         break;
   }
}

void WatchdogApplication::HandleTimerExpiry( )
{
   Guardian *guardianBlamedForFailureAndReboot = NULL;
   vector<Guardian*>::iterator i;
   bool allGood = true;

   // Check each guardian in turn
   for(i = m_guardians.begin(); i != m_guardians.end(); i++)
   {
      Guardian *g = *i;

      if(!g->IsGood())
      {
         if(!guardianBlamedForFailureAndReboot)
         {
            guardianBlamedForFailureAndReboot = g;
         }

         allGood = false;
         printf("Guardian unresponsive: %s\n", g->ToString().c_str());
      }
   }

   // Kick the dog if all guardians are okay
   if(m_dog)
   {
      if(allGood)
      {
         m_dog->Kick();
#ifdef BRDCM
         brcm_wd_rearm();
#endif
         m_consecutiveMissedKicks = 0;
      }
      else
      {
         m_consecutiveMissedKicks++;
         printf("Watckdog kicks missed=%d\n", m_consecutiveMissedKicks);
      }

      if(m_consecutiveMissedKicks == 3)
      {
			int ret;
         printf( "Watchdog failure, possibly due to %s.\n", guardianBlamedForFailureAndReboot->ToString().c_str());
#ifdef BRDCM
         printf("Stopping BRDCM H/W WD, because L1_L2_log_info.sh is going to execute by S/W WD\n");
         brcm_wd_stop();
#endif
         ret = system("sh L1_L2_log_info.sh");
         ret = system("cd /mnt/tmp/ && sh ftpputLog.sh");
      }
   }
}

int main (int argc, char **argv)
{
   if (argc == 3)
   {
      softTimeOut = atoi(argv[1]);
      hardTimeOut = atoi(argv[2]);

      if(softTimeOut < 5 || softTimeOut > 10)
      {
         printf("Value : (%d) not in range(%d,%d),executing with default value: (%d)\n",
         softTimeOut,WD_TMR_INTERVAL,WR_TMR_MAX_INTERVAL,WD_TMR_INTERVAL);
         softTimeOut = WD_TMR_INTERVAL;
      }
      if(hardTimeOut <120 || hardTimeOut > 300)
      {
         printf("Value: (%d) not in range(%d ,%d), executing with default value: (%d)\n",
         hardTimeOut,KERNAL_WATCHDOG_TIMEOUT_VAL,KERNAL_WATCHDOG_MAX_TIMEOUT_VAL,
         KERNAL_WATCHDOG_TIMEOUT_VAL);
         hardTimeOut = KERNAL_WATCHDOG_TIMEOUT_VAL;
      }
   }
   else
   {
      printf("Running with default values");
      softTimeOut = WD_TMR_INTERVAL;
      hardTimeOut = KERNAL_WATCHDOG_TIMEOUT_VAL;
   }
   return(WatchdogApplication::GetInstance().ThreadProcedure());
}

// END OF FILE
