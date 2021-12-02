<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_utente1=$kairos_cookie[0];
$id_utente=$_REQUEST["id_utente"];

if (!$id_utente1) {
	echo "
	<html>
	<head><title>Sulaina: $stringa[errore]</title>
	<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
	<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
	</HEAD>
	<BODY bgcolor=$colore_sfondo>
	<span class=testo>$stringa[errore_no_login]</span>
	</body>
	</html>";
	exit();
};

if ($kairos_cookie[0]=='ospite' and $cod_area=='kairos_eprof') {
	echo "
	<html>
	<head><title>Sulaina: $stringa[errore]</title>
	<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
	<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
	</HEAD>
	<BODY bgcolor=$colore_sfondo>
	<span class=testo>Non puoi accedere a questa funzione o area.</span>
	</body>
	</html>";
	exit();
};

$query="SELECT * FROM utenti WHERE id_utente='$id_utente'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();

$pwd_utente=$riga["pwd_utente"];
$nome=$riga["nome"];
$cognome=$riga["cognome"];
$indirizzo=$riga["indirizzo"];
$cap=$riga["cap"];
$citta=$riga["citta"];
$prov=$riga["prov"];
$scuola=$riga["scuola"];
$telefono=$riga["telefono"];
$email=$riga["email"];
$sitoweb=$riga["sitoweb"];
$sesso=$riga["sesso"];
$eta=$riga["eta"];
$professione=$riga["professione"];
$interesse=$riga["interesse"];
$newsletter=$riga["newsletter"];
$privacy=split(",",$riga["privacy"]);
$biografia=$riga["biografia"];
$ruolo_scuola=$riga["ruolo_scuola"];
$materia=$riga["materia"];
$id_eproffaro=$riga["id_eproffaro"];


if (!$kairos_cookie[9]) $ruolo_utente=ruolo_utente($id_utente1);

header("Cache-Control: no-cache");
header("Pragma: no-cache");
?>
<html>
<head>
<title><?php echo"$stringa[utente]: $id_utente";?></title>
<?php 
echo "
<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">";
?>
</head>
<BODY bgcolor=<?php echo($colore_sfondo_neutro);?>>
<p>&nbsp;</p>
<TABLE border=0 width=100%>
<TR>
<TD>
<span class=testo><b><?php echo($stringa[utente]);?>: <?php echo($id_utente); 

	if (!$kairos_cookie[9]) $ruolo=ruolo_utente($id_utente);

	switch($ruolo) {
	case "admin":
		echo " ($stringa[admin])";
		break;
	
	case 'staff':
		echo " ($stringa[staff])";
		break;
	};

echo "
<a class=miolink href=\"javascript:;\" title=\"$stringa[manda_messaggio]\" onclick=\"javascript:apri_scheda('form_messaggio_scrivi.php?id_utente=$id_utente','myRemotePosta',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowPosta');\"><img src=img/envelope.gif width=14 height=10 border=0></a>
";
?></b>


</span>



</TD>
<?php
$immagine=false;
$file_immagine = $PATH_ROOT_FILE."foto_utenti/$cod_area/".$id_utente.".gif";
$file_immagine = strtolower($file_immagine);

if (file_exists($file_immagine)) {
	$nome_immagine = "$id_utente.gif";
	$nome_immagine = strtolower($nome_immagine);
	$immagine = true;
};

if (!$immagine) {
	$file_immagine = $PATH_ROOT_FILE."foto_utenti/$cod_area/".$id_utente.".jpg";
	$file_immagine = strtolower($file_immagine);
	if (file_exists($file_immagine)) {
		$nome_immagine = "$id_utente.jpg";
		$nome_immagine = strtolower($nome_immagine);
		$immagine = true;
	};
};

$tag_img="";
$max_img_size=350;
if ($immagine) {
	$size=getimagesize("foto_utenti/$cod_area/$nome_immagine");
	$w=$size[0];
	$h=$size[1];
	
	while ($w>$max_img_size or $h>$max_img_size) {
	
		if ($w>$max_img_size) {
			$h=floor($h*$max_img_size/$w);
			$w=$max_img_size;
		};
		
		if ($h>$max_img_size) {
			$w=floor($w*$max_img_size/$h);
			$h=$max_img_size;
		};
		
	};

	$tag_img="<img src=\"foto_utenti/$cod_area/$nome_immagine\" ALT=\"$id_utente\" width=\"$w\" height=\"$h\">";
};

if ($immagine) {
	echo "<td valign=top>$tag_img</td>";
} else {
	echo "<td>&nbsp;</td>";
};
?>
</tr>

<TR>
<TD colspan=2>


            <TABLE border=0 width=100%>
			  <TR>
                <TD colSpan=2>
                  <HR>
                </TD></TR>
				
				<?php
				if ($cod_area=="kairos_atlanteragazzi" and $id_eproffaro) {
echo "<tr> <TD align=right><span class=testopiccolo><b>Insegnante E-Prof responsabile:</b></span></TD>
<td><span class=testopiccolo><b>$id_eproffaro</b></span>";
echo "</td></tr>";
};
				?>
					  
              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[nome]);?>:</b></span></TD>
                <TD>
				<span class=testopiccolo><?php echo($nome);?></span></TD></TR>

<?php if ($cod_area<>"kairos_amicosole" and $cod_area<>'kairos_oppla' and $cod_area<>"kairos_bandaingamba") { ?>
				
              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[cognome]);?>:</b></span></TD>
                <TD><span class=testopiccolo><?php echo($cognome);?></span></TD></TR>

