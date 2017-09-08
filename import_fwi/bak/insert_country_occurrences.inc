<?php

///////////////////////////////////////////////
// Normalizes taxon occurrences for regions
// representing a single country, or a pair
// of countries sharing the same island, or
// very small sets of islands belonging to
// two countries
///////////////////////////////////////////////

echo "Inserting comprehensive country checklists...";

$sql="
INSERT INTO fwi_raw_final (
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
SELECT
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
FROM fwi_raw_temp
WHERE country IS NOT NULL
;

";
sql_execute_multiple($sql);	
echo $done;

?>