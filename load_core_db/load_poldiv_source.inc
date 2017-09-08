<?php

echo "  Loading metadata on checklist regions...";
$sql="
INSERT INTO poldiv_source (
poldiv_id,
poldiv_type,
source_id,
checklist_type,
checklist_details
) 
SELECT
a.poldiv_id,
a.poldiv_type,
b.source_id,
a.checklist_type,
a.checklist_details
FROM poldiv_source_staging a JOIN source b
ON a.source_name=b.source_name
;
";
sql_execute_multiple($sql);
echo $done;
?>
