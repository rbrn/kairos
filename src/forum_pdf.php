<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
require "./include/funzioni_forum.inc";

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

require_once('html2pdf/html2fpdf.php');
require_once('html2pdf/htmltoolkit.php');

$id_thread=$_REQUEST["id_thread"];
if (!$id_thread) {
	exit;
};

$thread_html="";
$query = "SELECT id_post,oggetto,testo,id_autore,nome_file,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,icona_post,attinenza,n_attinenze FROM forum_posts WHERE id_post='$id_thread'";
$result=$mysqli->query($query);
$intervento = $result->fetch_array();

$id_post = $intervento["id_post"];
$query0 = "SELECT id_post FROM forum_posts WHERE id_post_padre='$id_post'";
$result0=$mysqli->query($query0);
$nrep = $result0->num_rows;
	

$id_autore=$intervento["id_autore"];
$icona_post = $intervento["icona_post"];

if (!$icona_post) {
	$icona_post = "messaggio";
};	
			
$thread_html.="<hr size=1>\n";

$thread_html.="<img src=img/forum/$icona_post.gif> <span class=testopiccolo>".$intervento["oggetto"]."</span>";
	
$ruolo_str="";
		if ($tipo_forum=='1' or $tipo_forum=='2' or $tipo_forum=='3') {
		$query_s="SELECT ruolo FROM ruolo_utenti WHERE id_utente='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'  LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_".$riga_s["ruolo"];
		if ($riga_s["ruolo"]) $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
		
		$query_s="SELECT id_tutor FROM gruppo_utenti WHERE id_tutor='$id_autore' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'  LIMIT 1";
		$result_s=$mysqli->query($query_s);
		$riga_s=$result_s->fetch_array();
		$ruolo_s="staff_tutor";
		if (!$ruolo_str and $riga_s["id_tutor"]) $ruolo_str="&nbsp;<font color=#ff9900>Staff $stringa[$ruolo_s]</font>";
		};

	
		$thread_html.= "<span class=testopiccolo> (<i>$id_autore</i>$ruolo_str</span>";
		
		$thread_html.="<span class=testopiccolo><i> - ".$intervento["data_p"].")</i></span>";
		$testo = $intervento["testo"];
		$testo = parse_href($testo);
		$testo = parse_quote($testo);

		$thread_html.= "
<table border=0 width=90% cellspacing=10 cellpadding=2>
<tr>
<td><span class=testo>$testo</span></td>
</tr></table>";
		
	
		if ($nrep) {
	 		getThread($id_post); 
		}


$html_to_convert="<html><head><title>Forum thread</title>
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\"></head><body>".$thread_html."</body></html>";
//echo $html_to_convert;

$html2pdf = new HTML2FPDF();
$html2pdf->AddPage();
@$html2pdf->WriteHTML($html_to_convert);
$html2pdf->Output();

?>
