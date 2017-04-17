

/********************************************************************20**
 
     Name:     System Services -- Message manipulation functions
 
     Type:     C source file
 
     Desc:     Source Code for message related functions.
 
     File:     ss_msg.c
 
     Sid:      ss_msg.c@@/main/TeNB_Main_BR/1 - Thu Jan  2 22:33:18 2014
 
     Prg:      sn
 
*********************************************************************21*/
 


/* header include files (.h) */

#include "envopt.h"        /* environment options */
#include "envdep.h"        /* environment dependent */
#include "envind.h"        /* environment independent */
  
#include "gen.h"           /* general layer */
#include "ssi.h"           /* system services */

#include "ss_err.h"        /* errors */
#include "ss_dep.h"        /* implementation-specific */
#include "ss_queue.h"      /* queues */
#include "ss_strm.h"       /* STREAMS */
#include "ss_msg.h"        /* messaging */
#include "ss_mem.h"        /* memory management interface */
#include "ss_gen.h"        /* general */



/* header/extern include files (.x) */

#include "gen.x"           /* general layer */
#include "ssi.x"           /* system services */

#include "ss_dep.x"        /* implementation-specific */
#include "ss_queue.x"      /* queues */
#include "ss_task.x"       /* tasking */
#include "ss_timer.x"      /* timers */
#include "ss_strm.x"       /* STREAMS */
#include "ss_msg.x"        /* messaging */
#include "ss_mem.x"        /* memory management interface */
#include "ss_drvr.x"       /* driver tasks */
#include "ss_gen.x"        /* general */



/* forward declarations */
PUBLIC S16 ssGetDBufOfSize ARGS((Region region, Size size, Buffer **dBuf));

#if 1 /* ss012.13: Addition */
#ifdef SS_M_PROTO_REGION 
PRIVATE Buffer *DupMsg ARGS((Region region, Buffer *buffer));
#endif /* SS_M_PROTO_REGION */
#endif /* ss012.13: Addition */

/* local defines */
#define MBSIZE   (sizeof(SsMblk))
#define MDBSIZE  (sizeof(SsDblk) + sizeof(SsMblk))
#define MSGSIZE  (MDBSIZE + sizeof(SsMsgInfo))

#define INITMBLK(mp, dp, dat)   {\
   mp->b_next = NULLP;\
   mp->b_prev = NULLP;\
   mp->b_cont = NULLP;\
   mp->b_rptr = dat;\
   mp->b_wptr = dat;\
   mp->b_datap = dp;\
}

#define INITDBLK(dp, dat, size, frtn)   {\
   dp->db_frtnp = frtn;\
   dp->db_base = dat;\
   dp->db_lim = (dat == NULLP ? dat : (dat + size));\
   dp->db_ref = 1;\
   dp->db_type = SS_M_DATA;\
}

#define INITB(mp, dp, dat, size, frtn)   {\
   INITMBLK(mp, dp, dat)\
   INITDBLK(dp, dat, size, frtn)\
}



/*
*
*       Fun:   ssGetDBufOfSize
*
*       Desc:  This function gets a message buffer from specified region and
*              size
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: message is created. message is returned via message buffer
*              pointer. Buffer type is SS_M_DATA.
*              return is ok.
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 ssGetDBufOfSize
(
Region region,
Size size,
Buffer **dBuf
)
#else
PUBLIC S16 ssGetDBufOfSize(region, size, dBuf)
Region region;
Size size;
Buffer **dBuf;
#endif
{
   Size mdsize;
   Data *data;
   SsDblk *dptr;

   TRC1(ssGetDBufOfSize)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (!dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS272, ERRZERO, "ssGetDBufOfSize : Null\
                 Buffer");
      RETVALUE(RFAILED);
   }
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS273, ERRZERO, "ssGetDBufOfSize : Invalid\
                region id");
      RETVALUE(RFAILED);
   }
 
   if (size <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS274, ERRZERO, "ssGetDBufOfSize : Invalid\
                 size");
      RETVALUE(RFAILED);
   }
#endif

   mdsize = MDBSIZE;
#if 0 /* ss012.13: Deletion */
   if (osCp.regionTbl[region].flags & SS_OUTBOARD_FLAG)
   {
      /* allocate memory for data buffer */
      if (SAlloc(region, &size, 0, &data) != ROK)
         RETVALUE(ROUTRES);
      if (SAlloc(SS_DFLT_REGION, &mdsize, 0, (Data **) dBuf) != ROK)
      {
         SFree(region, (Data *) data, size);
         RETVALUE(ROUTRES);
      }
   }
   else
   {
      mdsize += size;
      if (SAlloc(region, &mdsize, 0, (Data **) dBuf) != ROK)
      {
         RETVALUE(ROUTRES);
      }
      data = (Data *) (*dBuf) + MDBSIZE;
      size = mdsize - MDBSIZE;
   }
#endif /* ss012.13: Deletion */
#if 1 /* ss012.13: Addition */
#ifndef SS_M_PROTO_REGION 
   if (osCp.regionTbl[region].flags & SS_OUTBOARD_FLAG)
   {
      /* allocate memory for data buffer */
      if (SAlloc(region, &size, 0, &data) != ROK)
         RETVALUE(ROUTRES);
      if (SAlloc(SS_DFLT_REGION, &mdsize, 0, (Data **) dBuf) != ROK)
      {
         SFree(region, (Data *) data, size);
         RETVALUE(ROUTRES);
      }
   }
   else
   {
      mdsize += size;
      if (SAlloc(region, &mdsize, 0, (Data **) dBuf) != ROK)
      {
         RETVALUE(ROUTRES);
      }
      data = (Data *) (*dBuf) + MDBSIZE;
      size = mdsize - MDBSIZE;
   }
#else /* SS_M_PROTO_REGION */
   mdsize += size;
   if (SAlloc(region, &mdsize, 0, (Data **) dBuf) != ROK)
   {
      RETVALUE(ROUTRES);
   }
   data = (Data *) (*dBuf) + MDBSIZE;
   size = mdsize - MDBSIZE;
#endif /* SS_M_PROTO_REGION */
#endif /* ss012.13: Addition */
 
   dptr = (SsDblk*) (((Data *) (*dBuf)) + MBSIZE);
 
   INITB((*dBuf), dptr, data, size, NULLP)

   RETVALUE(ROK);
} /* ssGetDBufOfSize */


/*
*
*       Fun:   SGetMsg
*
*       Desc:  This function gets a message
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: message is created. message is set to type SS_M_PROTO.
*              message is returned via message buffer pointer.
*              return is ok.
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SGetMsg
(
Region region,              /* region id */
Pool pool,                  /* pool id */
Buffer **mBuf               /* pointer to message buffer */
)
#else
PUBLIC S16 SGetMsg(region, pool, mBuf)
Region region;              /* region id */
Pool pool;                  /* pool id */
Buffer **mBuf;              /* pointer to message buffer */
#endif
{
   SsMsgInfo *minfo;
   Size size;
   SsDblk *dptr;
   Data *data;
   /* ss021.103 - Addition of return value */
#ifndef SS_PERF
#if (ERRCLASS & ERRCLS_INT_PAR)
   S16 ret;
#endif
#endif

   TRC1(SGetMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS275, ERRZERO, "SGetMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS276, ERRZERO, "SGetMsg : Invalid region\
                                                   id");
      RETVALUE(RFAILED);
   }
 
   if (pool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS277, ERRZERO, "SGetMsg : Invalid pool id");
      RETVALUE(RFAILED);
   }

/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* ss021.103 - Addition to check if region is registered */
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS278, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }
#endif
#endif
#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is present */
   if (osCp.regionTbl[region].used == FALSE)
   {
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS279, ERRZERO,
                  "Could not release semaphore");
         RETVALUE(RFAILED);
#endif
      }
#endif
      SSLOGERROR(ERRCLS_INT_PAR, ESS280, region, "Region not registered");
      RETVALUE(RFAILED);
   }
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS281, ERRZERO,
                  "Could not release semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif
#endif

   size = MSGSIZE;
#if 0 /* ss012.13: Deletion */
   if (SAlloc(SS_DFLT_REGION, &size, 0, (Data**) mBuf) != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS282, ERRZERO, "SGetMsg:Failed in SAlloc");
      RETVALUE(ROUTRES);
   }
#endif /* ss012.13: Deletion */
#if 1 /* ss012.13: Addition */
#ifdef SS_M_PROTO_REGION
   if (SAlloc(region, &size, 0, (Data**) mBuf) != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS283, ERRZERO, "SGetMsg:Failed in SAlloc");
      RETVALUE(ROUTRES);
   }
#else /* SS_M_PROTO_REGION */  
   if (SAlloc(SS_DFLT_REGION, &size, 0, (Data**) mBuf) != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS284, ERRZERO, "SGetMsg:Failed in SAlloc");
      RETVALUE(ROUTRES);
   }
#endif /* SS_M_PROTO_REGION */
#endif /* ss012.13: Addition */

   dptr = (SsDblk*) (((Data *) (*mBuf)) + MBSIZE);
   data = (Data*) (((Data *) (*mBuf)) + MDBSIZE);
 
   /* INITB initialises and sets up the message blk */
#if 0 /* ss016.13: Deletion */
   INITB((*mBuf), dptr, data, size, NULLP)
#else
   INITB((*mBuf), dptr, data, sizeof(SsMsgInfo), NULLP)
#endif /* ss016.13: Addition */

   (*mBuf)->b_datap->db_type = SS_M_PROTO;
   (*mBuf)->b_wptr = (*mBuf)->b_rptr + sizeof(SsMsgInfo);

   /* initialise message info of mBuf */
   minfo = (SsMsgInfo*) (*mBuf)->b_rptr;

   minfo->region = region;
   minfo->pool = pool;
   minfo->len = 0;
   minfo->endptr = NULLP;
   minfo->eventInfo.event = SS_EVNT_DATA;
   /* ss021.103 - Addition to initialize next and route */
   minfo->next = NULLP;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SPutMsg
*
*       Desc:  This function deallocates a message back.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: all data attached to message is returned to memory.
*              message is returned to memory. return is ok.
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SPutMsg
(
Buffer *mBuf
)
#else
PUBLIC S16 SPutMsg(mBuf)
Buffer *mBuf;
#endif
{
   Buffer *tmp;
   SsMsgInfo *minfo;

   TRC1(SPutMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS285, ERRZERO, "SPutMsg: Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS286, ERRZERO, "SPutMsg: Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the message info */
   minfo = (SsMsgInfo *) mBuf->b_rptr;

   while ((tmp = mBuf->b_cont))
   {
      /* set b_cont of mBuf to point to the b_cont of tmp */
      mBuf->b_cont = tmp->b_cont;
      (Void) SPutDBuf(minfo->region, minfo->pool, tmp);
   }
#if 0 /* ss012.13: Deletion */
   SFree(SS_DFLT_REGION, (Data *) mBuf, MSGSIZE);
#endif /* ss012.13: Deletion */
#if 1 /* ss012.13: Addition */
#ifdef SS_M_PROTO_REGION
   /* ss021.103 - Addition to check return value of SFree */
   if (SFree(minfo->region, (Data *) mBuf, MSGSIZE) == RFAILED)
      RETVALUE(RFAILED);
#else /* SS_M_PROTO_REGION */
   /* ss021.103 - Addition to check return value of SFree */
   if (SFree(SS_DFLT_REGION, (Data *) mBuf, MSGSIZE) == RFAILED)
      RETVALUE(RFAILED);
#endif /* SS_M_PROTO_REGION */
#endif /* ss012.13: Addition */

   RETVALUE(ROK);
}

/*
*
*       Fun:   SInitMsg
*
*       Desc:  This function deallocates a message back and then
*              reinitializes the message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: all data attached to message is returned to memory.
*              message is set to empty. message is not returned to
*              memory. return is ok.
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SInitMsg
(
Buffer *mBuf
)
#else
PUBLIC S16 SInitMsg(mBuf)
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;

   TRC1(SInitMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS287, ERRZERO, "SInitMsg: Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS288, ERRZERO, "SInitMsg: Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the message info */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   /* free all SS_M_DATA blks */
   while ((tmp = mBuf->b_cont))
   {
      mBuf->b_cont = tmp->b_cont;
      (Void) SPutDBuf(minfo->region, minfo->pool, tmp);
   }
   /* initialise the length and endptr variables of mBuf */

   minfo->len = 0;
   minfo->endptr = NULLP;
   minfo->next = NULLP;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SAddPreMsg
*
*       Desc:  This function copies one byte of data to the
*              beginning of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*
*              if message is not empty: data is placed in front of all
*              other data in message. message length is incremented.
*              return is ok.
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SAddPreMsg
(
Data data,
Buffer *mBuf
)
#else
PUBLIC S16 SAddPreMsg (data, mBuf)
Data data;
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
   Buffer *newb;

   TRC1(SAddPreMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS289, ERRZERO, "SAddPreMsg: Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS290, ERRZERO, "SAddPreMsg: Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED); 
   }
#endif

   minfo = (SsMsgInfo *) mBuf->b_rptr;

   /* ss021.103 - Addition to check if exceeding maximum message length */
#ifdef LONG_MSG
   if (minfo->len == 0x7FFFFFFF)
#else
   if (minfo->len == 0x7FFF)
#endif
   {
      RETVALUE(ROUTRES);
   }
      
   /*
    * allocate a message blk using SGetDBuf(), if there are no data blks in the
    * message, mBuf, or if the reference count of the first data blk is greater
    * than 1, or if there is no space to append databytes in front of the read
    * pointer of the first data blk
   */
   if (!(tmp = mBuf->b_cont) || (tmp->b_datap->db_ref > 1) ||
        (tmp->b_rptr == tmp->b_datap->db_base))
   {
      if (SGetDBuf(minfo->region, minfo->pool, &newb) != ROK)
      {
         SSLOGERROR(ERRCLS_DEBUG, ESS291, ERRZERO, "SAddPreMsg:Failed in\
                    SGetDBuf");
         RETVALUE(ROUTRES);
      }
      /* set the read and write pointers to end of data buffer */
      /* subsequent prepends have all the buffer to insert data into */
      newb->b_wptr = newb->b_datap->db_lim;
      newb->b_rptr = newb->b_datap->db_lim;

      /* insert newb before tmp */
      newb -> b_cont = tmp;
      mBuf->b_cont = newb;

      /* if endptr of mBuf is NULLP, set it to newb */
      if (tmp == NULLP)
         minfo->endptr = newb;
      tmp = newb;
   }
   /* insert data, increment length */
   *--tmp->b_rptr = data;
   minfo->len++;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SAddPstMsg
