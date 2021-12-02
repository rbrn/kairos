<?php
require "./teleskill/teleskill.php";
$ts=new Teleskill();

$userid=$_REQUEST["userid"];
$dal_gg=$_REQUEST["dal_gg"];
$dal_mm=$_REQUEST["dal_mm"];
$anno=$_REQUEST["anno"];

$dal_hh=$_REQUEST["dal_hh"];
$dal_ss=$_REQUEST["dal_ss"];

$al_hh=$_REQUEST["al_hh"];
$al_ss=$_REQUEST["al_ss"];

$titolo=$_REQUEST["titolo"];

$start_date=$anno."-".$dal_mm."-".$dal_gg." ".$dal_hh.":".$dal_ss.":00";
$end_date=$anno."-".$dal_mm."-".$dal_gg." ".$al_hh.":".$al_ss.":00";

$res=$ts->openRoom($userid,$id_corso_s,$id_edizione_s,$titolo,$start_date,$end_date,'','http://ec2-54-229-184-60.eu-west-1.compute.amazonaws.com/kairos/img/tvclive_logo.gif');


echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td>";

echo "
<table border=0 width=100% cellspacing=0 cellpadding=0>
<tr>";
echo "
<td valign=top width=67% class=titolodot>VIDEOCONFERENZA</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=30%>&nbsp;</td>";
echo "</tr>";

echo "<tr><td valign=top width=67%>";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td>";

if (!$res[errorcode]) {
	echo "	
<p>
<span class=testopiccolo>Stanza di videoconferenza creata, <b>tutto ok</b></span>
</p>
<span class=testopiccolo>[<a href=index.php?risorsa=teleskill>Torna all'elenco delle stanze</a>]</span>
";
} else {
	echo "	
<p>
<span class=testopiccolo><b>Errore: </b>".$res[errormessage]."</span>
</p>
<span class=testopiccolo>[<a href=\"javascript:history.back()\">Indietro</a>]</span>
";

}



echo "
</td></tr>
</table>";

echo "</td>";



echo "</tr></table>";



echo "
</td></tr>
</table>";

echo "
</td></tr>
</table>";
?>
