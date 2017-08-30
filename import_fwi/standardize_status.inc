<?php

//////////////////////////////////////////////////////
// Standardized status codes in raw data
// leave blank if raw table does not have status
// codes; populate fixed status codes when load to
// staging table in final step
//////////////////////////////////////////////////////

$tbl = "fwi_temp";

echo "Standardizing status codes:\r\n";

echo "  native status...";
$sql="
UPDATE $tbl
SET native_status=status_verbatim
;
-- Introduced
-- Note that blanks = cultivated, absent or introduced 
UPDATE $tbl
SET native_status=
CASE
WHEN native_status LIKE '%absent%' THEN 'introduced'
WHEN native_status LIKE '%cultivated%' THEN 'introduced'
WHEN native_status LIKE '%doubful%' THEN 'introduced'
WHEN native_status LIKE '%doubtful%' THEN 'introduced'
WHEN native_status LIKE '%dubious%' THEN 'introduced'
WHEN native_status LIKE '%exotic%' THEN 'introduced'
WHEN native_status LIKE '%invasive%' THEN 'introduced'
WHEN native_status LIKE '%natiralized%' THEN 'introduced'
WHEN native_status LIKE '%aturalized%' THEN 'introduced'
WHEN trim(native_status)='' THEN 'introduced'
WHEN native_status LIKE '%xxx%' THEN 'introduced'
ELSE native_status
END
;

-- Endemic & native
UPDATE $tbl
SET native_status=
CASE
WHEN native_status LIKE '%endemic%' THEN 'endemic'
WHEN native_status LIKE '%native%' THEN 'native'
WHEN native_status='Navassa' THEN 'native'
WHEN native_status='possible' THEN 'native'
WHEN native_status='St. Thomas' THEN 'native'
WHEN native_status LIKE '%hybrid%' THEN 'native'
ELSE native_status
END
;
";
sql_execute_multiple($sql);
echo $done;

echo "  cultivated status...";
$sql="
UPDATE $tbl
SET cult_status=
CASE
WHEN status_verbatim LIKE '%cult%' THEN 'introduced'
ELSE NULL
END
;
";
sql_execute_multiple($sql);
echo $done;

?>