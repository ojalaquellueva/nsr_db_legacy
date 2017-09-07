<?php

/////////////////////////////////////////////////////
// Inserts explicit country x species combinations
// where species marked as absent.
// These can safely propagate downward from regions
// to countries in regions.
/////////////////////////////////////////////////////

// The following values treated as 'absent':
$absent_vals="
'absent',
'absent?',
'absent ?',
'doubful',
'doubtful',
'dubious'
";

echo "Inserting explicit absences by region:\r\n";

// Get regions which are NOT single countries
$sql_region="
SELECT region, is_country 
FROM fwi_regions_raw
WHERE is_country<>1 
AND region NOT IN ('hispaniola','virginIslands')
;
";
$regions = mysql_query($sql_region);

// Process each region, inserting only absences
while ($row = mysql_fetch_assoc($regions)) {	
	$region = $row["region"];
	$region_col = $region;
	$is_country = $row["is_country"];
	echo "  $region...";
		
	// Insert region_country combinations
	$sql = "
	INSERT INTO fwi_temp (
	source_name,
	country,
	state_province,
	county_parish,
	family,
	genus,
	species,
	taxon,
	taxon_rank,
	status_verbatim
	)
	SELECT DISTINCT
	'$src (explicit absence in region)',
	b.country,
	NULL,
	NULL,
	family,
	genus,
	TRIM(CONCAT_WS(' ',IFNULL(genus,''),IFNULL(epithet,''))),
	taxon,
	taxon_rank,
	'absent'
	FROM fwi_raw a, fwi_region_country b 
	WHERE b.region='$region'
	AND TRIM(a.$region_col) IN ($absent_vals)
	;
	";

	// add record to new table
	sql_execute_multiple($sql);	
	echo $done;
}

?>