<?php
$elenco_corsi="";
$query="SELECT * FROM edizioni WHERE stato='attiva' ORDER BY id_corso,id_edizione DESC";
$result=$mysqli->query($query);
	

while ($riga=$result->fetch_array()) {
$id_corso=$riga["id_corso"];
$id_edizione=$riga["id_edizione"];
$elenco_corsi .= "<option value=\"$id_corso $id_edizione\">$id_corso ($id_edizione)";
};
?>
<p>
<span class=titolopagina>
Registra iscritti ai corsi
</span>
</p>
<p>
<span class=testo>
Registra da Atlante gli utenti che hanno sottoscritto il corso:<br>
<form action=index.php method=post>
<input type=hidden name=risorsa value="registra_iscritti">
<select name="id_corso_edizione">
<?php echo($elenco_corsi) ?>
</select>
&nbsp;<input type=submit value=ok>
</form>
<br>
<br>
