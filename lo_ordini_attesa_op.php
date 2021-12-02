<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
 
$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$ruolo=ruolo_utente($kairos_cookie[0]);
if ($ruolo<>"admin") {
	$msg="Accesso riservato solo allo staff.";
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

$pagina=$_REQUEST["pagina"];
$pag_size=$_REQUEST["pag_size"];
$filtro=$_REQUEST["filtro"];
$titolo_cerca=$_REQUEST["titolo_cerca"];
$materia_cerca=$_REQUEST["materia_cerca"];
$id_purchase=$_REQUEST["id_purchase"];

for ($i=0;$i<count($id_purchase);$i++) {
	$id_ordine=$id_purchase[$i];
	
	$query="SELECT * FROM lo_purchase WHERE id_purchase='$id_ordine'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	
	$id_u=$riga["id_utente"];
	$id_lo=$riga["id_lo"];
	
	$query="SELECT * FROM utenti WHERE id_utente='$id_u'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$email=$riga["email"];
	$nome=$riga["nome"];
	$cognome=$riga["cognome"];
	
	$query="SELECT * FROM lo_repository WHERE id_lo='$id_lo'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	
	$titolo=$riga["titolo"];
	$materia=$riga["materia"];
	
	$query = "UPDATE lo_purchase SET stato_ordine='2' WHERE id_purchase='$id_ordine'";
	$mysqli->query($query);
	
	$msg = "Gentile $nome $cognome,
	
	confermiamo l'acquisto del Learning Object: $titolo ($materia)
	
	puoi da ora eseguirlo online o scaricarlo dal Repository di CurriculumDigitale
	
	http://www.curriculumdigitale.it
	
	Grazie.
"; 
		$id_package=uniqid("");	
	mail_job($id_package,"$email","Conferma acquisto Learning Object","$msg","ordini@garamond.it","ordini@garamond.it","");
		mysql_select_db($DBASE,$db);	
		
};

Header("Location:index.php?risorsa=lo_ordini_attesa&pagina=$pagina&pag_size=$pag_size&titolo_cerca=$titolo_cerca&materia_cerca=$materia_cerca&filtro=$filtro");
?>
