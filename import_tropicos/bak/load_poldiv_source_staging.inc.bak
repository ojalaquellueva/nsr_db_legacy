<?php

///////////////////////////////////////////////////////
// Load raw distribution data to staging table
///////////////////////////////////////////////////////

echo "Loading checklist metadata to table poldiv_source_staging:\r\n";

if ($cclist_countries=="") {
	$cclist_notin_where="1";
} else {
	$cclist_notin_where="country NOT IN ($cclist_countries)";
}

echo "  Loading comprehensive country checklists...";
if (!$cclist_countries=='') {
	$sql="
	INSERT INTO poldiv_source_staging (
	poldiv_id, 
	poldiv_type, 
	source_name, 
	checklist_type,
	checklist_details
	)
	SELECT DISTINCT
	country_id, 
	'country', 
	'$src', 
	'comprehensive',
	'$source_name_full'
	FROM country
	WHERE country IN ($cclist_countries)
	;
	";
	sql_execute_multiple($sql);
	echo $done;
} else {
	echo "nothing to add\r\n";
}

echo "  Loading explicit partial country checklists...";
$sql="
INSERT INTO poldiv_source_staging (
poldiv_id, 
poldiv_type, 
source_name, 
checklist_type,
checklist_details
)
SELECT DISTINCT
a.country_id, 
'country', 
'$src', 
'partial',
'$source_name_full'
FROM country a JOIN tropicos_raw b 
ON a.country=b.country
WHERE a.$cclist_notin_where
;
";
sql_execute_multiple($sql);
echo $done;

?>