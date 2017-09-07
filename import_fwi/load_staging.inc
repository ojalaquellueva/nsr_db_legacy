<?php

///////////////////////////////////////////////////////
// Load raw distribution data to staging table
///////////////////////////////////////////////////////

echo "Loading raw data to staging table distribution_staging:\r\n";

echo "  Inserting unique records...";
$sql="
INSERT INTO distribution_staging (
source_name,
country,
state_province,
county_parish,
taxon,
taxon_rank,
native_status,
cult_status
)
SELECT DISTINCT
'$src',
country,
state_province,
county_parish,
taxon,
taxon_rank,
native_status,
cult_status
FROM fwi_final
;
";
sql_execute_multiple($sql);
echo $done;

?>