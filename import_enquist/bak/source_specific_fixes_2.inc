<?php

/////////////////////////////////////////////////////////////
// Fixes specific to this source, if any
//
// Leave content between this comment and closing line blank 
// if no source-specific fixes required
/////////////////////////////////////////////////////////////

echo "  Source-specific corrections...";

$sql="
UPDATE $tbl_raw
SET $fld_scientific_name=REPLACE($fld_scientific_name,'_',' ')
WHERE $fld_scientific_name LIKE '%_%'
;
UPDATE $tbl_raw
SET country='Australia'
WHERE country='Austrailia'
;
";
sql_execute_multiple($sql);
echo $done;

?>