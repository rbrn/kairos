<table border=0 width=100% cellspacing=10 cellpadding=0>

<tr>
<td class=titolodot>
<?php echo(strtoupper($stringa[cerca_materiali]));?>
</td>
</tr>

<?php
echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";
?>

<tr><td>


<?php
$stringa_cerca=$_REQUEST["stringa_cerca"];
$cerca_in=$_REQUEST["cerca_in"];
$pagina=$_REQUEST["pagina"];
$pag_size=$_REQUEST["pag_size"];

if (!$stringa_cerca) {
	echo "<p><span class=testo>$stringa[inserisci_stringa]</span></p>";
	exit();
};


if ($cerca_in=="corso") {
	$tabella="risorse_materiali";
	$azione="materiali_browse.php?risorsa=";
	$where_mat="";
} else {
	$tabella="lab_materiali";
	$azione="index.php?risorsa=lab_materiali_view&id_risorsa=";
	$where_mat="id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND ";
};
	
$query = "SELECT id_risorsa,id_autore,risorsa_padre,titolo,descrizione,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m FROM $tabella WHERE $where_mat (titolo like '%$stringa_cerca%' OR descrizione like '%$stringa_cerca%' OR parole_chiave like '%$stringa_cerca%') AND (tipo=0 or tipo=1 or tipo=4) ORDER BY id_risorsa";
$result=$mysqli->query($query);

$tot_righe=$result->num_rows;

if (!$tot_righe) {
	echo "<p><span class=testo>$stringa[non_trovato]</span></p>";
	exit();
};

$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$inizio=$pag_size*($pagina-1);
$query .= " LIMIT $inizio,$pag_size";
$result=$mysqli->query($query);

$progr=$inizio+1;

$righe=1;
while ($risorsa=$result->fetch_array()) {
	$id_risorsa = $risorsa["id_risorsa"];
	$id_autore=$risorsa["id_autore"];
	$titolo=$risorsa["titolo"];
	$descrizione=$risorsa["descrizione"];
	$file_size=$risorsa["file_size"];
	$tipo = $risorsa["tipo"];
	$data_m = $risorsa["data_m"];
	$risorsa_padre=$risorsa["risorsa_padre"];
	if ($cerca_in=="corso") {
		$id_modulo=id_corso($id_risorsa);
		$query_modulo="SELECT titolo FROM risorse_materiali WHERE id_risorsa='$id_modulo'";
		$result_modulo=$mysqli->query($query_modulo);
		$riga_modulo=$result_modulo->fetch_array();
		$titolo_modulo=$riga_modulo[titolo];
	} else {
		$query_modulo="SELECT titolo FROM lab_materiali WHERE id_risorsa='$risorsa_padre'";
		$result_modulo=$mysqli->query($query_modulo);
		$riga_modulo=$result_modulo->fetch_array();
		$titolo_modulo=$riga_modulo[titolo];
	};
	
	$link=true;
	if ($ruolo<>'staff' and $ruolo<>'admin' and $cerca_in=='corso') {
		if (!risorsa_accessibile($id_risorsa)) {
			$link=false;
		};
	};
	
	
 	switch ($tipo) {
			case 0:
				echo "<li style=\"list-style-type:none\">\n";
				echo "
			<img src=img/pagina_web.gif width=16 height=16 border=0> <span class=testo>";
				if ($link) {
					echo "<a href=$azione"."$id_risorsa  title=\"$titolo\">$titolo</a>";
				} else {
					echo "$titolo";
				};
				echo " ($titolo_modulo)</span><br>\n";	
				echo "</li><br>\n";
				break;
				
			case 4:
				echo "<li style=\"list-style-type:none\">\n";
				echo "
			<img src=img/pagina_web_link.gif width=16 height=16 border=0> <span class=testo>";
				if ($link) {
					echo "<a href=$azione"."$id_risorsa  title=\"$titolo\">$titolo</a>";
				} else {
					echo "$titolo";
				};
				echo " ($titolo_modulo)</span><br>\n";	
				echo "</li><br>\n";
				break;	

			case 1:
				$icona="file.gif";			
				$est = substr($titolo,-3);
				$tipi_file = array ("zip","exe","xls","doc","pdf","rtf","jpg","gif","mid","mp3",
							"wav","avi","htm","txt","mpg","bmp","ppt");
				if (in_array($est,$tipi_file)) {
					$icona=$est.".gif";
				}; 
				
				echo "<li style=\"list-style-type:none\">\n";
				echo "
			<img src=img/".$icona." width=16 height=16 border=0> <span class=testo>";
				if ($link) {
					echo "<a href=$azione"."$id_risorsa title=\"$titolo\">$titolo - ".stringa_filesize($file_size)."</a>"; 
				} else {
					echo "$titolo - ".stringa_filesize($file_size);
				};
				
				echo " ($titolo_modulo)<br>
$descrizione</span><br>\n";	
				echo "</li><br>\n";
				break;
		};

	$righe++;
	
};      
?>		
<?php
echo "<br><span class=testopiccolo>$stringa[pagine]:&nbsp";
$i=1;
while ($i<=$tot_pag) {
	if ($i==$pagina) {
		echo "[<b>$i</b>]";
	} else {
		echo "
		[<a href=index.php?risorsa=cerca_materiali&pagina=$i&pag_size=$pag_size&stringa_cerca=$stringa_cerca&cerca_in=$cerca_in>$i</a>]
		";
	};
	$i++;
};
echo "</span>";	
?>
</td>
  </tr>
</table>
<br>
