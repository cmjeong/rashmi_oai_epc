<?php



$source;
$header;
$interface;


// function called from fsmc script
function GenerateJava( )
{
  global $source, $header, $interface;
  global $fsmComponent;
  global $fsmStates, $fsmOverloadableMethods;

  /*
  print("===================== FSM States ================================\n");
  print_r($fsmStates);
  print("===================== FSM Overloadable Methods ================================\n");
  print_r($fsmOverloadableMethods);
  print("====================================================\n");
  */

	// Write the output files...
	generateFsmJavaClass( $header );
	generateInterfaceJava( $interface );
}

// function called from fsmc script
function writeFsmJavaClassCallBaseExitStatement( $file, $spacePrefix)
{
  fwrite( $file, $spacePrefix . "m_fsm.m_state.exit();\n");
}

function writeFsmJavaClassCallStateEntryStatement( $file, $spacePrefix, $entryStateName)
{
  fwrite( $file, $spacePrefix . "m_fsm." . fsmUtilConvertToAttributeName($entryStateName) . ".entry();\n");
}

function parseFileStatementBasenameJava( &$statement, &$featureList )
{                      
  addParameterisedFeature( $statement, $featureList );

  global $source, $header, $interface, $argv;

//  if(! $source = fopen( fsmDotCppJava(), 'w' ))
//  {
//    die( "Cannot create file " . fsmDotCppJava() );
//  }

  if(! $header = fopen( fsmGetJavaFileName(), 'w' ))
  {
    die( "Cannot create file " . fsmGetJavaFileName() );
  }

  if(! $interface = fopen( interfaceDotHJava(), 'w' ))
  {
    die( "Cannot create file " . interfaceDotHJava() );
  }
  global $fsmFeatureList;

}

// function called from fsmc script
function parseFileStatementFsmJava( &$statement, &$featureList )
{
  addParameterisedFeature( $statement, $featureList );
}

//
// Local functions used only within this script only
//

//
// Should be encapsulated within a class so that name collisions can be avoided 
// in a better way that it is done below.
//

function writeJavaPackageName($file)
{
  global $fsmFeatureList;

  $namespace = $fsmFeatureList["namespace"];

  if( $namespace )
  {
    fwrite( $file, "package " . $namespace . ";\n");
    fwrite( $file, "\n");
  }
  else
  {
    error( "Package name", "Package name must be specifed for Java in the input file." );
  }
}


function writeFsmJavaClassEventNames( $file )
{
    global $fsmComponent;

    fwrite( $file, "    private final static String[] m_eventName = {\n");

    foreach( $fsmComponent as $event => $type )
    {
        if($type == "event")
        {
            fwrite( $file, "        \"" . $event . "\",\n");
        }
    }
    fwrite( $file, "    };\n");
    fwrite( $file, "\n");
}


function writeFsmJavaClassEventGuardConditionAndAction( $file, &$state, &$reaction )
{
  // print("writeFsmJavaClassEventGuardConditionAndAction()\n");

  if($reaction->_guard_condition)
  {
    // print("guardCondition: $reaction->_guard_condition\n");

    fwrite( $file, "            // Guard condition\n");
    //BookMark A: Action function with guard condition
    fwrite( $file, "            if (m_fsm.m_fsmInterface." . fsmUtilConvertToMethodName($reaction->_guard_condition) . "(eventData)) {\n");
    fwrite( $file, "                if (m_fsm.m_fsmTraceLevel >= TRACE_LEVEL_TRACE_EVENTS_CONDITIONS_ACTIONS_AND_STATE_TRANSITIONS) {\n");
    fwrite( $file, "                    // TRACE_PRINTF(\"%s.%d: " . fsmUtilConvertToMethodName($reaction->_guard_condition) . "? (true).\", m_fsm.m_name, m_fsm.m_eventCounter );\n");
    fwrite( $file, "                    String msg = String.format(\"%s.%d: " . fsmUtilConvertToMethodName($reaction->_guard_condition) . "? (true).%n\", m_fsm.m_name, m_fsm.m_eventCounter);\n");
    fwrite( $file, "                    m_log.finest(msg);\n");
    fwrite( $file, "                }\n");
    fwrite( $file, "\n");
  }
  else
  {
    // BookMark C: This open brace is sometimes superfluous!
    fwrite( $file, "            { // This open brace is sometimes superfluous! \n");
  }

  writeStateExit( $file, $state, $reaction, "                " );

  if($reaction->_action)
  {
    global $fsmActionResults;

    // print("reation=>action: $reaction->_action\n");

    fwrite( $file, "                if (m_fsm.m_fsmTraceLevel >= TRACE_LEVEL_TRACE_EVENTS_ACTIONS_AND_STATE_TRANSITIONS) {\n");
    fwrite( $file, "                    // TRACE_PRINTF(\"%s.%d: Do " . fsmUtilConvertToMethodName($reaction->_action) . " \", m_fsm.m_name, m_fsm.m_eventCounter );\n");
    fwrite( $file, "                    String msg = String.format(\"%s.%d: Do " . fsmUtilConvertToMethodName($reaction->_action) . " %n\", m_fsm.m_name, m_fsm.m_eventCounter);\n");
    fwrite( $file, "                    m_log.finest(msg);\n");
    fwrite( $file, "                }\n");
    fwrite( $file, "\n");

    if( count($fsmActionResults[$reaction->_action]) > 1 )
    {
      fwrite( $file, "                switch (m_fsm.m_fsmInterface." . fsmUtilConvertToMethodName($reaction->_action) . "(eventData)) {\n");

      foreach( $reaction->_outcome as $outcome => $nextState )
      {
        fwrite( $file, "                case " . fsmUtilsCreateActionOutcomeIdName($reaction->_action, $outcome) . ":\n");
        fwrite( $file, "                    if (m_fsm.m_fsmTraceLevel >= TRACE_LEVEL_TRACE_EVENTS_ACTIONS_AND_STATE_TRANSITIONS) {\n");
        fwrite( $file, "                        // TRACE_PRINTF(\"%s.%d: " . fsmUtilConvertToClassName($reaction->_action) . "=" . $outcome . " \", m_fsm.m_name, m_fsm.m_eventCounter);\n");
        fwrite( $file, "                        String msg = String.format(\"%s.%d: " . fsmUtilConvertToClassName($reaction->_action) . "=" . $outcome . " %n\", m_fsm.m_name, m_fsm.m_eventCounter);\n");
        fwrite( $file, "                        m_log.finest(msg);\n");
        fwrite( $file, "                    }\n");
        fwrite( $file, "\n");

        writeStateTransitionAfterAction(  $file, $state, $reaction, $outcome, "                    " );

        fwrite( $file, "                break;\n");
      }
      // close brace for switch statement.
      fwrite( $file, "                default:\n");
      fwrite( $file, "                    m_log.warning(\"ASSERT  - unknown Outcom code from the action function! \");\n");
      fwrite( $file, "                    break;\n");
      fwrite( $file, "                } // end of switch \n");
    }
    else
    {
      fwrite( $file, "                m_fsm.m_fsmInterface." . fsmUtilConvertToMethodName($reaction->_action) . "(eventData);\n");
      fwrite( $file, "\n");
      writeStateTransitionAfterAction(  $file, $state, $reaction, $reaction->_action[0], "SUCCESS", "                " );
    }
  }
  else
  {
      writeStateEntry( $file, $state, $reaction, "                " );
  }
  // BookMark B: This matches with BookMark A.  Close brace for open brace at BookMark A and BookMark C.
  fwrite( $file, "            }  // end of guard condition block (or sometimes this close brace is superfluous!) \n");
}

