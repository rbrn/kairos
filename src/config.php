<?php

/************************************************************************/
/* DOCEBO CORE - Framework                                              */
/* ============================================                         */
/*                                                                      */
/* Copyright (c) 2005                                                   */
/* http://www.docebo.com                                                */
/*                                                                      */
/* This program is free software. You can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation; either version 2 of the License.       */
/************************************************************************/

$GLOBALS['dbhost'] 		= 'db2.clio.it';					//host where the database is
$GLOBALS['dbuname'] 	= 'aforisma';						//database username
$GLOBALS['dbpass'] 		= 'a76f5r98';							//database password for the user
$GLOBALS['dbname'] 		= 'aforisma';					//database name

$GLOBALS['prefix_fw'] 	= 'core';						//prefix for tables
$GLOBALS['prefix_lms'] = 'learning';					//prefix for tables
$GLOBALS['prefix_cms'] = 'cms';						//prefix for tables
$GLOBALS['prefix_scs'] = 'conference';					//prefix for tables
$GLOBALS['prefix_kms'] = 'kms';						//prefix for tables

/*file upload information************************************************/

$GLOBALS['uploadType'] = 'ftp';

$GLOBALS['ftphost'] 	= '195.60.128.113';					// normally this settings is ok
$GLOBALS['ftpport'] 	= '21';							// same as above
$GLOBALS['ftpuser'] 	= 'aforisma-org';
$GLOBALS['ftppass'] 	= 'federica';
$GLOBALS['ftppath'] 	= '/docebo2/';

$GLOBALS['where_files']  = '/files';
?>
