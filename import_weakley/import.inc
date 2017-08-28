<?php
// Imports raw text file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by and $ignore_lines
// are set in parameters file

echo "Loading raw data:\r\n";

echo "  Importing file $file_raw_weakley_exotic_part to table `raw_weakley_exotic_part`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_weakley_exotic_part' 
INTO TABLE raw_weakley_exotic_part 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($sql);
if (!(empty_string_to_null($tbl_raw))) die("Error\r\n.");
echo $done;

echo "  Importing file $file_raw_weakley_exotic_all to table `raw_weakley_exotic_all`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_weakley_exotic_all' 
INTO TABLE raw_weakley_exotic_all 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($sql);
if (!(empty_string_to_null($tbl_raw))) die("Error\r\n.");
echo $done;

echo "  Importing file $file_raw_weakley_origin to table `raw_weakley_origin`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_weakley_origin' 
INTO TABLE raw_weakley_origin 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($sql);
if (!(empty_string_to_null($tbl_raw))) die("Error\r\n.");
echo $done;

echo "  Importing file $file_raw_weakley_poldivs to table `raw_weakley_poldivs`...";
$sql = "
LOAD DATA $local INFILE '$datapath$file_raw_weakley_poldivs' 
INTO TABLE raw_weakley_poldivs 
$fields_terminated_by 
$optionally_enclosed_by 
$lines_terminated_by 
$ignore_lines;
";
sql_execute_multiple($sql);
if (!(empty_string_to_null($tbl_raw))) die("Error\r\n.");
echo $done;


?>