function  writeFsmJavaClassStateEventMethodBody( $file, &$state, $eventName )
{
    $handlerState = getStateThatHandlesEventJava( $state, $eventName );
    // print("State: $state->_name eventName: $eventName handlerState: $handlerState->_name\n");


    if( $handlerState->_eventList[$eventName]->_defer )
    {
	      fwrite( $file, "            // - Deferred-\n");
    }
    else
    {
	      while( !$handlerState->_eventList[$eventName]->_unConditionalParsed )
	      {
	          foreach( $handlerState->_eventList[$eventName]->_reaction as $idx => $reaction )
	          {
	              writeFsmJavaClassEventGuardConditionAndAction( $file, $state, $reaction );
	              fwrite( $file, "            else\n");
		        }
	          $handlerState = getAncestorStateThatHandlesEventJava( $handlerState, $eventName );
        }
	
        foreach( $handlerState->_eventList[$eventName]->_reaction as $idx => $reaction )
        {
            writeFsmJavaClassEventGuardConditionAndAction( $file, $state, $reaction );
        
            if($reaction->_guard_condition)
            {
                fwrite( $file, "            else // no guard condition (or begining of another guard condition!) \n");
            }
        }
    }
}

function writeFsmJavaClassStateEventMethods( $file, &$state)
{
  global $fsmComponent;

  foreach( $fsmComponent as $eventName => $componentType )
  {
    if($componentType == "event")
    {
      fwrite( $file, "        public void " . fsmUtilConvertToMethodName($eventName) . "(Object eventData) {\n");
      writeFsmJavaClassStateEventMethodBody( $file, $state, $eventName );
      fwrite( $file, "        }\n");
      fwrite( $file, "\n");
    }
  }
}

function writeFsmJavaClassStateEntryMethod( $file, &$state )
{
    fwrite( $file, "        public void entry() {\n");

    $superstateName = getSuperstateName( $state->_name );

    if( $superstateName )
    {
        fwrite( $file, "            // RSYS_ASSERT(m_fsm.m_state == m_fsm." . fsmUtilConvertToAttributeName($superstateName) . ");\n");
    }
    else
    {
        fwrite( $file, "            // RSYS_ASSERT(m_fsm.m_state == null);\n");
    }
    fwrite( $file, "\n");

    // Trace output
    fwrite( $file, "            if (m_fsm.m_fsmTraceLevel >= TRACE_LEVEL_TRACE_EVENTS_AND_STATE_TRANSITIONS) {\n");
    fwrite( $file, "                // TRACE_PRINTF(\"%s.%d: %s (entry) \", m_fsm.m_name, m_fsm.m_eventCounter, m_fsm.m_state.m_name);\n");
    fwrite( $file, "                String msg = String.format(\"%s.%d: %s (entry) %n\", m_fsm.m_name, m_fsm.m_eventCounter, m_name);\n");
    fwrite( $file, "                m_log.finer(msg);\n");
    fwrite( $file, "            }\n");
    fwrite( $file, "\n");

    if( $state->_featureList["entry"] )
    {
        fwrite( $file, "            m_fsm.m_fsmInterface." . fsmUtilCreateEntryMethodName($state->_name) . "();\n");
        fwrite( $file, "\n");
    }

    fwrite( $file, "            m_fsm.m_state = m_fsm." . fsmUtilConvertToAttributeName($state->_name) . ";\n");
    fwrite( $file, "\n");

    fwrite( $file, "        }\n");
    fwrite( $file, "\n");
}

//       
function writeFsmJavaClassStateExitMethod( $file, &$state)
{
    fwrite( $file, "        public void exit() {\n");

    fwrite( $file, "            // RSYS_ASSERT( m_fsm.m_state == m_fsm." . fsmUtilConvertToAttributeName($state->_name) . ");\n");
    fwrite( $file, "\n");

//    fwrite( $file, "\n");

    fwrite( $file, "            if (m_fsm.m_fsmTraceLevel >= TRACE_LEVEL_TRACE_EVENTS_AND_STATE_TRANSITIONS) {\n");
    fwrite( $file, "                // TRACE_PRINTF(\"%s.%d: %s (exit) \", m_fsm.m_name, m_fsm.m_eventCounter, m_fsm.m_state.m_name);\n");
    fwrite( $file, "                String msg = String.format(\"%s.%d: %s (exit) %n\", m_fsm.m_name, m_fsm.m_eventCounter, m_name);\n");
    fwrite( $file, "                m_log.finer(msg);\n");
    fwrite( $file, "            }\n");

    if( $state->_featureList["exit"] )
    {
        fwrite( $file, "            m_fsm.m_fsmInterface." . fsmUtilCreateExitMethodName($state->_name) . "();\n");
        fwrite( $file, "\n");
    }

    $superstateName = getSuperstateName( $state->_name );

    if( $superstateName )
    {
        fwrite( $file, "            m_fsm.m_state = m_fsm." . fsmUtilConvertToAttributeName($superstateName) . ";\n");
    }
    else
    {
        fwrite( $file, "            m_fsm.m_state = null;\n");
    }

    fwrite( $file, "        }\n");
    fwrite( $file, "\n");
}

function writeFsmJavaClassStateDeferEventCaseStatements( $file, &$state, $eventName )
{
    $handlerState = getStateThatHandlesEventJava( $state, $eventName );

    if( $handlerState->_eventList[$eventName]->_defer )
    {
        fwrite( $file, "            case " . fsmUtilCreateEventIdName($eventName) . ":\n");
        fwrite( $file, "                return true;\n");
        fwrite( $file, "\n");
    }

}

//       
function writeFsmJavaClassStateDeferEventMethod( $file, &$state)
{
    global $fsmComponent;
    
    fwrite( $file, "        public boolean deferEvent(int eventId) {\n");
    fwrite( $file, "            switch (eventId) {\n");
    foreach( $fsmComponent as $eventName => $type )
    {
      if($type == "event")
      {
        writeFsmJavaClassStateDeferEventCaseStatements( $file, $state, $eventName );
      }
    }
    fwrite( $file, "            default:\n");
    fwrite( $file, "                return false;\n");
    fwrite( $file, "            }\n");
    fwrite( $file, "        }\n");
    fwrite( $file, "\n");
}


function writeFsmJavaClassIntro( $file )
{
  global $fsmComponent, $fsmFeatureList, $argv, $argv;

  fwrite( $file, "///////////////////////////////////////////////////////////////////////////////\n");
  fwrite( $file, "//\n");
  fwrite( $file, "// " .  fsmGetJavaFileName() . "\n");
  fwrite( $file, "//\n");
  fwrite( $file, "// Autogenerated using " . $argv[0] . " from " . $argv[1] . " " . $argv[2] . "\n");
  fwrite( $file, "//\n");
  fwrite( $file, "// See header file for documentation.\n");
  fwrite( $file, "//\n");
  fwrite( $file, "// Copyright Radisys Limited\n");
  fwrite( $file, "//\n");
  fwrite( $file, "///////////////////////////////////////////////////////////////////////////////\n");
  fwrite( $file, "\n");

  writeJavaPackageName($file);

  fwrite( $file, "import java.util.LinkedList;\n");
  fwrite( $file, "import java.util.logging.Logger;\n");

  fwrite( $file, "\n");

}


