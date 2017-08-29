<?php

//////////////////////////////////////////
// fix misc errors in state_province
//////////////////////////////////////////

echo "Fixing errors in political division tables:\r\n";

echo " state_province...";
$sql="
UPDATE state_province
SET 
state_province_ascii='Estado de Veracruz'
state_province_std='Veracruz'
WHERE country_iso='MX'  
AND state_province_ascii='Estado de Veracruz-Llave'
;
UPDATE state_province
SET 
state_province_ascii='Estado de Michoacan'
state_province_std='Michoacan'
WHERE country_iso='MX'  
AND state_province_ascii='Estado de Michoacan de Ocampo'
;
UPDATE state_province
SET 
state_province_ascii='Estado de Coahuila'
state_province_std='Coahuila'
WHERE country_iso='MX'  
AND state_province_ascii='Estado de Coahuila de Zaragoza'
;
";
sql_execute_multiple($sql);
echo $done;

echo " state_province_name...";
$sql="
UPDATE state_province_name
SET 
state_province_ascii='Estado de Veracruz'
state_province_std='Veracruz'
WHERE country_iso='MX'  
AND state_province_ascii='Estado de Veracruz-Llave'
;
UPDATE state_province_name
SET 
state_province_ascii='Estado de Michoacan'
state_province_std='Michoacan'
WHERE country_iso='MX'  
AND state_province_ascii='Estado de Michoacan de Ocampo'
;
UPDATE state_province_name
SET 
state_province_ascii='Estado de Coahuila'
state_province_std='Coahuila'
WHERE country_iso='MX'  
AND state_province_ascii='Estado de Coahuila de Zaragoza'
;
";
sql_execute_multiple($sql);
echo $done;

?>