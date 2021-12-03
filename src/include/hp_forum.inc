<?php


$query = "SELECT * FROM forum WHERE tipo=0 ORDER BY ordine";
$forum_comuni=get_news_forum($query);


$query = "SELECT * FROM forum WHERE (tipo=1 or tipo=3) AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='' AND (archiviato IS NULL or archiviato=0) ORDER BY ordine";
$forum_corso=get_news_forum($query);

/*
$query = "SELECT * FROM forum WHERE tipo=3 AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='' ORDER BY ordine";
$forum_lab=get_news_forum($query);
*/

if ($ruolo<>'staff' and $ruolo<>'admin' and $id_gruppo_s and $id_corso_s) {
	$query = "SELECT * FROM forum WHERE (tipo=1 or tipo=3) AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_s' AND (archiviato IS NULL or archiviato=0) ORDER BY ordine";
	$forum_gruppo=get_news_forum($query);
};

if ($ruolo<>'staff' and $ruolo<>'admin' and $id_corso_s) {
	$query="SELECT * FROM iscrizioni_gruppo_pw WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_utente='$id_utente'";
	$result=$mysqli->query($query);
	//echo "$query <br>";
	$gruppi="";
	while ($riga=$result->fetch_array()) {
		$id_gruppo_x=$riga["id_gruppo"];
		if ($gruppi) {
			$gruppi.=" or id_gruppo='$id_gruppo_x' ";
		} else {
			$gruppi .= " id_gruppo='$id_gruppo_x' ";
		};
	};
	
	if ($gruppi) {
		$query = "SELECT * FROM forum WHERE (tipo=1 or tipo=3) AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND ($gruppi) AND (archiviato IS NULL or archiviato=0) ORDER BY ordine";
		//echo "$query <br>";
		$forum_gruppo_pw=get_news_forum($query);
	};
};

if (($ruolo=='staff' or $ruolo=='admin') and $id_corso_s) {
	$query="SELECT * FROM gruppo_utenti WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_tutor='$id_utente'";
	$result=$mysqli->query($query);
	//echo "$query <br>";
	$gruppi="";
	while ($riga=$result->fetch_array()) {
		$id_gruppo_x=$riga["id_gruppo"];
		if ($gruppi) {
			$gruppi.=" or id_gruppo='$id_gruppo_x' ";
		} else {
			$gruppi .= " id_gruppo='$id_gruppo_x' ";
		};
	};
	
	if ($gruppi) {
		$query = "SELECT * FROM forum WHERE (tipo=1 or tipo=3) AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND ($gruppi) AND (archiviato IS NULL or archiviato=0) ORDER BY ordine";
		//echo "$query <br>";
		$forum_gruppo=get_news_forum($query);
	};
};

if ($cod_area<>"kairos_area_corsi") {		
if (count($forum_comuni)) {
	echo "
<table border=0 width=100% cellspacing=3 cellpadding=3>
<tr><td valign=\"top\" class=titolodot><img src=\"img/ico_home_forum.gif\" width=\"25\" height=\"20\" alt=\"\" border=\"0\" align=\"bottom\">$stringa[news_forum_comuni]</td></tr>";

	for ($i=0;$i<count($forum_comuni);$i++) {
		echo "<tr><td><span class=\"testopiccolo\">$forum_comuni[$i]</span></td></tr>";
	};

	echo "</table>";
};
};

if (count($forum_corso)) {
	echo "
<table border=0 width=100% cellspacing=3 cellpadding=3>
<tr><td valign=\"top\" class=titolodot><img src=\"img/ico_home_forum.gif\" width=\"25\" height=\"20\" alt=\"\" border=\"0\" align=\"bottom\">$stringa[news_forum_corso]</td></tr>";

	for ($i=0;$i<count($forum_corso);$i++) {
		echo "<tr><td><span class=\"testopiccolo\">$forum_corso[$i]</span></td></tr>";
	};

	echo "</table>";
};

if ($ruolo<>'staff' and $ruolo<>'admin' and $id_gruppo_s and $id_corso_s) {
if (count($forum_gruppo)) {
	echo "
<table border=0 width=100% cellspacing=3 cellpadding=3>
<tr><td valign=\"top\" class=titolodot><img src=\"img/ico_home_forum.gif\" width=\"25\" height=\"20\" alt=\"\" border=\"0\" align=\"bottom\">$stringa[news_forum_gruppo]</td></tr>";

	for ($i=0;$i<count($forum_gruppo);$i++) {
		echo "<tr><td><span class=\"testopiccolo\">$forum_gruppo[$i]</span></td></tr>";
	};

	echo "</table>";
};

if (count($forum_gruppo_pw)) {
	echo "
<table border=0 width=100% cellspacing=3 cellpadding=3>
<tr><td valign=\"top\" class=titolodot><img src=\"img/ico_home_forum.gif\" width=\"25\" height=\"20\" alt=\"\" border=\"0\" align=\"bottom\">$stringa[news_forum_gruppo_pw]</td></tr>";

	for ($i=0;$i<count($forum_gruppo_pw);$i++) {
		echo "<tr><td><span class=\"testopiccolo\">$forum_gruppo_pw[$i]</span></td></tr>";
	};

	echo "</table>";
};

};

if (($ruolo=='staff' or $ruolo=='admin') and $id_corso_s) {
if (count($forum_gruppo)) {
	echo "
<table border=0 width=100% cellspacing=3 cellpadding=3>
<tr><td valign=\"top\" class=titolodot><img src=\"img/ico_home_forum.gif\" width=\"25\" height=\"20\" alt=\"\" border=\"0\" align=\"bottom\">$stringa[news_forum_gruppo_tutor]</td></tr>";

	for ($i=0;$i<count($forum_gruppo);$i++) {
		echo "<tr><td><span class=\"testopiccolo\">$forum_gruppo[$i]</span></td></tr>";
	};

	echo "</table>";
};
};

?>
