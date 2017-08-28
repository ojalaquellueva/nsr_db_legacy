<?php

////////////////////////////////////////////////////////////
// Adds missing (parent) species to country list where record for 
// infraspecific taxon (variety, subspecies, etc.) is present but 
// species is not
////////////////////////////////////////////////////////////

echo "    Missing species...";

// Populate species column
$sql="
UPDATE distribution_staging
SET species=CONCAT_WS(' ',
strSplit(taxon,' ',1),
strSplit(taxon,' ',2)
)
;
";
sql_execute_multiple($sql);

// Create temporary table of missing country+species combinations
$sql="
DROP TABLE IF EXISTS temp_missing_species
;
CREATE TABLE temp_missing_species
SELECT DISTINCT country, state_province, county_parish, species
FROM distribution_staging
WHERE native_status<>'introduced' AND taxon_rank<>'hybrid'
;
ALTER TABLE temp_missing_species
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (county_parish),
ADD INDEX (species)
;

-- Mark species+poldiv combinations already present
UPDATE temp_missing_species s JOIN distribution_staging d
ON s.species=d.taxon AND s.country=d.country AND s.state_province=d.state_province
AND s.county_parish=d.county_parish
SET s.species='DELETE'
;

-- Delete marked records
DELETE FROM temp_missing_species
WHERE species='DELETE'
;
";
sql_execute_multiple($sql);

// Insert missing species
$sql="
INSERT INTO distribution_staging (
source_name,
country,
state_province,
county_parish,
taxon,
taxon_rank,
native_status,
cult_status,
species
)
SELECT
'$src',
country,
state_province,
county_parish,
species,
'species',
'unknown',
'unknown',
species
FROM temp_missing_species
;
";
sql_execute_multiple($sql);

// Drop temporary table
$sql="
DROP TABLE temp_missing_species;
";
sql_execute_multiple($sql);
echo $done;

?>