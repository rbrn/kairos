<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_utente_form=$_REQUEST["id_utente_form"];
$pwd_utente_form=$_REQUEST["pwd_utente_form"];
$url=$_REQUEST["url"];
$id_utente_form=trim($id_utente_form);
$pwd_utente_form=md5(trim($pwd_utente_form));

if (authenticateUser($id_utente_form,$pwd_utente_form)) {
	setCookies($id_utente_form,$pwd_utente_form);
	refresh_utente($id_utente_form);
	$query = "INSERT INTO log_sito(id_utente,data_log,dettagli) VALUES ('$id_utente_form',NOW(),'login')";
	$result=$mysqli->query($query);
	
	$ruolo=ruolo_utente($id_utente_form);
	if ($ruolo<>'staff' and $ruolo<>'admin') {
		$query="SELECT corso.id_corso,iscrizioni_corso.id_edizione,iscrizioni_corso.id_gruppo FROM corso,iscrizioni_corso,edizioni WHERE 
corso.id_corso=iscrizioni_corso.id_corso AND iscrizioni_corso.id_corso=edizioni.id_corso AND iscrizioni_corso.id_edizione=edizioni.id_edizione AND 
edizioni.stato='attiva' AND 
iscrizioni_corso.id_utente='$id_utente_form'";
		$result=$mysqli->query($query);
	
		if ($result->num_rows==1) {
			$riga=$result->fetch_array();
			$id_corso=$riga["id_corso"];
			$id_edizione=$riga["id_edizione"];
			$id_gruppo=$riga["id_gruppo"];
	
			$query="SELECT id_tutor FROM gruppo_utenti WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
			$result=$mysqli->query($query);
			$riga=$result->fetch_array();
			$id_tutor=$riga["id_tutor"];
	
			$valore =$id_corso." ".$id_edizione." ".$id_gruppo." ".$id_tutor;
			setcookie("kairos_cookie[2]",$valore,0,"/",$dominio);
			
			$query="REPLACE INTO contesto SET
			id_utente='$id_utente_form',
			id_corso='$valore'";
			$mysqli->query($query);

		};
	};	
	
	$query="SELECT * FROM contesto WHERE id_utente='$id_utente_form'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$valore=$riga[id_corso];
	if ($valore) {
		list($id_corso,$id_edizione,$id_gruppo_s,$id_tutor_s)=split(" ",$valore);
		$query="SELECT id_gruppo FROM iscrizioni_corso WHERE id_utente='$id_utente_form' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		$id_gruppo=$riga["id_gruppo"];

		$query="SELECT id_tutor FROM gruppo_utenti WHERE id_gruppo='$id_gruppo' AND id_corso='$id_corso' AND id_edizione='$id_edizione'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		$id_tutor=$riga["id_tutor"];
	
		$valore =$id_corso." ".$id_edizione." ".$id_gruppo." ".$id_tutor;

		setcookie("kairos_cookie[2]",$valore,0,"/",$dominio);
	};

    if($_REQUEST["social"]){
            $url = "index.php?risorsa=index";
    }
	
	if ($url) {
		header("Location:$url");
	} else {
		header("Location:index.php?risorsa=index");
	};
	exit();
} else {
	$msg=$stringa[errore_no_parametri];
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
}
?>
