<?php
require "./include/funzioni_materiali.inc";
$id_cartella=$_REQUEST["id_cartella"];
$id_pagina=$_REQUEST["id_pagina"];

if (!$pagina) $pagina=1;


if (!isset($id_cartella)) {
	$id_cartella="root";
};

$ruolo=ruolo_utente($id_utente);

if ($id_cartella<>"root") {
	mysql_select_db($DBASE);
	$query="select titolo,risorsa_padre FROM risorse_materiali WHERE id_risorsa='$id_cartella'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	$titolo=$riga[titolo];
	$id_cartella_sup=$riga["risorsa_padre"];
	$path_cartella=path_cartella($id_cartella_sup)."/".$titolo;
} else {
	$titolo="";
	$id_cartella_sup="";
	$path_cartella=$titolo;
};


?>
<p>
<span class=titolopagina><?php echo($stringa[gestione_materiali]);?></span>
</p>
<TABLE BORDER=0 width=100%>
<tr>

<tr><td></td></tr>
<tr><td></td></tr>

<tr><td></td></tr>
<tr><td></td></tr>
<tr><td>
<span class=testo>[<a href=index.php?risorsa=test_index><?php echo($stringa[gestione_test]);?></a>]</span>
</td></tr>
<tr><td>
<?php if ($id_corso_s) {
?>
<span class=testo>[<a href=index.php?risorsa=materiali_sequenza_edit&comuni=0><?php echo($stringa[sequenza_pubblicazione]);?></a>]</span>
<?php } else { ?>
<span class=testo>[<?php echo($stringa[sequenza_pubblicazione]);?>]</span>
<?php }; ?>
</td></tr>
<tr><td>
<span class=testo>[<a href=index.php?risorsa=materiali_sequenza_edit&comuni=1><?php echo($stringa[sequenza_pubblicazione_comune]);?></a>]</span>
</td></tr>


<tr><td></td></tr>
<tr><td><hr size=1></td></tr>
<tr><td>
<?php
mysql_select_db($DBASE,$db);	

echo "<span class=testo><b>$stringa[contenuto_cartella]: $path_cartella</b></a><br><br></span>";

if ($id_cartella_sup) {
	//$id_cartella_sup=$riga["risorsa_padre"];
	echo "<span class=testo>[<a href=index.php?risorsa=materiali_index&id_cartella=$id_cartella_sup>$stringa[dir_superiore]</a>]</span> ";
};
?>
<a href=materiali_risorsa_form_add.php?padre=<?php echo($id_cartella);?>&tipo=0><img src="img/new_page.gif" width=25 height=24 alt="<?php echo($stringa[nuova_pagina_web]);?>" border="0"></a><a href=materiali_risorsa_form_add.php?padre=<?php echo($id_cartella);?>&tipo=1><img src="img/new_file.gif" width=25 height=24 alt="<?php echo($stringa[nuovo_file]);?>" border="0"></a><a href=materiali_risorsa_form_add.php?padre=<?php echo($id_cartella);?>&tipo=2><img src="img/new_folder.gif" width=25 height=24 alt="<?php echo($stringa[nuova_cartella]);?>" border="0"></a>
</td></tr>
<tr><td>
<!-- elenco risorse -->
<?php
thread_risorse($id_cartella,$pagina);
?>
<!-- fine elenco risorse -->
</td></tr>
</table>
