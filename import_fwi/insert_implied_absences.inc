<?php

/////////////////////////////////////////////////////
// Flags a species as absent in all countries not
// in region of endemism. 
// This is only safe way to interpret assertions of
// a species being endemic to a multi-country region. 
// Can't definitively mark such species as endemic or
// even present in all countries comprising that region. 
// Would end up marking dozens of Cuban endemics as
// present on other West Indian islands where they 
// do not occur. But can at least mark these same 
// species as absent from all other
// countries.
// Note that we can do nothing with species listed
// as 'native' to multi-country regions.
/////////////////////////////////////////////////////

echo "Inserting implied absences due to endemism in region:\r\n";

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
	'$src (implied absence due to endemism)',
	b.country,
	NULL,
	NULL,
	family,
	genus,
	TRIM(CONCAT_WS(' ',IFNULL(genus,''),IFNULL(epithet,''))),
	taxon,
	taxon_rank,
	'absent'
	FROM fwi_raw a, country b 
	LEFT JOIN (
	SELECT country, region
	FROM fwi_region_country
	WHERE region='$region'
	) c
	ON b.country=c.country
	WHERE c.country IS NULL
	AND TRIM(a.$region_col) LIKE '%endemic%'
	;
	";

	// add record to new table
	sql_execute_multiple($sql);	
	echo $done;
}

?>