<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_utente1=$kairos_cookie[0];

if (!$id_utente1) {
	echo "
	<html>
	<head><title>$stringa[errore]</title>
	<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
	<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
	</HEAD>
	<BODY bgcolor=$colore_sfondo>
	<span class=testo>$stringa[errore_no_login]</span>
	</body>
	</html>";
	exit();
};


?>


<html>
<head>
<title><?php echo($stringa[cerca_materiali]);?></title>
<?php 
echo "
<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">";
echo"
<script language=\"JavaScript\">
	function assegna_id(id) {
		self.close();
		opener.document.form1.$campo.value=id;
		opener.focus();
	};
</script>
";

?>
</head>
<BODY bgcolor=<?php echo($colore_sfondo);?>>

<?php


$campo=$_REQUEST["campo"];
$dir=$_REQUEST[dir];

$id_risorsa_cerca=$_REQUEST["id_risorsa_cerca"];
$titolo_cerca=$_REQUEST["titolo"];
$pagina=$_REQUEST["pagina"];
$pag_size=$_REQUEST["pag_size"];

if (!$pagina) $pagina=1;
if (!$pag_size) $pag_size=20;

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	
	
echo "<p><span class=titolopagina>$stringa[cerca_materiali]</span></p>";

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$query1 = "";
if ($dir) $query1=" id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ";

// creo la condizione where

$id_risorsa_cerca=trim($id_risorsa_cerca);
	
if ($id_risorsa_cerca) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (id_risorsa LIKE '%$id_risorsa_cerca%') ";
};

if ($titolo_cerca) {
	if ($query1) $query1 .= "AND";
	$query1 .= " (titolo LIKE '%$titolo_cerca%') ";
};


if ($query1) $query1 .= "AND";

$query1 .= " (tipo='0' or tipo='4' or tipo='3') ";

if ($dir) {
	$query = "SELECT id_risorsa,titolo,tipo FROM materiali_gruppo";
} else {
	$query = "SELECT id_risorsa,titolo,tipo FROM risorse_materiali";
};
if ($query1) $query .= " WHERE $query1 "; 
$query .= " ORDER BY id_risorsa";


$result = $mysqli->query($query);

$tot_righe=$result->num_rows;

if (!$tot_righe) {
	echo "<p><span class=testo>$stringa[non_trovato]</span></p>";
	exit();
};

$tot_pag=floor($tot_righe/$pag_size);
if ( ($tot_righe % $pag_size) <> 0) $tot_pag++;

$inizio=$pag_size*($pagina-1);
$query .= " LIMIT $inizio,$pag_size";
$result = $mysqli->query($query);

$progr=$inizio+1;

echo "
<hr size=1>
<TABLE BORDER=0 cellspacing=2 cellpadding=2>
<tr>
<td><span class=testo><b>$stringa[num]</b></span></td>
<td><span class=testo><b>$stringa[pagina_web]</b></span></td>
<td></td>
</tr>";

$righe=1;
$continua = true;
while ($risorsa=$result->fetch_array()) {
	$id_risorsa=$risorsa["id_risorsa"];
	$titolo = $risorsa["titolo"];
	$tipo = $risorsa["tipo"];
	$nota="";
	if ($tipo=="3") $nota="(*)";
	echo "<tr>";
	echo "<td><span class=testopiccolo>$progr</span></td>";

	echo "<td>
	<span class=testopiccolo>
	<a href=\"javascript:;\" onclick=\"assegna_id('$id_risorsa')\">($id_risorsa) $titolo $nota</a>
	</span>
	</td>
	</tr>";	


	$righe++;
	$progr++;
};      
?>		
</td></tr>
</table><br>
<?php
echo "<br><span class=testopiccolo>$stringa[pagine]:&nbsp;";
$i=1;
while ($i<=$tot_pag) {
	if ($i==$pagina) {
		echo "[<b>$i</b>]";
	} else {
		echo "
		[<a href=cerca_pagina_popup_op.php?campo=$campo&pagina=$i&pag_size=$pag_size&id_risorsa_cerca=$id_risorsa_cerca&titolo=$titolo_cerca&dir=$dir>$i</a>]
		";
	};
	$i++;
};
echo "</span><br>";	
?>
<br>
<!-- FINE CONTENUTO DELLA PAGINA -->

</body>
</html>
