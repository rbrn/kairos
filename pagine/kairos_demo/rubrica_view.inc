<!-- CONTENUTO DELLA PAGINA -->
<table width="100%" border="0" cellspacing=2 cellpadding=0>
<tr><td valign=top> 
<?php
$id_rubrica=$_REQUEST["id_rubrica"];
$pagina=$_REQUEST["pagina"];
$pag_size=$_REQUEST["pag_size"];

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	
$query="SELECT titolo FROM rubrica WHERE id_rubrica='$id_rubrica'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$titolo_rubrica=$riga["titolo"];
	
echo "<p><span class=titolopagina>$titolo_rubrica</span></p>";
$query="SELECT * FROM articolo WHERE id_rubrica='$id_rubrica' AND stato='approvato' ORDER BY data_articolo DESC";
$result=$mysqli->query($query);

$tot_righe=$result->num_rows;

$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

//scorro fino alla pagina
$num_pag=1;
$righe=0;
$continua=true;
$articolo = $result->fetch_array();
while ($num_pag<>$pagina and $continua) {
	if ($articolo) {
		$righe++;
	} else {
		$continua=false;
	};
	if ($righe>$pag_size) {
		$num_pag++;
		$righe=1;
	};
	if ($num_pag<>$pagina) {
		$articolo = $result->fetch_array();
	};
};

$righe=1;
$continua = true;
while ($articolo and  $continua) {
	$id_rubrica=$articolo["id_rubrica"];
	$titolo=$articolo["titolo"];
	$sommario=$articolo["sommario"];
	$id_articolo=$articolo["id_articolo"];
	$data_articolo=$articolo["data_articolo"];
	$id_autore = $articolo["id_utente"];
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
				
	echo "
	<table border=0 width=100% cellspacing=3 cellpadding=3 bgcolor=$colore_sfondo>
	<tr><td>";
		
	if ($immagine) {
		echo "<img src=immagini/$cod_area/$nome_immagine border=0 align=left hspace=5 vspace=5>";
	};
				
	echo "
	<span class=testo>
	<a href=index.php?risorsa=articolo_view&id_articolo=$id_articolo><b>$titolo</b></a>
	<br><br>
	$sommario
	<br><br>
	<i>$id_autore - $data</i>
	<br>
	</span>
	</td></tr>
	</table>";	

	$righe++;
	$articolo = $result->fetch_array();
	if ($righe > $pag_size) {
		$continua = false;
	};
};      
?>		
<?php
echo "<br><span class=testopiccolo>Pagine:&nbsp";
$i=1;
while ($i<=$tot_pag) {
	if ($i==$pagina) {
		echo "[<b>$i</b>]";
	} else {
		echo "
		[<a href=index.php?risorsa=rubrica_view&pagina=$i&pag_size=$pag_size&>$i</a>]
		";
	};
	$i++;
};
echo "</span>";	
?>
</td>

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
