<?php
$id_articolo=$_REQUEST["id_articolo"];

$query="SELECT * FROM articolo WHERE id_articolo='$id_articolo'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$id_autore=$riga["id_utente"];
$titolo=$riga["titolo"];
$sommario = str_replace("\n","<br>",$riga["sommario"]);
$id_rubrica=$riga["id_rubrica"];
$testo=$riga["testo"];
//$testo = str_replace("\n","<br>",$riga["testo"]);
//$area_link = ereg_replace("\n","<br>",$riga["area_link"]);
//$area_link = parse_link($area_link);
$area_link=split("\n",$riga["area_link"]);
$area_label=split("\n",$riga["area_label"]);

$stato=$riga["stato"];

$data_articolo=$riga["data_articolo"];
$data = date("d/m/Y",strtotime($data_articolo));

$immagine=false;
$file_immagine = $PATH_ROOT_FILE."immagini/$cod_area/im_".$id_articolo.".gif";
$file_immagine = strtolower($file_immagine);

if (file_exists($file_immagine)) {
	$nome_immagine = "im_".$id_articolo.".gif";
	$nome_immagine = strtolower($nome_immagine);
	$immagine = true;
};

if (!$immagine) {
	$file_immagine = $PATH_ROOT_FILE."immagini/$cod_area/im_".$id_articolo.".jpg";
	$file_immagine = strtolower($file_immagine);
	if (file_exists($file_immagine)) {
		$nome_immagine = "im_".$id_articolo.".jpg";
		$nome_immagine = strtolower($nome_immagine);
		$immagine = true;
	};
};


if ($id_utente) {
	$query="SELECT nome,cognome,email FROM utenti WHERE id_utente='$id_utente'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$nome=$riga["nome"];
	$cognome=$riga["cognome"];
	$email=$riga["email"];
};

$query="SELECT nome,cognome,email FROM utenti WHERE id_utente='$id_autore'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$nome_autore=$riga["nome"];
$cognome_autore=$riga["cognome"];
$email_autore=$riga["email"];

$query="SELECT titolo FROM rubrica WHERE id_rubrica='$id_rubrica'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$titolo_rubrica=$riga["titolo"];

?>

<!-- CONTENUTO DELLA PAGINA -->

<table width="100%" border="0" cellspacing=2 cellpadding=0>
  <tr>  

<!-- SECONDA COLONNA -->
  	<?php 

		echo "<td valign=\"TOP\" width=\"70%\" align=left>";
		
		echo "
		<table border=0 bgcolor=#706EA0 width=100%>
		<tr><td>
		<span class=testonegativo><b>$titolo_rubrica</b></span>
		</td></tr>
		</table>\n";
			
   echo "
   <p><span class=testo><b>$titolo</b></span></p>
   <p><span class=testo><i>$sommario<br></i></span></p>";

	if ($immagine) {
		echo "<img src=\"immagini/$cod_area/$nome_immagine\" border=0 align=left hspace=5 vspace=5>";
	};
	
	echo "
    <p><span class=testo>$testo</span></p>
	<p><span class=testo><i>$data $id_autore</i></span></p>";


echo "<hr size=1>";
if (count($area_link)>0) { 
	echo "	
     <p><span class=testo><b>Link consigliati</b></span></p>
	";
	for ($i=0;$i<count($area_link);$i++) {
		$link=$area_link[$i];
		$label=$area_label[$i];
		echo "<p><span class=testo><a href=$link target=_blank>$label</a><br></span></p>";
	};
	echo "<hr size=1>";
};

if ($id_utente) {
echo "
<form action=commento_nuovo.php method=post>
<input type=hidden name=id_articolo value=\"$id_articolo\">
<input type=hidden name=id_lettore value=\"$id_utente\">
<table border=0>
<tr>
<td colspan=2>
<span class=testo>Aggiungi un commento a questo articolo:</span>
</td>
</tr>
<tr>
<td colspan=2 align=right><textarea name=testo rows=04 cols=40></textarea></td>
</tr>
<tr>
<td align=right><span class=testo>Lettore:</span></td>
<td><span class=testo>$id_utente</span></td>
</tr>
<tr>
<td colspan=2 align=right>
<input type=submit value=\"Aggiungi commento\">
</td>
</tr>
</table>";
} else {
	echo "<p><span class=testopiccolo>Puoi aggiungere un commento a questo articolo ma prima devi effettuare <b>login</b> dalla <a href=index.php?risorsa=index>home page</a>. </span></p><p>&nbsp;</p>";
};

$query="SELECT id_commento,nome_lettore,email_lettore,testo,date_format(data_commento,\"%d/%m/%Y %H:%i:%s\") as data_com FROM commento WHERE id_articolo='$id_articolo' ORDER BY data_commento DESC";
$result=$mysqli->query($query);

if ($result->num_rows) {
	echo "
	<hr size=1>
	<span class=testo><b>I commenti dei lettori</b></span><br><br>
	<table border=0 width=450 cellpadding=3>";
	while ($riga=$result->fetch_array()) {
		$id_commento=$riga["id_commento"];
		$id_lettore=$riga["nome_lettore"];
		$testo=ereg_replace("&nbsp;"," ",$riga["testo"]);
		$data_com = $riga["data_com"];
		echo "
		<tr>
		<td width=450>
		";
		echo "		
			<span class=testo><a class=miolink href=\"javascript:;\" title=\"Clicca per sapere chi ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½...\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_lettore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\"><b>$id_lettore</b></a></span>";
		echo " - <span class=testo>$data_com</span>
		</td>
		</tr>
		<tr>
		<td width=450><span class=testo>$testo</span>
		";
		
		if ($ruolo=='admin' or $ruolo=='staff') {
			echo "<p><span class=testo>[<a href=commento_del.php?id_commento=$id_commento&id_articolo=$id_articolo>Cancella</a>]</span></p>";
		};
		
		echo "	
		</td>
		</tr>

		<tr>
		<td width=450><hr size=1></td>
		</tr>
		";		
	};
	echo "</table>";
} else {
	echo "<p>&nbsp;</p>";
};

?>
           
		
	</td>
	<!-- FINE SECONDA COLONNA -->
	
	<td valign=top width=1 bgcolor=#cccccc >
	<img src="img/pixel.gif" width="1" height="1" alt="" border="0">
	</td>

		<?php 
			
			echo "<td valign=\"TOP\" width=\"30%\" align=left>";

			echo "
			<table border=0 bgcolor=#706EA0 width=100%>
			<tr><td>
			<span class=testopiccolonegativo><b>RUBRICHE</b></span>
			</td></tr>
			</table>\n";
		
			$db = mysql_connect("localhost",$DBUSER,$DBPWD);
			mysql_select_db($DBASE,$db);	
			$query="SELECT id_rubrica,titolo FROM rubrica ORDER BY posizione";
			$result=$mysqli->query($query);
			echo "<table border=0 cellspacing=5 cellpadding=5><tr><td>";
			while ($riga=$result->fetch_array()) {
				$id_rubrica=$riga["id_rubrica"];
				$titolo=$riga["titolo"];
	
				echo "
				<p>
				<span class=testo><a href=index.php?risorsa=rubrica_view&id_rubrica=$id_rubrica&pagina=1&pag_size=10><b>$titolo</b></a>
				</span>
				</p>
				";
				
			};		
			echo "</td></tr></table>";
		
		?>   
		<br><br>
	</td>
  </tr>
</table>

<!-- FINE CONTENUTO DELLA PAGINA -->
