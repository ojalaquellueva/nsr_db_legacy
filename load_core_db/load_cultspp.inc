<?php

echo "  Loading table cultspp...";
$sql="
INSERT INTO cultspp (
source_id,
taxon_rank,
taxon
)
SELECT DISTINCT
$source_id,
taxon_rank,
taxon
FROM cultspp_staging
WHERE is_in_db=0;
;
";
sql_execute_multiple($sql);
echo $done;

?>