<?php
require "../../include/init_sito_atlante.inc";

$PATH_FILE = "/var/www/html/prototipo/$tipo_area";
$PATH_ARCHIVI = "/var/www/archivi/$tipo_area/";

function copia_risorsa($area_da,$area_a,$id_risorsa) {
	global $DBHOST,$DBUSER,$DBPWD;
	global $PATH_FILE,$PATH_ARCHIVI;
	$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
	mysql_select_db($area_da,$db);
	$query = "SELECT * FROM risorse_materiali where id_risorsa='$id_risorsa'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();

	$risorsa_padre=$riga["risorsa_padre"];	
	$livello=$riga["livello"];
	$titolo=$riga["titolo"];		
	$descrizione=$riga["descrizione"];
	$parole_chiave=$riga["parole_chiave"];
	$id_gruppo=$riga["id_gruppo"];
	$tipo=$riga["tipo"];
	$id_autore=$riga["id_autore"];
	$id_utente=$riga["id_editor"];
	$posizione=$riga["posizione"];
	$data_crea=$riga["data_crea"];
	$file_size=$riga["file_size"];
	
	
	mysql_select_db($area_a,$db);
	$query = "DELETE FROM risorse_materiali where id_risorsa='$id_risorsa'";
	$result=$mysqli->query($query);
	
	$query = "INSERT INTO risorse_materiali (id_risorsa,tipo,risorsa_padre,titolo,descrizione,parole_chiave,id_autore,data_crea,livello,id_gruppo,file_size,posizione,id_editor) VALUES ('$id_risorsa','$tipo','$risorsa_padre','$titolo','$descrizione','$parole_chiave','$id_autore','$data_crea','$livello','$id_gruppo','$file_size','$posizione','$id_utente')";

};

function copia_pagina($area_da,$area_a,$id_risorsa) {
	global $PATH_FILE,$PATH_ARCHIVI;
	
	copia_risorsa($area_da,$area_a,$id_risorsa);
	$pagina_da="$PATH_FILE/materiali/$area_da/$id_risorsa.inc";
	$pagina_a="$PATH_FILE/materiali/$area_a/$id_risorsa.inc";
	copy($pagina_da,$pagina_a);
};

function copia_file($area_da,$area_a,$id_risorsa) {
	global $DBHOST,$DBUSER,$DBPWD;
	global $PATH_FILE,$PATH_ARCHIVI;
	$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);

	mysql_select_db($area_da,$db);
	$query = "SELECT * FROM risorse_materiali where id_risorsa='$id_risorsa'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$titolo=$riga["titolo"];	
	
	copia_risorsa($area_da,$area_a,$id_risorsa);

	$pagina_da="$PATH_ARCHIVI/materiali/$area_da/$titolo";
	$pagina_a="$PATH_ARCHIVI/materiali/$area_a/$titolo";
	copy($pagina_da,$pagina_a);
};

function copia_cartella($area_da,$area_a,$id_risorsa) {
	global $DBHOST,$DBUSER,$DBPWD;
	global $PATH_FILE,$PATH_ARCHIVI;
	
	copia_risorsa($area_da,$area_a,$id_risorsa);
	$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
	mysql_select_db($area_da,$db);
	
	$query = "SELECT * FROM risorse_materiali where risorsa_padre='$id_risorsa'";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_risorsa2=$riga["id_risorsa"];
		$tipo=$riga["tipo"];
		switch ($tipo) {
			case 0:
				copia_pagina($area_da,$area_a,$id_risorsa2);
				mysql_select_db($area_da,$db);
				break;
				
			case 4:
				copia_risorsa($area_da,$area_a,$id_risorsa2);
				mysql_select_db($area_da,$db);
				break;	

			case 1:
				copia_file($area_da,$area_a,$id_risorsa2);
				mysql_select_db($area_da,$db);
				break;

			case 2:
				copia_cartella($area_da,$area_a,$id_risorsa2);
				mysql_select_db($area_da,$db);
				break;
		};
	};
	
};

for ($i=0;$i<count($materiali);$i++) {
	list($tipo,$id_risorsa)=split(" ",$materiali[$i]);
	switch ($tipo) {
			case "pagina":
				copia_pagina($area_da,$area_a,$id_risorsa);
				break;
				
			case "link":
				copia_risorsa($area_da,$area_a,$id_risorsa);
				break;	

			case "file":
				copia_file($area_da,$area_a,$id_risorsa);
				break;

			case "cartella":
				copia_cartella($area_da,$area_a,$id_risorsa);
				break;
		
		  case "test":
				copia_test($area_da,$area_a,$id_risorsa);
				break;
	};
};


?>
