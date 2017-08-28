<?php

/////////////////////////////////////////////////////////
// Combines raw data files into single file
/////////////////////////////////////////////////////////

echo "Combining separate raw data tables in table $tbl_raw:\r\n";

echo "  Inserting species endemic to specific Old World countries...";
$sql="
INSERT INTO $tbl_raw (
taxon,
country,
native_status
)
SELECT DISTINCT
taxon,
country,
'endemic'
FROM raw_enquist_country_endemics
;
";
sql_execute_multiple($sql);
echo $done;

echo "  Inserting Old World endemics as exotic records in each New World country...";
// Note cartesian product 
// Inserts a record for each Old World taxon in every New World country,
// with status='Introduced'
$sql="
INSERT INTO $tbl_raw (
taxon,
country,
native_status
)
SELECT DISTINCT
w.taxon,
c.country,
'introduced'
FROM raw_enquist_ow_endemics w, 
(
SELECT DISTINCT countryNameStd AS country
FROM countryName 
WHERE isNewWorld=1
) AS c
;
";
sql_execute_multiple($sql);
echo $done;

?>