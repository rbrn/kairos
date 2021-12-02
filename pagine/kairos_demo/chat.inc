<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td>";

echo "
<table border=0 width=100% cellspacing=0 cellpadding=0>
<tr>";
echo "
<td valign=top width=67% class=titolodot>".strtoupper($stringa[chat])."</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=30%>&nbsp;</td>";
echo "</tr>";

echo "<tr><td valign=top width=67%>";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td>";

echo "	
<p>
<span class=testopiccolo>$stringa[chat_intro]</span>
</p>
";

echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr>
<td valign=top>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
<tr><td>
";

$tempo=time() - 2 * 60 * 60;
$query="DELETE FROM ".C_MSG_TBL." WHERE m_time < $tempo";
$result=$mysqli->query($query);

$tempo=time() - 2 * 60 * 60;
$query="DELETE FROM ".C_USR_TBL." WHERE u_time < $tempo";
$result=$mysqli->query($query);

require "./include/mysql.class.inc";
$DbLink = new DB;		

for($i = 0; $i < count($DefaultChatRooms); $i++)
{
	$tmpRoom = stripslashes($DefaultChatRooms[$i]);
	$id_tmpRoom=$tmpRoom;
	//if ($id_corso_s) $id_tmpRoom =$tmpRoom."_".$id_corso_s;
	
	$DbLink->query("SELECT DISTINCT username FROM  ".C_USR_TBL."  WHERE room = '$id_tmpRoom'");
	$Nb = $DbLink->num_rows();
							
		echo "
		&nbsp;<img src=\"img/ico_forum.gif\" width=\"12\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testo>
		<a href=chat_entra.php?stanza=$id_tmpRoom>$stringa[$tmpRoom]</a> (</span>";
		if (!$Nb) {
			echo "<span class=testopiccolo>0</span>";
			$query="DELETE FROM musica_chat WHERE stanza='$id_tmpRoom'";
			$mysqli->query($query);
			
			$query="DELETE FROM musica_chat_stato WHERE stanza='$id_tmpRoom'";
			$mysqli->query($query);

		} else {
			for ($j=1;$j<=$Nb;$j++) {
				list($id_utente1) = $DbLink->next_record();
				echo "
				<span class=testopiccolo>
				<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente1',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente1</a>
</span>";		
			};
		};
		echo "<span class=testo>)</span><br>";	

};

if ($id_corso_s) {
	$DbLink->query("SELECT descrizione FROM corso WHERE id_corso = '$id_corso_s'");
	list($descrizione_corso) = $DbLink->next_record();
	$nome_stanza=$descrizione_corso;
	$id_tmpRoom=$id_corso_s;
	
	$DbLink->query("SELECT DISTINCT username FROM  ".C_USR_TBL."  WHERE room = '$id_tmpRoom'");
	$Nb = $DbLink->num_rows();
							
	echo "
		&nbsp;<img src=\"img/ico_forum.gif\" width=\"12\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testo>
		<a href=chat_entra.php?stanza=$id_tmpRoom>$nome_stanza</a> (</span>";
	if ($Nb==0) {
		echo "<span class=testopiccolo>0</span>";
		$query="DELETE FROM musica_chat WHERE stanza='$id_tmpRoom'";
		$mysqli->query($query);
			
		$query="DELETE FROM musica_chat_stato WHERE stanza='$id_tmpRoom'";
		$mysqli->query($query);
			
	} else {
		for ($j=1;$j<=$Nb;$j++) {
			list($id_utente1) = $DbLink->next_record();
			echo "
			<span class=testopiccolo>
			<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente1',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente1</a>
</span>";		
		};
	};
	echo "<span class=testo>)</span><br>";		

	$nome_stanza="Laboratorio $descrizione_corso";
	$id_tmpRoom="lab_".$id_corso_s;
	
	$DbLink->query("SELECT DISTINCT username FROM  ".C_USR_TBL."  WHERE room = '$id_tmpRoom'");
	$Nb = $DbLink->num_rows();
							
	echo "
		&nbsp;<img src=\"img/ico_forum.gif\" width=\"12\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testo>
		<a href=chat_entra.php?stanza=$id_tmpRoom>$nome_stanza</a> (</span>";
	if ($Nb==0) {
		echo "<span class=testopiccolo>0</span>";
	} else {
		for ($j=1;$j<=$Nb;$j++) {
			list($id_utente1) = $DbLink->next_record();
			echo "
			<span class=testopiccolo>
			<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente1',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente1</a>
</span>";		
		};
	};
	echo "<span class=testo>)</span><br>";		
	
	if ($ruolo<>'staff' and $ruolo<>'admin' ) {
		$query_gruppo="SELECT a.id_gruppo,a.descrizione FROM gruppo_utenti as a,iscrizioni_gruppo_pw as b WHERE a.id_corso=b.id_corso AND a.id_edizione=b.id_edizione AND a.id_gruppo=b.id_gruppo AND a.tipo_gruppo=1 AND a.id_corso='$id_corso_s' AND a.id_edizione='$id_edizione_s' AND b.id_utente='$kairos_cookie[0]' ORDER BY id_gruppo";
		$result_gruppo=$mysqli->query($query_gruppo);
		if ($result_gruppo->num_rows) {
			while ($riga_gruppo=$result_gruppo->fetch_array()) {
				$id_gruppo_s=$riga_gruppo["id_gruppo"];
				$descr_gruppo_s=$riga_gruppo["descrizione"];
				$nome_stanza=$descr_gruppo_s;
				$id_tmpRoom=$id_corso_s."-".$id_gruppo_s;
				$DbLink->query("SELECT DISTINCT username FROM  ".C_USR_TBL."  WHERE room = '$id_tmpRoom'");
				$Nb = $DbLink->num_rows();
							
				echo "
		&nbsp;<img src=\"img/ico_forum.gif\" width=\"12\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testo>
		<a href=chat_entra.php?stanza=$id_tmpRoom>$nome_stanza</a> (</span>";
				if ($Nb==0) {
					echo "<span class=testopiccolo>0</span>";
				} else {
					for ($j=1;$j<=$Nb;$j++) {
						list($id_utente1) = $DbLink->next_record();
						echo "
			<span class=testopiccolo>
			<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente1',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente1</a>
</span>";		
					};
				};
				echo "<span class=testo>)</span><br>";		
				
			};
		};
	};
	
	if ($ruolo=='staff' or $ruolo=='admin' ) {
		$query_gruppo="SELECT id_gruppo,descrizione FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND tipo_gruppo=1 ORDER BY id_gruppo";
		$result_gruppo=$mysqli->query($query_gruppo);
		if ($result_gruppo->num_rows) {
			while ($riga_gruppo=$result_gruppo->fetch_array()) {
				$id_gruppo_s=$riga_gruppo["id_gruppo"];
				$descr_gruppo_s=$riga_gruppo["descrizione"];
				$nome_stanza=$descr_gruppo_s;
				$id_tmpRoom=$id_corso_s."-".$id_gruppo_s;
				$DbLink->query("SELECT DISTINCT username FROM  ".C_USR_TBL."  WHERE room = '$id_tmpRoom'");
				$Nb = $DbLink->num_rows();
							
				echo "
		&nbsp;<img src=\"img/ico_forum.gif\" width=\"12\" height=\"10\" alt=\"\" border=\"0\">&nbsp;<span class=testo>
		<a href=chat_entra.php?stanza=$id_tmpRoom>$nome_stanza</a> (</span>";
				if ($Nb==0) {
					echo "<span class=testopiccolo>0</span>";
				} else {
					for ($j=1;$j<=$Nb;$j++) {
						list($id_utente1) = $DbLink->next_record();
						echo "
			<span class=testopiccolo>
			<a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_utente1',                   'myRemoteUtente',        'height=400,width=450,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_utente1</a>
</span>";		
					};
				};
				echo "<span class=testo>)</span><br>";		
				
			};
		};
	};
	
};
	
echo "
</td></tr>
</table>
</td></tr>
</table>";

echo "
</td></tr>
</table>";

echo "</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=30%>";

echo "		
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro_neutro\">

<tr> 
<td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testo\" height=\"21\"> 
<span class=titolo><img src=\"img/ico_chat_archivio.gif\" width=\"19\" height=\"12\" alt=\"\" border=\"0\">&nbsp;<b>$stringa[archivio_chat]</b></span>
</td>
</tr>

<tr><td>";

echo "
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo_neutro\" width=\"100%\">
<tr><td align=center>
<a href=\"index.php?risorsa=form_monitor_chat\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_1','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" name=\"img_apri_1\" align=\"middle\"></a>&nbsp;<a href=index.php?risorsa=form_monitor_chat onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_1','','img/ico_apri_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[apri])."</span></a>
</td></tr>
</table>";

echo "</td></tr></table>";

//if ($wimba and ($ruolo=='admin' or $ruolo=='staff')) {
if ($wimba) {
echo "	
<br>	
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro_neutro\">

<tr> 
<td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testo\" height=\"21\"> 
<span class=titolo><img src=\"img/ico_chat_archivio.gif\" width=\"19\" height=\"12\" alt=\"\" border=\"0\">&nbsp;<b>Audio Chat</b></span>
</td>
</tr>

<tr><td>";

echo "
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo_neutro\" width=\"100%\">
<tr><td align=center>
<a href=\"index.php?risorsa=audio_chat\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_2','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"$stringa[apri]\" border=\"0\" name=\"img_apri_2\" align=\"middle\"></a>&nbsp;<a href=index.php?risorsa=audio_chat onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_apri_2','','img/ico_apri_over.gif',1)\"><span class=testopiccolo>".strtoupper($stringa[apri])."</span></a>
</td></tr>
<tr><td align=left>
<span class=\"testopiccolo\">
Dopo aver scaricato l'applet inserisci il tuo identificativo nel campo <b>Screen name</b> e quindi entra. 
</span>
</td></tr>
</table>";

echo "</td></tr>
</table>";
};


echo "
</td></tr>
</table>";

echo "
</td></tr>
</table>";
?>
