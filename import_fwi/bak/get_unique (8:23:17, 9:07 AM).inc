<?php

/////////////////////////////////////////////////////////////
// Extract unique records
/////////////////////////////////////////////////////////////

$tbl_raw_temp = $tbl_raw . "_temp";

echo "  Removing non-unique records...";
$sql="
DROP TABLE IF EXISTS $tbl_raw_temp;
CREATE TABLE $tbl_raw_temp (
family VARCHAR(255) DEFAULT NULL,
genus VARCHAR(255) DEFAULT NULL,
epithet VARCHAR(255) DEFAULT NULL,
author VARCHAR(255) DEFAULT NULL,
westIndies VARCHAR(255) DEFAULT NULL,
greaterAntilles VARCHAR(255) DEFAULT NULL,
jamaica VARCHAR(255) DEFAULT NULL,
cuba VARCHAR(255) DEFAULT NULL,
caymanIsland VARCHAR(255) DEFAULT NULL,
hispaniola VARCHAR(255) DEFAULT NULL,
puertoRico VARCHAR(255) DEFAULT NULL,
virginIslands VARCHAR(255) DEFAULT NULL,
bahamas VARCHAR(255) DEFAULT NULL,
lesserAntillles VARCHAR(255) DEFAULT NULL
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

INSERT INTO $tbl_raw_temp (
family,
genus,
epithet,
author,
westIndies,
greaterAntilles,
jamaica,
cuba,
caymanIsland,
hispaniola,
puertoRico,
virginIslands,
bahamas,
lesserAntillles
)
SELECT DISTINCT
family,
genus,
epithet,
author,
westIndies,
greaterAntilles,
jamaica,
cuba,
caymanIsland,
hispaniola,
puertoRico,
virginIslands,
bahamas,
lesserAntillles
FROM $tbl_raw
;
DROP TABLE $tbl_raw;
RENAME TABLE $tbl_raw_temp TO $tbl_raw;
";
sql_execute_multiple($sql);
echo $done;


/*
// look up state names
$results = mysql_query("
SELECT DISTINCT stateCode FROM `$tbl_raw`;
");

while ($row = mysql_fetch_assoc($results)) {
	$stateCode = $row["stateCode"];
	
	$state = state_name_US($stateCode);
	$sql="
	UPDATE `$tbl_raw`
	SET state='$state'
	WHERE stateCode='$stateCode'
	;		
	";
	sql_execute_multiple($sql);
}

echo $done;
*/

?>