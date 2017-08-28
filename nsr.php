<?php

///////////////////////////////////////////////////////////////////////
// Checks and update native and cultivated status for all records
// in table observation
///////////////////////////////////////////////////////////////////////

include "global_params.inc";

$appdir="nsr/";

// Confirm operation
$msg_proceed="
Check native status of species observation records?
Enter 'Yes' to proceed, or 'No' to cancel: ";
$proceed=responseYesNoDie($msg_proceed);
if ($proceed===false) die("\r\nOperation cancelled\r\n");

//////////////////////////////////////////////////////////////////
// Start time and open db connection
//////////////////////////////////////////////////////////////////

// Start timer and connect to mysql
echo "\r\n********* Begin operation *********\r\n\r\n";
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

include $appdir."alter_observation.inc";
include $appdir."check_absence.inc";
include $appdir."check_presence.inc";
include $appdir."check_cultivated.inc";
include $appdir."infer_status.inc";
include "append_to_cache.php";

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