<?php

///////////////////////////////////////////////////////////////////////
// Loads test records from BIEN2 database
///////////////////////////////////////////////////////////////////////

include "global_params.inc";

$appdir="test_nsr/";

// Confirm operation
$msg_proceed="
Load test observations from BIEN2 (replace previous table observaton)?
Enter 'Yes' to proceed, or 'No' to cancel: ";
$proceed=responseYesNoDie($msg_proceed);
if ($proceed===false) die("\r\nOperation cancelled\r\n");

//////////////////////////////////////////////////////////////////
// Start time and open db connection
//////////////////////////////////////////////////////////////////

// Start timer and connect to mysql
echo "\r\n********* Begin operation *********\r\n";
include $timer_on;

// connect to mysql
$dbh = mysql_connect($HOST,$USER,$PWD,FALSE,128);
if (!$dbh) die("\r\nCould not connect to database!\r\n");

// Connect to database
$sql="USE `".$DB."`;";
sql_execute_multiple($sql);

//////////////////////////////////////////////////////////////////
// Main script
//////////////////////////////////////////////////////////////////

include "create_observation.inc";
include $appdir."alter_observation.inc";
include $appdir."load_observations.inc";
include $appdir."validate_observations.inc";


//////////////////////////////////////////////////////////////////
// Close connection and report total time elapsed 
//////////////////////////////////////////////////////////////////

mysql_close($dbh);
include $timer_off;
$msg = "\r\nTotal time elapsed: " . $tsecs . " seconds.\r\n"; 
$msg = $msg . "********* Operation completed " . $curr_time . " *********";
if  ($echo_on) echo $msg . "\r\n\r\n"; 

//////////////////////////////////////////////////////////////////
// End script
//////////////////////////////////////////////////////////////////