function writeFsmJavaClassTraceConstants( $file )
{
    fwrite( $file, "    // Constants to control TRACE output.\n");
    fwrite( $file, "    public final static int TRACE_LEVEL_TRACE_OFF = 0;\n");
    fwrite( $file, "    public final static int TRACE_LEVEL_TRACE_EVENTS = 1;\n");
    fwrite( $file, "    public final static int TRACE_LEVEL_TRACE_EVENTS_AND_STATE_TRANSITIONS = 2;\n");
    fwrite( $file, "    public final static int TRACE_LEVEL_TRACE_EVENTS_ACTIONS_AND_STATE_TRANSITIONS = 3;\n");
    fwrite( $file, "    public final static int TRACE_LEVEL_TRACE_EVENTS_CONDITIONS_ACTIONS_AND_STATE_TRANSITIONS = 4;\n");
    fwrite( $file, "    public final static int TRACE_LEVEL_TRACE_ALL = 5;\n");
    fwrite( $file, "\n");
}


function writeFsmJavaClassEventIdConstants( $file )
{
    global $fsmComponent;

    $eventIdConstant = 0;
    foreach( $fsmComponent as $event => $type )
    {
        if($type == "event")
        {
          fwrite( $file, "    private final static int " . fsmUtilCreateEventIdName($event) . " = " . $eventIdConstant . ";\n");
          $eventIdConstant++;
        }
    }

    fwrite( $file, "    private final static int EVENT_ID_FSM_NUMBER_OF_INJECTABLE_EVENTS = " . $eventIdConstant . ";\n");
    fwrite( $file, "\n");        
}

function writeFsmJavaClassQueuedClass( $file )
{
    fwrite( $file, "    // Class encapsulating queued FSM events.\n");
    fwrite( $file, "    private class QueuedFsmEvent {\n");
    fwrite( $file, "        int m_eventId;\n");
    fwrite( $file, "        Object m_eventData;\n");
    fwrite( $file, "\n");
    fwrite( $file, "        public QueuedFsmEvent(int eventId, Object eventData) {\n");
    fwrite( $file, "            m_eventId = eventId;\n");
    fwrite( $file, "            m_eventData = eventData;\n");
    fwrite( $file, "        }\n");
    fwrite( $file, "    }\n");
    fwrite( $file, "\n");
}

function writeFsmJavaClassWriteStateMembers( $file, &$statesList, $state )
{
	if($statesList[$state] != "done")
	{
		$statesList[$state] = "done";

		global $fsmSuperstates;
		
    foreach($fsmSuperstates as $substate => $superstate)
    {
      if($superstate = $state) 
      {
        writeFsmJavaClassWriteStateMembers( $file, $statesList, $substate );
      }
		}
		
    fwrite( $file, "    private " . fsmUtilConvertToClassName($state) . " " . fsmUtilConvertToAttributeName($state) . ";\n");
	}
}

function writeFsmJavaClassAttributes( $file )
{
  global $fsmStates, $fsmSuperstates;

  fwrite( $file, "    //FSM class attributes.\n");

	$statesList = array();;

	foreach( $fsmStates as $key => $state )
	{
		if($key)
		{
			$statesList[$key] = $key;
		}
	}

 	$superstates = $fsmSuperstates;
  
	foreach( $statesList as $key => $state )
	{
	  writeFsmJavaClassWriteStateMembers( $file, $statesList, $state );
	}

  fwrite( $file, "    private State m_state;\n");
  fwrite( $file, "    private " . fsmInterfaceClassJava() . " m_fsmInterface;\n");
  fwrite( $file, "    private String m_name;\n");
  fwrite( $file, "    private LinkedList <QueuedFsmEvent> m_fsmEventQueue;\n");
  fwrite( $file, "    private boolean m_fsmInjectInProgress;\n");
  fwrite( $file, "    private int m_fsmTraceLevel;\n");
  fwrite( $file, "    private int m_eventCounter;\n");
  fwrite( $file, "    private Logger m_log;\n");
}

function writeFsmJavaClassConstructorConstructStates( $file, &$statesList, $state)
{
	if($statesList[$state] != "done")
	{
		echo "writeFsmJavaClassConstructorConstructStates" . $state . "\n";

		$statesList[$state] = "done";

		global $fsmSuperstates;
		
    foreach($fsmSuperstates as $substate => $superstate)
    {
      if($superstate = $state) 
      {
        writeFsmJavaClassConstructorConstructStates( $file, $statesList, $substate );
      }
		}
		
		global $fsmComponent, $fsmStates;
		
    if($fsmComponent[$state] == "superstate")
		{
      global $fsmStates;
		    
			if($fsmStates[$state]->_featureList[initial_state])
			{
//				fwrite( $file, "==>    m" . $state . "(*this, &m" . $fsmStates[$state]->_featureList[initial_state] . "), <=====\n");
        fwrite( $file, "        " . fsmUtilConvertToAttributeName($state) . " = new " . fsmUtilConvertToClassName($state) . "(this, " . fsmUtilConvertToAttributeName($fsmStates[$state]->_featureList[initial_state]) . ");\n");
			}
			else
			{
        fwrite( $file, "        " . fsmUtilConvertToAttributeName($state) . " = new " . fsmUtilConvertToClassName($state) . "(this, null);\n");
			}
    }
    else
    {
        fwrite( $file, "        " . fsmUtilConvertToAttributeName($state) . " = new " . fsmUtilConvertToClassName($state) . "(this);\n");
    }
	}
}

function writeFsmJavaClassConstructor( $file )
{
    global $fsmStates;
    fwrite( $file, "    public " . fsmClassJava() . " (" . fsmInterfaceClassJava() . " interfaceClass,\n");
    fwrite( $file, "            int traceLevel,\n");
    fwrite( $file, "            String name,\n");
    fwrite( $file, "            Logger logger) {\n");
    fwrite( $file, "        // Initialise attributes.\n");
    fwrite( $file, "        m_fsmInterface = interfaceClass;\n");
    fwrite( $file, "        m_fsmTraceLevel = traceLevel;\n");
    fwrite( $file, "        m_log = logger;\n");
    fwrite( $file, "        m_fsmEventQueue = new LinkedList <QueuedFsmEvent>();\n");
    fwrite( $file, "        m_fsmInjectInProgress = false;\n");
    fwrite( $file, "        m_eventCounter = 0;\n");
    fwrite( $file, "        \n"); 
    fwrite( $file, "        if (name == null) {\n");
    fwrite( $file, "            m_name = new String(\"" . fsmClassJava() . "\");\n");
    fwrite( $file, "        } else {\n");
    fwrite( $file, "            m_name = name;\n");
    fwrite( $file, "        }\n");
    fwrite( $file, "        // Initialise state factory \n"); 

	  $statesList = array();;

    foreach( $fsmStates as $key => $state )
    {
      if($key)
      {
        $statesList[$key] = $key;
      }
    }

  	$superstates = $fsmSuperstates;
  
    foreach( $statesList as $key => $state )
    {
      writeFsmJavaClassConstructorConstructStates( $file, $statesList, $state );
    }

    global $fsmFeatureList;

    $initial_state = $fsmFeatureList["initial_state"];

    if( $initial_state )
    {
      fwrite( $file, "        // Initial state\n");
      fwrite( $file, "        m_state = null;\n");

	    $statesToEnter = stateNestedDepth( "", $initial_state );

	    while($statesToEnter-- > 0)
	    {
	      $entryStateName = ancestorStateName( $initial_state, $statesToEnter );
	
        fwrite( $file, "        " . fsmUtilConvertToAttributeName($entryStateName) . ".entry();\n");
	    }
    }
    else
    {
      error( "EOF", "No initial_state specified for FSM." );
    }

    fwrite( $file, "\n");
    fwrite( $file, "    } \n");
}

