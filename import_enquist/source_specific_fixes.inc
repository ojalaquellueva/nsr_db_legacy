<?php

/////////////////////////////////////////////////////////////
// Fixes specific to this source, if any
//
// Leave content between this comment and closing line blank 
// if no source-specific fixes required
/////////////////////////////////////////////////////////////

echo "  Source-specific corrections...";

// Extract just the taxon name from the old world endemics table
$sql="
RENAME TABLE raw_enquist_ow_endemics TO raw_enquist_ow_endemics_orig
;
DROP TABLE IF EXISTS raw_enquist_ow_endemics
;
CREATE TABLE raw_enquist_ow_endemics (
taxon VARCHAR(250) DEFAULT NULL,
INDEX (taxon)
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci
;
INSERT INTO raw_enquist_ow_endemics (taxon)
SELECT DISTINCT taxon
FROM raw_enquist_ow_endemics_orig
;
DROP TABLE raw_enquist_ow_endemics_orig
;
";
sql_execute_multiple($sql);

echo $done;

?>