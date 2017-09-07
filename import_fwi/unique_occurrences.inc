<?php

//////////////////////////////////////////////////
// Save unique occurrences to main raw table and 
//////////////////////////////////////////////////

echo "Preparing final checklist:\r\n";

//////////////////////////////////////////////////////
// Assign numeric ranks to native status to allow 
// selecting of single value to apply to each species
//////////////////////////////////////////////////////

echo "  Extracting unique occurrences...";
$sql="
INSERT INTO fwi_final (
source_name,
country, 
family, 
genus, 
species, 
taxon, 
taxon_rank, 
native_status_all,
cult_status_all
)
SELECT 
'$src',
country, 
family, 
genus, 
species, 
taxon, 
taxon_rank, 
GROUP_CONCAT(native_status SEPARATOR ', '),
GROUP_CONCAT(cult_status SEPARATOR ', ')
FROM (
SELECT DISTINCT
'$src',
country, 
family, 
genus, 
species, 
taxon, 
taxon_rank, 
native_status,
cult_status
FROM fwi_temp 
) AS a
GROUP BY country, family, taxon
ORDER BY country, family, genus, species, taxon
;
";
sql_execute_multiple($sql);
echo $done;
 /*
echo "  Inferring final native status...";
$sql="
-- Only one classificatication
UPDATE fwi_final
SET native_status=native_status_all 
WHERE native_status_all NOT LIKE '%,%'
;

-- 

I";
sql_execute_multiple($sql);
echo $done;

echo "  Inferring final cultivated status...";
$sql="
I";
sql_execute_multiple($sql);
echo $done;
*/
?>