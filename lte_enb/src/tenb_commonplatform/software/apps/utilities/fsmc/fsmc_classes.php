<?php



class Token 
{
    public function __construct( $token, $lineNumber )
    {
        $this->_token = $token;
        $this->_lineNumber = $lineNumber;
    }

    public $_token;
    public $_lineNumber;	
}

class Statement 
{
    public function __construct( $tokenArray, $firstTokenIdx, $lastTokenIdx, $offsetBy = 0 )
    { 
    	$idx = 0;
    	$total = $lastTokenIdx - $firstTokenIdx + 1;

        for( $idx = 0; $idx <= $offsetBy ; $idx++ )
        {
        	$lineNumber = $tokenArray[0]->_lineNumber;
            $this->_tokens[$idx] = new Token( "", $lineNumber );
        }
    	
        for( $idx = 0; $idx < $total ; $idx++ )
        {
        	$srcToken = $tokenArray[$firstTokenIdx + $idx];
            $this->_tokens[$idx + $offsetBy] = new Token ($srcToken->_token, $srcToken->_lineNumber) ;
        }
    }

    public $_tokens = array();
}

class Action
{
    public function __construct( $name )
    { 
    	$this->_name = $name;
    }

	public $_name;
    public $_faultList = array();
}

class EventReaction
{
    public function __construct( $eventName, $stateName )
    { 
        $this->_eventName  = $eventName;
        $this->_stateName  = $stateName;
        $this->_viaStateName  = $stateName;
        $this->_targetState = $stateName;
        $this->_internalTransition  = 1;
        $this->_guard_condition = "";
    }

    public $_eventName;
    public $_stateName;
    public $_viaStateName;
    public $_targetState;
    public $_internalTransition;
    public $_guard_condition;
    public $_action = array();
}



class Event
{
    public function __construct( $name, $stateName )
    { 
        $this->_name = $name;
        $this->_stateName = $stateName;
        $this->_defer = 0;
        $this->_ifParsed = 0;
        $this->_unConditionalParsed = 0;
    }

    public $_name;
    public $_defer;
    public $_stateName;
    public $_ifParsed;
    public $_unConditionalParsed;
    public $_reaction = array();
}

class State
{
    public function __construct( $name )
    { 
        //echo "State::State(" . $name . ")\n";
        $this->_name = $name;
        $this->_status = "declared";
    }

    public $_name;
    public $_status;
    public $_componentList = array();
    public $_statements = array();
    public $_featureList = array();
    public $_eventList = array();
    public $_faultList = array();
}

class OverloadedMethod
{
    public function __construct( $name )
    { 
        $this->_name = $name;
    }

    public $_name;
    public $_cTypeList = array();
}

$fsmFileTokens = array();
$fsmFileStatements = array();
$fsmComponent = array();
$fsmFeatureList = array();
$fsmSuperstates = array();
$fsmJunctions = array();
$fsmEventTypes = array();
$fsmActionResults = array();
$fsmStates = array();
$fsmFaults = array();
$fsmSelects = array();
$fsmIncludes = array();
$fsmOverloadableMethods = array();



?>
