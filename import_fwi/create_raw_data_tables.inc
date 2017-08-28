<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data table $tbl_raw:\r\n";

echo "  $tbl_raw...";
$sql="
DROP TABLE IF EXISTS `$tbl_raw`;
CREATE TABLE $tbl_raw (
family VARCHAR(255) DEFAULT NULL,
genus VARCHAR(255) DEFAULT NULL,
epithet VARCHAR(255) DEFAULT NULL,
author VARCHAR(255) DEFAULT NULL,
publication VARCHAR(255) DEFAULT NULL,
westIndies VARCHAR(255) DEFAULT NULL,
greaterAntilles VARCHAR(255) DEFAULT NULL,
jamaica VARCHAR(255) DEFAULT NULL,
cuba VARCHAR(255) DEFAULT NULL,
caymanIsland VARCHAR(255) DEFAULT NULL,
hispaniola VARCHAR(255) DEFAULT NULL,
puertoRico VARCHAR(255) DEFAULT NULL,
virginIslands VARCHAR(255) DEFAULT NULL,
bahamas VARCHAR(255) DEFAULT NULL,
lesserAntillles VARCHAR(255) DEFAULT NULL,
editedDate VARCHAR(255) DEFAULT NULL,
data VARCHAR(255) DEFAULT NULL
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo "done";
	
?>