*
*       Desc:  This function copies one byte of data to the
*              end of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*
*              if message is not empty: data is placed in back of all
*              other data in message. message length is incremented.
*              return is ok.
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SAddPstMsg
(
Data data,
Buffer *mBuf
)
#else
PUBLIC S16 SAddPstMsg (data, mBuf)
Data data;
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
   Buffer *newb;
 
   TRC1(SAddPstMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS292, ERRZERO, "SAddPstMsg: Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS293, ERRZERO, "SAddPstMsg: Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the message info */
   minfo = (SsMsgInfo *) mBuf->b_rptr;
 
   if (!(tmp = minfo->endptr) || (tmp->b_datap->db_ref > 1) ||
        (tmp->b_wptr == tmp->b_datap->db_lim))
   {
      if (SGetDBuf(minfo->region, minfo->pool, &newb) != ROK)
      {
         SSLOGERROR(ERRCLS_DEBUG, ESS294, ERRZERO, "SAddPstMsg: Failed in\
                                                    SGetDBuf()");
         RETVALUE(ROUTRES);
      }

      /* append newb to the end of the mBuf chain */
      if (tmp)
         tmp->b_cont = newb;
      else
         mBuf->b_cont = newb;

      /* set the endptr of mBuf to newb */
      minfo->endptr = newb;

      tmp = newb;
   }
   /* insert data, increment length */
   *tmp->b_wptr++ = data;
   minfo->len++;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SAddPreMsgMult
*
*       Desc:  This function copies consecutive bytes of data to the
*              beginning of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*
*              if message is not empty: data is read by source pointer,
*              data is placed in front of all other data in message.
*              message length is incremented. return is ok.
*
*              the first byte of data pointed to by the source pointer will
*              be placed at the front of the message first, the last byte of
*              data pointed to by the source pointer will be placed at the
*              front of the message last (i.e. it will become the first
*              byte of the message).
*
*       File:  ss_msg.c
*
*/
 
#ifdef ANSI
PUBLIC S16 SAddPreMsgMult
(
Data *src,
MsgLen cnt,
Buffer *mBuf
)
#else
PUBLIC S16 SAddPreMsgMult(src, cnt, mBuf)
Data *src;
MsgLen cnt;
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;   /* Message info */
   Buffer *tmp;
   Buffer *curblk;
   Buffer *newblk;
   Buffer *prevblk;
   MsgLen numBytes;  /* no. of bytes to be copied */
   MsgLen len;
   MsgLen offset;
   Data *rptr;

   TRC1(SAddPreMsgMult)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS295, ERRZERO, "SAddPreMsgMult:Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check source */
   if (src == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS296, ERRZERO, "SAddPreMsgMult:Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check count */
   if (cnt <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS297, ERRZERO, "SAddPreMsgMult: Invalid\
                                                   count");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS298, ERRZERO, "SAddPreMsgMult: Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the SsMsgInfo of mBuf */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   /* store cnt in length */
   len = cnt;
#if 1  /* ss014.13: Addition */
   offset = 0;
#endif /* ss014.13: Addition */

   if ((tmp = mBuf->b_cont) && (tmp->b_datap->db_ref == 1) &&
       (tmp->b_datap->db_base < tmp->b_rptr))
   {
      /* store the offset of the read pointer of tmp */
      offset = tmp->b_rptr - tmp->b_datap->db_base;

      /* determine the number of bytes to copy */
      numBytes = MIN(cnt, offset);

      /* decrement cnt */
      cnt -= numBytes;

      /* copy data */
      while (numBytes--)
         *--tmp->b_rptr = *src++;
      if (!cnt)
      {
         minfo->len += len;
         RETVALUE(ROK);
      }
   }
   newblk = prevblk = NULLP;
   while (cnt)
   {
      /* allocate a message blk */
      if (SGetDBuf(minfo->region, minfo->pool, &curblk) != ROK)
      {
         while ((curblk = prevblk))
         {
            prevblk = prevblk->b_cont;
            (Void) SPutDBuf(minfo->region, minfo->pool, curblk);
         }

         if (tmp)
         {
            tmp->b_rptr = tmp->b_datap->db_base + offset;
         }

         RETVALUE(ROUTRES);
      }
      /* attach curblk in the newblk chain */
      if (prevblk)
         curblk->b_cont = prevblk; /* stack them up */
      else
         newblk = curblk;
      prevblk = curblk;

      /* set the read and write pointers to the end of the data buffer */
      /* subsequent prepends have all the buffer to insert data into */
      curblk->b_wptr = curblk->b_datap->db_lim;
      rptr = curblk->b_datap->db_lim;

      /* copy data */
      numBytes = MIN(cnt, (rptr - curblk->b_datap->db_base));

      /* decrement cnt */
      cnt -= numBytes;

      while (numBytes--)
         *--rptr = *src++;
      curblk->b_rptr = rptr;
   }

   /* attach the newblk chain into mBuf */
   newblk -> b_cont = tmp;
   mBuf -> b_cont = curblk;

   /* update endptr of mBuf */
   if (!tmp)
      minfo -> endptr = newblk;

   /* update length of message */
   minfo->len += len;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SAddPstMsgMult
*
*       Desc:  This function copies consecutive bytes of data to the
*              end of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: data is placed in the message. message
*              length is incremented. return is ok.
*
*              if message is not empty: data is read by source pointer,
*              data is placed in back of all other data in message.
*              message length is incremented. return is ok.
*
*              the first byte of data pointed to by the source pointer will
*              be placed at the back of the message first, the last byte of
*              data pointed to by the source pointer will be placed at the
*              back of the message last (i.e. it will become the last
*              byte of the message).
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SAddPstMsgMult
(
Data *src,
MsgLen cnt,
Buffer *mBuf
)
#else
PUBLIC S16 SAddPstMsgMult(src, cnt, mBuf)
Data *src;
MsgLen cnt;
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
   Buffer *newblk;
   Buffer *curblk;
   Buffer *prevblk;
   MsgLen len;
   MsgLen offset;
   MsgLen numBytes;
   Data *wptr;

   TRC1(SAddPstMsgMult)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS299, ERRZERO, "SAddPstMsgMult:Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check source */
   if (src == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS300, ERRZERO, "SAddPstMsgMult:Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check count */
   if (cnt <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS301, ERRZERO, "SAddPstMsgMult:Invalid\
                                                   count");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS302, ERRZERO, "SAddPstMsgMult: Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif
 
   /* get the SsMsgInfo of mBuf */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   /* store cnt in len */
   len = cnt;

#if 1  /* ss014.13: Addition */
   offset = 0;
#endif /* ss014.13: Addition */

   if ((tmp = minfo->endptr) && (tmp->b_datap->db_ref == 1) &&
       (tmp->b_datap->db_lim > tmp->b_wptr))
   {
      /* store offset of the write pointer */
      /* incase subsequent allocations fail, offset is read reset to original */
      offset = tmp->b_datap->db_lim - tmp->b_wptr;

      /* determine the number of bytes to copy */
      numBytes = MIN(cnt, offset);

      /* decrement cnt */
      cnt -= numBytes;
#if 0 /* ss002.13: deletion */
      while (numBytes--)
         *tmp->b_wptr++ = *src++;
#endif /* ss002.13: deletion */


#if 1 /* ss002.13: addition */

#if 0 /* ss003.13: deletion */
      SMemCpy((VOID *) tmp->b_wptr, (VOID *) src, (size_t) numBytes);
#endif /* ss003.13: deletion */
#if 1 /* ss003.13: addition */
      SMemCpy((Void *) tmp->b_wptr, (Void *) src, (size_t) numBytes);
#endif /* ss003.13: addition */
      tmp->b_wptr += numBytes;
      src += numBytes;
#endif /* ss002.13: addition */

      if (!cnt)
      {
         minfo->len += len;
         RETVALUE(ROK);
      }
   }

   newblk = prevblk = NULLP;

   while (cnt)
   {
      /* allocate a message blk */
      if (SGetDBuf(minfo->region, minfo->pool, &curblk) != ROK)
      {
         while ((curblk = newblk))
         {
            newblk = newblk->b_cont;
            (Void) SPutDBuf(minfo->region, minfo->pool, curblk);
         }

         if (tmp)
         {
            tmp->b_wptr = tmp->b_datap->db_lim - offset;
         }

         RETVALUE(ROUTRES);
      }

      /* insert curblk in the newblk chain */
      if (prevblk)
         prevblk->b_cont = curblk; /* stack them down */
      else
         newblk = curblk;
      prevblk = curblk;

      /* copy data */
      wptr = curblk->b_wptr;
      numBytes = MIN(cnt, curblk->b_datap->db_lim - wptr);

      /* decrement cnt */
      cnt -= numBytes;

#if 0 /* ss002.13: deletion */
      while (numBytes--)
         *wptr++ = *src++;
      curblk->b_wptr = wptr;
#endif /* ss002.13: deletion */

#if 1 /* ss002.13: addition */
#if 0 /* ss003.13: deletion */
      SMemCpy( (VOID *) wptr, (VOID *) src, (size_t) numBytes);
#endif /* ss003.13: deletion */
#if 1 /* ss003.13: addition */
      SMemCpy( (Void *) wptr, (Void *) src, (size_t) numBytes);
#endif /* ss003.13: addition */
      src = src + numBytes;

      curblk->b_wptr +=  numBytes;  
#endif /* ss002.13: addition */
 }
   /* insert newblk chain into mBuf */
   if (tmp)
      tmp->b_cont = newblk;
   else
      mBuf->b_cont = newblk;
   minfo->endptr = curblk;

   /* update length */
   minfo->len += len;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SRemPreMsg
*
*       Desc:  This function copies and then removes one byte of
*              data from the beginning of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*
*              if message is not empty: data is removed from front of
*              message, data is returned via pointer to data. message
*              length is decremented. return is ok.
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SRemPreMsg
(
Data *dataPtr,
Buffer *mBuf
)
#else
PUBLIC S16 SRemPreMsg(dataPtr, mBuf)
Data *dataPtr;
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;

   TRC1(SRemPreMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!dataPtr)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS303, ERRZERO, "SRemPreMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS304, ERRZERO, "SRemPreMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS305, ERRZERO, "SRemPreMsg : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   if (!(tmp = mBuf->b_cont))
      RETVALUE(ROKDNA);

   /* get SsMsgInfo of mBuf */
   minfo = (SsMsgInfo *) mBuf->b_rptr;

   /* read databyte into dataPtr and incrment read ptr */
   *dataPtr = *tmp->b_rptr++;

   /* if all data is exhausted, release the blk */
   if (tmp->b_rptr == tmp->b_wptr)
   {
      mBuf->b_cont = tmp->b_cont;
      (Void) SPutDBuf(minfo->region, minfo->pool, tmp);
   }
   /* update SsMsgInfo */
   if (!--minfo->len)
      minfo->endptr = NULLP;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SRemPstMsg
*
*       Desc:  This function copies and then removes one byte of
*              data from the end of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*
*              if message is not empty: data is removed from back of
*              message, data is returned via pointer to data. message
*              length is decremented. return is ok.
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SRemPstMsg
(
Data *dataPtr,              /* pointer to data */
Buffer *mBuf
)
#else
PUBLIC S16 SRemPstMsg(dataPtr, mBuf)
Data *dataPtr;              /* pointer to data */
Buffer *mBuf;               /* message buffer */
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
   Buffer *last;

   TRC1(SRemPstMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (dataPtr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS306, ERRZERO, "SRemPstMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS307, ERRZERO, "SRemPstMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS308, ERRZERO, "SRemPstMsg : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the SsMsgInfo */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   if (!(last = minfo->endptr))
      RETVALUE(ROKDNA);

   /* read databyte into dataPtr and decrement write ptr */
   *dataPtr = *--last->b_wptr;

   /* if all data is exhausted, release the blk */
   if (last->b_rptr == last->b_wptr)
   {
      for (tmp = mBuf; tmp->b_cont != last;)
         tmp = tmp->b_cont;
      tmp->b_cont = NULLP;
      (Void) SPutDBuf(minfo->region, minfo->pool, last);

      /* update endptr */
      if (mBuf->b_cont)
         minfo->endptr = tmp;
      else
         minfo->endptr = NULLP;
   }
   /* update SsMsgInfo */
   minfo->len--;

   RETVALUE(ROK);
}


/*
*
*       Fun:   SRemPreMsgMult
*
*       Desc:  This function copies and then removes consecutive bytes of
*              data from the beginning of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*
*              if the destination buffer is NULL, data is not copied.
*
*              if message is not empty: data is removed from front of
*              message, data is returned by destination pointer. message
*              length is decremented. return is ok.
*
*              the first byte of data read from the message will be placed
*              in the destination buffer first (i.e. this was the first byte
*              of the message), the last byte of data read from the message
*              will be placed in the destination buffer last.
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SRemPreMsgMult
(
Data *dst,                  /* destination */
MsgLen cnt,                 /* count */
Buffer *mBuf
)
#else
PUBLIC S16 SRemPreMsgMult(dst, cnt, mBuf)
Data *dst;                  /* destination */
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
   MsgLen numBytes;

   TRC1(SRemPreMsgMult)

   /* ss023.103 - Modification of SRemPreMsgMult for bug fix */

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check count */
   if (cnt <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS309, ERRZERO, "SRemPreMsgMult:Invalid\
                                                   count");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS310, ERRZERO, "SRemPreMsgMult:Null Buffer");
      RETVALUE(RFAILED);
   }
   /* ss021.103 - Addition to check for NULL pointer */
   /* check data pointer */
   /* ss022.103 - Removed check for NULL pointer */
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS311, ERRZERO, "SRemPreMsgMult : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the SsMsgInfo */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   /* check if data present */
   if (minfo->len < cnt)
      RETVALUE(ROKDNA);
   else
      minfo->len -= cnt;

   while (cnt)
   {
      /* get the first SS_M_DATA blk */
      tmp = mBuf->b_cont;

      /* determine the number of bytes to be copy */
      numBytes = MIN(cnt, tmp->b_wptr - tmp->b_rptr);

      /* decrement cnt */
      cnt -= numBytes;

      /* move data into dst */
      if (dst != NULLP)
      {

        SMemCpy( (Void *) dst, (Void *) tmp->b_rptr,  (size_t) numBytes);
        dst += numBytes;
      }
      
      tmp->b_rptr += numBytes;

      if (tmp->b_rptr == tmp->b_wptr)
      {
         mBuf->b_cont = tmp->b_cont;
        (Void) SPutDBuf(minfo->region, minfo->pool, tmp);
      }
   }
   /* update SsMsgInfo */
   if (!minfo->len)
      minfo->endptr = NULLP;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SRemPstMsgMult
*
*       Desc:  This function copies and then removes consecutive bytes of
*              data from the end of a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: if message is empty: message is unchanged. return is ok,
*              data not available.
*
*              if the destination buffer is NULL, data is not copied.
*
*              if message is not empty: data is removed from front of
*              message, data is returned by destination pointer. message
*              length is decremented. return is ok.
*
*              the first byte of data read from the message will be placed
*              in the destination buffer first (i.e. this was the last byte
*              of the message), the last byte of data read from the message
*              will be placed in the destination buffer last.
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SRemPstMsgMult
(
Data *dst,                  /* destination */
MsgLen cnt,                 /* count */
Buffer *mBuf
)
#else
PUBLIC S16 SRemPstMsgMult(dst, cnt, mBuf)
Data *dst;                  /* destination */
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
   Buffer *prev;
   MsgLen count;
   MsgLen numBytes;
   Data *cptr;

   TRC1(SRemPstMsgMult)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check count */
   if (cnt <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS312, ERRZERO, "SRemPstMsgMult:Invalid\
                                                   count");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS313, ERRZERO, "SRemPstMsgMult:Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS314, ERRZERO, "SRemPstMsgMult : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
   /* ss021.103 - Addition to check dst data pointer */
   /* check data pointer */
   /* ss022.103 - Removed check for NULL destination pointer */
#endif
 
   /* get the SsMsgInfo */
   minfo = (SsMsgInfo*) mBuf->b_rptr;
 
   /* check if data present */
   if (minfo->len < cnt)
      RETVALUE(ROKDNA);
   else
   {
      minfo->len -= cnt;
      count = minfo->len;
      prev = mBuf;
      tmp = mBuf->b_cont;
   }

   /* determine blk containing offset, and prev node */
   FIND_OFFSET_AND_PREV(prev, tmp, count)

   if (dst != NULLP)
      dst += cnt;

   while (cnt)
   {
      numBytes = MIN(cnt, (tmp->b_wptr - tmp->b_rptr - count));

      tmp->b_wptr -= numBytes;

      cnt -= numBytes;

      /* copy data */
      cptr = tmp->b_wptr;
      if (dst != NULLP)
      {
         while (numBytes--)
            *--dst = *cptr++;
      }

      if (tmp->b_rptr == tmp->b_wptr)
      {
         prev->b_cont = tmp->b_cont;
         (Void) SPutDBuf(minfo->region, minfo->pool, tmp);
         tmp = prev;
      }
      prev = tmp;
      tmp = tmp->b_cont;

      count = 0;
   }
   if (mBuf == prev)
      minfo->endptr = NULLP;
   else
      minfo->endptr = prev;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SExamMsg
*
*       Desc:  This function copies one byte of data from a message
*              without modifying the message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: index is 0 based and indicates location in message
*
*              if index is less than the length of the message:
*              message is unchanged and data is examined at specified
*              index and returned via pointer to data. message length
*              is unchanged. return is ok.
*
*              if index is greater than or equal to
*              the length of the message: message is unchanged and 0
*              is returned via pointer to data. return is ok, data
*              not available.
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SExamMsg
(
Data *dataPtr,              /* pointer to data */
Buffer *mBuf,               /* message buffer */
MsgLen idx
)
#else
PUBLIC S16 SExamMsg(dataPtr, mBuf, idx)
Data *dataPtr;              /* pointer to data */
Buffer *mBuf;               /* message buffer */
MsgLen idx;                 /* index */
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;

   TRC1(SExamMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check data pointer */
   if (!dataPtr)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS315, ERRZERO, "SExamMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message buffer */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS316, ERRZERO, "SExamMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check index */
   if (idx < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS317, ERRZERO, "SExamMsg : Invalid Index");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS318, ERRZERO, "SExamMsg : Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
#endif
 
   /* get the SsMsgInfo */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   if (minfo->len <= idx)
   {
      RETVALUE(ROKDNA);
   }

   /* get the first SS_M_DATA blk */
   tmp = mBuf->b_cont;

   /* determine offset */
   FIND_OFFSET(tmp, idx)

   *dataPtr = *(tmp->b_rptr + idx);

   RETVALUE(ROK);
}

/*
*
*       Fun:   SFndLenMsg
*
*       Desc:  This function determines the length of data within
*              a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: length of message is determined, message is unchanged
*              and length is returned via pointer to length. return is ok.
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SFndLenMsg
(
REG1 Buffer *mBuf,          /* message buffer */
MsgLen *lngPtr
)
#else
PUBLIC S16 SFndLenMsg(mBuf, lngPtr)
REG1 Buffer *mBuf;          /* message buffer */
MsgLen *lngPtr;             /* pointer to length */
#endif
{
   SsMsgInfo *minfo;

   TRC1(SFndLenMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS319, ERRZERO, "SFndLenMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check length pointer */
   if (lngPtr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS320, ERRZERO, "SFndLenMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS321, ERRZERO, "SFndLenMsg : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif
 
   /* get the SsMsgInfo */
   minfo = (SsMsgInfo*) mBuf->b_rptr;

   /* read length */
   *lngPtr = minfo->len;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SSegMsg
*
*       Desc:  This function will segment one specified message into two
*              messages.
*
*       Ret:   ROK     - ok
*              ROKDNA  - ok, data not available
*              RFAILED - failed, general (optional)
*              ROUTRES - failed, out of resources (optional)
*
*       Notes: message 1 is the original message.
*
*              message 2 is the new message.
*
*              index is 0 based and indicates location in message 1
*              from which message 2 will be created.
*
*              if index is equal to 0: message 2 is created and all data
*              attached to message 1 is moved to message 2. message 1
*              is not returned to memory. return is ok.
*
*              if index is not equal to 0 and less than the length of
*              the message minus 1: message 2 is created, all data
*              attached to message 1 from index (inclusive) is moved to
*              message 2. message 1 contains data from index 0 to index
*              minus 1. return is ok.
*
*              if index is not equal to 0 and greater than or equal to
*              the length of the message minus 1: message 1 is unchanged.
*              message 2 is set to null. return is ok, data not available.
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SSegMsg
(
Buffer *mBuf1,              /* message 1 */
MsgLen idx,                 /* index */
Buffer **mBuf2
)
#else
PUBLIC S16 SSegMsg(mBuf1, idx, mBuf2)
Buffer *mBuf1;              /* message 1 */
MsgLen idx;                 /* index */
Buffer **mBuf2;             /* message 2 */
#endif
{
   SsMsgInfo *minfo1;
   SsMsgInfo *minfo2;
   Buffer *tmp;
   Buffer *prev;
   Buffer *next;

   TRC1(SSegMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer 1 */
   if (mBuf1 == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS322, ERRZERO, "SSegMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message buffer 2 */
   if (mBuf2 == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS323, ERRZERO, "SSegMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (idx < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS324, ERRZERO, "SSegMsg : Invalid index");
      RETVALUE(RFAILED);
   }
   if (mBuf1->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS325, ERRZERO, "SSegMsg : Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the SsMsgInfo of mBuf1 */
   minfo1 = (SsMsgInfo*) mBuf1->b_rptr;

   /* if index > length of mBuf, return */
   if (idx >= minfo1->len)
   {
      *mBuf2 = NULLP;
      RETVALUE(ROKDNA);
   }
   /* allocate message buffer */
   if (SGetMsg(minfo1->region, minfo1->pool, mBuf2) != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS326, ERRZERO, "SSegMsg : SGetMsg failed");
      RETVALUE(RFAILED);
   }

   /* get the SsMsgInfo of mBuf2 */
   minfo2 = (SsMsgInfo*) (*mBuf2)->b_rptr;

   /* adjust the lengths of mBuf1, mBuf2 */
   minfo2->len = minfo1->len - idx;
   minfo1->len = idx;

   /* set the endptr of mBuf2 to mBuf1 */
   minfo2->endptr = minfo1->endptr;

   /* if index is zero ... */
   if (!idx)
   {
      (*mBuf2)->b_cont = mBuf1->b_cont;

      /* set the endptr and b_cont of mBuf1 to NULLP */
      minfo1->endptr = NULLP;
      mBuf1->b_cont = NULLP;

      RETVALUE(ROK);
   }

   /* get the first SS_M_DATA blk */
   tmp = mBuf1->b_cont;
   prev = mBuf1;

   FIND_OFFSET_AND_PREV(prev, tmp, idx)

   /* segmented at the start of a blk */
   if (!idx)
   {
      (*mBuf2)->b_cont = tmp;
      prev->b_cont = NULLP;
      minfo1->endptr = prev;
   }
   else
   {
#ifndef SSI_MEM_CHNG
      /* allocate a message blk without a data blk */
      /* ssDupB internally increments the reference count */
#if 0 /* ss012.13: Deletion */
      if (!(next = ssDupB(tmp)))
#else
#ifdef SS_M_PROTO_REGION
      if (!(next = DupMsg(minfo1->region, tmp)))
#else
      if (!(next = ssDupB(tmp)))
#endif /* SS_M_PROTO_REGION */
#endif /* ss012.13: Addition */
      {
         /* reset length */
         minfo1->len += minfo2->len;
         (Void) SPutMsg(*mBuf2);
         RETVALUE(ROUTRES);
      }

      (*mBuf2)->b_cont = next;

      tmp->b_cont = NULLP;

      tmp->b_wptr = tmp->b_rptr + idx;
      next->b_rptr = tmp->b_wptr;

#if 0 /* ss001.13: change - old code */
      minfo1->endptr = tmp;
#else /* ss001.13: change - new code */
      /* If the index was in the last mblk of the message, the
       *  end pointer of the new message needs to be set to the
       *  dup'ped mblk. Otherwise, the end pointer of the first
       *  message will be set to the mblk in which the index
       *  was found, and the end pointer of the new message can
       *  remain where it is.
       */
      if (minfo1->endptr == tmp)
      {
         minfo2->endptr = next;
      }
      else
      {
         minfo1->endptr = tmp;
      }
#endif /* ss001.13: change */
#else /*SSI_MEM_CHNG*/
      if (!(next = DupMsg(minfo1->region, tmp)))
      {
         /* reset length */
         minfo1->len += minfo2->len;
         (Void) SPutMsg(*mBuf2);
         RETVALUE(ROUTRES);
      }
      (*mBuf2)->b_cont = next;
      tmp->b_wptr = tmp->b_rptr + idx;
      next->b_rptr += idx;
      prev = tmp;
      tmp = tmp->b_cont;
      /* copy rest of the blocks */
      if(tmp)
      {
         next->b_cont = tmp;
         prev->b_cont = NULLP;
         minfo2->endptr = minfo1->endptr; /* srinivas - 2nd June */
         minfo1->endptr = prev;
      }
      else
      {
         next->b_cont = NULLP;
         minfo2->endptr = next;
#if 0 
         /* for sanity checking - need to delete later */
         if(minfo1->endptr != prev)
         {
             printf("!!!!! SSegMsg() mBuf1 endPtr != tmp !!!!!\n");
         }
#endif
      }

#endif /*SSI_MEM_CHNG*/
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   SCpyFixMsg
*
*       Desc:  This function copies data from a fixed buffer to a
*              message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SCpyFixMsg
(
Data *srcBuf,               /* source buffer */
Buffer *dstMbuf,            /* destination message buffer */
MsgLen dstIdx,              /* destination index */
MsgLen cnt,                 /* count */
MsgLen *cCnt
)
#else
PUBLIC S16 SCpyFixMsg(srcBuf, dstMbuf, dstIdx, cnt, cCnt)
Data *srcBuf;               /* source buffer */
Buffer *dstMbuf;            /* destination message buffer */
MsgLen dstIdx;              /* destination index */
MsgLen cnt;                 /* count */
MsgLen *cCnt;               /* copied count */
#endif
{
   S16 ret;
   SsMsgInfo *minfo;
   Buffer *right;

   TRC1(SCpyFixMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check source message buffer */
   if (srcBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS327, ERRZERO, "SCpyFixMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check destination message buffer */
   if (dstMbuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS328, ERRZERO, "SCpyFixMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check copied count buffer */
   if (cCnt == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS329, ERRZERO, "SCpyFixMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check copy count */
   if (cnt <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS330, ERRZERO, "SCpyFixMsg : Invalid count");
      RETVALUE(RFAILED);
   }
   if (dstMbuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS331, ERRZERO, "SCpyFixMsg : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   minfo = (SsMsgInfo*) dstMbuf->b_rptr;

   if (minfo->len < dstIdx)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS332, ERRZERO, "SCpyFixMsg : Invalid Index");
#endif
      RETVALUE(RFAILED);
   }

/* ss021.103 - Addition test if message length will exceed max msg length */
#if (ERRCLASS & ERRCLS_INT_PAR)
#ifdef LONG_MSG
   if (minfo->len > 0x7FFFFFFF - cnt)
#else
   if (minfo->len > 0x7FFF - cnt)
#endif
   {
      *cCnt = 0;

      SSLOGERROR(ERRCLS_INT_PAR, ESS333, ERRZERO, "SCpyFixMsg : msgLen + cnt > maxS16");
      RETVALUE(ROUTRES);
   }
#endif
   
   /* add data at the start of dst buffer */
   if (!dstIdx)
   {
      if ((ret = SAddPreMsgMult(srcBuf, cnt, dstMbuf)) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS334, ERRZERO, "SCpyFixMsg : Failed in\
                                                    SAddPreMsgMult");
#endif
         RETVALUE(ret);
      }
      *cCnt = cnt;

      RETVALUE(ROK);
   }

   /* add data at the end of the dst buffer */
   if (minfo->len == dstIdx)
   {
      if ((ret = SAddPstMsgMult(srcBuf, cnt, dstMbuf)) != ROK)
      {
         RETVALUE(ret);
      }
      *cCnt = cnt;

      RETVALUE(ROK);
   }

   /* segment the message into dstMbuf and right */
   if ((ret = SSegMsg(dstMbuf, dstIdx, &right)) != ROK)
   {
      RETVALUE(ret);
   }

   /* append data at the end of dstMbuf */
   if ((ret = SAddPstMsgMult(srcBuf, cnt, dstMbuf)) != ROK)
   {
      /* ss020.103 - Addition for cleanup */
      (Void) SPutMsg(right);
      RETVALUE(ret);
   }

   /* cancatenate dstMbuf and right */
   if ((ret = SCatMsg(dstMbuf, right, M1M2)) != ROK)
   {
      /* ss020.103 - Addition for cleanup */
      (Void) SPutMsg(right);
      RETVALUE(ret);
   }

   *cCnt = cnt;

   (Void) SPutMsg(right);

   RETVALUE(ROK);
}

/*
*
*       Fun:   SCpyMsgFix
*
*       Desc:  This function copies data from a message
*              into a fixed buffer.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SCpyMsgFix
(
Buffer *srcMbuf,            /* source message buffer */
MsgLen srcIdx,              /* source index */
MsgLen cnt,                 /* count */
Data *dstBuf,               /* destination buffer */
MsgLen *cCnt
)
#else
PUBLIC S16 SCpyMsgFix(srcMbuf, srcIdx, cnt, dstBuf, cCnt)
Buffer *srcMbuf;            /* source message buffer */
MsgLen srcIdx;              /* source index */
MsgLen cnt;                 /* count */
Data *dstBuf;               /* destination buffer */
MsgLen *cCnt;               /* copied count */
#endif
{
   Data *cptr;
   Buffer *tmp;
   SsMsgInfo *minfo;
   MsgLen numBytes;

   TRC1(SCpyMsgFix)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check source message buffer */
   if (srcMbuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS335, ERRZERO, "SCpyMsgFix : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check destination message buffer */
   if (dstBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS336, ERRZERO, "SCpyMsgFix : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (cnt <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS337, ERRZERO, "SCpyMsgFix : Invalid Index");
      RETVALUE(RFAILED);
   }
 
   if (srcIdx < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS338, ERRZERO, "SCpyMsgFix : Invalid Index");
      RETVALUE(RFAILED);
   }
   if (!cCnt)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS339, ERRZERO, "SCpyMsgFix : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (srcMbuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS340, ERRZERO, "SCpyMsgFix : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* get SsMsgInfo */
   minfo = (SsMsgInfo*) srcMbuf->b_rptr;

   if ((srcIdx + cnt) > minfo->len)
   {
      *cCnt = 0;
      RETVALUE(ROKDNA);
   }

   /* get the first SS_M_DATA blk */
   tmp = srcMbuf->b_cont;

   /* get to the srcIdx-th offset */
   FIND_OFFSET(tmp, srcIdx)

   *cCnt = cnt;

   /* set cptr to the read ptr of tmp + offset */
   cptr = tmp->b_rptr + srcIdx;

   while (cnt)
   {
      /* determine the number of bytes to be copied */
      numBytes = MIN(cnt, (tmp->b_wptr - cptr));

      /* decrement cnt */
      cnt -= numBytes;

      /* copy data */
#if 0  /* ss002.13 deletion */
      while (numBytes--)
         *dstBuf++ = *cptr++;
#endif /* ss002.13 deletion */

#if 1  /* ss002.13 addition */
#if 0  /* ss003.13 deletion */
      SMemCpy((VOID *) dstBuf, (VOID *) cptr, (size_t) numBytes);
#endif /* ss003.13 deletion */
#if 1  /* ss003.13 addition */
      SMemCpy((Void *) dstBuf, (Void *) cptr, (size_t) numBytes);
#endif /* ss003.13 addition */
      cptr += numBytes;
      dstBuf += numBytes;
#endif /* ss002.13 addition */


      /* get the next blk */
      if ((tmp = tmp->b_cont))
         /* set cptr to the read ptr of tmp */
         cptr = tmp->b_rptr;
      else
         break;
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   SCpyMsgMsg
*
*       Desc:  This function is used to copy a message into
*              a new region and or pool of memory.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SCpyMsgMsg
(
Buffer *srcBuf,
Region dstRegion,
Pool dstPool,
Buffer **dstBuf
)
#else
PUBLIC S16 SCpyMsgMsg(srcBuf, dstRegion, dstPool, dstBuf)
Buffer *srcBuf;
Region dstRegion;
Pool dstPool;
Buffer **dstBuf;
#endif
{
   SsMsgInfo *minfo1;
   SsMsgInfo *minfo2;
   Buffer *tmp;
   Buffer *dBuf;
   Buffer *curblk;
   Buffer *newblk;
   Buffer *prevblk;
   Data *cptr;
   MsgLen numBytes;
 
   /* ss021.103 - Addition of return value */
#ifndef SS_PERF
#if (ERRCLASS & ERRCLS_INT_PAR)
   S16 ret;
#endif
#endif
 
   TRC1(SCpyMsgMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!srcBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS341, ERRZERO, "SCpyMsgMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (srcBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS342, ERRZERO, "SCpyMsgMsg : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
   /* ss021.103 - Addition to validate region and pool */
   if (dstRegion >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS343, ERRZERO, 
                 "SCpyMsgMsg : Invalid region id");
      RETVALUE(RFAILED);
   }
 
   if (dstPool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS344, ERRZERO, 
                 "SCpyMsgMsg : Invalid pool id");
      RETVALUE(RFAILED);
   }
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* ss021.103 - Addition to check if region is valid */
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS345, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }
#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is present */
   if (osCp.regionTbl[dstRegion].used == FALSE)
   {
#ifndef SS_PERF
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS346, ERRZERO,
                  "Could not release semaphore");
         RETVALUE(RFAILED);
#endif
      }
#endif
      SSLOGERROR(ERRCLS_INT_PAR, ESS347, dstRegion, "Region not registered");
      RETVALUE(RFAILED);
   }
#endif
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS348, ERRZERO,
                  "Could not release semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif
#endif

   /* allocate a message buffer */
   if (SGetMsg(dstRegion, dstPool, dstBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS349, ERRZERO, "SCpyMsgMsg : SGetMsg failed");
#endif
      RETVALUE(RFAILED);
   }
   /* get the SsMsgInfo from srcBuf */
   minfo1 = (SsMsgInfo*) srcBuf->b_rptr;

   /* get the SsMsgInfo from srcBuf */
   minfo2 = (SsMsgInfo*) (*dstBuf)->b_rptr;

   /* get the first SS_M_DATA blk of srcBuf */
   tmp = srcBuf->b_cont;

   /* if srcBuf and dstBuf belong to the same region, increment the reference
    * count
    */
   if (dstRegion == minfo1->region)
   {
      newblk = NULLP;
      curblk = NULLP;
      prevblk = NULLP;

      while (tmp)
      {
#if 0 /* ss012.13: Deletion */
         if ((curblk = ssDupB(tmp)) == NULLP)
#else /* ss012.13: Deletion */
#ifdef SS_M_PROTO_REGION 
         if ((curblk = DupMsg(dstRegion,tmp)) == NULLP)
#else
         if ((curblk = ssDupB(tmp)) == NULLP)
#endif /* SS_M_PROTO_REGION */
#endif /* ss012.13: Addition */
         {
            while (newblk)
            {
               curblk = newblk->b_cont;
               (Void) SPutDBuf(minfo1->region, minfo1->pool, newblk);
               newblk = curblk;
            }
            (Void) SPutMsg(*dstBuf);
            RETVALUE(ROUTRES);
         }

         if (!prevblk)
            newblk = curblk;
         else
            prevblk->b_cont = curblk;
         prevblk = curblk;

         tmp = tmp->b_cont;
      }
      if (curblk)
         curblk->b_cont = NULLP;

      minfo2->len = minfo1->len;
      minfo2->endptr = curblk;
      (*dstBuf)->b_cont = newblk;

      RETVALUE(ROK);
   }

   /* allocate a data buffer */
   if (ssGetDBufOfSize(dstRegion, minfo1->len, &dBuf) != ROK)
   {
#if 1 /* ss016.13: addition */
      (Void) SPutMsg(*dstBuf);
#endif /* ss016.13: addition */
      SSLOGERROR(ERRCLS_DEBUG, ESS350, ERRZERO, "SCpyMsgMsg : ssGetDBufOfSize\
                 failed");
      RETVALUE(ROUTRES);
   }
   dBuf->b_datap->db_type = SS_M_DATA;

   while (tmp)
   {
      numBytes = tmp->b_wptr - tmp->b_rptr;
      cptr = tmp->b_rptr;
#if 0   /* ss002.13: deletion */
      while (numBytes--)
         *dBuf->b_wptr++ = *cptr++;
#endif /* ss002.13: deletion */

#if 1  /* ss002.13: addition */
#if 0   /* ss003.13: deletion */
      SMemCpy( (VOID *) dBuf->b_wptr, (VOID *) cptr, (size_t) numBytes);
#endif /* ss003.13: deletion */
#if 1  /* ss003.13: addition */
      SMemCpy( (Void *) dBuf->b_wptr, (Void *) cptr, (size_t) numBytes);
#endif /* ss003.13: addition */
      dBuf->b_wptr += numBytes;
      cptr += numBytes;
#endif /* ss002.13: addition */

      tmp = tmp->b_cont;
   }
   minfo2->len = minfo1->len;
   /* set the endptr and b_cont of dstBuf to point to dBuf */
   minfo2->endptr = dBuf;
   (*dstBuf)->b_cont = dBuf;

   RETVALUE(ROK);
}



/*
*
*       Fun:   SAddMsgRef
*
*       Desc:  This function is used to copy a message into
*              a new region and or pool of memory.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SAddMsgRef
(
Buffer *srcBuf,
Region dstRegion,
Pool dstPool,
Buffer **dstBuf
)
#else
PUBLIC S16 SAddMsgRef(srcBuf, dstRegion, dstPool, dstBuf)
Buffer *srcBuf;
Region dstRegion;
Pool dstPool;
Buffer **dstBuf;
#endif
{
   SsMsgInfo *minfo1;
   SsMsgInfo *minfo2;
   Buffer *tmp;
   Buffer *dBuf;
   Buffer *curblk;
   Buffer *newblk;
   Buffer *prevblk;
   Data *cptr;
   MsgLen numBytes;

   TRC1(SAddMsgRef)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!srcBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS351, ERRZERO, "SAddMsgRef : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (srcBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS352, ERRZERO, "SAddMsgRef : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* allocate a message buffer */
   if (SGetMsg(dstRegion, dstPool, dstBuf) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS353, ERRZERO, "SAddMsgRef : SGetMsg failed");
#endif
      RETVALUE(RFAILED);
   }
   /* get the SsMsgInfo from srcBuf */
   minfo1 = (SsMsgInfo*) srcBuf->b_rptr;

   /* get the SsMsgInfo from srcBuf */
   minfo2 = (SsMsgInfo*) (*dstBuf)->b_rptr;

   /* get the first SS_M_DATA blk of srcBuf */
   tmp = srcBuf->b_cont;

   /* if srcBuf and dstBuf belong to the same region, increment the reference
    * count
    */
   if (dstRegion == minfo1->region)
   {
      newblk = NULLP;
      curblk = NULLP;
      prevblk = NULLP;

      while (tmp)
      {
#if 0 /* ss012.13: deletion */
         if ((curblk = ssDupB(tmp)) == NULLP)
#else /* ss012.13: deletion */
#ifdef SS_M_PROTO_REGION 
         if ((curblk = DupMsg(dstRegion, tmp)) == NULLP)
#else
         if ((curblk = ssDupB(tmp)) == NULLP)
#endif /* SS_M_PROTO_REGION */
#endif /* ss012.13: addition */
         {
            while (newblk)
            {
               curblk = newblk->b_cont;
               (Void) SPutDBuf(minfo1->region, minfo1->pool, newblk);
               newblk = curblk;
            }
            (Void) SPutMsg(*dstBuf);
            RETVALUE(ROUTRES);
         }

         if (!prevblk)
            newblk = curblk;
         else
            prevblk->b_cont = curblk;
         prevblk = curblk;

         tmp = tmp->b_cont;
      }
      if (curblk)
         curblk->b_cont = NULLP;

      minfo2->len = minfo1->len;
      minfo2->endptr = curblk;
      (*dstBuf)->b_cont = newblk;

      RETVALUE(ROK);
   }

   /* allocate a data buffer */
   if (ssGetDBufOfSize(dstRegion, minfo1->len, &dBuf) != ROK)
   {
#if 1 /* ss016.13: addition */
      (Void) SPutMsg(*dstBuf);
#endif /* ss016.13: addition */
      SSLOGERROR(ERRCLS_DEBUG, ESS354, ERRZERO, "SAddMsgRef : ssGetDBufOfSize\
                 failed");
      RETVALUE(ROUTRES);
   }
   dBuf->b_datap->db_type = SS_M_DATA;

   while (tmp)
   {
      numBytes = tmp->b_wptr - tmp->b_rptr;
      cptr = tmp->b_rptr;
      while (numBytes--)
         *dBuf->b_wptr++ = *cptr++;
      tmp = tmp->b_cont;
   }
   minfo2->len = minfo1->len;
   /* set the endptr and b_cont of dstBuf to point to dBuf */
   minfo2->endptr = dBuf;
   (*dstBuf)->b_cont = dBuf;

   RETVALUE(ROK);
}
#if 1 /* ss012.13: Addition */
#ifdef SS_M_PROTO_REGION 
/*
*
*       Fun:   DupMsg
*
*       Desc:  Duplicates the specified message block, copying it
*              into a newly-allocated message block. Increments
*              the reference count of the data block that is pointed
*              at by the original message block descriptor.
*
*       Ret:   non-NULL - ok
*              NULL     - failure
*
*       Notes:
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PRIVATE Buffer *DupMsg
(
Region region,              /* region id */
Buffer *mp                  /* message block */
)
#else
PRIVATE Buffer *DupMsg(region, mp)
Region region;              /* region id */
Buffer *mp;                 /* message block */
#endif
{
   Buffer *bp;                  /* mblk for iteration */
   S16 r;                       /* return value */
   Size m;                      /* temporary */
#ifdef SSI_MEM_CHNG
   MsgLen numBytes;
   Data  *data;
   Data  *cptr;
#endif

   TRC1(DupMsg);


#if (ERRCLASS & ERRCLS_INT_PAR)
   if (mp == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS355, ERRZERO, "Null pointer");
      RETVALUE(NULLP);
   }

  if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS356, ERRZERO, "DupMsg : Invalid region\
                                                   id");
      RETVALUE(NULLP);
   }
