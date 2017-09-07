<?php
// Imports species distribution data from source USDA Plants

include "params.inc";	// everything you need to set is here and in global_params.inc

////////////// Import raw data file //////////////////////

// create empty import table
// These must be identical in structure to raw data file
include "create_raw_data_tables.inc";

// import raw data file
include "import.inc";

echo "Standardizing $tbl_raw:\r\n";

// Add any extra columns and indexes needed
include "alter_tbl_raw.inc";

// Make fixes specific to this source, if any
include "source_specific_fixes.inc";

// standardize hybrid x to plain ascii
include "fix_hybrid_x.inc";

// separate taxon name from author and dump to taxon field
include "detect_rank.inc";

// Normalize the raw data
include "normalize_fwi_regions.inc";

// Insert the occurrences
include "insert_country_occurrences.inc";
include "insert_explicit_absences.inc";
include "insert_explicit_introduced.inc";
include "insert_implied_absences.inc";

// standardize status codes
include "standardize_status.inc";

// Insert unique values into main table
include "unique_occurrences.inc";

//exit("Exiting...\r\n");

// load data from combined raw data table to standardized staging table
include "create_distribution_staging.inc";
include "load_staging.inc";

// delete temporary tables, if any
if ($drop_raw) {
	include "cleanup.inc";
}

//////////////////////////////////////////////////////////


?>