function writeFsmJavaClassEventInjectMethods( $file )
{
    global $fsmComponent, $fsmEventTypes;

    foreach( $fsmComponent as $eventName => $type )
    {
        if($type == "event")
        {
            fwrite( $file, "    // Use this method to inject event: " . fsmUtilCreateEventIdName($eventName) . " into the FSM\n");
            fwrite( $file, "    public void " . fsmUtilConvertToMethodName($eventName) . "(Object eventData) {\n");
            fwrite( $file, "        enqueue(" . fsmUtilCreateEventIdName($eventName) . ", eventData);\n");
            fwrite( $file, "    }\n\n");
        }
    }
}

function writeFsmJavaClassTraceEnableMethod( $file )
{
    fwrite( $file, "    public void setFsmTraceEnable(final int traceLevel) {\n");
    fwrite( $file, "        m_fsmTraceLevel = traceLevel;\n");
    fwrite( $file, "    }\n");
    fwrite( $file, "\n");        
}

function writeFsmJavaClassEnqueueMethod( $file )
{
    fwrite( $file, "    private void enqueue(final int eventId, Object eventData) {\n");
    fwrite( $file, "        // RSYS_ASSERT(eventId < NUMBER_OF_INJECTABLE_EVENTS);\n");
    fwrite( $file, "\n");
    fwrite( $file, "        // Reentrancy Protection is NOT intended to make thread-safe\n");
    fwrite( $file, "        \n");
    fwrite( $file, "        m_fsmEventQueue.addLast(new QueuedFsmEvent(eventId, eventData));\n");
    fwrite( $file, "        if (!m_fsmInjectInProgress) {\n");
    fwrite( $file, "            m_fsmInjectInProgress = true;\n");
    fwrite( $file, "\n");
    fwrite( $file, "            while (!m_fsmEventQueue.isEmpty()) {\n");
    fwrite( $file, "                QueuedFsmEvent queuedEvent = m_fsmEventQueue.removeFirst();\n");
    fwrite( $file, "\n");
    fwrite( $file, "                // ASSERT(event != null);\n");
    fwrite( $file, "                // ASSERT(m_state != null);\n");
    fwrite( $file, "\n");
    fwrite( $file, "                int queuedEventId = queuedEvent.m_eventId;\n");
    fwrite( $file, "\n");
    fwrite( $file, "                // We should only be in a state that is SimpleState.  Other \n");
    fwrite( $file, "                // states such as SuperState and Junction are transient states\n");
    fwrite( $file, "                // once the state transition is completed we should be in a \n");
    fwrite( $file, "                // SimpleState if not this is an error.\n");
    fwrite( $file, "\n");
    fwrite( $file, "                if (m_state instanceof SimpleState) {\n");
    fwrite( $file, "                    SimpleState simpleState = (SimpleState)m_state;\n");
    fwrite( $file, "\n");
    fwrite( $file, "                    if (simpleState.deferEvent(queuedEventId)) {\n");
    fwrite( $file, "                        // defer event\n");
    fwrite( $file, "                        if (m_fsmTraceLevel  >= TRACE_LEVEL_TRACE_EVENTS) {\n");
    fwrite( $file, "                            // TRACE_PRINTF((\"%s: %s (%s deferred)\", m_name, m_state.m_name, m_eventName[queuedEventId] ));\n");
    fwrite( $file, "                            String msg = String.format(\"%s: %s (%s deferred)%n\", m_name, m_state.m_name, m_eventName[queuedEventId]);\n");
    fwrite( $file, "                            m_log.fine(msg);\n");
    fwrite( $file, "                        }\n");
    fwrite( $file, "                    } else {\n");
    fwrite( $file, "                        ++m_eventCounter;\n");
    fwrite( $file, "                        if (m_fsmTraceLevel >= TRACE_LEVEL_TRACE_EVENTS) { \n");
    fwrite( $file, "                            // TRACE_PRINTF((\"%s.%d: %s <--(%s)-- \", m_name, m_eventCounter, m_state.m_name, m_eventName[queuedEventId])); \n");
    fwrite( $file, "                            String msg = String.format(\"%s.%d: %s <--(%s)-- %n\", m_name, m_eventCounter, m_state.m_name, m_eventName[queuedEventId]);\n");
    fwrite( $file, "                            m_log.fine(msg);\n");
    fwrite( $file, "                        }\n");
    fwrite( $file, "\n");
    fwrite( $file, "                        // inject the event\n");
    fwrite( $file, "                        simpleState.inject(queuedEventId, queuedEvent.m_eventData);\n");
    fwrite( $file, "\n");

    fwrite( $file, "                        while (m_state.m_initialState != null) {\n");
    fwrite( $file, "                            m_state.m_initialState.entry();\n");
    fwrite( $file, "                        }\n");

    fwrite( $file, "                        // ASSERT(m_state != null);\n");
    fwrite( $file, "                    }\n");
    fwrite( $file, "                } else {\n");
    fwrite( $file, "                    // Error.  m_state is NOT an instance of SimpleState!\n");
    fwrite( $file, "                    assert false;\n");
    fwrite( $file, "                }\n");
    fwrite( $file, "            }\n");
    fwrite( $file, "            m_fsmInjectInProgress = false;\n");
    fwrite( $file, "        } else {\n");
    fwrite( $file, "            // event has been queued!\n");
    fwrite( $file, "            if (m_fsmTraceLevel >= TRACE_LEVEL_TRACE_EVENTS ) {\n");
    fwrite( $file, "                // TRACE_PRINTF((\"%s: (%s enqueued)\", m_name, m_eventName[eventId])); \n");
    fwrite( $file, "                String msg = String.format(\"%s: (%s enqueued)%n\", m_name, m_eventName[eventId]);\n");
    fwrite( $file, "                m_log.fine(msg);\n");
    fwrite( $file, "            }\n");
    fwrite( $file, "        }\n");
    fwrite( $file, "    }\n");
    fwrite( $file, "\n");
}