<?php 
if ($cod_area<>'kairos_larimart') {
?>

			<?php 
			if (($ruolo_utente=='staff' or $ruolo_utente=='admin') and $email) {
				echo "
				<TR>
                <TD align=right><span class=testopiccolo><b>$stringa[email]:</b></span></TD>
                <TD><span class=testopiccolo><a href=mailto:$email>$email</a></span></TD></TR>";
			};
			?>
               
			  <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[citta]);?>:</b></span></TD>
                <TD><span class=testopiccolo><?php echo "$citta ($prov)";?></span></TD></TR>
             
       		  <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[scuola]);?>:</b></span></TD>
                <TD><span class=testopiccolo><?php echo($scuola);?></span></TD></TR>
              
			  <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[sitoweb]);?>:</b></span></TD>
                <TD><span class=testopiccolo><?php
				$sitoweb=trim($sitoweb);
				if ($sitoweb and $sitoweb<>"http://") {
					if (!eregi("^http://",$sitoweb)) {
						$sitoweb = "http://".$sitoweb;
					};
				    echo "<a href=$sitoweb target=_blank>$sitoweb</a>";
				};
				?></span></TD></TR>

		  	<?php
			/*
			$url_utente="";
			
			$file_utente_htm=$PATH_ROOT_FILE."utenti/$cod_area/$id_utente/index.htm";
			$file_utente_php=$PATH_ROOT_FILE."utenti/$cod_area/$id_utente/index.php";
			
			if (file_exists($file_utente_htm) or file_exists($file_utente_php)) {
				$url_utente=$PATH_ROOT."utenti/$cod_area/$id_utente";
			};
			
			if ($url_utente) {
				echo "
				  <TR>
                <TD align=right><span class=testopiccolo><b>$stringa[project_work]:</b></span></TD>
                <TD><span class=testopiccolo>
				    <a href=$url_utente target=_blank>$url_utente</a>
				</span>
				</TD></TR>
             	";
			};
			*/
			if ($id_corso_s) {
				$query_m="select id_risorsa FROM lab_materiali WHERE titolo='$id_utente' and tipo=2 and id_corso='$id_corso_s' and id_edizione='$id_edizione_s'";
				$result_m=$mysqli->query($query_m);
				$riga_m=$result_m->fetch_array();
				$id_cartella=$riga_m[id_risorsa];
				if ($id_cartella) {
					echo "
				  <TR>
                <TD align=right><span class=testopiccolo><b>$stringa[cartella_utente]:</b></span></TD>
                <TD><span class=testopiccolo>
				    <a style=\"cursor:hand;text-decoration:underline\" onclick=\"apri_cartella_utente('$id_cartella')\">$id_utente</a>
				</span>
				</TD></TR>
             	";
				};
			};
			
			?>
			
			<TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[ruolo_scuola]);?>:</b></span></TD>
                <TD><span class=testopiccolo><?php echo($ruolo_scuola);?></span></TD></TR>

			<TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[materia_insegnata]);?>:</b></span></TD>
                <TD><span class=testopiccolo><?php echo($materia);?></span></TD></TR>


			  <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[interessi]);?>:</b></span></TD>
                <TD><span class=testopiccolo><?php echo($interesse);?></span></TD></TR>

				<TR>
                <TD align=right valign=top><span class=testopiccolo><b><?php echo($stringa[qualcosa_di_me]);?>:</b></span></TD>
                <TD><TEXTAREA readonly name=biografia rows=10 cols=30><?php echo($biografia);?></textarea></TD></TR>

<?php 
};
?>


			<tr>
			<td colspan=2>
			<hr size=1>
			</td>
			</tr>
			
			<?php 
			if ($id_corso_s) {
				$query = "SELECT id_forum,id_post,oggetto,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post FROM forum_posts WHERE id_autore='$id_utente' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY id_post DESC LIMIT 8";
				$result=$mysqli->query($query);
				if ($result->num_rows) {
					echo "<tr><td valign=top colspan=2>
				<p><span class=testo><b>Interventi recenti nei forum di questo corso</b></span></p>
					";
					while ($intervento=$result->fetch_array()) {
						$id_post = $intervento["id_post"];
						$id_forum = $intervento["id_forum"];
						/*
						$query_forum = "SELECT * FROM forum WHERE id_forum='$id_forum'";
						$result_forum=$mysqli->query($query_forum);
						$riga_forum = $result_forum->fetch_array();	
						$titolo_forum=$riga_forum["descrizione"];
						*/
						$icona_post = $intervento["icona_post"];

						if (!$icona_post) $icona_post = "messaggio";

						if ($intervento["nome_file"]) {
							echo "<img src=img/forum/allegato.gif width=16 height=16 border=0>";
						};
		
						echo "<img src=img/forum/$icona_post.gif alt=$icona_post> ";
						echo "<span class=testopiccolo><a href=\"javascript:;\" onclick=\"goLocation('index.php?risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$id_post&vista=thread&modo=esteso')\">".$intervento["oggetto"]."</a></span>";
						//echo "<span class=testopiccolo><a href=\"javascript:;\" onclick=\"opener.document.location.href='index.php?risorsa=forum_mostra_post&id_forum=$id_forum&id_post=$id_post&vista=thread&modo=esteso'\">".$intervento["oggetto"]."</a></span>"; 
						//echo "<span class=testopiccolo><a href=\"javascript:;\" onclick=\"opener.showPost('$id_forum','$id_post','thread','1');\">".$intervento["oggetto"]."</a></span>"; 
						echo "&nbsp;<span class=testopiccolo><i>(".$intervento["data_p"].")</i></span><br>\n";

					};
					echo "<br><br></td></tr>";
				};
			};
			?>
			<tr>
			<td valign=top colspan=2>
			<?php storia_corsi($id_utente); ?>
			</td>
			</tr>
			
<?php }; ?>		
		</TABLE>
		<BR>
           
</TD></TR>


</TABLE>
</body>
</html>