#endif


/* allocate a single block for the mblock and the dblock */
#ifndef SSI_MEM_CHNG
   m = (sizeof(SsMblk) + sizeof(SsDblk));
#else
   numBytes = mp->b_wptr - mp->b_rptr;
   m = MDBSIZE + numBytes;
#endif /* SSI_MEM_CHNG */
   r = SAlloc(region, &m, 0, (Data **)&bp);
   if (r != ROK)
   {
#if (ERRCLASS & ERRCLS_ADD_RES)
      SSLOGERROR(ERRCLS_ADD_RES, ESS357, (ErrVal) r, "SAlloc() failed");
#endif

     RETVALUE(NULLP);
   }
/* generic set-up-message function */
#ifndef SSI_MEM_CHNG
   SS_STRM_INITB(bp, (SsDblk *)(((U8 *)bp) + sizeof(SsMblk)), NULLP, 0, NULLP);
#else
   data = (Data *) (bp) + MDBSIZE;
   SS_STRM_INITB(bp,(SsDblk *)(((U8 *)bp) + sizeof(SsMblk)), data, numBytes, NULLP);
#endif /* SSI_MEM_CHNG */


   /*  make the new message block identical to the one to be dup'ed.
    *  notice that an mblk/dblk pair is allocated but only the mblk
    *  is used,, this is for optimum performance in the average case.
    */
