<?php

////////////////////////////////////////////////////////////
// Adds missing (parent) family to country list where 
// record for genus is present but family is not
////////////////////////////////////////////////////////////

echo "    Missing families...";

// Get APGIII family from TNRS lookup for each genus
$url_tnrs_base='http://tnrs.iplantc.org/tnrsm-svc/matchNames?retrieve=best&names=';

$sql_genera="
SELECT DISTINCT genus
FROM distribution_staging
WHERE genus IS NOT NULL AND genus<>''
;
";
$result = mysql_query($sql_genera);

echo "performing TNRS lookups...";
while ($row = mysql_fetch_assoc($result)) {
	$gen = $row["genus"];
	$fam = '';
	
	$name=urlencode($gen);
	$url_tnrs=$url_tnrs_base.$name;	
	$json=file_get_contents($url_tnrs);
	$tnrs_results = json_decode($json,true);
	$fam = $tnrs_results['items'][0]['family'];	
	
	if ($fam<>'') {
		$sql_update_family = "
			UPDATE distribution_staging
			SET family='$fam'
			WHERE genus='$gen';
		";
		sql_execute_multiple($sql_update_family);
	}
}

echo "updating...";

// Create temporary table of missing poldiv+family combinations
$sql="
DROP TABLE IF EXISTS temp_missing_family
;
CREATE TABLE temp_missing_family
SELECT DISTINCT country, state_province, county_parish, family
FROM distribution_staging
WHERE native_status<>'introduced' AND taxon_rank<>'hybrid'
;
ALTER TABLE temp_missing_family
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (county_parish),
ADD INDEX (family)
;

-- Mark family+poldiv combinations already present
UPDATE temp_missing_family f JOIN distribution_staging d
ON f.family=d.taxon AND f.country=d.country AND f.state_province=d.state_province
AND f.county_parish=d.county_parish
SET f.family='DELETE'
;

-- Delete marked records
DELETE FROM temp_missing_family
WHERE family='DELETE' OR family IS NULL OR TRIM(family)=''
;
";
sql_execute_multiple($sql);

// Insert missing families
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
family
)
SELECT
'$src',
country,
state_province,
county_parish,
family,
'family',
'unknown',
'unknown',
family
FROM temp_missing_family
;
";
sql_execute_multiple($sql);

// Drop temporary table
$sql="
DROP TABLE temp_missing_family;
";
sql_execute_multiple($sql);
echo $done;

?>