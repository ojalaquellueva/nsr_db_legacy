<?php

///////////////////////////////////////////////////////////////
// Add any permanent columns or indices needed
// Comment out whatever not needed
///////////////////////////////////////////////////////////////

echo "  Adding new columns and indexes...";

// Create column of species names only
$sql="
ALTER TABLE raw_vascan_taxon
ADD COLUMN species VARCHAR(250) DEFAULT NULL,
ADD INDEX (species)
;
UPDATE raw_vascan_taxon
SET genus=IF(TRIM(genus)='',NULL,genus),
specificEpithet=IF(TRIM(specificEpithet)='',NULL,specificEpithet),
infraspecificEpithet=IF(TRIM(infraspecificEpithet)='',NULL,infraspecificEpithet)
;
UPDATE raw_vascan_taxon
SET species=CONCAT(genus,' ',specificEpithet)
WHERE genus IS NOT NULL AND specificEpithet IS NOT NULL 
AND infraspecificEpithet IS NULL
;
";
sql_execute_multiple($sql);

echo $done;

?>
