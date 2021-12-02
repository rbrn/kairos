<?php
function mostra_staff($ruolo) {
	global $DBASE,$DBUSER,$DBPWD,$USER_ADMIN,$id_corso_s,$id_edizione_s,$id_gruppo_s;
	global $stringa;
	$db = mysql_connect("localhost",$DBUSER,$DBPWD);
	mysql_select_db($DBASE,$db);	
	
	switch ($ruolo) {
		case "direttore":
			$query="SELECT  utenti.nome,utenti.cognome,ruolo_utenti.id_utente FROM ruolo_utenti,utenti WHERE 
utenti.id_utente=ruolo_utenti.id_utente AND
ruolo_utenti.ruolo='$ruolo' AND ruolo_utenti.id_corso='$id_corso_s'  AND ruolo_utenti.id_edizione='$id_edizione_s'";
			break;
		
		case "coordinatore":
			$query="SELECT  utenti.nome,utenti.cognome,ruolo_utenti.id_utente FROM ruolo_utenti,utenti WHERE 
utenti.id_utente=ruolo_utenti.id_utente AND
ruolo_utenti.ruolo='$ruolo' AND ruolo_utenti.id_corso='$id_corso_s'  AND ruolo_utenti.id_edizione='$id_edizione_s'";
			break;
			
		case "autore":
			$query="SELECT  utenti.nome,utenti.cognome,utenti.id_utente FROM materiali_sequenza,risorse_materiali,utenti 
WHERE 
materiali_sequenza.id_corso='$id_corso_s' AND
materiali_sequenza.id_edizione='$id_edizione_s' AND
materiali_sequenza.id_risorsa=risorse_materiali.id_risorsa AND
risorse_materiali.id_autore=utenti.id_utente";
			break;
		
		case "tutor":
			$query="SELECT  utenti.nome,utenti.cognome,utenti.id_utente,gruppo_utenti.descrizione FROM gruppo_utenti,utenti 
WHERE 
gruppo_utenti.id_corso='$id_corso_s' AND 
gruppo_utenti.id_edizione='$id_edizione_s' AND 
gruppo_utenti.id_tutor=utenti.id_utente";
			break;
		
		case "docente":
			$query="SELECT  utenti.nome,utenti.cognome,ruolo_utenti.id_utente FROM ruolo_utenti,utenti WHERE 
utenti.id_utente=ruolo_utenti.id_utente AND
ruolo_utenti.ruolo='$ruolo' AND ruolo_utenti.id_corso='$id_corso_s' AND ruolo_utenti.id_edizione='$id_edizione_s'";
			break;
		
		case "esperto":
			$query="SELECT utenti.nome,utenti.cognome,ruolo_utenti.id_utente FROM ruolo_utenti,utenti WHERE 
utenti.id_utente=ruolo_utenti.id_utente AND
ruolo_utenti.ruolo='$ruolo' AND ruolo_utenti.id_corso='$id_corso_s'  AND ruolo_utenti.id_edizione='$id_edizione_s'";
			break;
				
	};
	
	$result=$mysqli->query($query);
	
	
	if ($result->num_rows) {
	$str="staff_".$ruolo;
	
	echo "
<table border=0 cellpadding=5>
<tr><td><span class=testopiccolo><b>$stringa[$str]</b></span></td></tr>";

	$nomi=array();
	while ($riga=$result->fetch_array()) {
		$id_ut=$riga[id_utente];
		if (!in_array($id_ut,$nomi)) {
		$nome=$riga[nome];
		$cognome=$riga[cognome];
		$descrizione="";
		//if ($ruolo=="tutor") $descrizione=$riga[descrizione].": ";
		echo "<tr><td>
		<span class=testo>$descrizione<a href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_ut',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$nome $cognome ($id_ut)</a></span></td></tr>";
		$nomi[]=$id_ut;
		};
		
	};
	echo "
	</table>
	";
	};
	
};

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[staff])."</td></tr>";

echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";

echo "
<tr><td>";



mostra_staff("direttore");
mostra_staff("coordinatore");

if ($id_corso_s) {
	mostra_staff("tutor");
	//mostra_staff("autore");
	mostra_staff("docente");
	mostra_staff("esperto");
};

?>
</td></tr></table>
<br>
