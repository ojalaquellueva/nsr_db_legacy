<?php

///////////////////////////////////////////////////////////////////
// Delete temporary tables, if any
// Comment out if none
// Do not delete the raw table here; all raw tables can be deleted
// in a single step 
///////////////////////////////////////////////////////////////////

echo "Deleting temporary tables...";
$sql="
DROP TABLE IF EXISTS raw_weakley;
DROP TABLE IF EXISTS raw_weakley_exotic_all;
DROP TABLE IF EXISTS raw_weakley_exotic_part;
DROP TABLE IF EXISTS raw_weakley_origin;
DROP TABLE IF EXISTS raw_weakley_poldivs;
";
sql_execute_multiple($sql);
echo $done;	


?>