#ifndef SSI_MEM_CHNG
   SMemCpy( (Void *)bp, (Void *)mp, (size_t)sizeof(SsMblk));

   /* increment the reference count of the dblock */
   mp->b_datap->db_ref++;
#else
   cptr =  mp->b_rptr;
   SMemCpy((Void*)bp->b_wptr, (Void*)cptr, numBytes);
   bp->b_wptr +=  numBytes;
#endif /* SSI_MEM_CHNG */

   RETVALUE(bp);
} /* DupMsg */
#endif /* SS_M_PROTO_REGION */
#endif /* ss012.13: Addition */

/*
*
*       Fun:   SGetDBuf
*
*       Desc:  This function allocates a buffer from the dynamic
*              memory pool indicated by the caller.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: The dynamic memory pools are used to create and
*              manipulate messages.
*
*              SGetDBuf is never called by a protocol layer.
*
*              SGetDBuf assumes that interrupts are already disabled.
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SGetDBuf
(
Region region,              /* region id */
Pool pool,                  /* pool id */
Buffer **bufPtr
)
#else
PUBLIC S16 SGetDBuf(region, pool, bufPtr)
Region region;              /* region id */
Pool pool;                  /* pool id */
Buffer **bufPtr;            /* pointer to buffer */
#endif
{
   Size size;
   Size mdsize;
   Data *data;
   SsDblk *dptr;
   SsRegionEntry *regp;
      /* ss021.103 - Addition of return value */
#ifndef SS_PERF
#if (ERRCLASS & ERRCLS_INT_PAR)
   S16 ret;
#endif
#endif
   
   TRC1(SGetDBuf)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (!bufPtr)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS358, ERRZERO, "SGetDBuf : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS359, ERRZERO, "SGetDBuf : Invalid region\
                                                   id");
      RETVALUE(RFAILED);
   }
 
   if (pool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS360, ERRZERO, "SGetDBuf : Invalid pool id");
      RETVALUE(RFAILED);
   }
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* ss021.103 - Addition to check if region is registered */
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS361, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }

#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is present */
   if (osCp.regionTbl[region].used == FALSE)
   {
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS362, ERRZERO,
                  "Could not release semaphore");
         RETVALUE(RFAILED);
#endif
      }
#endif
      SSLOGERROR(ERRCLS_INT_PAR, ESS363, region, "Region not registered");
      RETVALUE(RFAILED);
   }
#endif
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS364, ERRZERO,
                  "Could not release semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif
#endif

   regp = &osCp.regionTbl[region];

#if (ERRCLASS & ERRCLS_DEBUG)
   if (regp->poolTbl[pool].type != SS_POOL_DYNAMIC)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS365, ERRZERO,
                  "SGetDBuf : Invalid pool type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the size from region/pool */
   size = regp->poolTbl[pool].u.dpool.size;

   mdsize = MDBSIZE;

#if 0 /* ss012.13: Deletion */
   /* out board memory */
   if (regp->flags & SS_OUTBOARD_FLAG)
   {
      /* allocate memory for data buffer */
      if (SAlloc(region, &size, 0, &data) != ROK)
      {
         RETVALUE(ROUTRES);
      }
      if (SAlloc(SS_DFLT_REGION, &mdsize, 0, (Data **) bufPtr) != ROK)
      {
         SFree(region, (Data *) data, size);
         RETVALUE(ROUTRES);
      }
   }
   else
   {
      mdsize += size;
      if (SAlloc(region, &mdsize, 0, (Data **) bufPtr) != ROK)
      {
         RETVALUE(ROUTRES);
      }
      data = (Data *) (*bufPtr) + MDBSIZE;
      size = mdsize - MDBSIZE;
   }
#endif /* ss012.13: Deletion */
#if 1 /* ss012.13: Addition */
#ifndef SS_M_PROTO_REGION 
   /* out board memory */
   if (regp->flags & SS_OUTBOARD_FLAG)
   {
      /* allocate memory for data buffer */
      if (SAlloc(region, &size, 0, &data) != ROK)
      {
         RETVALUE(ROUTRES);
      }
      if (SAlloc(SS_DFLT_REGION, &mdsize, 0, (Data **) bufPtr) != ROK)
      {
         SFree(region, (Data *) data, size);
         RETVALUE(ROUTRES);
      }
   }
   else
   {
      mdsize += size;
      if (SAlloc(region, &mdsize, 0, (Data **) bufPtr) != ROK)
      {
         RETVALUE(ROUTRES);
      }
      data = (Data *) (*bufPtr) + MDBSIZE;
      size = mdsize - MDBSIZE;
   }
#else /* SS_M_PROTO_REGION */
    mdsize += size;
    if (SAlloc(region, &mdsize, 0, (Data **) bufPtr) != ROK)
    {
       RETVALUE(ROUTRES);
    }
    data = (Data *) (*bufPtr) + MDBSIZE;
    size = mdsize - MDBSIZE;
#endif /* SS_M_PROTO_REGION */
#endif /* ss012.13: Addition */

   dptr = (SsDblk*) (((Data *) (*bufPtr)) + MBSIZE);

   INITB((*bufPtr), dptr, data, size, NULLP)

   RETVALUE(ROK);
}

/*
*
*       Fun:   SPutDBuf
*
*       Desc:  This function deallocates a buffer back to the
*              dynamic memory pool indicated by the caller.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: The dynamic memory pools are used to create and
*              manipulate messages.
*
*              SPutDBuf is never called by a protocol layer.
*
*              SPutDBuf assumes that interrupts are already disabled.
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SPutDBuf
(
Region region,
Pool pool,
Buffer *buf
)
#else
PUBLIC S16 SPutDBuf(region, pool, buf)
Region region;
Pool pool;
Buffer *buf;
#endif
{
#if 0 /* ss016.13: Deletion */
   Buffer *tmp;
#else
   register SsDblk *dptr;
#endif /* ss016.13: Addition */
   SsRegionEntry *regp;
   /* ss021.103 - Addition to check return value of SFree */
   S16 ret;
 
   TRC2(SPutDBuf);
 
   /* ss021.103 - Addition of ret initialization */
   ret = ROK;
 
#if (ERRCLASS & ERRCLS_INT_PAR)
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS366, ERRZERO, "SPutDBuf:Invalid region");
      RETVALUE(RFAILED);
   }
 
   if (pool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS367, ERRZERO, "SPutDBuf:Invalid pool");
      RETVALUE(RFAILED);
   }
 
   if (buf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS368, ERRZERO, "SPutDBuf:Null pointer");
      RETVALUE(RFAILED);
   }

   if ( (buf->b_datap->db_type != SS_M_DATA) && (buf->b_datap->db_type != SS_M_PROTO))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS369, ERRZERO, "SPutDBuf:Incorrect\
                 buffer type");
      RETVALUE(RFAILED);
   }
#endif
#if 1  /* ss016.13: Addition */
   dptr = buf->b_datap; 
#endif /* ss016.13: Addition */
   regp = &osCp.regionTbl[region];

#if (ERRCLASS & ERRCLS_DEBUG)
   if (regp->poolTbl[pool].type != SS_POOL_DYNAMIC)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS370, ERRZERO, "SPutDBuf:Invalid pool type");
      RETVALUE(RFAILED);
   }
