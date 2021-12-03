<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$db = mysql_connect(C_DB_HOST,C_DB_USER,C_DB_PASS);
mysql_select_db(C_DB_NAME,$db);

$chat_op=$_REQUEST["chat_op"];
$id_utente_abilitato=$_REQUEST["id_utente_abilitato"];
$chat_stanza=$_REQUEST["chat_stanza"];
$id_utente=$kairos_cookie[0];
$ruolo=ruolo_utente($id_utente);

$query="SELECT * FROM c_moderazione WHERE id_stanza='$chat_stanza'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$id_moderatore=$riga[id_moderatore];

switch ($chat_op) {
	case "chatlibero":
		if ($id_moderatore==$id_utente or $ruolo=="admin") {
			$query="DELETE FROM c_moderazione WHERE id_stanza='$chat_stanza'";
			$result=$mysqli->query($query);
			$msg="Il chat ora ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ libero! :)";
		};
		break;
		
	case "chatmoderato":
		if ($ruolo=="staff" or $ruolo=="admin") {
			$query="INSERT INTO c_moderazione SET
			id_moderatore='$id_utente',
			id_stanza='$chat_stanza',
			time_out='".time()."'";
			$result=$mysqli->query($query);
			$msg="Il chat ora ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ moderato da $id_utente. Per prendere la parola bisogna prenotarsi alzando la mano.";
		};
		break;
		
	case "alzolamano":
		$msg="$id_utente alza la mano";
		break;
		
	case "si":
		$query = "LOCK TABLES c_moderazione";
		$result=$mysqli->query($query);
		
		$query="SELECT si FROM c_moderazione WHERE id_stanza='$chat_stanza'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		$si=$riga[si]+1;
		
		$query="UPDATE c_moderazione SET si='$si' WHERE id_stanza='$chat_stanza'";
		$result=$mysqli->query($query);
		
		$query = "UNLOCK TABLES";
		$result=$mysqli->query($query);	
		
		$msg="$id_utente dice SÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½";
		break;
	
	case "no":
		$query = "LOCK TABLES c_moderazione";
		$result=$mysqli->query($query);
		
		$query="SELECT no FROM c_moderazione WHERE id_stanza='$chat_stanza'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		$no=$riga[no]+1;
		
		$query="UPDATE c_moderazione SET no='$no' WHERE id_stanza='$chat_stanza'";
		$result=$mysqli->query($query);
		
		$query = "UNLOCK TABLES";
		$result=$mysqli->query($query);
		
		$msg="$id_utente dice No";
		break;
	
	case "azzerapoll":
		if ($id_moderatore==$id_utente or $ruolo=="admin") {
			$query="UPDATE c_moderazione SET si='0',no='0' WHERE id_stanza='$chat_stanza'";
			$result=$mysqli->query($query);
			$msg="I contatori (SÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½/No) sono stati azzerati.";
		};
		break;
		
	case "Ok":
		if ($id_moderatore==$id_utente or $ruolo=="admin") {
			$query="UPDATE c_moderazione SET id_utente_abilitato='$id_utente_abilitato' WHERE id_stanza='$chat_stanza'";
			$result=$mysqli->query($query);
			$msg="PuÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ parlare $id_utente_abilitato";
		};
		break;
};

			
/* rimuovo gli eventuali slash */

$riga_chat = stripslashes ($msg);


/* ok, se l'utente ha scritto qualcosa, la aggiungo al file insieme alla data, all'ora e al suo identificativo */

if ($riga_chat){
	
	$M=$riga_chat;

	$riga_chat=addslashes($M);
	
	
	$query="INSERT INTO ".C_MSG_TBL." VALUES ('', '$chat_stanza', '', '', ".time().", '', '/moderazione $riga_chat')";

	$mysqli->query($query);
	//echo mysql_error();
	
	$query="SELECT username FROM ".C_USR_TBL." WHERE username='$id_utente'"; 
	$result=$mysqli->query($query);
	$riga_utente=$result->fetch_array();
	
	if ($riga_utente["username"]) {
		$query="UPDATE ".C_USR_TBL." SET room='$chat_stanza',u_time='".time()."', status='' WHERE username='$id_utente'"; 
	} else {
		$query="INSERT INTO ".C_USR_TBL." VALUES ('$chat_stanza', '$id_utente', '1', ".time().", '')";
	};
	
	$mysqli->query($query);
}



Header("Location:utenti_chat.php");

?>
