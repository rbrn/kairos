<?php

for ($i=1;$i<=$n_news;$i++) {
	if (!$id_corso_s) {		
		$query="SELECT * FROM hp_news WHERE tipo=0 AND posizione='r".$i."' AND (id_corso IS NULL OR id_corso='') AND (id_edizione IS NULL OR id_edizione='')";
	} else {
		$query="SELECT * FROM hp_news WHERE tipo=0 AND posizione='r".$i."' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
	};

	$result=$mysqli->query($query);
	$news[$i]=@$result->fetch_array();
};

	
echo "
	<table border=0 cellspacing=0 cellpadding=8 width=100%>";
	
	for ($j=1;$j<=$n_news/2;$j++) {
	
		$i=2*($j-1)+1;
		$tr=false;
		if ($news[$i] and $news[$i+1]) {
			$tr=true;
			echo "<tr>";
			echo "<td valign=top width=50%>";
		} else if ($news[$i] or $news[$i+1]) { 
			$tr=true;
			echo "<tr>";
			echo "<td valign=top colspan=2>";
		};
	
		for ($k=0;$k<=1;$k++) {
			if ($news[$i+$k]) {
				if ($k==1) {
					if ($news[$i]) echo "<td valign=top width=50%>";
				};
				$id_news=$news[$i+$k]["id_news"];
				$url=$news[$i+$k]["url"];
				$url_label=$news[$i+$k]["url_label"];
				$testo=$news[$i+$k]["testo"];
		
				if ($url) {
					echo "
					<span class=testo><a href=$url><b>$url_label</b></a></span>";
				} else {
					echo "
					<span class=testo><b>$url_label</b></span>";
				};
		
				echo "<br>";
				echo "<span class=testo>$testo</span>";
				if ($ruolo=='admin' or $ruolo=='staff') {
					echo "<br>";
					echo "<a href=index.php?risorsa=news_mod&tipo_news=0&posizione=r".($i+$k)." onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_news','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_news\" vspace=\"5\"></a>&nbsp;<a href=index.php?risorsa=msg&msg=conf_canc&pagina=news_delete.php&tipo_news=0&posizione=r".($i+$k)." onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_news','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_news\" vspace=\"5\"></a>\n";
				};
		
				echo "</td>";
			};
		};
		
		if ($tr) echo "</tr>";
	
		
	
	};
	
	
	
	echo "</table>";

?>
