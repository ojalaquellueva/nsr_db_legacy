<?php

echo "  Dropping staging table...";
$sql="
DROP TABLE IF EXISTS distribution_staging;
DROP TABLE IF EXISTS cultspp_staging;
DROP TABLE IF EXISTS poldiv_source_staging;
";
sql_execute_multiple($sql);
echo $done;

?>