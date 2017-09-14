<?php

//////////////////////////////////////////////////
//////////////////////////////////////////////////
// Loading scripts for BIEN Cultivated Species database
//
// By: Brad Boyle
// Contact: bboyle@email.arizona.edu
// Date created: 18 Feb. 2014
// Date last revised: 
//
// Everything you need to set is here and in local
// params.inc file in each import directory
//
// Read the readme files in this directory and 
// all main subdirectories!
//////////////////////////////////////////////////
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// Distribution sources
//
// CRITICAL!!!
// Include in this array the name of every source
// you will be importing into the database
// Import scripts and data for each source MUST
// be their own directory called "import_[$sourceName]",
// for example, "import_tropicos". Source names 
// below MUST match the parameter $sourceName 
// as specified in params.inc in import subdirectory
// for that source. 
//////////////////////////////////////////////////

$src_array=array(
	"enquist"
);

/*
$src_array=array(
	"enquist",
	"fwi",
	"ipane",
	"mab",
	"mexico",
	"tropicos",
	"usda",
	"vascan",
	"weakley"
);
*/

//////////////////////////////////////////////////
// Replace database? (true/false)
//
// IMPORTANT! Set to true to replace database entirely
// all tables will be dropped and replaced with new,
// empty tables. Application will automatically prompt
// for confirmation if this option is set to true.
//
// Set to false keep existing database and
// add (if new) or replace (if already present) only
// the source(s) listed in $src_array.
//
//////////////////////////////////////////////////
$replace_db = true;

//////////////////////////////////////////////////
// Drop raw data tables after import complete?
// (true/false)
//////////////////////////////////////////////////
$drop_raw=true;
$drap_raw_force=true;		// over-rides any source-specific settings

//////////////////////////////////////////////////
// Include paths and filenames
//////////////////////////////////////////////////

$local_utilities_path="functions/";
$global_utilities_path="../global_utilities/";

include $global_utilities_path."functions.inc";
include $global_utilities_path."taxon_functions.inc";
include $global_utilities_path."sql_functions.inc";
include $global_utilities_path."geo_functions.inc";
$timer_on=$global_utilities_path."timer_on.inc";
$timer_off=$global_utilities_path."timer_off.inc";

//////////////////////////////////////////////////
// Db connection info
//////////////////////////////////////////////////

include_once "../db_config_nsr.inc";

//////////////////////////////////////////////////
// Error-reporting & runtime behavior
//////////////////////////////////////////////////

// echos error messages to screen
$echo_on = true;		

// aborts entire script on error
$die_on_fail = true;		

// default success and fail messages
$done = "done\r\n";
$msg_success = "done\r\n";
$msg_fail = "failed!\r\n";

?>
