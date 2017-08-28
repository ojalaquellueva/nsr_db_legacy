<?php

echo "Creating tables...";
$sql="
DROP TABLE IF EXISTS cultspp;
DROP TABLE IF EXISTS distribution;
DROP TABLE IF EXISTS source;
DROP TABLE IF EXISTS $tbl_country;

CREATE TABLE source (
source_id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
source_name VARCHAR(50) NOT NULL,
source_name_full VARCHAR(250) NOT NULL,
source_url VARCHAR(500) DEFAULT NULL,
source_contact_name VARCHAR(50) DEFAULT NULL,
source_contact_email VARCHAR(250) DEFAULT NULL,
date_accessed VARCHAR(10) DEFAULT NULL,
is_comprehensive INT(1) DEFAULT NULL,
regional_scope VARCHAR(50) DEFAULT 'country',
taxonomic_scope VARCHAR(250) DEFAULT NULL,
PRIMARY KEY (source_id)
);

CREATE TABLE distribution (
distribution_id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
source_id INT(11) UNSIGNED NOT NULL,
taxon_rank VARCHAR(25) NOT NULL,
taxon VARCHAR(150) NOT NULL,
country VARCHAR(50) NOT NULL,
state_province VARCHAR(100) DEFAULT NULL,
county_parish VARCHAR(100) DEFAULT NULL,
native_status VARCHAR(25) DEFAULT NULL,
cult_status VARCHAR(25) DEFAULT NULL,
PRIMARY KEY(distribution_id),
FOREIGN KEY (source_id) REFERENCES source(source_id)
);

CREATE TABLE $tbl_country (
countryNameID INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
countryName VARCHAR(100) DEFAULT NULL,
countryID INT(11) UNSIGNED NOT NULL,
isoCode VARCHAR(2) DEFAULT NULL,
countryCode3Char VARCHAR(3) DEFAULT NULL,
countryNameStd VARCHAR(100) DEFAULT NULL,
isNewWorld INT(1) DEFAULT 0,
PRIMARY KEY (countryNameID),
INDEX (countryName),
INDEX (countryID),
INDEX (isoCode),
INDEX (countryCode3Char),
INDEX (countryNameStd),
INDEX (isNewWorld)
);

CREATE TABLE cultspp (
cultspp_id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
source_id INT(11) UNSIGNED NOT NULL,
taxon_rank VARCHAR(25) NOT NULL,
taxon VARCHAR(150) NOT NULL,
PRIMARY KEY(cultspp_id),
INDEX(taxon_rank),
INDEX(taxon),
FOREIGN KEY (source_id) REFERENCES source(source_id)
);

DROP TABLE IF EXISTS cache;
CREATE TABLE cache (
id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
family VARCHAR(50) DEFAULT NULL,
genus VARCHAR(50) DEFAULT NULL,
species VARCHAR(150) DEFAULT NULL,
country VARCHAR(50) DEFAULT NULL,
state_province VARCHAR(50) DEFAULT NULL,
county_parish VARCHAR(50) DEFAULT NULL,
native_status_country VARCHAR(25) DEFAULT NULL,
native_status_state_province VARCHAR(25) DEFAULT NULL,
native_status_county_parish VARCHAR(25) DEFAULT NULL,
native_status VARCHAR(25) DEFAULT NULL,
native_status_reason VARCHAR(250) DEFAULT NULL,
native_status_sources VARCHAR(250) DEFAULT NULL,
isIntroduced INT(1) DEFAULT NULL,
isCultivatedNSR INT(1) DEFAULT 0,
PRIMARY KEY (id)
);


";
sql_execute_multiple($sql);
echo $done;

echo "Indexing tables...";
$sql="
ALTER TABLE source
ADD INDEX (source_name),
ADD INDEX (is_comprehensive),
ADD INDEX (regional_scope),
ADD INDEX (taxonomic_scope)
;

ALTER TABLE distribution
ADD INDEX (taxon_rank),
ADD INDEX (taxon),
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (county_parish),
ADD INDEX (native_status),
ADD INDEX (cult_status)
;

ALTER TABLE cache
ADD INDEX (family),
ADD INDEX (genus),
ADD INDEX (species),
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (county_parish)
;

";
sql_execute_multiple($sql);
echo $done;

?>



