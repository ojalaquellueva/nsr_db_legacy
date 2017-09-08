<?php

///////////////////////////////////////////////////////
// Load raw distribution data to staging table
///////////////////////////////////////////////////////

echo "Loading checklist metadata to table poldiv_source_staging:\r\n";

echo "  Loading comprehensive country checklists...";
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
'From Flora of the West Indies'
FROM country
WHERE country IN ($cclist_countries)
;
";
sql_execute_multiple($sql);
echo $done;

echo "  Loading explicit partial country checklists...";
if (!$pclist_countries=='') {
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
	'partial',
	'Partial checklist from Flora of the West Indies'
	FROM country
	WHERE country IN ($pclist_countries)
	;
	";
	sql_execute_multiple($sql);
}
echo $done;

echo "  Loading inferred-by-endemisim partial country checklists...";
if ($pclist_countries=="") {
	$pclist_where="1";
} else {
	$pclist_where="country NOT IN ($pclist_countries)";
}

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
'partial',
'Introduced species inferred from endemics in Flora of the West Indies'
FROM country a JOIN distribution_staging b
ON a.country=b.country
WHERE a.country NOT IN ($cclist_countries)
AND $pclist_where
;
";
sql_execute_multiple($sql);
echo $done;

?>