<?php

echo "Altering table observation...";
$sql="
ALTER TABLE observation
ADD COLUMN isCultivatedOrig INT(1) DEFAULT NULL,
ADD INDEX (isCultivatedOrig)
;
";
sql_execute_multiple($sql);
echo "done";


?>