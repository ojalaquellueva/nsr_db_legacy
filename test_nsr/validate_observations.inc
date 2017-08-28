<?php

/////////////////////////////////////////////////////////////
// Performs basic validation on input observations
// If passes, parses genus from species field
/////////////////////////////////////////////////////////////

echo "Validating observations:\r\n";
$is_valid=true;
$passed="passed\r\n";

echo "  country...";
$sql="
SELECT COUNT(*) as null_ctry 
FROM observation 
WHERE country IS NULL;
";
if ($null_ctry=sql_get_first_result($sql,'null_ctry')>0) {
	echo "$null_ctry records have no value for country\r\n";
	$is_valid=false;
} else {
	echo $passed;
}

// check that any values of countyParish accompanied by stateProvince
$sql="
SELECT COUNT(*) as county_parishes FROM observation WHERE county_parish IS NOT NULL;
";
if (sql_get_first_result($sql,'county_parishes')>0) {
	echo "  county_parish...";
	$sql="
	SELECT COUNT(*) as null_state_province 
	FROM observation 
	WHERE state_province IS NULL AND county_parish IS NOT NULL;
	";
	if ($null_state_province=sql_get_first_result($sql,'null_state_province')>0) {
		echo "$null_state_province records have a value for county_parish but not for state_province\r\n";
		$is_valid=false;
	} else {
		echo $passed;
	}
}

echo "  species...";
$sql="
SELECT COUNT(*) as bad_species 
ROM observation 
WHERE species IS NULL OR species NOT LIKE '% %';
";
if ($bad_species=sql_get_first_result($sql,'bad_species')>0) {
	echo "$bad_species records have invalid or missing values of species\r\n";
	$is_valid=false;
} else {
	echo $passed;
}

echo "  family...";
$sql="
SELECT COUNT(*) as bad_family
ROM observation 
WHERE family IS NULL OR family NOT LIKE '%aceae' OR family LIKE '% %';
";
if ($bad_family=sql_get_first_result($sql,'bad_family')>0) {
	echo "$bad_family records have invalid or missing values of family\r\n";
	$is_valid=false;
} else {
	echo $passed;
}

if (!$is_valid) die("Validation failed.\r\nPlease fix errors and try again.\r\n");

echo "Parsing genus from species...";
$sql="
UPDATE observation
SET genus=strSplit(species,' ',1);
";
sql_execute_multiple($sql);
echo $done;
echo "Validation complete\r\n";

?>