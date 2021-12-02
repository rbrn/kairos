<?php

$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND (id_gruppo='' OR id_gruppo IS NULL) AND tipo_risorsa='20' ORDER BY ordine";
$result=$mysqli->query($query);

if ($result->num_rows) {
	echo "
	<table border=0 width=100% cellspacing=3 cellpadding=3>
	<tr><td valign=\"top\" class=titolodot><img src=\"img/ico_materiali.gif\" width=\"24\" height=\"19\" alt=\"\" border=\"0\" align=bottom>$stringa[lo_dafare]</td></tr>";


		echo "<tr><td>";
		lo_mostra($kairos_cookie[0],$id_corso_s,$id_edizione_s);
		echo "</td></tr>";


	echo "</table>";
};


?>