function writeFsmJavaClassStateBaseClass( $file )
{
    global $fsmComponent, $fsmEventTypes;
    // base class declaration
    fwrite( $file, "    // Base class for Junction and SuperState. \n");
    fwrite( $file, "    private abstract class State {\n");
    fwrite( $file, "\n");
    // base class attributes
    fwrite( $file, "        public " . fsmClassJava() . " m_fsm;\n");
    fwrite( $file, "        public String m_name;\n");
    fwrite( $file, "        public State m_initialState;\n");
    fwrite( $file, "\n");
    // base class constructor
    fwrite( $file, "        public State(" . fsmClassJava() . " fsm, String name, State initialState) {\n");
    fwrite( $file, "            m_fsm = fsm;\n");
    fwrite( $file, "            m_name = name;\n");
    fwrite( $file, "            m_initialState = initialState;\n");
    fwrite( $file, "        }\n"); 
    fwrite( $file, "\n");
    // base class abstract methods
    fwrite( $file, "        public abstract void entry();\n");
    fwrite( $file, "        public abstract void exit();\n");
    fwrite( $file, "\n");

    fwrite( $file, "    }\n");
    fwrite( $file, "\n");
}



function writeFsmJavaClassSuperStateBaseClass( $file )
{
    global $fsmComponent, $fsmEventTypes;

    // base class declaration
    fwrite( $file, "    // Base class for all super states.\n");
    fwrite( $file, "    private abstract class SuperState extends State {\n");
    // base class constructor
    fwrite( $file, "        public SuperState(" . fsmClassJava() . " fsm, String name, State initialState) {\n");
    fwrite( $file, "            super(fsm, name, initialState);\n");
    fwrite( $file, "        }\n");
    // base class methods
    fwrite( $file, "        public abstract void entry();\n");
    fwrite( $file, "        public abstract void exit();\n");
    fwrite( $file, "\n");
    fwrite( $file, "    }\n");
    fwrite( $file, "\n");
}

function writeFsmJavaClassSimpleStateBaseClass( $file )
{
    global $fsmComponent, $fsmEventTypes;

    fwrite( $file, "    // SimpleState, base class for all simple states.\n");
    fwrite( $file, "    private abstract class SimpleState extends State implements EventsInterface {\n");
    fwrite( $file, "        public SimpleState(" . fsmClassJava() . " fsm, String name) {\n");
    fwrite( $file, "            super(fsm, name, null);\n");
    fwrite( $file, "        }\n");

    // Event injection method
    fwrite( $file, "        public void inject(int eventId, Object eventData) {\n");
    fwrite( $file, "            // RSYS_ASSERT(eventId < NUMBER_OF_INJECTABLE_EVENTS);\n");
    fwrite( $file, "            switch(eventId) {\n");

    foreach( $fsmComponent as $event => $typeOfComponent )
    {
      if($typeOfComponent == "event")
      {
        $c_type = $fsmEventTypes[$event];
        $c_typeToken = stringToToken($c_type);
        $fsmEventClass = "FsmEvent_" . $c_typeToken;
        $fsmTypeEnum = "FSM_EVENT_TYPE_" . $c_typeToken;

        fwrite( $file, "            case " . fsmUtilCreateEventIdName($event) . ":\n");
        fwrite( $file, "                //Injecting event::" . fsmUtilCreateEventIdName($event) . "\n");
        fwrite( $file, "                " . fsmUtilConvertToMethodName($event) . "(eventData);\n");
        fwrite( $file, "                break;\n");
        fwrite( $file, "\n");
      }
    }
    fwrite( $file, "            default:\n");
    fwrite( $file, "                // RSYS_ASSERT(false);\n");
    fwrite( $file, "                break;\n");

    fwrite( $file, "            }\n");
    fwrite( $file, "        }\n");        
    fwrite( $file, "    }\n");        
    fwrite( $file, "\n");
}

function writeFsmJavaClassJunctionBaseClass( $file )
{
    fwrite( $file, "    // Base class for junctions\n");
    fwrite( $file, "    private abstract class Junction extends State {\n");
    fwrite( $file, "        public Junction(" . fsmClassJava() . " fsm, String name) {\n");
    fwrite( $file, "            super(fsm, name, null);\n");
    fwrite( $file, "        }\n");
    fwrite( $file, "    }\n");
    fwrite( $file, "\n");
}

function writeFsmJavaClassEventsInterfaceClass( $file )
{
    global $fsmComponent, $fsmEventTypes;

    fwrite( $file, "    // Events interface\n");
    fwrite( $file, "    private interface EventsInterface {\n");
    fwrite( $file, "        boolean deferEvent(int eventId);\n");

    // for each event write the event injection method
    fwrite( $file, "        // Event injection methods.\n");
    foreach( $fsmComponent as $event => $type )
    {
        if($type == "event")
        {
     	 	$eventType = $fsmEventTypes[$event];
            fwrite( $file, "        void " . fsmUtilConvertToMethodName($event) . "(Object eventData);\n");
        }
    }
    fwrite( $file, "    }\n");
    fwrite( $file, "\n");
}


function writeFsmJavaClassConcreteStateClass( $file, &$state )
{
    global $fsmComponent, $fsmEventTypes;

    // class declaration
    fwrite( $file, "    // Concrete state - ". fsmUtilConvertToClassName($state->_name) . "\n");
    fwrite( $file, "    private class " . fsmUtilConvertToClassName($state->_name) . " extends SimpleState {\n");
    // constructor
    fwrite( $file, "        public " . fsmUtilConvertToClassName($state->_name) . "(" . fsmClassJava() . " fsm) {\n");
    fwrite( $file, "            super(fsm, new String(\"" . fsmUtilConvertToClassName($state->_name) . "\"));\n");
    fwrite( $file, "        }\n");
    fwrite( $file, "\n");
    // entry method
    writeFsmJavaClassStateEntryMethod( $file, $state);
    fwrite( $file, "\n");
    // exit method
    writeFsmJavaClassStateExitMethod( $file, $state);
    fwrite( $file, "\n");        
    // defer event method
    writeFsmJavaClassStateDeferEventMethod( $file, $state);
    fwrite( $file, "\n");

    // concrete event injection methods
    fwrite( $file, "        // Concrete event injection methods.\n");
    writeFsmJavaClassStateEventMethods( $file, $state);
    fwrite( $file, "    }\n");
    fwrite( $file, "\n");
}

function writeFsmJavaClassConcreteStateClasses( $file )
{
    global $fsmComponent;

    // print("writeFsmJavaClassConcreteStateClasses()\n");
    foreach( $fsmComponent as $stateName => $type )
    {
        if($type == "state")
        {
            $state = getStateFromName($stateName);

            writeFsmJavaClassConcreteStateClass( $file, $state );
        }
    }
}

function writeFsmJavaClassConcreteSuperStateClass( $file, &$state )
{
    global $fsmComponent;

    fwrite( $file, "    // Concrete super states - ". fsmUtilConvertToClassName($state->_name) . "\n");
    fwrite( $file, "    private class " . fsmUtilConvertToClassName($state->_name) . " extends SuperState {\n");
    fwrite( $file, "        public " . fsmUtilConvertToClassName($state->_name) . "(" . fsmClassJava() . " fsm, State initialState) {\n");
    fwrite( $file, "            super(fsm, new String(\"" . fsmUtilConvertToClassName($state->_name) . "\"), initialState);\n");
    fwrite( $file, "        }\n");
    fwrite( $file, "\n");
    // Entry method
    writeFsmJavaClassStateEntryMethod( $file, $state);
    fwrite( $file, "\n");
    // Exit method
    writeFsmJavaClassStateExitMethod( $file, $state);
    fwrite( $file, "    }\n");
    fwrite( $file, "\n");
}


