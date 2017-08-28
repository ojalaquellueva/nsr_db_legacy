<?php
// Imports raw text file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by and $ignore_lines
// are set in parameters file

echo "Loading raw data:\r\n";

echo "  Importing file $file_raw_vascan_distribution to table `raw_vascan_distribution`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_vascan_distribution' 
INTO TABLE raw_vascan_distribution 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($sql);
if (!(empty_string_to_null($tbl_raw))) die("Error\r\n.");
echo $done;

echo "  Importing file $file_raw_vascan_taxon to table `raw_vascan_taxon`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_vascan_taxon' 
INTO TABLE raw_vascan_taxon 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($sql);
if (!(empty_string_to_null($tbl_raw))) die("Error\r\n.");
echo $done;

?>
