<?php

//////////////////////////////////////////////////
// Save unique occurrences to main raw table and 
//////////////////////////////////////////////////

echo "Saving unique occurrences...";
$sql="
INSERT INTO fwi (
source_name,
country,
state_province,
county_parish,
family,
genus,
species,
taxon,
taxon_rank,
native_status,
cult_status
)
SELECT DISTINCT 
source_name,
country,
state_province,
county_parish,
family,
genus,
species,
taxon,
taxon_rank,
native_status,
cult_status
FROM fwi_temp;
";
sql_execute_multiple($sql);
echo $done;

?>