function writeFsmJavaClassConcreteSuperStateClasses( $file )
{
    global $fsmComponent;

    foreach( $fsmComponent as $superstateName => $type )
    {
        if($type == "superstate")
        {
            $superstate = getStateFromName($superstateName);

            writeFsmJavaClassConcreteSuperStateClass( $file, $superstate );
        }
    }
}

function writeFsmJavaClassJunctionGuardConditionsCode( $file, &$state, $reaction )
{
    if($reaction->_guard_condition)
    {
      fwrite( $file, "            // Guard condition\n");
      fwrite( $file, "            if (m_fsm.m_fsmInterface." . fsmUtilConvertToMethodName($reaction->_guard_condition) . "()) {\n");
      fwrite( $file, "                if (m_fsm.m_fsmTraceLevel >= TRACE_LEVEL_TRACE_EVENTS_CONDITIONS_ACTIONS_AND_STATE_TRANSITIONS) {\n");
      fwrite( $file, "                    // TRACE_PRINTF(\"%s.%u: " . fsmUtilConvertToMethodName($reaction->_guard_condition) . "? (true).\", m_fsm.m_name, m_fsm.m_eventCounter);\n");
      fwrite( $file, "                    String msg = String.format(\"%s.%d: " . fsmUtilConvertToMethodName($reaction->_guard_condition) . "? (true).\", m_fsm.m_name, m_fsm.m_eventCounter);\n");
      fwrite( $file, "                    m_log.finest(msg);\n");
      fwrite( $file, "                }\n");
      fwrite( $file, "\n");
    }
    else
    {
      fwrite( $file, "            { // This open brace is sometimes superfluous! \n");
    }

    writeStateExit( $file, $state, $reaction, "                " );

    if($reaction->_action)
    {
      global $fsmActionResults;
  
      fwrite( $file, "                if (m_fsm.m_fsmTraceLevel >= TRACE_LEVEL_TRACE_EVENTS_ACTIONS_AND_STATE_TRANSITIONS) { \n");
      fwrite( $file, "                    //TRACE_PRINTF(\"%s.%u: Do " . $reaction->_action . "\", mFsm.mName.c_str(), mFsm.mEventCounter );\n");
      fwrite( $file, "                    String msg = String.format(\"%s.%d: " . fsmUtilConvertToMethodName($reaction->_action) . "\", m_fsm.m_name, m_fsm.m_eventCounter);\n");
      fwrite( $file, "                    m_log.finest(msg);\n");
      fwrite( $file, "                }\n");
      fwrite( $file, "\n");

      if( count($fsmActionResults[$reaction->_action]) > 1 )
      {
        fwrite( $file, "                switch (m_fsm.m_fsmInterface." . fsmUtilConvertToMethodName($reaction->_action) . "()) {\n");

        foreach( $reaction->_outcome as $outcome => $nextState )
        {
          fwrite( $file, "                case " . fsmUtilsCreateActionOutcomeIdName($reaction->_action, $outcome) . ":\n");
          fwrite( $file, "                    if (m_fsm.m_fsmTraceLevel >= TRACE_LEVEL_TRACE_EVENTS_ACTIONS_AND_STATE_TRANSITIONS) {\n");
          fwrite( $file, "                        // TRACE_PRINTF(\"%s.%d: " . fsmUtilConvertToClassName($reaction->_action) . "=" . $outcome . " \", m_fsm.m_name, m_fsm.m_eventCounter);\n");
          fwrite( $file, "                        String msg = String.format(\"%s.%d: " . fsmUtilConvertToClassName($reaction->_action) . "=" . $outcome . " %n\", m_fsm.m_name, m_fsm.m_eventCounter);\n");
          fwrite( $file, "                        m_log.finest(msg);\n");
          fwrite( $file, "                    }\n");
          fwrite( $file, "\n");

          writeStateTransitionAfterAction(  $file, $state, $reaction, $outcome, "                    " );

          fwrite( $file, "                break;\n");
        }
        // close brace for switch statement.
        fwrite( $file, "                default:\n");
        fwrite( $file, "                    m_log.warning(\"ASSERT  - unknown Outcom code from the action function! \");\n");
        fwrite( $file, "                    break;\n");
        fwrite( $file, "                } // end of switch \n");
      }
      else
      {
        fwrite( $file, "        m_fsm.m_fsmInterface." . fsmUtilConvertToMethodName($reaction->_action) . "();\n");
        fwrite( $file, "\n");
        writeStateTransitionAfterAction(  $file, $state, $reaction, $reaction->_action[0], "SUCCESS", "                     " );
      }
    }
    else
    {
      writeStateEntry( $file, $state, $reaction, "                " );
    }
    fwrite( $file, "            }  // end of guard condition block (or sometimes this close brace is superfluous!)\n");

}

function writeFsmJavaClassJunctionEntryMethodGuardConditions( $file, &$state, $eventName )
{
    foreach( $state->_eventList[$eventName]->_reaction as $idx => $reaction )
    {
        writeFsmJavaClassJunctionGuardConditionsCode( $file, $state, $reaction );

        if($reaction->_guard_condition)
        {
           fwrite( $file, "            else\n");
        }
    }
}


function writeFsmJavaClassConcreteJunctionClassEntryMethod( $file, $state )
{
    fwrite( $file, "        public void entry() {\n");

    $superstateName = getSuperstateName( $state->_name );

    if( $superstateName )
    {
        fwrite( $file, "            // RSYS_ASSERT(m_fsm.m_state == m_fsm.m" . fsmUtilConvertToClassName($superstateName) . ");\n");
    }
    else
    {
        fwrite( $file, "            // RSYS_ASSERT(m_fsm.m_state == null);\n");
    }
    fwrite( $file, "\n");

    fwrite( $file, "            if (m_fsm.m_fsmTraceLevel >= TRACE_LEVEL_TRACE_EVENTS_AND_STATE_TRANSITIONS) {\n");
    fwrite( $file, "                // TRACE_PRINTF(\"%s.%u: %s (entry) \", mFsm.mName.c_str(), mFsm.mEventCounter, mName.c_str() );\n");
    fwrite( $file, "                String msg = String.format(\"%s.%d: %s (entry) \", m_fsm.m_name, m_fsm.m_eventCounter, m_name);\n");
    fwrite( $file, "                m_log.finer(msg);\n");
    fwrite( $file, "            }\n");
    fwrite( $file, "\n");
    
    if( $state->_featureList["entry"] )
    {
        fwrite( $file, "            m_fsm.m_fsmInterface." . fsmUtilCreateEntryMethodName($state->_name) . "();\n");
        fwrite( $file, "\n");
    }

    fwrite( $file, "            m_fsm.m_state = m_fsm." . fsmUtilConvertToAttributeName($state->_name) . ";\n");
    fwrite( $file, "\n");

    $eventName = "*";
    writeFsmJavaClassJunctionEntryMethodGuardConditions( $file, $state, $eventName );
    
    fwrite( $file, "         }\n");
    fwrite( $file, "\n");

}

