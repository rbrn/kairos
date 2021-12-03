<?php

$stato=$_REQUEST["stato"];

$titolo=$_REQUEST["titolo"];

if ($ruolo <> 'admin') {

	$query = "SELECT * FROM articolo WHERE stato='$stato' AND id_utente='$id_utente' ";

	if ($titolo) {

		$query .= " AND titolo like '$titolo%' ";

	}



} else {

	$query = "SELECT * FROM articolo WHERE stato='$stato' ";

	

	if ($titolo) {

		$query .= " AND titolo like '$titolo%' ";

	}

};



$query .= "ORDER BY id_rubrica,id_articolo";



$result=$mysqli->query($query);

	

echo "

<span class=titolopagina>Elenco Articoli</span>

<hr>

<span class=testo>[<a href=index.php?risorsa=gestione_articoli>Gestione Articoli</a>]</span>

<br><br>

<table border=1>

<tr>

<td><span class=testo><b>Id Articolo</b></span></td>

<td><span class=testo><b>Stato</b></span></td>

<td><span class=testo><b>Id Autore</b></span></td>

<td><span class=testo><b>Titolo</b></span></td>

<td></td>

<td></td>

<td></td>

</tr>";



while ($riga = $result->fetch_array()) {

	$id_articolo=$riga["id_articolo"];

	$stato=$riga["stato"];

	$id_utente=$riga["id_utente"];

	$titolo=$riga["titolo"];

	echo "

	<tr>

	<td><span class=testo>$id_articolo</span></td>

	<td><span class=testo>$stato</span></td>

	<td><span class=testo>$id_utente</span></td>

	<td><span class=testo>$titolo</span></td>

	";

	

	if (( ($stato=='bozza') or ($stato=="approvato" and $ruolo=='admin'))) {

		echo "

	<td>

	<span class=testo><a href=index.php?risorsa=articolo_mod_form&id_articolo=$id_articolo>Modifica</a></span></td>

	<td><span class=testo><a href=articolo_del.php?id_articolo=$id_articolo>Cancella</a></span></td>

	<td><span class=testo><a href=index.php?risorsa=articolo_view.php&id_articolo=$id_articolo target=_blank>Anteprima</a></span></td>

	</tr>";

	} else {

		echo "<td>&nbsp;</td><td>&nbsp;</td>";

	};



};



?>	



</table>

<br>