#endif
#if 0 /* ss012.13: Deletion */
   /* if reference count falls to zero */
   if (!--buf->b_datap->db_ref)
   {
      /* if the buffer, buf is a message blk obtained during dupb */
      if (buf != (SsMblk *) (((Data*) (buf->b_datap)) - MBSIZE))
      {
         tmp = (SsMblk *) (((Data*) (buf->b_datap)) - MBSIZE);
         SFree(SS_DFLT_REGION, (Data *) buf, MDBSIZE);
         buf = tmp;
      }
      /* if not outboard memory, release MDBSIZE + data buffer */
      if (!(regp->flags & SS_OUTBOARD_FLAG))
         SFree(region, (Data *) buf, MDBSIZE +
                        buf->b_datap->db_lim - buf->b_datap->db_base);
      else
      {
         SFree(region, (Data *) buf->b_datap->db_base,
                        buf->b_datap->db_lim - buf->b_datap->db_base);
         SFree(SS_DFLT_REGION, (Data *) buf, MDBSIZE);
      }
   }
   else
      /* if the buffer, buf is a message blk obtained during dupb, */
      /* release the message blk */
      if (buf != (SsMblk *) (((Data*) (buf->b_datap)) - MBSIZE))
         SFree(SS_DFLT_REGION, (Data *) buf, MDBSIZE);
#endif /* ss012.13: Deletion */

#if 0 /* ss016.13: Deletion */
#if 1 /* ss012.13: Addition */
#ifndef SS_M_PROTO_REGION 
   /* if reference count falls to zero */
   if (!--buf->b_datap->db_ref)
   {
      /* if the buffer, buf is a message blk obtained during dupb */
      if (buf != (SsMblk *) (((Data*) (buf->b_datap)) - MBSIZE))
      {
         tmp = (SsMblk *) (((Data*) (buf->b_datap)) - MBSIZE);
         SFree(SS_DFLT_REGION, (Data *) buf, MDBSIZE);
         buf = tmp;
      }
      /* if not outboard memory, release MDBSIZE + data buffer */
      if (!(regp->flags & SS_OUTBOARD_FLAG))
         SFree(region, (Data *) buf, MDBSIZE +
                        buf->b_datap->db_lim - buf->b_datap->db_base);
      else
      {
         SFree(region, (Data *) buf->b_datap->db_base,
                        buf->b_datap->db_lim - buf->b_datap->db_base);
         SFree(SS_DFLT_REGION, (Data *) buf, MDBSIZE);
      }
   }
   else
      /* if the buffer, buf is a message blk obtained during dupb, */
      /* release the message blk */
      if (buf != (SsMblk *) (((Data*) (buf->b_datap)) - MBSIZE))
         SFree(SS_DFLT_REGION, (Data *) buf, MDBSIZE);
#else /* SS_M_PROTO_REGION */
   /* if reference count falls to zero */
   if (!--buf->b_datap->db_ref)
   {
      /* if the buffer, buf is a message blk obtained during dupb */
      if (buf != (SsMblk *) (((Data*) (buf->b_datap)) - MBSIZE))
      {
         tmp = (SsMblk *) (((Data*) (buf->b_datap)) - MBSIZE);
         SFree(region, (Data *) buf, MDBSIZE);
         buf = tmp;
      }
      SFree(region, (Data *) buf, MDBSIZE +
                     buf->b_datap->db_lim - buf->b_datap->db_base);
   }
   else
      /* if the buffer, buf is a message blk obtained during dupb, */
      /* release the message blk */
      if (buf != (SsMblk *) (((Data*) (buf->b_datap)) - MBSIZE))
         SFree(region, (Data *) buf, MDBSIZE);
#endif /* SS_M_PROTO_REGION */

#endif /* ss012.13: Addition */
#endif /* ss016.13: Deletion */

   /* ss028.103 - Addition of lock for mBuf reference count */
#ifndef SSI_MEM_CHNG
   ret = SLock(&osCp.mBufRefLock);
   if (ret != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS371, ERRZERO,
                     "Could not lock the mBuf Ref Lock");
      RETVALUE(RFAILED);
   }
#endif /* SSI_MEM_CHNG */

#if 1  /* ss016.13: Addition */
#ifndef SS_M_PROTO_REGION
   /* if reference count falls to zero */
   if (!--dptr->db_ref)
   {
      /* if buffer's message blk is obtained during dupb */
      if (buf != (SsMblk *) (((Data*) dptr) - MBSIZE))
      {
	 /* ss021.103 - Addition to check return value of SFree */
         if (SFree(SS_DFLT_REGION, (Data *) buf, MDBSIZE) == RFAILED)
            ret = RFAILED;
         buf = (SsMblk *) (((Data*) dptr) - MBSIZE);
      }

      /* to understand the underlaying logic it is */
      /* recommended to examine ssMsgConv2ss routine */

      /* if outboard memory */
      if (regp->flags & SS_OUTBOARD_FLAG)
      {
         /* if free routine */
         if (dptr->db_frtnp)
         {
            /* free external data buffer */
            (*dptr->db_frtnp->free_func)(dptr->db_frtnp->free_arg);
            /* free outboard data buffer to region */
	    /* ss021.103 - Addition to check return value of SFree */
            if (SFree(region, (Data *) dptr->db_frtnp,
                  *(((Size *) dptr->db_frtnp) - 1)) == RFAILED)
               ret = RFAILED;
         }
         else
            /* free data buffer to region */
	    /* ss021.103 - Addition to check return value of SFree */
            if (SFree(region, (Data *) dptr->db_base,
                  dptr->db_lim - dptr->db_base) == RFAILED)
               ret = RFAILED;

         /* always free mblk/dblk to default region */
	 /* ss021.103 - Addition to check return value of SFree */
         if (SFree(SS_DFLT_REGION, (Data *) buf, MDBSIZE) == RFAILED)
            ret = RFAILED;
      }
      else /* if not outboard memory */
      {
         /* if free routine */
         if (dptr->db_frtnp)
         {
            /* free external data buffer */
            (*dptr->db_frtnp->free_func)(dptr->db_frtnp->free_arg);
            /* free mblk/dblk + internal data buffer to region */
	    /* ss021.103 - Addition to check return value of SFree */
            if (SFree(region, (Data *) buf,
                  MDBSIZE + *(((Size *) dptr->db_frtnp) - 1)) == RFAILED)
               ret = RFAILED;
         }
         else
            /* free buffer to region */
	    /* ss021.103 - Addition to check return value of SFree */
            if (SFree(region, (Data *) buf,
                  MDBSIZE + dptr->db_lim - dptr->db_base) == RFAILED)
               ret = RFAILED;
      }
   }
   else
      /* if the buffer, buf is a message blk obtained during dupb, */
      /* release the message blk */
      if (buf != (SsMblk *) (((Data*) dptr) - MBSIZE))
	 /* ss021.103 - Addition to check return value of SFree */
         if (SFree(SS_DFLT_REGION, (Data *) buf, MDBSIZE) == RFAILED)
            ret = RFAILED;
#else /* SS_M_PROTO_REGION */
   /* if reference count falls to zero */
   if (!--dptr->db_ref)
   {
      /* if buffer's message blk is obtained during dupb */
      if (buf != (SsMblk *) (((Data*) dptr) - MBSIZE))
      {
	 /* ss021.103 - Addition to check return value of SFree */
         if (SFree(region, (Data *) buf, MDBSIZE) == RFAILED)
            ret = RFAILED;
         buf = (SsMblk *) (((Data*) dptr) - MBSIZE);
      }

      /* if free routine */
      if (dptr->db_frtnp)
      {
         /* free external data buffer */
         (*dptr->db_frtnp->free_func)(dptr->db_frtnp->free_arg);
         /* free mblk/dblk + internal data buffer to region */
	 /* ss021.103 - Addition to check return value of SFree */
         if (SFree(region, (Data *) buf,
               MDBSIZE + *(((Size *) dptr->db_frtnp) - 1)) == RFAILED)
            ret = RFAILED;
      }
      else
         /* free buffer to region */
	 /* ss021.103 - Addition to check return value of SFree */
         if (SFree(region, (Data *) buf, MDBSIZE + dptr->db_lim - dptr->db_base) == RFAILED)
            ret = RFAILED;
   }
   else
      /* if the buffer, buf is a message blk obtained during dupb, */
      /* release the message blk */
      if (buf != (SsMblk *) (((Data*) dptr) - MBSIZE))
	 /* ss021.103 - Addition to check return value of SFree */
         if (SFree(region, (Data *) buf, MDBSIZE) == RFAILED)
            ret = RFAILED;
#endif /* SS_M_PROTO_REGION */
#endif /* ss016.13: Addition */

  /* ss028.103 - Addition of lock for mBuf reference count */
#ifndef SSI_MEM_CHNG
  if ( SUnlock(&osCp.mBufRefLock) != ROK)
  {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS372, ERRZERO,
                      "Could not give the Semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif /*SSI_MEM_CHNG*/

   RETVALUE(ret);
}


/*
*
*       Fun:   SCatMsg
*
*       Desc:  This function will concatenate the two specified messages
*              into one message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: if order equal M1M2: all data attached to message 2 is
*              moved to the end of message 1. message 2 is set to empty.
*              message 1 length is increased by length of message 2.
*              message 2 length is set to zero. message 2 is not returned
*              to memory. return is ok.
*
*              if order equal M2M1: all data attached to message 2 is
*              moved to the front of message 1. message 2 is set to empty.
*              message 1 length is increased by length of message 2.
*              message 2 length is set to zero. message 2 is not returned
*              to memory. return is ok.
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SCatMsg
(
Buffer *mBuf1,              /* message 1 */
Buffer *mBuf2,              /* message 2 */
Order order
)
#else
PUBLIC S16 SCatMsg(mBuf1, mBuf2, order)
Buffer *mBuf1;              /* message 1 */
Buffer *mBuf2;              /* message 2 */
Order order;                /* order */
#endif
{
   SsMsgInfo *minfo1;
   SsMsgInfo *minfo2;
   Buffer *tmp;
   Buffer *newb;

   TRC1(SCatMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer 1 */
   if (mBuf1 == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS373, ERRZERO, "SCatMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message buffer 2 */
   if (mBuf2 == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS374, ERRZERO, "SCatMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* ss021.103 - Addition to test if same buffer */
   /* check message buffer 1 and 2 not same buffer */
   if (mBuf1 == mBuf2)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS375, ERRZERO, "SCatMsg : mBuf1 == mBuf2");
      RETVALUE(RFAILED);
   }
   if ((order != M1M2) && (order != M2M1))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS376, ERRZERO, "SCatMsg : Invalid Order");
      RETVALUE(RFAILED);
   }
   if ((mBuf1->b_datap->db_type != SS_M_PROTO) ||
       (mBuf2->b_datap->db_type != SS_M_PROTO))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS377, ERRZERO, 
                                         "SCatMsg : Incorrect buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* no data to append or prepend */
   if (!mBuf2->b_cont)
      RETVALUE(ROK);

   minfo1 = (SsMsgInfo*) mBuf1->b_rptr;
   minfo2 = (SsMsgInfo*) mBuf2->b_rptr;

/* ss021.103 - Addition to test max length of message is not exceeded */
#if (ERRCLASS & ERRCLS_INT_PAR)
#ifdef LONG_MSG
   if (minfo1->len > 0x7FFFFFFF - minfo2->len)
#else
   if (minfo1->len > 0x7FFF - minfo2->len)
#endif
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS378, ERRZERO, "SCpyFixMsg : messages too big");
      RETVALUE(ROUTRES);
   }
#endif
   
   if (minfo1->region != minfo2->region)
   {
      /* duplicate mBuf2 from the region/pool of mBuf1, initialise mBuf2 */
#if 0 /* ss015.13: deletion */
      if (SCpyMsgMsg(mBuf1, minfo1->region, minfo1->pool, &newb) != ROK)
         RETVALUE(RFAILED);
#endif /* ss015.13: deletion */
#if 1 /*ss015.13: addition */
      if (SCpyMsgMsg(mBuf2, minfo1->region, minfo1->pool, &newb) != ROK)
         RETVALUE(RFAILED);
#endif /*ss015.13: addition */
      minfo2 = (SsMsgInfo*) newb->b_rptr;
   }
   else
      newb = mBuf2;

   if ((tmp = mBuf1->b_cont) == NULLP)
   {
      mBuf1->b_cont = newb->b_cont;
      minfo1->endptr = minfo2->endptr;
   }
   else
   {
      if (order == M1M2)
      /* attach newb after mBuf1 */
      {
         minfo1->endptr->b_cont = newb->b_cont;
         minfo1->endptr = minfo2->endptr;
      }
      else
      {
         if (order == M2M1)
         /* attach newb before mBuf1 */
         {
            minfo2->endptr->b_cont = mBuf1->b_cont;
            mBuf1->b_cont = newb->b_cont;
         }
         else /* invalid order */
         {
#if (ERRCLASS & ERRCLS_DEBUG)
            SSLOGERROR(ERRCLS_DEBUG, ESS379, ERRZERO, "SCatMsg:Invalid order");
#endif
            if (newb && (newb != mBuf2))
               (Void) SPutMsg(newb);
            RETVALUE(RFAILED);
         }
      }
   }
   minfo1->len += minfo2->len;


   minfo2->endptr = NULLP;
   minfo2->len = 0;
 
   newb->b_cont = NULLP;

   if (newb != mBuf2)
   {
      (Void) SPutMsg(newb);
      (Void) SInitMsg(mBuf2);
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   SRepMsg
*
*       Desc:  This function replaces one byte of data in a message.
*
*       Ret:   ROK      - ok
*              ROKDNA   - ok, data not available
*              RFAILED  - failed, general (optional)
*
*       Notes: index is 0 based and indicates location in message
*
*               if index is less than the length of the message:
*              data is replaced at specified index. message length
*              is unchanged. return is ok.
*
*              if index is greater than or equal to
*              the length of the message: message is unchanged.
*              return is ok, data not available.
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SRepMsg
(
Data data,                  /* data */
Buffer *mBuf,               /* message buffer */
MsgLen idx
)
#else
PUBLIC S16 SRepMsg(data, mBuf, idx)
Data data;                  /* data */
Buffer *mBuf;               /* message buffer */
MsgLen idx;                 /* index */
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;
   Buffer *newb;
   Buffer *prev;
   MsgLen numBytes;

   TRC1(SRepMsg)

#if ( ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS380, ERRZERO, "SRepMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (idx < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS381, ERRZERO, "SRepMsg : Invalid index");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS382, ERRZERO, "SRepMsg : Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
#endif

   minfo = (SsMsgInfo*) (mBuf)->b_rptr;

   /* if index > length of the buffer */
   if (minfo->len <= idx)
   {
      RETVALUE(ROKDNA);
   }

   tmp = mBuf->b_cont; /* get the first SS_M_DATA blk */
   prev = mBuf;        /* parent */

   FIND_OFFSET_AND_PREV(prev, tmp, idx)

   /* if ref cnt is greater than 1, duplicate tmp */
   if (tmp->b_datap->db_ref > 1)
   {
      /* allocate a message blk of message size of tmp */
      numBytes = tmp->b_wptr - tmp->b_rptr;
      if (ssGetDBufOfSize(minfo->region, numBytes, &newb) != ROK)
      {
         SSLOGERROR(ERRCLS_DEBUG, ESS383, ERRZERO, "SRepMsg : ssGetDBufOfSize\
                    failed");
         RETVALUE(RFAILED);
      }
      while (numBytes--)
         *newb->b_wptr++ = *tmp->b_rptr++;

      newb->b_cont = tmp->b_cont;
      prev->b_cont = newb;
      if (minfo->endptr == tmp)
         minfo->endptr = newb;

      /* free tmp */
      (Void) SPutDBuf(minfo->region, minfo->pool, tmp);
      tmp = newb;
   }
   *(tmp->b_rptr + idx) = data;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SUpdMsg
*
*       Desc:  Update a message with a new dBuf
*
*       Ret:   ROK/RFAILED
*
*       Notes:
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SUpdMsg
(
Buffer *mBuf,                   /* message buffer */
Buffer *dBuf,                   /* data buffer */
MsgLen dLen
)
#else
PUBLIC S16 SUpdMsg(mBuf, dBuf, dLen)
Buffer *mBuf;                   /* message buffer */
Buffer *dBuf;                   /* data buffer */
MsgLen dLen;                    /* data length */
#endif
{
   SsMsgInfo *minfo;

   TRC1(SUpdMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS384, ERRZERO, "SUpdMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (!dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS385, ERRZERO, "SUpdMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (dLen < 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS386, ERRZERO, "SUpdMsg : Invalid length");
      RETVALUE(RFAILED);
   }
   if ((mBuf->b_datap->db_type != SS_M_PROTO) ||
       (dBuf->b_datap->db_type != SS_M_DATA))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS387, ERRZERO, "SUpdMsg : Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
#endif

   /* get the message info of mBuf */
   minfo = (SsMsgInfo*) (mBuf)->b_rptr;

#if 0 /* ss016.13: Deletion */
   /* if data length is zero, return ROK */
   if (!dLen)
   {
      (Void) SPutDBuf(minfo->region, minfo->pool, dBuf);
      RETVALUE(ROK);
   }
#else
  /* accept zero length data */
#endif /* ss016.13: Deletion */

   /* buffer offset out of bounds */
   if ((dBuf->b_rptr + dLen) > dBuf->b_datap->db_lim)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS388, ERRZERO, "SUpdMsg:Offset out of bounds");
      RETVALUE(RFAILED);
   }

   /* offset write ptr from read ptr by dLen */
   dBuf->b_wptr = dBuf->b_rptr + dLen;

   /* attach dBuf at the end of mBuf */
   if (minfo->endptr)
      minfo->endptr->b_cont = dBuf;
   else
      mBuf->b_cont = dBuf;

   /* update SsMsgInfo */
   minfo->endptr = dBuf;

   minfo->len += dLen;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SAddDBufPst
