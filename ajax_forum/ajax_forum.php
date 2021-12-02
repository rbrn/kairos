<?php
require_once '../include/properies.php';
require "../include/funzioni_sito.inc";
require "../include/funzioni_forum.inc";



$op=$_GET["op"];
$id_forum=$_GET["id_forum"];
$id_post=$_GET["id_post"];
$cod_area=$_GET["cod_area"];
$id_utente=$_GET["id_utente"];


$id_corso_ed_s=$kairos_cookie[2];
list($id_corso_s,$id_edizione_s,$id_gruppo_s,$id_tutor_s)=split(" ",$id_corso_ed_s);
$id_gruppo_s=strtolower($id_gruppo_s);

$db = mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

switch ($op) {
	case "getPost":
		$query2 = "SELECT * FROM forum WHERE id_forum='$id_forum'";
		$result2=$mysqli->query($query2);
		$dati_forum=$result2->fetch_array();
		$tipo_forum=$dati_forum["tipo"];
		$id_gruppo_forum=strtolower($dati_forum[id_gruppo]);
	
		if ($id_gruppo_forum) {
			$query_gr="select * from gruppo_utenti where id_gruppo='$id_gruppo_forum' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s'";
			$result_r=mysql_query($query_gr);
			$riga_gr=$result_r->fetch_array();
			$tipo_gruppo_gr=$riga_gr["tipo_gruppo"];
		};

		
		$edit_forum=1;
		$ruolo=ruolo_utente($id_utente);
		
		if ($ruolo<>"staff" and $ruolo<>"admin") {
			if ($id_gruppo_forum AND !$tipo_gruppo_gr AND $id_gruppo_forum<>$id_gruppo_s) {
				$edit_forum=0;
			} else {
				if ($id_gruppo_forum AND $tipo_gruppo_gr) {
					$query_f="SELECT id_utente FROM iscrizioni_gruppo_pw WHERE id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_gruppo='$id_gruppo_forum' AND id_utente='$kairos_cookie[0]'";
					$result_f=$mysqli->query($query_f);
					if (!$result_f->num_rows) $edit_forum=0;
				};
			};
		};

		$query_mark = "SELECT * FROM forum_mark WHERE id_utente='$id_utente' AND id_post='$id_post'";
		$result_mark=$mysqli->query($query_mark);
		$riga_mark = $result_mark->fetch_array();
		
		if ($id_utente<>"garamond") {
		$query="SELECT id_post FROM forum_read WHERE id_post='$id_post' AND id_utente='$id_utente'";
		$result=$mysqli->query($query);
		
		if (!$result->num_rows) {
			$query="INSERT INTO forum_read(id_post,id_forum,id_utente,data_read,azione,id_corso,id_edizione,id_gruppo) VALUES ('$id_post','$id_forum','$id_utente',NOW(),'letto','$id_corso_s','$id_edizione_s','$id_gruppo_s')";
			$result=$mysqli->query($query);
		};
		};
		
		$query = "SELECT id_post,oggetto,id_autore,DATE_FORMAT(data_post,'%d/%m/%Y %H:%i') as data_p,testo,nome_file,file_size,id_post_padre,icona_post,attinenza,n_attinenze FROM forum_posts WHERE id_forum='$id_forum' AND id_post='$id_post'";
		$result=$mysqli->query($query);
		$intervento = $result->fetch_array();
		
		$str0="";
		
		$id_autore=$intervento["id_autore"];
		$icona_post = $intervento["icona_post"];

		$immagine=false;
		$file_immagine = $PATH_ROOT_FILE."foto_utenti/$cod_area/".$id_autore.".gif";
		$file_immagine = strtolower($file_immagine);

		if (file_exists($file_immagine)) {
			$nome_immagine = "$id_autore.gif";
			$nome_immagine = strtolower($nome_immagine);
			$immagine = true;
		};

		if (!$immagine) {
			$file_immagine = $PATH_ROOT_FILE."foto_utenti/$cod_area/".$id_autore.".jpg";
			$file_immagine = strtolower($file_immagine);
			if (file_exists($file_immagine)) {
				$nome_immagine = "$id_autore.jpg";
				$nome_immagine = strtolower($nome_immagine);
				$immagine = true;
			};
		};

		$tag_img="";
		$max_img_size=120;
		if ($immagine) {
			$size=getimagesize($PATH_ROOT_FILE."foto_utenti/$cod_area/$nome_immagine");
			$w=$size[0];
			$h=$size[1];
	
			while ($w>$max_img_size or $h>$max_img_size) {
	
				if ($w>$max_img_size) {
					$h=floor($h*$max_img_size/$w);
					$w=$max_img_size;
				};
		
				if ($h>$max_img_size) {
					$w=floor($w*$max_img_size/$h);
					$h=$max_img_size;
				};
		
			};
			
		
			$tag_img="<img src=\"foto_utenti/$cod_area/$nome_immagine\" ALT=\"$id_autore\" width=\"$w\" height=\"$h\">";
		};


		if (!$icona_post) {
			$icona_post = "messaggio";
		};
		

		$icoMark="img/ico_forum_segnainteres.gif";
		if (!$riga_mark) {
			$icoMark="img/ico_forum_segnainteres_fade.gif";
		};
		
		$str0.="<table border=0 cellspacing=5 cellpadding=0><tr><td valign=top>$tag_img</td><td valign=top align=left>";

		$str0.= "
<span class=testopiccolo><b>Autore:</b>
<a class=miolink href=\"javascript:;\" title=\"clicca per sapere chi ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ $nome_immagine\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">$id_autore</a>&nbsp;($intervento[data_p])&nbsp;</span>";
		$str0.="<p>&nbsp;";
		
		$mostra_piume=true;
		if ($id_autore<>$id_utente) {
			$query_att="SELECT * FROM forum_posts_attinenze WHERE id_post='$id_post' AND id_utente='$id_utente'";
			$result_att=$mysqli->query($query_att);
			if (!$result_att->num_rows) {
				$mostra_piume=false;
				$str0.="<span id=\"piume".$id_post."\">";
				for ($i=0;$i<4;$i++) {
					$livello=$i+1;
					$str0.= "<a href=\"javascript:;\" onclick=\"setPiuma('$id_post','$i')\" title=\"valuta l'intervento a livello: $livello\"><img id=\"piuma_".$id_post."_".$i."\" src=\"img/piuma.gif\" width=\"30\" height=\"30\" border=\"0\" alt=\"piuma $livello\" onmouseover=\"accendiPiume('$id_post','$i')\" onmouseout=\"spegniPiume('$id_post','$i')\" ></a>";
				}
				$str0.="</span>";
			} else {
				$mostra_piume=true;
			}
		};
		
		$mostra_piume=false;
		if ($mostra_piume) {
			if ($intervento["n_attinenze"]>2) {
				$n_attinenze=$intervento["n_attinenze"];
				$attinenza=$intervento["attinenza"];
				for ($at=0;$at<$attinenza;$at++) 
					$str0.= "<img src=\"img/piuma_on.gif\" width=\"30\" height=\"30\" alt=\"piuma\">";
			};
		};
		
		$str0.="<a href=\"javascript:;\" onclick=\"markPost('$id_forum','$id_post','$vista','$pagina')\"><img src=\"$icoMark\" width=\"20\" height=\"20\" alt=\"marca come interessante/non interessante\" border=\"0\" id=\"img_mark_$id_post\" name=\"img_mark_$id_post\"></a>";
		$str0.="<br><span class=testopiccolo><b>Oggetto:</b>&nbsp;<img src=img/forum/".$icona_post.".gif alt=".$icona_pos."> ".$intervento["oggetto"]."</span></p>"; 
		

		$str0.= "</td></tr></table>";

		$testo = $intervento["testo"];
		$testo = parse_href($testo);
		$testo = parse_quote($testo);
		$str0.= "
<table border=0 width=90% cellspacing=10 cellpadding=2>
<tr>
<td><span class=testo>$testo</span></td>
</tr></table>";

		if ($intervento["nome_file"]) {
			$str0.="<p><span class=testopiccolo><b>File allegato:</b> <a href=forum_scarica.php?file=".$intervento["nome_file"].">".$intervento["nome_file"]."</a> <i>(".stringa_filesize($intervento["file_size"]).")</i></span></p>";
		};


		//$str0.= "</td></tr></table>";
		
		print($edit_forum.$str0);
		exit();
		break;

	case "markPost": 
		$query="SELECT * FROM forum_mark WHERE id_utente='$id_utente' AND id_post='$id_post' LIMIT 1";
		$result=$mysqli->query($query);
		$mark='1';
		if ($result->num_rows) $mark='0';
		
		if ($mark=='1') {
			$query="INSERT INTO forum_mark (id_utente,id_post,id_forum,id_corso,id_edizione,id_gruppo) VALUES ('$id_utente','$id_post','$id_forum','','','')";
			$result=$mysqli->query($query);

		} else {
			$query="DELETE FROM forum_mark WHERE id_utente='$id_utente' AND id_post='$id_post'";
			$result=$mysqli->query($query);
		};		
		print($mark);
		exit();
		break;
	
	case "setPiuma":
		$livello=$_GET["livello"];

		if ($livello<1) $livello=1;
		if ($livello>4) $livello=4;

		$query="SELECT * FROM forum_posts_attinenze WHERE id_post='$id_post' AND id_utente='$id_utente'";
		$result=$mysqli->query($query);

		if (!$result->num_rows) {
		$query="INSERT INTO forum_posts_attinenze SET "
	." id_post='$id_post',"
	." id_utente='$id_utente',"
	." valore='$livello'";
		$mysqli->query($query);

		$query="SELECT sum(valore) AS somma_valore FROM forum_posts_attinenze WHERE id_post='$id_post'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();

		$somma_valore=$riga["somma_valore"];

		$query="SELECT count(*) AS num_valore FROM forum_posts_attinenze WHERE id_post='$id_post'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();

		$num_valore=$riga["num_valore"];

		$attinenza=0;
		if ($num_valore>2) $attinenza=round($somma_valore/$num_valore);

		$query="UPDATE forum_posts SET attinenza='$attinenza',n_attinenze='$num_valore' WHERE id_post='$id_post'";
		$mysqli->query($query);
		};
		print ("1");
		exit();
		break;
}
print ("0");
?>
