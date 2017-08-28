<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating raw data tables:\r\n";

echo "  raw_weakley_exotic_part...";
$sql="
DROP TABLE IF EXISTS `raw_weakley_exotic_part`;
CREATE TABLE raw_weakley_exotic_part (
taxon VARCHAR(250) DEFAULT NULL,
stateProvinceCode VARCHAR(4) DEFAULT NULL,
INDEX (taxon),
INDEX (stateProvinceCode)
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;

echo "  raw_weakley_exotic_all...";
$sql="
DROP TABLE IF EXISTS `raw_weakley_exotic_all`;
CREATE TABLE raw_weakley_exotic_all (
taxon VARCHAR(250) DEFAULT NULL,
INDEX (taxon)
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;

echo "  raw_weakley_origin...";
$sql="
DROP TABLE IF EXISTS `raw_weakley_origin`;
CREATE TABLE raw_weakley_origin (
family VARCHAR(150) DEFAULT NULL,
taxon VARCHAR(250) DEFAULT NULL,
origin VARCHAR(50) DEFAULT NULL,
INDEX (family),
INDEX (taxon),
INDEX (origin)
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;
	
echo "  raw_weakley_poldivs...";
$sql="
DROP TABLE IF EXISTS `raw_weakley_poldivs`;
CREATE TABLE raw_weakley_poldivs (
stateProvinceCode VARCHAR(4) DEFAULT NULL,
country VARCHAR(50) DEFAULT NULL,
INDEX (stateProvinceCode),
INDEX (country)
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;

echo "  raw_weakley...";
$sql="
DROP TABLE IF EXISTS `raw_weakley`;
CREATE TABLE raw_weakley (
id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT,
taxon VARCHAR(250) DEFAULT NULL,
taxon_rank VARCHAR(50) DEFAULT NULL,
country VARCHAR(50) DEFAULT NULL,
stateProvince VARCHAR(150) DEFAULT NULL,
native_status VARCHAR(50) DEFAULT NULL,
INDEX (id),
INDEX (taxon),
INDEX (taxon_rank),
INDEX (country),
INDEX (stateProvince),
INDEX (native_status)
)  ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($sql);
echo $done;

?>