*
*       Desc:  This function queues a data buffer to the
*              back of the specified message buffer .
*
*       Ret:   ROK     - ok
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: buffer is placed in the queue.
*              queue length is incremented.
*
*              if queue is not empty: buffer is placed behind all
*              other buffers in queue. queue length is incremented.
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SAddDBufPst
(
Buffer *mBuf,                   /* message buffer */
Buffer *dBuf
)
#else
PUBLIC S16 SAddDBufPst(mBuf, dBuf)
Buffer *mBuf;                   /* message buffer */
Buffer *dBuf;                   /* data buffer */
#endif
{
   SsMsgInfo *minfo;

   TRC1(SAddDBufPst)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer queue */
   if (!mBuf || !dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS389, ERRZERO, "SAddDBufPst : Null Buffer");
      RETVALUE(RFAILED);
   }
   if ((mBuf->b_datap->db_type != SS_M_PROTO) ||
       (dBuf->b_datap->db_type != SS_M_DATA))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS390, ERRZERO, "SAddDBufPst : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* no data, return */
   if (dBuf->b_wptr == dBuf->b_rptr)
      RETVALUE(ROK);

   minfo = (SsMsgInfo*) (mBuf)->b_rptr;
 
   /* attach dBuf at the end of mBuf */
   if (minfo->endptr)
      minfo->endptr->b_cont = dBuf;
   else
      mBuf->b_cont = dBuf;

   /* update SsMsgInfo */
   minfo->endptr = dBuf;

   minfo->len += dBuf->b_wptr - dBuf->b_rptr;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SAddDBufPre
*
*       Desc:  This function queues a data buffer to the
*              front of the specified message buffer.
*
*       Ret:   ROK     - ok
*              RFAILED - failed, general (optional)
*
*       Notes: if buffer queue is empty: buffer is placed in the queue. queue
*              length is incremented.
*
*              if buffer queue is not empty: buffer is placed in front of all
*              other buffers in queue. queue length is incremented.
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SAddDBufPre
(
Buffer *mBuf,                    /* message buffer */
Buffer *dBuf
)
#else
PUBLIC S16 SAddDBufPre(mBuf, dBuf)
Buffer *mBuf;                    /* message buffer */
Buffer *dBuf;                    /* data buffer */
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;

   TRC1(SAddDBufPre)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer queue */
   if (!mBuf || !dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS391, ERRZERO, "SAddDBufPre : Null Buffer");
      RETVALUE(RFAILED);
   }
   if ((mBuf->b_datap->db_type != SS_M_PROTO) ||
       (dBuf->b_datap->db_type != SS_M_DATA))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS392, ERRZERO, "SAddDBufPre : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif
 
   /* no data, return */
   if (dBuf->b_wptr == dBuf->b_rptr)
      RETVALUE(ROK);
 
   minfo = (SsMsgInfo*) (mBuf)->b_rptr;

   tmp = mBuf->b_cont;

   /* attach dBuf at the start of mBuf */
   mBuf->b_cont = dBuf;
   dBuf->b_cont = tmp;

   minfo->len += dBuf->b_wptr - dBuf->b_rptr;

   if (!tmp)
      minfo->endptr = dBuf;

   RETVALUE(ROK);
}
 
/*
*
*       Fun:   SRemDBufPre
*
*       Desc:  This function dequeues a data buffer from
*              the front of the specified message buffer.
*
*       Ret:   ROK     - ok
*              ROKDNA  - ok, data not available
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*
*              if queue is not empty: pointer to buffer is set to first
*              buffer in queue, first buffer in queue is removed and
*              return is ok. queue length is decremented.
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SRemDBufPre
(
Buffer *mBuf,                   /* message buffer */
Buffer **dBufPtr
)
#else
PUBLIC S16 SRemDBufPre(mBuf, dBufPtr)
Buffer *mBuf;                   /* message buffer */
Buffer **dBufPtr;               /* pointer to data buffer */
#endif
{
   SsMsgInfo *minfo;

   TRC1(SRemDBufPre)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (dBufPtr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS393, ERRZERO, "SRemDBufPre : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check queue */
   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS394, ERRZERO, "SRemDBufPre : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS395, ERRZERO, "SRemDBufPre : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   /* no data blk, return */
   if ((*dBufPtr = mBuf->b_cont) == NULLP)
   {
      return ROKDNA;
   }
   minfo = (SsMsgInfo*) (mBuf)->b_rptr;

   mBuf->b_cont = (*dBufPtr)->b_cont;
   (*dBufPtr)->b_cont = NULLP;

   /* update SsMsgInfo */
   if (!(minfo->len -= (*dBufPtr)->b_wptr - (*dBufPtr)->b_rptr))
      minfo->endptr = NULLP;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SRemDBufPst
*
*       Desc:  This function dequeues a data or message buffer from the
*              back of the specified message buffer.
*
*       Ret:   ROK     - ok
*              ROKDNA  - ok, data not available
*              RFAILED - failed, general (optional)
*
*       Notes: if queue is empty: pointer to buffer is set to null and
*              return is ok, data not available. queue length is unchanged.
*
*              if queue is not empty: pointer to buffer is set to last
*              buffer in queue, last buffer in queue is removed and
*              return is ok. queue length is decremented.
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SRemDBufPst
(
Buffer *mBuf,                   /* message buffer */
Buffer **dBufPtr
)
#else
PUBLIC S16 SRemDBufPst(mBuf, dBufPtr)
Buffer *mBuf;                   /* message buffer */
Buffer **dBufPtr;               /* pointer to data buffer */
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;

   TRC1(SRemDBufPst)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check buffer pointer */
   if (!dBufPtr)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS396, ERRZERO, "SRemDBufPst : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message */
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS397, ERRZERO, "SRemDBufPst : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS398, ERRZERO, "SRemDBufPst : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif
 
   minfo = (SsMsgInfo*) (mBuf)->b_rptr;
 
   /* no data blk, return */
   if ((*dBufPtr = minfo->endptr) == NULLP)
   {
      return ROKDNA;
   }
   for (tmp = mBuf; tmp->b_cont != (*dBufPtr); )
      tmp = tmp->b_cont;

   tmp->b_cont = NULLP;

   /* update SsMsgInfo */
   if (!(minfo->len -= (*dBufPtr)->b_wptr - (*dBufPtr)->b_rptr))
      minfo->endptr = NULLP;
   else
      minfo->endptr = tmp;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SInitNxtDBuf
*
*       Desc:  Initialize next Data Buffer Id
*
*       Ret:   ROK/RFAILED
*
*       Notes: Must be called prior to SGetNxtDBuf
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SInitNxtDBuf
(
Buffer *mBuf
)
#else
PUBLIC S16 SInitNxtDBuf(mBuf)
Buffer *mBuf;                   /* message buffer */
#endif
{
   SsMsgInfo *minfo;

   TRC1(SInitNxtDBuf)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS399, ERRZERO, "SInitNxtDBuf : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS400, ERRZERO, "SInitNxtDBuf : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   minfo = (SsMsgInfo*) mBuf->b_rptr;

   /* set the next ptr of mBuf to point to the first SS_M_DATA blk */
   minfo->next = mBuf->b_cont;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SGetNxtDBuf
*
*       Desc:  Get next dBuf in message chain
*
*       Ret:   ROK/RFAILED
*
*       Notes: Must be called after SInitNxtDBuf
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SGetNxtDBuf
(
Buffer *mBuf,                   /* message buffer */
Buffer **dBuf
)
#else
PUBLIC S16 SGetNxtDBuf(mBuf, dBuf)
Buffer *mBuf;                   /* message buffer */
Buffer **dBuf;                  /* data buffer return */
#endif
{
   SsMsgInfo *minfo;

   TRC1(SGetNxtDBuf)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS401, ERRZERO, "SGetNxtDBuf : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (!dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS402, ERRZERO, "SGetNxtDBuf : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS403, ERRZERO, "SGetNxtDBuf : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   minfo = (SsMsgInfo*) (mBuf)->b_rptr;

   /* if next ptr of mBuf is NULLP, return */
   if ((*dBuf = minfo->next) == NULLP)
      RETVALUE(ROKDNA);

   /* update next */
   minfo->next = (*dBuf)->b_cont;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SChkNxtDBuf
*
*       Desc:  check if next data buffer exists.
*
*       Ret:   ROK/ROKDNA/RFAILED
*
*       Notes: doesn't modify nxtDBuf
*
*       File:  ss_msg.c
*
*/

#ifdef ANSI
PUBLIC S16 SChkNxtDBuf
(
Buffer *mBuf
)
#else
PUBLIC S16 SChkNxtDBuf(mBuf)
Buffer *mBuf;                   /* message buffer */
#endif
{
   SsMsgInfo *minfo;

   TRC1(SChkNxtDBuf)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS404, ERRZERO, "SChkNxtDBuf : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS405, ERRZERO, "SChkNxtDBuf : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS */

   minfo = (SsMsgInfo*) (mBuf)->b_rptr;

   /* if next is valid, return ROK */
   if (minfo->next)
      RETVALUE(ROK);
   else
      RETVALUE(ROKDNA);
}

/*
*
*       Fun:   SGetDataRx
*
*       Desc:  Given a data buffer, return a pointer to the
*              data payload, and the length of the payload
*
*
*       Ret:   ROK ok
*              RFAILED error
*
*       Notes: This assumes an uninitialized dBuf
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SGetDataRx
(
Buffer *dBuf,                   /* data buffer */
MsgLen pad,                     /* pad */
Data **retDatPtr,               /* return data pointer */
MsgLen *retDatLen
)
#else
PUBLIC S16 SGetDataRx(dBuf, pad, retDatPtr, retDatLen)
Buffer *dBuf;                   /* data buffer */
MsgLen pad;                     /* pad */
Data **retDatPtr;               /* return data pointer */
MsgLen *retDatLen;              /* return data length */
#endif
{
   TRC1(SGetDataRx)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS406, ERRZERO, "SGetDataRx : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (!retDatLen || (pad < 0))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS407, ERRZERO, "SGetDataRx : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (!retDatPtr)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS408, ERRZERO, "SGetDataRx : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (dBuf->b_datap->db_type != SS_M_DATA)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS409, ERRZERO, "SGetDataRx : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS */

   if (dBuf->b_datap->db_ref > 1)   /* cannot write to a shared buffer */
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS410, ERRZERO, "SGetDataRx : Reference\
                                                 count > 1");
#endif
      RETVALUE(RFAILED);
   }

   /* return the write ptr loc(with padding) if there is data to write to */
   if ((*retDatLen = (dBuf->b_datap->db_lim - dBuf->b_wptr - pad)) > 0)
      *retDatPtr = dBuf->b_wptr + pad;
   else
   {
      *retDatPtr = NULLP;
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS411, ERRZERO, "SGetDataRx:No data available");
#endif
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

/*
*
*       Fun:   SGetDataTx
*
*       Desc:  Given a data buffer, return a pointer to the
*              data payload, and the length of the payload
*
*
*       Ret:   ROK ok
*              RFAILED error
*
*       Notes: This assumes an initialized dBuf
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SGetDataTx
(
Buffer *dBuf,                   /* data buffer */
Data **retDatPtr,               /* return data pointer */
MsgLen *retDatLen               /* return data length */
)
#else
PUBLIC S16 SGetDataTx(dBuf, retDatPtr, retDatLen)
Buffer *dBuf;                   /* data buffer */
Data **retDatPtr;               /* return data pointer */
MsgLen *retDatLen;              /* return data length */
#endif
{
   TRC1(SGetDataTx)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* ss021.103 - Modification to check parameters */
   if (!retDatPtr)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS412, ERRZERO, "SGetDataTx : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (!dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS413, ERRZERO, "SGetDataTx : Null Buffer");
      *retDatPtr = (Data *)NULLP;
      RETVALUE(RFAILED);
   }
   if (!retDatLen)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS414, ERRZERO, "SGetDataTx : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (dBuf->b_datap->db_type != SS_M_DATA)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS415, ERRZERO, "SGetDataTx : Incorrect\
                                                   buffer type");
      *retDatPtr = (Data *)NULLP;
      RETVALUE(RFAILED);
   }
#endif /* ERRCLASS */

   /* if there is data, return read ptr */
   if ((*retDatLen = dBuf->b_wptr - dBuf->b_rptr))
      *retDatPtr = dBuf->b_rptr;
   else
   {
      *retDatPtr = NULLP;
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS416, ERRZERO, "SGetDataTx : Buffer empty");
#endif
      RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}

#ifndef SS_ENABLE_MACROS

/*
*
*       Fun:   SGetBufRegionPool
*
*       Desc:  returns the region and pool of the message buffer
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetBufRegionPool
(
Buffer *mBuf,                   /* message buffer */
Region *region,                 /* region */
Pool   *pool                    /* pool */
)
#else
PUBLIC S16 SGetBufRegionPool(mBuf, region, pool)
Buffer *mBuf;                   /* message buffer */
Region *region;                 /* region */
Pool   *pool;                   /* pool */
#endif
{
   SsMsgInfo *mInfo;            /* message info pointer */

   TRC1(SGetBufRegionPool)

#if (ERRCLASS & ERRCLS_INT_PAR)

   if (mBuf == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS417, ERRZERO, 
                 "SGetBufRegionPool : Null Buffer");
      RETVALUE(RFAILED);
   }
   if ((region == NULLP) && (pool == NULLP))
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS418, ERRZERO, 
                 "SGetBufRegionPool : Null region and pool pointers");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS419, ERRZERO, 
                 "SUpdMsg : Incorrect buffer type");
      RETVALUE(RFAILED);
   }
#endif /* (ERRCLASS & ERRCLS_INT_PAR */

   /* get message info of mBuf */
   if ((mInfo = (SsMsgInfo *) mBuf->b_rptr) == NULLP)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS420, ERRZERO, 
                 "SGetBufRegionPool : mBuf's control data is null");
#endif
      RETVALUE(RFAILED);
   }

   if (region != NULLP)
      *region = mInfo->region;
   if (pool != NULLP)
      *pool   = mInfo->pool;

   RETVALUE(ROK);
} /* end of SGetBufRegionPool */

#endif /* SS_ENABLE_MACROS */

/*
*
*       Fun:   SCompressMsg
*
*       Desc:  This function is used to compress a message into
*              the minimum number of data buffers needed.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/

 
#ifdef ANSI
PUBLIC S16 SCompressMsg
(
Buffer *mBuf
)
#else
PUBLIC S16 SCompressMsg(mBuf)
Buffer *mBuf;                    /* message buffer */
#endif
{
   SsMsgInfo *minfo;
   MsgLen numBytes;
   Buffer *dBuf;
   Buffer *tmp;
   Buffer *next;
   S16 ret;

   TRC1(SCompressMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!mBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS421, ERRZERO, "SCompressMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS422, ERRZERO, "SCompressMsg : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   minfo = (SsMsgInfo*) (mBuf)->b_rptr;

   if ((tmp = mBuf->b_cont) == minfo->endptr)
   {
      RETVALUE(ROK);
   }

   /* allocate a data buffer of size bytes*/
   if ((ret = ssGetDBufOfSize(minfo->region, minfo->len, &dBuf)) != ROK)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS423, ERRZERO, "SAddMsgRef : ssGetDBufOfSize\
                 failed");
      RETVALUE(RFAILED);
   }
   dBuf->b_datap->db_type = SS_M_DATA;

   while (tmp)
   {
      /* determine number of bytes to be copied */
      numBytes = tmp->b_wptr - tmp->b_rptr;

      /* copy data */
#if 0  /* ss002.13: deletion */
      while (numBytes--)
         *dBuf->b_wptr++ = *tmp->b_rptr++;
#endif /* ss002.13: deletion */

#if 1 /* ss002.13: addition */
#if 0  /* ss003.13: deletion */
      SMemCpy( (VOID *)dBuf->b_wptr, (VOID *)tmp->b_rptr, (size_t)numBytes);
#endif /* ss003.13: deletion */
#if 1 /* ss003.13: addition */
      SMemCpy( (Void *)dBuf->b_wptr, (Void *)tmp->b_rptr, (size_t)numBytes);
#endif /* ss003.13: addition */
      dBuf->b_wptr += numBytes;
      tmp->b_rptr += numBytes;
#endif /* ss002.13: addition */


      next = tmp->b_cont;
      (Void) SPutDBuf(minfo->region, minfo->pool, tmp);
      tmp = next;
   }
   /* update mBuf and SsMsgInfo */
   mBuf->b_cont = dBuf;
   minfo->endptr = dBuf;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SPrntMsg
