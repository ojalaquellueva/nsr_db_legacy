<?php

/////////////////////////////////////////////////////////////
// Fixes specific to this source, if any
//
// Leave content between this comment and closing line blank 
// if no source-specific fixes required
/////////////////////////////////////////////////////////////

echo "  Source-specific corrections...";

// Fix non-standard stateProvince codes
$sql="
UPDATE raw_weakley_poldivs
SET stateProvinceCode=
CASE
WHEN stateProvinceCode='PN' THEN 'PA'
WHEN stateProvinceCode='NL' THEN 'NF'
ELSE stateProvinceCode
END;
UPDATE raw_weakley_exotic_part
SET stateProvinceCode=
CASE
WHEN stateProvinceCode='PN' THEN 'PA'
WHEN stateProvinceCode='NL' THEN 'NF'
ELSE stateProvinceCode
END;
";
sql_execute_multiple($sql);

// Replace underscores with plain hybrid 'x'
$sql="
UPDATE raw_weakley_exotic_part
SET taxon=REPLACE(taxon,'_','x ')
WHERE taxon LIKE '%\_%';
UPDATE raw_weakley_exotic_all
SET taxon=REPLACE(taxon,'_','x ')
WHERE taxon LIKE '%\_%';
UPDATE raw_weakley_origin
SET taxon=REPLACE(taxon,'_','x ')
WHERE taxon LIKE '%\_%';
";
sql_execute_multiple($sql);

// Replace ssp. with subsp.
$sql="
UPDATE raw_weakley_exotic_part
SET taxon=REPLACE(taxon,'ssp.','subsp.')
WHERE taxon LIKE '%ssp.%';
UPDATE raw_weakley_exotic_all
SET taxon=REPLACE(taxon,'ssp.','subsp.')
WHERE taxon LIKE '%ssp.%';
UPDATE raw_weakley_origin
SET taxon=REPLACE(taxon,'ssp.','subsp.')
WHERE taxon LIKE '%ssp.%';
";
sql_execute_multiple($sql);

echo $done;

?>