<?php



$query="SELECT * FROM rubrica ORDER BY posizione";

$result=$mysqli->query($query);



echo "<p><span class=titolopagina>Gestione Rubriche</span></p>

<hr size=1>

<br>

<span class=testo>[<a href=index.php?risorsa=rubrica_nuova_form>Nuova Rubrica</a>]</span>

<br>

<hr size=1>

<br>

\n";



echo "

<table border=1>

<tr>

<td><p><span class=testo><b>Rubrica</b></span></p></td>

<td><p><span class=testo><b>Titolo</b></p></td>

<td><p><span class=testo><b>N. Articoli</b></span></p></td>

<td>&nbsp;</td>

<td>&nbsp;</td>

</tr>

\n";



while ($riga=$result->fetch_array()) {

	$id_rubrica = $riga["id_rubrica"];

	echo "<tr>\n";

	echo "<td><p><span class=testo>$id_rubrica</span></p></td>\n";

	printf ("<td><p><span class=testo>%s</span></p></td>\n",$riga["titolo"]);

	$query_t = "SELECT count(*) as n_art FROM articolo WHERE id_rubrica='$id_rubrica'";

	$result_t=$mysqli->query($query_t);

	$riga_t=$result_t->fetch_array();

	$n_art = $riga_t["n_art"];

	echo "<td align=right><p><span class=testo>$n_art</p></td>";

	echo "<td><p><a href=index.php?risorsa=rubrica_mod_form&id_rubrica=$id_rubrica><span class=testo>Modifica</span></a></p></td>\n";	

	if (!$n_art) {	

		echo "<td><p><a href=rubrica_del.php?id_rubrica=$id_rubrica><span class=testo>Cancella</span></a></p></td>\n";	

	} else {

		echo "<td>&nbsp;</td>";

	};

	echo "</tr>\n";

}

echo "</table><br><br>\n";

	  

?>