*
*       Desc:  This function prints the contents of a message. The
*              following information is printed: queue length,
*              message length, direction, hexadecimal and ASCII
*              (if appropriate) values of all bytes in the message.
*
*              This function should be used for debugging only.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ss_msg.c
*
*/
  
#ifdef ANSI
PUBLIC S16 SPrntMsg
(
Buffer *mBuf,               /* message buffer */
S16 src,                    /* source id */
S16 dst                     /* destination id */
)
#else
PUBLIC S16 SPrntMsg(mBuf, src, dst)
Buffer *mBuf;               /* message buffer */
S16 src;                    /* source id */
S16 dst;                    /* destination id */
#endif
{
   QLen qlen;               /* queue length */
   MsgLen mlen;             /* message length */
   S16 i;                   /* counter */
   S16 j;                   /* counter */
   S16 k;                   /* counter */
   U8 data;                 /* data */
   U8 tdata[16];            /* temporary data */
   S8 prntBuf[256];         /* print buffer */
   Buffer *tmp;             /* buffer ptr */
   Data *cptr;
#if 1 /* ss012.13: Addition */
   Data reg;
#endif


   TRC1(SPrntMsg)

   if (mBuf == NULLP)
   {
      sprintf(prntBuf,"\nmsg: empty\n");
      SPrint(prntBuf);
      SPrint( (S8*)"\n\n");
      RETVALUE(ROK);
   }

   for (qlen = 0, tmp = mBuf->b_cont; tmp; qlen++)
      tmp = tmp->b_cont;
   mlen = ((SsMsgInfo*)(mBuf->b_rptr))->len;
   reg = ((SsMsgInfo*)(mBuf->b_rptr))->region;
   sprintf(prntBuf,"\nmsg: qlen: %04d mlen: %04d   %02d-->%02d region: %02d\n",
           (U16)qlen,mlen,src,dst,reg);
   SPrint( prntBuf);
   SPrint((S8*) "dat: ");

   if (mlen == 0)
   {
      sprintf(prntBuf," empty\n");
      SPrint(prntBuf);
      SPrint( (S8*)"\n\n");
      RETVALUE(ROK);
   }
   tmp = mBuf->b_cont;
   cptr = tmp->b_rptr;
   data= *cptr++; 
   i = 0;
   while( i < mlen  ) 
   {
      j = 0;
      for( j = 0; j < 16; j++)
      {
         if( i < mlen )
         { 
            /* print hex */
            tdata[j]=data;
            sprintf( prntBuf,"%02x ",(U16) data);
            SPrint( prntBuf);
            if (cptr == tmp->b_wptr)
            {
               tmp = tmp->b_cont;
               if (tmp)
                  cptr = tmp->b_rptr;
            }
	    /* ss024.103 - Modification to fix bug */
            i++;
	    if ( i < mlen )
               data = *cptr++;
         }
         else
         {
            sprintf( prntBuf,"   ");
            SPrint( prntBuf );
         }
      } 
      for (k = 0; k < 16; k++)
      {
         if( (i >= mlen) && (k>=(mlen%16)) && mlen%16 != 0)
            break;
         if (AIsAscii(tdata[k]))
         {
            /* print character if printable */
            sprintf(prntBuf,"%c",tdata[k]);
            SPrint( prntBuf);
         }
         else
         {
            /* print . if non printable */
            SPrint((S8*) ".");
         }
      }
      sprintf(prntBuf,"\n     ");
      SPrint(prntBuf);
   }
   RETVALUE(ROK);

} /* end of SPrntMsg */



/*
*
*       Fun:   SGetPstMsgMult
*
*       Desc:  This function allocates consecutive bytes of data at the
*              end of a message.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*              ROUTRES  - failed, out of resources (optional)
*
*       Notes: if message is empty: message length is incremented.
*              return is ok.
*
*              if message is not empty: space is allocated in back of
*              all other data in message.  message length is incremented.
*              return is ok.
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetPstMsgMult
(
MsgLen cnt,                 /* count */
Buffer *mBuf                /* message buffer */
)
#else
PUBLIC S16 SGetPstMsgMult(cnt, mBuf)
MsgLen cnt;                 /* count */
Buffer *mBuf;               /* message buffer */
#endif
{
   Buffer *tmp;
   Buffer *newb;
   SsMsgInfo *minfo;
   MsgLen numBytes;
   MsgLen avail;

   TRC1(SGetPstMsgMult)

#if ( ERRCLASS & ERRCLS_INT_PAR )
   /* check message buffer */
   if (mBuf == NULLP)
   {
      RETVALUE(RFAILED);
   }
   /* check count */
   if (cnt <= 0)
   {
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      RETVALUE(RFAILED);
   }
#endif
   /* get the message info */
   minfo = (SsMsgInfo *) (mBuf->b_rptr);

   /* init avail */
   avail = 0;

   if ((tmp = minfo->endptr) && (tmp->b_datap->db_ref == 1) &&
       ((avail = tmp->b_datap->db_lim - tmp->b_wptr)))
   {
      numBytes = MIN(cnt, avail);

      cnt -= numBytes;
      minfo->len += numBytes;

#if 0 /* ss002.13: deletion */
      while (numBytes--)
         *tmp->b_wptr++ = '\0';
#endif /* ss002.13: deletion */

#if 1 /* ss002.13 addition */
#if 0 /* ss003.13: deletion */
      SMemSet( (VOID *)tmp->b_wptr, (Data)'\0', (size_t)numBytes);
#endif /* ss003.13: deletion */
#if 1 /* ss003.13 addition */
      SMemSet( (Void *)tmp->b_wptr, (Data)'\0', (size_t)numBytes);
#endif /* ss003.13: addition */
      tmp->b_wptr += numBytes;
#endif /* ss002.13: addition */
      if (!cnt)
         RETVALUE(ROK);
   }
   if (ssGetDBufOfSize(minfo->region, cnt, &newb) != ROK)
   {
      /* ss027.103 - Modification to fix bug in SGetPstMsgMult */
      if ((avail) && (tmp))
         tmp->b_wptr = tmp->b_datap->db_lim - avail;
      minfo->len -= avail;
      RETVALUE(ROUTRES);
   }

   minfo->len += cnt;

#if 0  /* ss002.13: deletion */
   while (cnt--)
      *newb->b_wptr++ = '\0';
#endif /* ss002.13: deletion */

#if 1 /* ss002.13: addition */
#if 0  /* ss003.13: deletion */
   SMemSet( (VOID *)newb->b_wptr, (Data)'\0', (size_t)cnt);
#endif /* ss003.13: deletion */
#if 1 /* ss003.13: addition */
   SMemSet( (Void *)newb->b_wptr, (Data)'\0', (size_t)cnt);
#endif /* ss003.13: addition */
   newb->b_wptr += cnt;
#endif /* ss002.13: addition */


   if (tmp)
      tmp->b_cont = newb;
   else
      mBuf->b_cont = newb;

   minfo->endptr = newb;

   RETVALUE(ROK);
}

/*
*
*       Fun:   SChkMsg
*
*       Desc:  Check Message
*
*       Ret:   ROK on success
*              RFAILED on error
*
*       Notes: Check that the first buffer in a message
*              contains at least two bytes. This check is required
*              by 68302/68360 processors to insure accurate fisu
*              generation.
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SChkMsg
(
Buffer *mBuf
)
#else
PUBLIC S16 SChkMsg(mBuf)
Buffer *mBuf;
#endif
{
   SsMsgInfo *minfo;
   Buffer *tmp;

   TRC1(SChkMsg)
 
#if ( ERRCLASS & ERRCLS_INT_PAR )
   /* check message buffer */
   if (mBuf == NULLP)
   {
      RETVALUE(RFAILED);
   }
   if (mBuf->b_datap->db_type != SS_M_PROTO)
   {
      RETVALUE(RFAILED);
   }
#endif
   /* get the message info */
   minfo = (SsMsgInfo *) (mBuf->b_rptr);

   if (minfo->len < 2)
      RETVALUE(RFAILED);

   /* get the first M_DATA blk*/
   tmp = mBuf->b_cont;

   if (((tmp->b_rptr + 2) <= tmp->b_wptr) || (SCompressMsg(mBuf) == ROK))
      RETVALUE(ROK);

   RETVALUE(RFAILED);
}

/*
*
*       Fun:   SAlignDBufEven
*
*       Desc:  align data portion of a data buffer on an even
*              byte boundary.
*
*       Ret:   ROK/RFAILED
*
*       Notes: required for SS7 microcode on the 68302
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SAlignDBufEven
(
Buffer *dBuf                      /* data buffer */
)
#else
PUBLIC S16 SAlignDBufEven(dBuf)
Buffer *dBuf;                   /* data buffer  */
#endif
{
   MsgLen len;
   Data *src;

   TRC1(SAlignDBufEven)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS424, ERRZERO, "SAlignDBufEven : Null\
                 Buffer");
      RETVALUE(RFAILED);
   }
   if (dBuf->b_datap->db_type != SS_M_DATA)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS425, ERRZERO, "SAlignDBufEven : Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   src = dBuf->b_rptr;
#if 0  /* ss008.13: deletion */
   if (!((U32)src % (U32)2))
      RETVALUE(ROK);
#endif /* ss008.13: deletion */
#if 1 /* ss008.13: addition */
   if (!((PTR)src % (PTR)2))
      RETVALUE(ROK);
#endif /* ss008.13: addition */

   if (dBuf->b_datap->db_ref > 1)
      RETVALUE(RFAILED);

   len = dBuf->b_wptr - dBuf->b_rptr;

   if (dBuf->b_datap->db_base < dBuf->b_rptr)
   {
      dBuf->b_wptr = --dBuf->b_rptr;
      while (len--)
         *dBuf->b_wptr++ = *src++;
   }
   else
      if (dBuf->b_datap->db_lim > dBuf->b_wptr)
      {
         src = dBuf->b_wptr - 1;
         dBuf->b_rptr = ++dBuf->b_wptr;
         while (len--)
            *--dBuf->b_rptr = *src--;
      }
      else
         RETVALUE(RFAILED);

   RETVALUE(ROK);
}

#if 1 /* ss004.13: addition */
/*
*
*       Fun:   SAlignDBuf
*
*       Desc:  Align data portion of a data buffer on the specified 
*              boundary. No restriction is imposed on the alignment.
*
*       Ret:   ROK/RFAILED
*
*       Notes: required by drivers (68360, 860)
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SAlignDBuf
(
Buffer *dBuf,                      /* data buffer */
U32    align                       /* alignemnt required */
)
#else
PUBLIC S16 SAlignDBuf(dBuf, align)
Buffer *dBuf;                      /* data buffer  */
U32    align;                      /* alignemnt required */
#endif
{
   MsgLen len;
   Data   *src;
   U32    upShift;                 /* no. of bytes to be shifted up */
   U32    downShift;               /* no. of bytes to be shifted down */

   TRC1(SAlignDBuf)

#if (ERRCLASS & ERRCLS_INT_PAR)
   if (!dBuf)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS426, ERRZERO, "SAlignDBuf: Null\
                 Buffer");
      RETVALUE(RFAILED);
   }
   if (dBuf->b_datap->db_type != SS_M_DATA)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS427, ERRZERO, "SAlignDBuf: Incorrect\
                                                   buffer type");
      RETVALUE(RFAILED);
   }
#endif

   src = dBuf->b_rptr;
#if 0  /* ss008.13: deletion */
   upShift = (U32)src % (U32)align; /* no. of bytes by which to shift up
                                     * the read and write pointers */
#endif /* ss008.13: deletion */
#if 1  /* ss008.13: addition */
   upShift = (PTR)src % (PTR)align; /* no. of bytes by which to shift up
                                     * the read and write pointers */
#endif /* ss008.13: addition */

   if (!upShift)
      RETVALUE(ROK);

   if (dBuf->b_datap->db_ref > 1)
      RETVALUE(RFAILED);

   downShift = align - upShift;   /* no of bytes by which to shift down
                                   * the read and write pointers */
   len = dBuf->b_wptr - dBuf->b_rptr;

   if (dBuf->b_datap->db_base <= (dBuf->b_rptr - upShift))
   {
      /* there is space to shift up the read and write pointers */

      dBuf->b_rptr -= upShift;   /* align the read pointer */
      dBuf->b_wptr = dBuf->b_rptr;
      SMemCpy( (Void *) dBuf->b_wptr, (Void *) src,  (size_t) len);
      dBuf->b_wptr = dBuf->b_wptr + len;
   }
   else
   {
      if (dBuf->b_datap->db_lim > dBuf->b_wptr + downShift)
      {
         src = dBuf->b_wptr - 1;
         dBuf->b_wptr = dBuf->b_wptr + downShift;
         dBuf->b_rptr = dBuf->b_wptr;
         while (len--)
            *--dBuf->b_rptr = *src--;
      }
      else
         RETVALUE(RFAILED);
   }

   RETVALUE(ROK);
}
#endif /* ss004.13: addition */


/*
*
*       Fun:   SGetSMem
*
*       Desc:  Allocates a static buffer pool within the specified
*              memory region.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: The new memory management scheme makes this function
*              meaningless. It merely sets the pool ID to zero and
*              returns.
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetSMem
(
Region region,                  /* region ID */
Size size,                      /* size */
Pool *pool                      /* pointer to pool ID */
)
#else
PUBLIC S16 SGetSMem(region, size, pool)
Region region;                  /* region ID */
Size size;                      /* size */
Pool *pool;                     /* pointer to pool ID */
#endif
{
   TRC1(SGetSMem);


   UNUSED(size);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS428, region, "Invalid region");
      RETVALUE(RFAILED);
   }

   /* validate pointer to pool ID */
   if (pool == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS429, region, "Null pointer");
      RETVALUE(RFAILED);
   }
#endif


   /* set the pool ID to zero and return success */
   *pool = 0;


   RETVALUE(ROK);
}


/*
*
*       Fun:   SPutSMem
*
*       Desc:  Deallocates a static buffer pool within the specified
*              memory region.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: The new memory management scheme makes this function
*              meaningless. It does nothing.
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SPutSMem
(
Region region,                  /* region ID */
Pool pool                       /* pool ID */
)
#else
PUBLIC S16 SPutSMem(region, pool)
Region region;                  /* region ID */
Pool pool;                      /* pool ID */
#endif
{
   /* ss021.103 - Addition of return value */
#if (ERRCLASS & ERRCLS_INT_PAR)
   S16	ret;
#endif

   TRC1(SPutSMem);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS430, region, "Invalid region");
      RETVALUE(RFAILED);
   }

   /* validate pool ID */
   if (pool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS431, region, "Invalid pool");
      RETVALUE(RFAILED);
   }

   /* ss021.103 - Addition to check if region is registered */
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS432, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is present */
   if (osCp.regionTbl[region].used == FALSE)
   {
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS433, ERRZERO,
                  "Could not release semaphore");
         RETVALUE(RFAILED);
#endif
      }

      SSLOGERROR(ERRCLS_INT_PAR, ESS434, region, "Region not registered");
      RETVALUE(RFAILED);
   }
#endif

   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS435, ERRZERO,
                  "Could not release semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif

   RETVALUE(ROK);
}


/*
*
*       Fun:   SGetSBuf
*
*       Desc:  Allocates a buffer from the specified static memory pool
*              in the specified region.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes: The new memory management scheme eliminates the concept
*              of pools. This call maps directly to a call to the memory
*              manager.
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SGetSBuf
(
Region region,                  /* region ID */
Pool pool,                      /* pool ID */
Data **ptr,                     /* pointer to buffer */
Size size                       /* size requested */
)
#else
PUBLIC S16 SGetSBuf(region, pool, ptr, size)
Region region;                  /* region ID */
Pool pool;                      /* pool ID */
Data **ptr;                     /* pointer to buffer */
Size size;                      /* size requested */
#endif
{
   S16 ret;
   U32 flags;


   TRC1(SGetSBuf);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS436, region, "Invalid region");
      RETVALUE(RFAILED);
   }

   /* validate pool ID */
   if (pool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS437, pool, "Invalid pool");
      RETVALUE(RFAILED);
   }
