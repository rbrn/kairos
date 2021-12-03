<?php

require "./include/init_sito.inc";

require "./include/funzioni_sito.inc";


$db = mysql_connect(C_DB_HOST,C_DB_USER,C_DB_PASS);

mysql_select_db(C_DB_NAME,$db);



$id_utente=$kairos_cookie[0];
$riga_chat=$_REQUEST["riga_chat"];
$chat_stanza=$_REQUEST["chat_stanza"];
$C=$_REQUEST["C"];

refresh_utente($id_utente);

$query="SELECT * FROM c_moderazione WHERE id_stanza='$chat_stanza'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$id_moderatore=$riga[id_moderatore];
$id_utente_abilitato=$riga[id_utente_abilitato];
$ruolo=ruolo_utente($id_utente);

if ($id_moderatore) {
	if ($id_moderatore<>$id_utente and $id_utente<>$id_utente_abilitato and $ruolo<>"admin") {
		Header("Location:input_chat.php");
		exit();
	};
};


/* rimuovo gli eventuali slash */

$riga_chat = stripslashes ($riga_chat);


/* ok, se l'utente ha scritto qualcosa, la aggiungo al file insieme alla data, all'ora e al suo identificativo */

if ($riga_chat){
	
	//if ($id_utente=="maria_caggegi") $riga_chat="scusami tanto fleo";
	$M=$riga_chat;

	$M = eregi_replace("([[:alnum:]]+)://([^[:space:]]*)([[:alnum:]#\?/&=])", "<a href=\"\\1://\\2\\3\" target=\"_blank\">\\1://\\2\\3</A>", $M);

	$M = eregi_replace("(([a-z0-9_]|\\-|\\.)+@([^[:space:]]*)([[:alnum:]-])\.([^[:space:]]*)([[:alnum:]-]))", "<a href=\"mailto:\\1\">\\1</a>", $M);
	
	require "./include/smilies.inc";

	$riga_chat=addslashes($M);
	
	if (isset($_REQUEST["CookieColor"])) $CookieColor = $_REQUEST["CookieColor"];
	if(!isset($C)) {
		if(!isset($CookieColor)) {
			$C = "#000000";
		} else {
			$C = $CookieColor;
		}
	};
	if ($id_utente=="maria_caggegi" or $id_utente=="m") $C="#0000FF";
	setcookie("CookieColor", $C, time() + 60*60*24*365);
	
	$rc=$riga_chat;
	
	$riga_chat="<FONT COLOR=\"$C\">$riga_chat</FONT>";
	
	$query="SELECT username FROM ".C_USR_TBL." WHERE username='$id_utente'"; 
	$result=$mysqli->query($query);
	$riga_utente=$result->fetch_array();
	
	if ($riga_utente["username"]) {
		$query="UPDATE ".C_USR_TBL." SET room='$chat_stanza',u_time='".time()."', status='' WHERE username='$id_utente'"; 
	} else {
		$query="INSERT INTO ".C_USR_TBL." VALUES ('$chat_stanza', '$id_utente', '1', ".time().", '')";
	};
	
	$mysqli->query($query);
	
	
	$parole=split(" ",$rc);
	if (strtolower($parole[0])=="suona") {
		$brano=trim($parole[1]);
		if ($brano=="rapimento") {
			$riga_chat="<b>SIAMO UN GRUPPO ARMATO DI AGENTI DEL NETWORK TELEVISIVO<br>ABBIAMO OCCUPATO IL CHAT E CATTURATO CAPO DI STATO MAGGIORE FLEO E GENERALE ALBERTO PIAN IN OSTAGGIO<br>INTERROMPETE OGNI ULTERIORE TENTATIVO DI PODCAST<br>LA RETE E\' SOLO NOSTRA E LA CONTROLLIAMO NOI</b>";
			$id_utente="agente armato";
			$query="DELETE FROM ".C_MSG_TBL." WHERE room='$chat_stanza'";
			$mysqli->query($query);
		};
	};
	
	if (strtolower($parole[0])=="rapimento") {
		$brano=trim($parole[1]);
		if ($brano=="scrivi") {
			$riga_chat="<b>SIAMO UN GRUPPO ARMATO DI AGENTI DEL NETWORK TELEVISIVO<br>ABBIAMO OCCUPATO IL CHAT E CATTURATO CAPO DI STATO MAGGIORE FLEO E GENERALE ALBERTO PIAN IN OSTAGGIO<br>INTERROMPETE OGNI ULTERIORE TENTATIVO DI PODCAST<br>LA RETE E\' SOLO NOSTRA E LA CONTROLLIAMO NOI</b>";
			$id_utente="agente armato";
			$query="DELETE FROM ".C_MSG_TBL." WHERE room='$chat_stanza'";
			$mysqli->query($query);
		};
	};
	
	if ($id_utente=="garamond") $id_utente="";
	
	$query="INSERT INTO ".C_MSG_TBL." VALUES ('', '$chat_stanza', '$id_utente', '', ".time().", '', '$riga_chat')";

	$mysqli->query($query);

	
	//echo mysql_error();
	
	
	//if ($chat_stanza<>"Generale" and $cod_area=="kairos_masterunitus") {
	$query="INSERT INTO ".C_MSG_TBL_ARCH." VALUES ('', '$chat_stanza', '$id_utente', '', ".time().", '', '$riga_chat')";
	$mysqli->query($query);
	//}

	for ($i=0;$i<count($suoni_chat);$i++) {
		$pat=$suoni_chat[$i];
		if (ereg("\*$pat\*",$riga_chat)) {
			$query3="SELECT username FROM ".C_USR_TBL." WHERE room='$chat_stanza' ORDER BY username";
			$result3=$mysqli->query($query3);
			while ($riga3=$result3->fetch_array()) {
				$un=$riga3[username];
				$query2="INSERT INTO ".C_MSG_TBL." SET room='$chat_stanza', m_time=".time().", username='$un',message='*".$pat."_ascolta*'";
				$mysqli->query($query2);
			};
		};
	};
	
	//$parole=split(" ",$rc);
	if (strtolower($parole[0])=="suona") {
		$brano=trim($parole[1]);
		if ($brano=="stop") {
			$query="DELETE FROM musica_chat WHERE stanza='$chat_stanza'";
			$mysqli->query($query);
			$query="DELETE FROM musica_chat_stato WHERE stanza='$chat_stanza'";
			$mysqli->query($query);
		} else {
			if (file_exists("./juke_box/$brano".".mp3")) {
				$query="SELECT * FROM musica_chat WHERE stanza='$chat_stanza'";
				$result=$mysqli->query($query);
				$riga=$result->fetch_array();
				if ($riga) {
					$query="UPDATE musica_chat SET brano='$brano' WHERE stanza='$chat_stanza'";
					$mysqli->query($query);
				} else {
					$query="INSERT INTO musica_chat SET stanza='$chat_stanza',brano='$brano'";
					$mysqli->query($query);
				};
		
			}
		}
	}
}



/* reindirizzo alla pagina che mostra la finestra di chat aggiornata */

$refresh=1;


Header("Location:input_chat.php?refresh=$refresh");

?>
