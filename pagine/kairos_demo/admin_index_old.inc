<?php
require "./include/function_admin.inc";
$id_cartella=$_REQUEST["id_cartella"];

if (!isset($id_cartella)) {
	$id_cartella="root";
};

$ruolo=ruolo_utente($id_utente);

if (($id_cartella=='admin' or risorsa_admin($id_cartella)) and $ruolo<>'admin') {
	$id_cartella="root";
};
?>
<p><span class=titolopagina><?php echo($stringa[area_admin]);?></span></p>
<TABLE BORDER=0 width=100%>
<tr>

<tr><td></td></tr>
<tr><td></td></tr>

<tr><td></td></tr>
<tr><td></td></tr>



<?php
if ($ruolo=='admin') {
?>
<tr><td>
<font face=verdana size=-1>[<a href=index.php?risorsa=utenti_cerca><?php echo($stringa[gestione_utenti]);?></a>]</font>
</td></tr>
<?php }; ?>


<tr><td>
<font face=verdana size=-1>[<a href=index.php?risorsa=materiali_index><?php echo($stringa[gestione_contenuti]);?></a>]</font>
</td></tr>


<tr><td>
<font face=verdana size=-1>[<a href=index.php?risorsa=corsi_index><?php echo($stringa[gestione_corsi]);?></a>]</font>
</td></tr>

<tr><td>
<font face=verdana size=-1>[<a href=index.php?risorsa=utility_index><?php echo($stringa[utility]);?></a>]</font>
</td></tr>

<!--

<tr><td>
<font face=verdana size=-1>[<a href=index.php?risorsa=forum_admin_index><?php echo($stringa[gestione_forum]);?></a>]</font>
</td></tr>

<?php
if ($ruolo=='admin') {
?>
<tr><td>
<font face=verdana size=-1>[<a href=index.php?risorsa=newsletter_globale_form><?php echo($stringa[invio_newsletter_globale]);?></a>]</font>
</td></tr>
<?php }; ?>

<tr><td>
<?php if ($id_corso_s and $cod_area<>'kairos_fortic') { ?>
<font face=verdana size=-1>[<a href=index.php?risorsa=newsletter_form><?php echo($stringa[invio_newsletter]);?></a>]</font>
<?php } else { ?>
<font face=verdana size=-1>[<?php echo($stringa[invio_newsletter]);?>]</font>
<?php }; ?>
</td></tr>

<tr><td>
<?php if ($id_corso_s) { ?>
<font face=verdana size=-1>[<a href=index.php?risorsa=stats_corso_form><?php echo($stringa[statistiche_corso]);?></a>]</font>
<?php } else { ?>
<font face=verdana size=-1>[<?php echo($stringa[statistiche_corso]);?>]</font>
<?php }; ?>
</td></tr>

<tr><td>
<?php if ($id_corso_s) { ?>
<font face=verdana size=-1>[<a href=index.php?risorsa=report_corso_form><?php echo($stringa[report_corso]);?></a>]</font>
<?php } else { ?>
<font face=verdana size=-1>[<?php echo($stringa[report_corso]);?>]</font>
<?php }; ?>
</td></tr>



<tr><td>
<font face=verdana size=-1>[<a href=index.php?risorsa=materiali_index><?php echo($stringa[gestione_materiali]);?></a>]</font>
</td></tr>

<?php
if ($ruolo=='admin') {
?>

<tr><td>
<font face=verdana size=-1>[<a href=configura.php><?php echo($stringa[personalizza_interfaccia]);?></a>]</font>
</td></tr>

<tr><td>
<font face=verdana size=-1>[<a href=index.php?risorsa=staff_index><?php echo($stringa[gestione_staff]);?></a>]</font>
</td></tr>

<tr><td>
<font face=verdana size=-1>[<a href=index.php?risorsa=utenti_cerca><?php echo($stringa[gestione_utenti]);?></a>]</font>
</td></tr>

<tr><td>
<font face=verdana size=-1>[<a href=index.php?risorsa=corsi_index><?php echo($stringa[gestione_corsi]);?></a>]</font>
</td></tr>
<!--
<?php if ($cod_area=='kairos_area_corsi') { ?>
<tr><td>
<font face=verdana size=-1>[<a href=index.php?risorsa=registra_iscritti_form><?php echo("Registrazione iscrizioni corsi da Atlante");?></a>]</font>
</td></tr>
<?php };
?>
-->
<?php };
?>

!-->
<tr><td></td></tr>
<tr><td><hr size=1></td></tr>
<tr><td>

<?php
if ($id_utente=='fleo') {
echo "<font face=verdana size=-1><b>$id_cartella</b></a><br><br></font>";
$query="select risorsa_padre from risorse where id_risorsa='$id_cartella'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
if ($riga) {
	$id_cartella_sup=$riga["risorsa_padre"];
	echo "<font face=verdana size=-1>[<a href=index.php?risorsa=admin_index&id_cartella=$id_cartella_sup>$stringa[dir_superiore]</a>]</font> ";
};
?>
<a href=risorsa_form_add.php?padre=<?php echo($id_cartella);?>&tipo=0><img src="img/new_page.gif" width=25 height=24 alt="<?php echo($stringa[nuova_pagina_web]);?>" border="0"></a><a href=risorsa_form_add.php?padre=<?php echo($id_cartella);?>&tipo=1><img src="img/new_file.gif" width=25 height=24 alt="<?php echo($stringa[nuovo_file]);?>" border="0"></a><a href=risorsa_form_add.php?padre=<?php echo($id_cartella);?>&tipo=2><img src="img/new_folder.gif" width=25 height=24 alt="<?php echo($stringa[nuova_cartella]);?>" border="0"></a> 
</td></tr>
<tr><td>
<!-- elenco risorse -->
<?php
thread_risorse($id_cartella);
?>
<!-- fine elenco risorse -->
<?php }; ?>
</td></tr>
</table>
