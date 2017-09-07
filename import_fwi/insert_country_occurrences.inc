<?php

///////////////////////////////////////////////
// Normalizes taxon occurrences for regions
// representing a single country, or a pair
// of countries sharing the same island, or
// very small sets of islands belonging to
// two countries
///////////////////////////////////////////////

echo "Inserting comprehensive country checklists:\r\n";

// Loop through each record of raw table
$sql_region="
SELECT region, is_country 
FROM fwi_regions_raw
WHERE is_country=1 
OR region IN ('hispaniola','virginIslands')
;
";
$regions = mysql_query($sql_region);

// Process each region
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
	'$src (country occurrence)',
	b.country,
	NULL,
	NULL,
	family,
	genus,
	TRIM(CONCAT_WS(' ',IFNULL(genus,''),IFNULL(epithet,''))),
	taxon,
	taxon_rank,
	$region_col
	FROM fwi_raw a, fwi_region_country b 
	WHERE b.region='$region'
	;
	";

	// add record to new table
	sql_execute_multiple($sql);	
	echo $done;
}

?>