function writeFsmJavaClassConcreteJunctionClassExitMethod( $file, &$state )
{
    writeFsmJavaClassStateExitMethod( $file, $state);
}

function writeFsmJavaClassConcreteJunctionClass( $file, &$state )
{
    global $fsmComponent;

    fwrite( $file, "    // Concrete junction states - ". fsmUtilConvertToClassName($state->_name) . "\n");
    fwrite( $file, "    private class " . fsmUtilConvertToClassName($state->_name) . " extends Junction {\n");
    fwrite( $file, "        public " . fsmUtilConvertToClassName($state->_name) . "(" . fsmClassJava() . " fsm) {\n");
    fwrite( $file, "            super(fsm, new String(\"" . fsmUtilConvertToClassName($state->_name) . "\"));\n");
    fwrite( $file, "        }\n");
    fwrite( $file, "\n");
    fwrite( $file, "        // Concrete entry exit functions\n");
    // Entry method
    writeFsmJavaClassConcreteJunctionClassEntryMethod( $file, $state );
    // Exit method
    writeFsmJavaClassConcreteJunctionClassExitMethod( $file, $state );
    fwrite( $file, "\n");
    fwrite( $file, "    }\n");
}

function writeFsmJavaClassConcreteJunctionClasses( $file )
{
    global $fsmComponent;

    foreach( $fsmComponent as $superstateName => $type )
    {
        if($type == "junction")
        {
            $state = getStateFromName($superstateName);
            
            writeFsmJavaClassConcreteJunctionClass( $file, $state );
        }
    }
}

function writeFsmJavaClassBody( $file )
{
    fwrite( $file, "public class " . fsmUtilConvertToClassName(fsmClassJava()) . " {\n");
    writeFsmJavaClassTraceConstants( $file );
    writeFsmJavaClassEventIdConstants( $file );
    writeFsmJavaClassAttributes( $file );
    writeFsmJavaClassEventNames( $file );

    // FSM class constructor.
    writeFsmJavaClassConstructor( $file );
    writeFsmJavaClassEventInjectMethods( $file );
    writeFsmJavaClassTraceEnableMethod ( $file );
    writeFsmJavaClassEnqueueMethod ( $file );

    // Write the State Base class.
    writeFsmJavaClassStateBaseClass ( $file );

    // Write EventsInterface interface class.
    writeFsmJavaClassEventsInterfaceClass( $file );
    
    // Write SimpleState base class.
    writeFsmJavaClassSimpleStateBaseClass( $file );

    // Write the Superstate Base class
    writeFsmJavaClassSuperStateBaseClass( $file );

    // Write Junction base class.
    writeFsmJavaClassJunctionBaseClass( $file );

    // write the concrete state classes
    writeFsmJavaClassConcreteStateClasses( $file );
    // write the concrete superstate classes
	  writeFsmJavaClassConcreteSuperStateClasses( $file );
    // write the concrete junction classes
    writeFsmJavaClassConcreteJunctionClasses( $file );

    writeFsmJavaClassQueuedClass( $file );

    fwrite( $file, "}\n");
    fwrite( $file, "\n");
}


function generateFsmJavaClass( $file )
{
    writeFsmJavaClassIntro( $file );

    writeFsmJavaClassBody( $file );
}



function writeFsmJavaInterfaceIntro( $file )
{
  global $fsmFeatureList, $argv, $argv;

  fwrite( $file, "///////////////////////////////////////////////////////////////////////////////\n");
  fwrite( $file, "//\n");
  fwrite( $file, "// " . interfaceDotHJava() ."\n");
  fwrite( $file, "//\n");
  fwrite( $file, "// Autogenerated using " . $argv[0] . " from " . $argv[1] . " " . $argv[2] . "\n");
  fwrite( $file, "//\n");
  fwrite( $file, "// Fsm Interface Class\n");
  fwrite( $file, "//\n");
  fwrite( $file, "// Copyright Radisys Limited\n");
  fwrite( $file, "//\n");
  fwrite( $file, "///////////////////////////////////////////////////////////////////////////////\n");
  fwrite( $file, "\n");

  writeJavaPackageName( $file);
  fwrite( $file, "\n");
}



function writeFsmJavaInterfaceActionClassReturningOutcome( $action )
{
  	global $fsmActionResults, $fsmOverloadableMethods;

    $className = fsmUtilCreateActionClassName($action);
    $fileName = $className . ".java";

    if (! $file = fopen($fileName, "w"))
    {
      die ("Cannot create file $fileName \n");
    }

    writeFsmJavaInterfaceIntro($file);
  	fwrite( $file, "public interface " . $className . " {\n");

  	fwrite( $file, "    public enum Outcome {\n");
  	foreach( $fsmActionResults[$action] as $failure => $stateName )
  	{
    	fwrite( $file, "        " . fsmUtilsCreateActionOutcomeIdName($action, $failure) . ",\n");
  	}
  	fwrite( $file, "    }\n");
  	fwrite( $file, "\n");


  	foreach( $fsmOverloadableMethods[$action]->_cTypeList as $c_type => $idx )
    {
      # If parameter list is not empty then it is a normal action function.  If it is empty then it is an overloaded action function.
      if ($idx == "")
      {  
        fwrite( $file, "    " . $className . ".Outcome " . fsmUtilConvertToMethodName($action) . "();\n");
      }
      else
      {
        # fwrite( $file, "    " . $className . ".Outcome " . fsmUtilConvertToMethodName($action) . "(" . $idx . " eventData);\n");
        fwrite( $file, "    " . $className . ".Outcome " . fsmUtilConvertToMethodName($action) . "(" . "Object eventData);\n");
      }
  	}

  	fwrite( $file, "}\n");
  	fwrite( $file, "\n");
}

function writeFsmJavaInterfaceActionClassReturningVoid( $action )
{
  	global $fsmActionResults, $fsmOverloadableMethods;

    $className = fsmUtilCreateActionClassName($action);
    $fileName = $className . ".java";

    if (! $file = fopen($fileName, "w"))
    {
      die ("Cannot create file $fileName \n");
    }
    
    writeFsmJavaInterfaceIntro($file);
  	fwrite( $file, "public interface " . $className . " {\n");

  	foreach( $fsmOverloadableMethods[$action]->_cTypeList as $c_type => $idx )
  	{
      # If parameter list is not empty then it is a normal action function.  If it is empty then it is an overloaded action function.
      if ($idx == "")
      { 
        fwrite( $file, "    void " . fsmUtilConvertToMethodName($action) . "();\n");
      }
      else
      {
  		  # fwrite( $file, "    void " . fsmUtilConvertToMethodName($action) . "(" . $idx . " eventData);\n");
  		  fwrite( $file, "    void " . fsmUtilConvertToMethodName($action) . "(" . "Object eventData);\n");
      }
  	}

  	fwrite( $file, "}\n");
  	fwrite( $file, "\n");
}