#if 0  /* ss008.13: deletion */
   /* validate data pointer */
   if (ptr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS438, ptr, "NULL data pointer");
      RETVALUE(RFAILED);
   }
#endif /* ss008.13: deletion */
#if 1  /* ss008.13: addition */
   /* validate data pointer */
   if (ptr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS439, (ErrVal)0 , "NULL data pointer");
      RETVALUE(RFAILED);
   }
#endif /* ss008.13: addition */

   /* validate size */
   if (size <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS440, size, "Invalid size");
      RETVALUE(RFAILED);
   }
#endif
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS441, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }

#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is present */
   if (osCp.regionTbl[region].used == FALSE)
   {
#if 0  /* ss006.13: deletion */
      SS_RELEASE_SEMA(&osCp.regionTblSem);
#endif /* ss006.13: deletion */

#ifndef SS_PERF
#if 1  /* ss006.13: addition */
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS442, ERRZERO,
                  "Could not release semaphore");
         RETVALUE(RFAILED);
#endif
      }
#endif /* ss006.13: addition */

      SSLOGERROR(ERRCLS_INT_PAR, ESS443, region, "Region not registered");
      RETVALUE(RFAILED);
#endif
   }
#endif


   flags = 0;

   /* ss024.103 - Addition for memory calculator tool */
#ifdef USE_MEMCAL
   if (region == SS_STATIC_REGION)
      flags = 1;
#endif
   
   /* call the memory manager, to allocate this memory */
/* ss036.103 - addition for passing additional parameter memType as static */
#ifdef SSI_DEBUG_LEVEL1
   ret = (osCp.regionTbl[region].alloc)
               (osCp.regionTbl[region].regCb, &size, flags, ptr, SS_STATIC_MEM_FLAG);
#else
   ret = (osCp.regionTbl[region].alloc)
               (osCp.regionTbl[region].regCb, &size, flags, ptr);
#endif /* SSI_DEBUG_LEVEL1 */

   /* release the semaphore we took */
#if 0  /* ss006.13: deletion */
   SS_RELEASE_SEMA(&osCp.regionTblSem);
#endif /* ss006.13: deletion */

#ifndef SS_PERF
#if 1  /* ss006.13: addition */
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS444, ERRZERO,
                  "Could not release semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif /* ss006.13: addition */
#endif
/* ss036.103 - Addition to handle the memory trampling return value
* This in turn might invoke SRegMemErrHdlr  
*/
#ifdef SSI_DEBUG_LEVEL1
    if (ret == RTRAMPLINGNOK)
    {
       SRegMemErrHdlr( region, *ptr, ret);
    }
#endif /* SSI_DEBUG_LEVEL1 */

   RETVALUE(ret);
}


/*
*
*       Fun:   SPutSBuf
*
*       Desc:  Returns a buffer to the specified static pool in the
*              specified memory region.
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SPutSBuf
(
Region region,                  /* region ID */
Pool pool,                      /* pool ID */
Data *ptr,                      /* pointer to buffer */
Size size                       /* size */
)
#else
PUBLIC S16 SPutSBuf(region, pool, ptr, size)
Region region;                  /* region ID */
Pool pool;                      /* pool ID */
Data *ptr;                      /* pointer to buffer */
Size size;                      /* size */
#endif
{
   S16 ret;


   TRC1(SPutSBuf);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS445, region, "Invalid region");
      RETVALUE(RFAILED);
   }

   /* validate pool ID */
   if (pool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS446, pool, "Invalid pool");
      RETVALUE(RFAILED);
   }
#if 0 /* ss008.13: deletion */
   /* validate data pointer */
   if (ptr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS447, ptr, "NULL data pointe");
      RETVALUE(RFAILED);
   }
#endif /* ss008.13: deletion */
#if 1  /* ss008.13: addition */
   /* validate data pointer */
   if (ptr == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS448, (ErrVal)0, "NULL data pointe");
      RETVALUE(RFAILED);
   }
#endif /* ss008.13: addition */

   /* validate size */
   if (size <= 0)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS449, size, "Invalid size");
      RETVALUE(RFAILED);
   }
#endif
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS450, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }
#endif

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is around */
   if (osCp.regionTbl[region].used == FALSE)
   {
#ifndef SS_PERF
#if 0  /* ss006.13: deletion */
      SS_RELEASE_SEMA(&osCp.regionTblSem);
#endif /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS451, ERRZERO,
                  "Could not release semaphore");
         RETVALUE(RFAILED);
#endif
      }
#endif /* ss006.13: addition */
#endif
      SSLOGERROR(ERRCLS_INT_PAR, ESS452, region, "Region not registered");
      RETVALUE(RFAILED);
   }
#endif


   /* call the memory manager to free this memory */
   ret = (osCp.regionTbl[region].free)(osCp.regionTbl[region].regCb, ptr, size);
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* release the semaphore we took */
#if 0  /* ss006.13: deletion */
   SS_RELEASE_SEMA(&osCp.regionTblSem);
#endif /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS453, ERRZERO,
                  "Could not release semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif /* ss006.13: addition */
#endif
/* ss036.103 - addition to handle double free and trampling return values
* This might invoke SRegMemErrHdlr 
*/
#ifdef SSI_DEBUG_LEVEL1
    /* handle the double free error here by calling the OS specific error handling function */
    if ((ret == RDBLFREE) || (ret == RTRAMPLINGNOK))
    {
       SRegMemErrHdlr( region,  ptr,  ret);
    }
#endif /* SSI_DEBUG_LEVEL1 */

   RETVALUE(ret);
}


/*
*
*       Fun:   SChkRes
*
*       Desc:  Checks the available system resources (memory).
*
*       Ret:   ROK      - ok
*              RFAILED  - failed, general (optional)
*
*       Notes:
*
*       File:  ss_msg.c
*
*/
#ifdef ANSI
PUBLIC S16 SChkRes
(
Region region,                  /* region ID */
Pool pool,                      /* pool ID */
Status *status                  /* pointer to status */
)
#else
PUBLIC S16 SChkRes(region, pool, status)
Region region;                  /* region ID */
Pool pool;                      /* pool ID */
Status *status;                 /* pointer to status */
#endif
{
   S16 ret;
   SMemCtl mctl;


   TRC1(SChkRes);


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* validate region ID */
   if (region >= SS_MAX_REGS)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS454, region, "Invalid region");
      RETVALUE(RFAILED);
   }

   /* validate pool ID */
   if (pool >= SS_MAX_POOLS_PER_REG)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS455, region, "Invalid pool");
      RETVALUE(RFAILED);
   }

   /* validate status pointer */
   if (status == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS456, ERRZERO, "Null pointer");
      RETVALUE(RFAILED);
   }
#endif
/* ss037.103 Removed the semaphore operation for performance enhancement */

#ifndef SS_PERF
   /* acquire one semaphore, to protect against deregistration */
   SS_ACQUIRE_SEMA(&osCp.regionTblSem, ret);
   if (ret != ROK)
   {

#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS457, (ErrVal) ret,
                  "Could not lock region table");
#endif

      RETVALUE(RFAILED);
   }


#if (ERRCLASS & ERRCLS_INT_PAR)
   /* verify that this region is around */
   if (osCp.regionTbl[region].used == FALSE)
   {
#if 0  /* ss006.13: deletion */
      SS_RELEASE_SEMA(&osCp.regionTblSem);
#endif /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
      if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
      {
#if (ERRCLASS & ERRCLS_DEBUG)
         SSLOGERROR(ERRCLS_DEBUG, ESS458, ERRZERO,
                  "Could not release semaphore");
         RETVALUE(RFAILED);
#endif
      }
#endif /* ss006.13: addition */

      SSLOGERROR(ERRCLS_INT_PAR, ESS459, region, "Region not registered");
      RETVALUE(RFAILED);
   }

   /* verify that this is a valid pool */
   if (osCp.regionTbl[region].poolTbl[pool].type != SS_POOL_DYNAMIC)
   {
      SSLOGERROR(ERRCLS_DEBUG, ESS460, ERRZERO, "Invalid pool");
      RETVALUE(RFAILED);
   }
#endif
#endif

   /* call the memory manager to check resources */
   mctl.op = SS_MEM_CHK_RES;
   mctl.u.chkres.size = osCp.regionTbl[region].poolTbl[pool].u.dpool.size;
   mctl.u.chkres.status = status;
   ret = (osCp.regionTbl[region].ctl)
             (osCp.regionTbl[region].regCb, SS_MEM_CHK_RES, &mctl);
#ifndef SS_PERF
   /* release the semaphore we took */
#if 0  /* ss006.13: deletion */
   SS_RELEASE_SEMA(&osCp.regionTblSem);
#endif /* ss006.13: deletion */

#if 1  /* ss006.13: addition */
   if( SS_RELEASE_SEMA(&osCp.regionTblSem) != ROK)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
      SSLOGERROR(ERRCLS_DEBUG, ESS461, ERRZERO,
                  "Could not release semaphore");
      RETVALUE(RFAILED);
#endif
   }
#endif /* ss006.13: addition */
#endif

   RETVALUE(ret);
}

/*
*
*       Fun:   SSwapMsg
*
*       Desc:  This function will swap two message data contents.
*              The original mBuf pointers are unchanged.
*
*       Ret:   ROK     - ok
*              RFAILED - failed
*
*       Notes: 
*
*       File:  ss_msg.c
*
*/


#ifdef ANSI
PUBLIC S16 SSwapMsg
(
Buffer *mBuf1,              /* message 1 */
Buffer *mBuf2               /* message 2 */
)
#else
PUBLIC S16 SSwapMsg(mBuf1, mBuf2)
Buffer *mBuf1;              /* message 1 */
Buffer *mBuf2;              /* message 2 */
#endif
{
   SsMsgInfo *minfop;
   SsMsgInfo minfo;
#if (ERRCLASS & ERRCLS_INT_PAR)
   SsMsgInfo *minfo1;
   SsMsgInfo *minfo2;
#endif
   Buffer *tmp;
   U8 tmp2;
   
   TRC1(SSwapMsg)

#if (ERRCLASS & ERRCLS_INT_PAR)
   /* check message buffer 1 */
   if (mBuf1 == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS462, ERRZERO, "SSwapMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   /* check message buffer 2 */
   if (mBuf2 == NULLP)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS463, ERRZERO, "SSwapMsg : Null Buffer");
      RETVALUE(RFAILED);
   }
   if (mBuf1->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS464, ERRZERO, "SSwapMsg: Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
   if (mBuf2->b_datap->db_type != SS_M_PROTO)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS465, ERRZERO, "SSwapMsg: Incorrect buffer\
                                                   type");
      RETVALUE(RFAILED);
   }
   minfo1 = (SsMsgInfo*) mBuf1->b_rptr;
   minfo2 = (SsMsgInfo*) mBuf2->b_rptr;
   if (minfo1->region != minfo2->region)
   {
      SSLOGERROR(ERRCLS_INT_PAR, ESS466, ERRZERO, "SSwapMsg: differnt regions\
                                                   for messages");
      RETVALUE(RFAILED);
   }
#endif


   tmp = mBuf1->b_next;
   mBuf1->b_next = mBuf2->b_next;
   mBuf2->b_next = tmp;

   tmp = mBuf1->b_prev;
   mBuf1->b_prev = mBuf2->b_prev;
   mBuf2->b_prev = tmp;

   tmp = mBuf1->b_cont;
   mBuf1->b_cont = mBuf2->b_cont;
   mBuf2->b_cont = tmp;

   tmp = (Buffer *) mBuf1->b_datap->db_frtnp;
   mBuf1->b_datap->db_frtnp = mBuf2->b_datap->db_frtnp;
   mBuf2->b_datap->db_frtnp = (struct ssfree_rtn *) tmp;

   tmp2 = mBuf1->b_datap->db_ref;
   mBuf1->b_datap->db_ref = mBuf2->b_datap->db_ref;
   mBuf2->b_datap->db_ref = tmp2;


   minfop = & minfo;
   
   SMemCpy((Void *) minfop, (Void *) (mBuf1->b_datap->db_base), (size_t)(sizeof(SsMsgInfo)));
   SMemCpy((Void *) (mBuf1->b_datap->db_base), (Void *) (mBuf2->b_datap->db_base), (size_t)(sizeof(SsMsgInfo)));
   SMemCpy((Void *) (mBuf2->b_datap->db_base), (Void *) minfop, (size_t)(sizeof(SsMsgInfo)));

   RETVALUE(ROK);
}



/********************************************************************30**
 
         End of file:     ss_msg.c@@/main/TeNB_Main_BR/1 - Thu Jan  2 22:33:18 2014
 
*********************************************************************31*/
 
 
/********************************************************************40**
 
        Notes:
 
*********************************************************************41*/
 
/********************************************************************50**
 
*********************************************************************51*/
 
 
/********************************************************************60**
 
        Revision history:
 
*********************************************************************61*/

/********************************************************************90**
 
     ver       pat    init                  description
------------ -------- ---- ----------------------------------------------
1.1          ---      sn   1. initial release
  
1.2          ---      kr   1. added SGetBufRegionPool call
             ---      bsr  2. A null destination buffer is allowed in 
                              SRemPreMsgMult and SRemPstMsgMult

1.3          ---      kp   1. Bug fix to SAddPreMsgMult() and
                              SAddPstMsgMult()

1.3+         ss001.21 kp   1. Bug fix to SSegMsg() when index is in the
                              last/only message block
             ---      jn   2. Included Macros "SMemCpy" & "SMemSet"
                              for Multiple Byte copy in functions:
                              SAddPstMsgMult, SGetPstMsgMult,
                              SRemPreMsgMult, SCpyMsgFix,
                              SCpyMsgMsg, SCompressMsg.
             ---      jn   3. Changed usage of VOID to Void  for the above
                              changes
             ss004.21 ada  4. Added SAlignDBuf (new System Service 
                              function) to align read and write pointers
                              of data buffer to any boundary
             ss006.13  jn  5. Removed compile warning for SS_RELEASE_SEMA.
             ss008.13  jn  6. Changed the U32 pointer type cast to PTR
                              for 64bit C++ compilation. Also removed 
                              compiler warnings.
             ss012.13  jn  7. Added the functionality that SS_M_PROTO
                              block would be allocated from the specified
                              region if SS_M_PROTO_REGION is enabled.
                              i.e. irrespective of the OUTBOARD flag being 
                              enabled the control blocks i.e. the M_PROTO blocks
                              and the Mblk and Dblk for DBufs will be allocated
                              from the specified region. 
             ss014.13  jn  8. The variable offset was not initialized in the 
                              functions - SAddPreMsgMult and SAddPstMsgMult.
             ss015.13 bdu  9. fixed a bug in SCatMsg and SPrntMsg. 
             ss016.13 zo  10. Modified the SGetMsg, SPutDBuf, SUpdMsg to support 
                              functions to convert STREAMS message to netBufLib 
                              message and viceversa.
                      bdu 11. Fixed a memory leak problem in SCpyMsgMsg
                              and SAddMsgRef
             ss018.13  bp 12. Fixed a memory leak in SPrntMsg
                              Re-implemented function
            ss020.103 bjp 13. Fixed bug in SCpyFixMsg
	    ss021.103 bjp 14. Added checking of return value for SFree
	                         in SPutDBuf and SPutMsg
			      Initialize and next to NULLP in SGetMsg
			      Validate region for SPutSMem, SGetMsg, and SGetDBuf
			      Validate region for SCpyMsgMsg
			      Added test for exceeding max length of message
			         in SCpyFixMsg and SCatMsg
			      Added test if buffers are the same in SCatMsg
			      Added test for dst data pointer in SRemPstMsgMult
			      Added test for max message length in SAddPreMsg
                              Added SSwapMsg function
			      Modification to check parameters for SGetDataTx
            ss022.103 bjp 15. Removed test for NULL data pointer in SRemPstMsgMult
	                      and SRemPreMsgMult
            ss023.103 bjp 16. Bug fix in SRemPreMsgMult
	    ss024.103 bjp 17. Addition for memory calulator tool
	                      Bug fix in SPrntMsg
       ss027.103 bjp 18. Modification to fix bug in SGetPstMsgMult 
       ss028.103 bjp  1. Addition of lock for mBuf reference count
       ss029.103 kkj  1. ESS modified
1.3+   ss036.103 vk   1. Changes for SSI enhancements
1.3+   ss037.103 gs   1. Changes for SSI enhancements guarded under 
						 SS_PERF
/main/4      ---      rp   1. SSI enhancements for Multi-core architecture
                         support
*********************************************************************91*/



