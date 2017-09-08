<?php

///////////////////////////////////////////////
// Normalizes taxon occurrences for regions
// representing a single country, or a pair
// of countries sharing the same island, or
// very small sets of islands belonging to
// two countries
///////////////////////////////////////////////

echo "Normalizing country occurrences:\r\n";

$sql="
DROP TABLE IF EXISTS fwi_temp;
CREATE TABLE fwi_temp LIKE fwi;
ALTER TABLE fwi_temp DROP COLUMN id;
";
sql_execute_multiple($sql);

// Loop through each record of raw table
$sql_region="
SELECT region, is_country 
FROM fwi_regions_raw
WHERE is_country=1 
OR region IN ('hispaniola','virginIslands')
;
";
$regions = mysql_query($sql_region);

echo "  Processing region";

// Process each region
while ($row = mysql_fetch_assoc($regions)) {	
	$region = $row["region"];
	$is_country = $row["is_country"];
	echo "\r  Processing region $region...";
	$curr_row = 1;
	
	$sql_raw="
	SELECT * FROM fwi_raw;
	";
	$raw_data = mysql_query($sql_raw);
	$nrows = mysql_num_rows($raw_data);

	// Process each row of raw data
	while ($row = mysql_fetch_assoc($raw_data)) {	
		$region_col = $region;
		$family = $row["family"];
		$genus = $row["genus"];
		$epithet = $row["epithet"];
		$species = trim($genus." ".$epithet);
		$taxon = $row["taxon"];
		$taxon_rank = $row["taxon_rank"];
		$status_verbatim = $row["$region_col"];
		
		echo "\r  Processing region $region...row $curr_row of $nrows";
		
		/* Not applicable to country-level occurrences
		// Adjust status; only countries retain endemic status
		if (!( $is_country==1 || $region=='hispaniola' || $region=='virginIslands' ) ) {
			if (strpos($status_verbatim, "endemic")) $status_verbatim = 'native';
		}
		*/
		
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
		'$src',
		b.country,
		NULL,
		NULL,
		'$family',
		'$genus',
		'$species',
		'$taxon',
		'$taxon_rank',
		'$status_verbatim'
		FROM fwi_raw a, fwi_region_country b 
		WHERE b.region='$region'
		;
		";
	
		// add record to new table
		sql_execute_multiple($sql);	
		
		$curr_row++;				
	}

	echo "\r  Processing region $region...row $curr_row of $nrows...done\r\n";
}

echo "Saving country occurrences...";
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
status_verbatim
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
status_verbatim
FROM fwi_temp;
";
sql_execute_multiple($sql);
echo $done;

?>