function writeFsmJavaInterfaceActionClasses( )
{
  global $fsmComponent;
  global $fsmActionResults;

  foreach( $fsmComponent as $action => $type )
  {
    if($type == "action")
    {
      if( count($fsmActionResults[$action]) > 1 )
      {
        writeFsmJavaInterfaceActionClassReturningOutcome( $action );
      }
      else
      {
        writeFsmJavaInterfaceActionClassReturningVoid( $action );
      }  
      
    }
  }
}

function writeFsmJavaInterfaceClassExtends( $file )
{
  global $fsmActionResults;

  $first = true;
  
  foreach( $fsmActionResults as $action => $outcome )
  {
    if($first)
    {
      fwrite( $file, " extends \n");
      $first = false;
    }
    else
    {
      fwrite( $file, ",\n");
    }

    fwrite( $file, "     " .  fsmUtilCreateActionClassName($action) );
  }

  fwrite( $file, " {\n");
}

function writeFsmJavaInterfaceClassStateEntryExitMethods( $file )
{
    global $fsmStates;

    foreach( $fsmStates as $stateName => $state )
    {
        if( $state->_featureList["entry"] )
        {
            fwrite( $file, "    void " . fsmUtilCreateEntryMethodName($stateName) . "();\n");
        }
        if( $state->_featureList["exit"] )
        {
            fwrite( $file, "    void " . fsmUtilCreateExitMethodName($stateName) . "();\n");
        }
    }
}


function writeFsmJavaInterfaceClassGuardConditionMethods( $file )
{
    global $fsmComponent, $fsmOverloadableMethods;

    foreach( $fsmComponent as $guard_condition => $type )
    {
        if($type == "guard_condition")
        {
          foreach( $fsmOverloadableMethods[$guard_condition]->_cTypeList as $c_type => $idx )
          {
            // print("Guard condition: " . fsmUtilConvertToMethodName($guard_condition) . " parameter list: " . $idx . "\n"); 
            
            // If the parameter list is empty then the guard condition belongs to a junction.  Create guard function 
            // with empty parameter list.
            if ($idx == "")
            {
              fwrite( $file, "    boolean " . fsmUtilConvertToMethodName($guard_condition) . "();\n");
            }
            else
            {
              # fwrite( $file, "    boolean " . fsmUtilConvertToMethodName($guard_condition) . "(" . $idx . " eventData);\n");
              fwrite( $file, "    boolean " . fsmUtilConvertToMethodName($guard_condition) . "(" . "Object eventData);\n");
            }
          }
        }
    }
}


function writeFsmJavaInterfaceClass( $file )
{
    fwrite( $file, "public interface " . fsmInterfaceClassJava() );
    writeFsmJavaInterfaceClassExtends( $file );
    fwrite( $file, "\n");
    writeFsmJavaInterfaceClassStateEntryExitMethods( $file );
    writeFsmJavaInterfaceClassGuardConditionMethods( $file );
    fwrite( $file, "}\n");

}

function generateInterfaceJava( $file )
{
  writeFsmJavaInterfaceActionClasses();


  writeFsmJavaInterfaceIntro( $file );
  writeFsmJavaInterfaceClass( $file );

}


function fsmDotCppJava ( )
{
  global $fsmFeatureList;

  return $fsmFeatureList["basename"] . "Fsm.dummy.java";
}

function fsmGetJavaFileName ( )
{
  global $fsmFeatureList;
  
  $fileName = fsmUtilConvertToClassName($fsmFeatureList["basename"] ) . "Fsm.java";
  return $fileName;
}

function interfaceDotHJava ( )
{
  global $fsmFeatureList;
  
  $fileName = fsmUtilConvertToClassName($fsmFeatureList["basename"]) . "FsmInterface.java";
  return $fileName;
}

function fsmNameJava()
{
  global $fsmFeatureList;

  return $fsmFeatureList["fsm"];
}

function fsmClassJava()
{
  return fsmUtilConvertToClassName(fsmNameJava()) . "Fsm" ;
}

function fsmInterfaceClassJava()
{
  return fsmUtilConvertToClassName(fsmNameJava()) . "FsmInterface" ;
}

// ============================================================================
//
// Common functions that can be moved to a common include file!
//
// ============================================================================

function getStateThatHandlesEventJava( &$state, $eventName )
{
  if(!$state->_eventList[$eventName])
  {
    return getAncestorStateThatHandlesEventJava( $state, $eventName );
  }
  return $state;
}

function getAncestorStateThatHandlesEventJava( &$state, $eventName )
{
  global $fsmSuperstates;

  $superstateName = $fsmSuperstates[$state->_name];

  if( !$superstateName )
  {
    // print_r($state);
    error("eof", "e0332 " . $eventName . " not handled (under all-possible conditions) in state " . $state->_name . " (nor its superstates).");
  }

  $stateBeingChecked = getStateFromName($superstateName);

  while( !$stateBeingChecked->_eventList[$eventName] )
  {
    $superstateName = $fsmSuperstates[$stateBeingChecked->_name];

    if( !$superstateName )
    {
      // print_r($state);
      error("eof", "e0334 " . $eventName . " not handled (under all-possible conditions) in state " . $state->_name . " (nor its superstates).");
    }

    $stateBeingChecked = getStateFromName($superstateName);
  }
  return $stateBeingChecked;
}



//
// ============================================================================
//

// To comply with Java naming conventions, convert the name to Java class name.
// Java class names starts with upper case letter, then camel case.
// We hope that the user has given states meaningful names.  We can only convert
// the first character to uppercase!
function fsmUtilConvertToClassName($className)
{
  return (ucfirst($className));  
}

// Same as above, convert a class attribute name to comply with Java naming 
// conventions.  
function fsmUtilConvertToAttributeName($attributeName)
{
  $javaAttribName = "m_" . strtolower($attributeName{0}) . substr($attributeName, 1);
  return $javaAttribName;
}

// Convert a method name to comply with Java naming conventions.
// The first character should be lower case.
function fsmUtilConvertToMethodName($methodName)
{
  $javaMethodName = strtolower($methodName{0}) . substr($methodName, 1);
  return $javaMethodName;
}

// Create state entry function name.
function fsmUtilCreateEntryMethodName($stateName)
{
  // Method names should start with lower case then camel case.
  $javaEntryName = fsmUtilConvertToMethodName($stateName) . "Entry";
  return $javaEntryName;
}

// Create state exit function name.
function fsmUtilCreateExitMethodName($stateName)
{
  // Method names should start with lower case then camel case.
  $javaExitName = fsmUtilConvertToMethodName($stateName) . "Exit";
  return $javaExitName;
}

// Create event ID names.  Java constant names should be all upper case with "_" separating words.
function fsmUtilCreateEventIdName($event)
{
  $javaConstantName = "EVENT_ID_FSM_EVENT_" . $event;
  return $javaConstantName;
}

// Create action outcome ID names
function fsmUtilsCreateActionOutcomeIdName($action, $outcome)
{
  $javaOutcomeName = "FSM_ACTION_" . strtoupper($action) . "_OUTCOME_" . $outcome;
  return $javaOutcomeName;
}

// Create action interface class name
function fsmUtilCreateActionClassName($action)
{
  $actionInterfaceName = fsmClassJava() . "Action" . fsmUtilConvertToClassName($action);
  return $actionInterfaceName;

}
