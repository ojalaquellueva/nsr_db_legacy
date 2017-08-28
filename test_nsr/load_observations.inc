<?php

/////////////////////////////////////////////////////////////
// Loads test records from BIEN2 database (bien_web) into
// cultspp.observation table
/////////////////////////////////////////////////////////////

////////////////////////////////
// Parameters
////////////////////////////////
// Number of records to use from each query
$limit = 1000000;

echo "\rLoading BIEN2 test records to table observation...";
$sql="
INSERT INTO observation (
family,
species,
country,
state_province,
county_parish,
isCultivatedOrig
)
SELECT DISTINCT
family,
species,
country,
stateProvince,
countyParish,
isCultivated
FROM bien_web.observation
WHERE family IS NOT NULL AND species IS NOT NULL
AND isGeoValid=1
AND observationType='specimen'
AND country IN ('Ecuador','Bolivia','Peru','Nicaragua','Canada','United States')
AND countyParish IS NULL
;
";
sql_execute_multiple($sql);
if (!(empty_string_to_null('observation'))) die("\r\nFailed to set empty strings to NULL!\r\n");
echo $done;

echo "\rManually inserting additional test records...";
$sql="
INSERT INTO observation (
family,
genus,
species,
country,
state_province
)
VALUES
(
'Myrtaceae',
'Eucalyptus',
'Eucalyptus communis',
'Nicaragua',
NULL
),
(
'Myrtaceae',
'Eucalyptus',
'Eucalyptus communis',
'Australia',
NULL
),
(
'Myrtaceae',
'Eucalyptus',
'Eucalyptus communis',
'Canada',
'Alberta'
),
(
'Tetracentraceae',
'Tetracentrus',
'Tetracentrus communis',
'Nicaragua',
NULL
)
;
";
sql_execute_multiple($sql);
echo $done;

?>