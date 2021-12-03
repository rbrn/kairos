<?php



/*

** DGS Search

** search.php written by James M. Sella

** Copyright (c) 2000 Digital Genesis Software, LLC. All Rights Reserved.

** Released under the GPL Version 2 License.

** http://www.digitalgenesis.com

*/

require("./include/init_sito.inc");

require("./cerca/config/config.php");

require("./cerca/libs/utils.php");



$q=$_REQUEST["q"];

$r=$_REQUEST["r"];

$o=$_REQUEST["o"];

$s=$_REQUEST["s"];

function search($q, $r, $o, $s) {

	global $config;

	$modules = $config["searchModules"];

	$installBase = ereg_replace("(^.*)[/\\]$", "\\1", $config["installBase"]);



	settype($retVal, "array");



	reset($modules);

	while (list(, $module) = each($modules)) {

		$modInclude = $installBase . $config["fileSeparator"] . "libs" . $config["fileSeparator"] . "search" . $config["fileSeparator"] . $module . ".php";

		if (!function_exists($module)) {

			if (is_readable($modInclude)) {

				include($modInclude);

			} else {

				printf("Error: Unable to access search module '%s' (%s).<BR>\n", $module, $modInclude);

			}

		}

		if (function_exists($module)) {

			$retVal = $module($retVal, $q, $r, $o, $s);

			if (is_string($retVal)) {

				printf("Error: Module '%s' had a fatal error. Details below:<BR>\n<BR>\n%s<BR>\n", $module, $retVal);

				exit(1);

			}

		} else {

			printf("Error: Search module '%s' (%s) is not usable.<BR>\nThis module must contain the function '%s(\$retVal, \$q, \$r, \$o, \$s)'.<BR>\n", $module, $modInclude, $module);

		}

	}

	

	return $retVal;

}



function display($retVal, $q, $r, $o, $s, $timer) {

	global $config,$cod_area;

	global $DBASE,$DBUSER,$DBPWD;

	$modules = $config["displayModules"];

	$installBase = ereg_replace("(^.*)[/\\]$", "\\1", $config["installBase"]);

/*

	$header = $installBase . $config["fileSeparator"] . $config["header"];

	include($header);

*/

	

	//require "./include/funzioni_sito.inc";

	$risorsa=""; 

	$titolo="Risultati della ricerca";

	

	require "./include/testata.inc";



	echo "

	<table border=0>

	<tr>

	<td width=5>&nbsp;</td>

	<td bgcolor=white>

	<p>

	&nbsp;

	</p>";

	

	reset($modules);

	while (list(, $module) = each($modules)) {

		$modInclude = $installBase . $config["fileSeparator"] . "libs" . $config["fileSeparator"] . "display" . $config["fileSeparator"] . $module . ".php";

		if (!function_exists($module)) {

			if (is_readable($modInclude)) {

				include($modInclude);

			} else {

				printf("Error: Unable to access search module '%s' (%s).<BR>\n", $module, $modInclude);

			}

		}

		if (function_exists($module)) {

			$error = $module($retVal, $q, $r, $o, $s, $timer);

			if (is_string($error)) {

				printf("Error: Display module '%s' had a fatal error. Details below:<BR>\n<BR>\n%s<BR>\n", $module, $error);

				break;

			}

		} else {

			printf("Error: Module '%s' (%s) is not usable.<BR>\nThis module must contain the function '%s(\$retVal, \$q, \$r, \$o, \$s)'.<BR>\n", $module, $modInclude, $module);

		}

	}



/*

	if (!$config["hideCredits"]) {

		printf("\t<DIV ALIGN=\"right\">\n\t\t<FONT FACE=\"%s\" SIZE=\"-1\"><A TARGET=\"_top\" HREF=\"http://www.digitalgenesis.com\">DGS Search %s</A></FONT>\n\t</DIV>\n", $fonts, $config["version"]);

	}

*/

	

/*

	$footer = $installBase . $config["fileSeparator"] . $config["footer"];

	include($footer);

*/

	echo "

	</td>

	</tr>

	</table>";



	require "./include/piede.inc";

}



/* Start of Main */



$timer = getTime();



$errors = verifyConfig();

if (!$errors) {

	$r = (!isset($r)) ? (($config["results"]) ? 10 : $config["results"]) : $r; //Set default for results per page.

	$r = ($r < 1) ? $config["maxResults"] : $r;

	$o = (!isset($o) || $o < 1) ? 0 : $o; //Set default for offset.

	$s = (!isset($s) || $s < 1) ? 0 : $s; //Set result set to 0 if we don't have a cached one.



	if (isset($q) && $q != "")

		$retVal = search($q, $r, $o, $s);

	display($retVal, $q, $r, $o, $s, $timer);

} else {

	printf("Error: Configuration error(s) in config.php. Details below:<BR>\n<BR>\n");

	reset($errors);

	while (list(, $error) = each($errors)) {

		printf("%s<BR>\n", $error);

	}

}



/* End of Main */

?>
