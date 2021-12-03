<?php
echo "
<p>
<span class=titolopagina>$stringa[helpdesk]</span>
</p>
<hr size=1>
<p>
<span class=sottotitolopagina>Manuale di Kairos:</span>
<span class=testo><a href=guida/kairos_manuale.zip>versione stampabile .zip/pdf</a> (1.5MB)</span>
</p>
<hr size=1>
<span class=sottotitolopagina>Risposte alle domande piÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ frequenti:</span>
";
if ($ruolo=='admin' or $ruolo=='staff') {
	echo "<span class=testo>[<a href=index.php?risorsa=faq_new&op=nuovo&pagina=helpdesk>$stringa[nuova_faq]</a>]</span>
<hr size=1>";
};

$query = "SELECT * FROM faq WHERE id_corso='' ORDER BY ordine";
$result=$mysqli->query($query);

echo "<ul>";
while ($faq = $result->fetch_array()) {
	$domanda=str_replace("\n","<br>",$faq["domanda"]);
	$id_faq = $faq["id_faq"];

	echo "
	<li><span class=testo>$domanda</a><br>
	[<a href=\"javascript:;\" onclick=\"faq_view('$id_faq')\">$stringa[risposta_f]</a>] ";
	if ($ruolo=='staff' or $ruolo=='admin') {
		echo "[<a href=index.php?risorsa=faq_edit&id_faq=$id_faq&pagina=helpdesk>$stringa[modifica]</a>] [<a href=faq_cancella.php?id_faq=$id_faq&pagina=helpdesk>$stringa[cancella]</a>]<br>";
	};
	echo "</span></li><br>";
};
echo "</ul>";

if ($cod_area=='kairos_larimart') {
echo "
<p>
<span class=testo>
$stringa[chiama_helpdesk]
</span>
</p>";
};
echo "
<br>";
?>
<br>



