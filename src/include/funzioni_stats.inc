<?php
function get_stats($id_utente,$da_data,$a_data) {
	global $DBASE,$DBUSER,$DBPWD,$id_corso_s,$id_edizione_s;

	$stat_utente = array();
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

	$query = "SELECT count(*) as num_login FROM log_sito WHERE id_utente='$id_utente' AND dettagli='login' AND data_log >= '$da_data' AND data_log <= '$a_data'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();

	$stat_utente[]=$riga["num_login"];
	
	$sessioni=array();
	
	$query = "SELECT * FROM log_sito WHERE id_utente='$id_utente' AND data_log >= '$da_data' AND data_log <= '$a_data' ORDER BY data_log";
	$result=$mysqli->query($query);
	
	$inizio_sessione="";
	$fine_sessione="";
	$tot_durata=0;
	while ($riga = $result->fetch_array()) {
		$dettaglio=$riga["dettagli"];
		$data_log=$riga["data_log"];
		$fine_sessione=$data_log;
		
		if ($dettaglio=='login' and !$inizio_sessione) {
			$inizio_sessione=$data_log;
		} else {
			if (($dettaglio=='login' or $dettaglio=='logout') and $inizio_sessione) {
			ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$inizio_sessione,$parti);
			$da_gg=$parti[3];
			$da_mm=$parti[2];
			$da_aa=$parti[1];
			$da_hh=$parti[4];
			$da_m=$parti[5];
			$da_ss=$parti[6];
			
			ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$fine_sessione,$parti);
			$a_gg=$parti[3];
			$a_mm=$parti[2];
			$a_aa=$parti[1];
			$a_hh=$parti[4];
			$a_m=$parti[5];
			$a_ss=$parti[6];
			
			
			$dal=mktime($da_hh,$da_m,$da_ss,$da_mm,$da_gg,$da_aa);
			$al=mktime($a_hh,$a_m,$a_ss,$a_mm,$a_gg,$a_aa);
			//echo "$id_utente: $al - $dal <br>";
			$durata=min($al-$dal,1800);
			$sessioni[]=$durata;
			$tot_durata+=$durata;
			//echo "$tot_durata <br>";
			
			if ($dettaglio=='login') {
				$inizio_sessione=$data_log;
			} else {
				$inizio_sessione="";
			};
			
			};
		};
		
	};
	
	if ($inizio_sessione) {
			ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$inizio_sessione,$parti);
			$da_gg=$parti[3];
			$da_mm=$parti[2];
			$da_aa=$parti[1];
			$da_hh=$parti[4];
			$da_m=$parti[5];
			$da_ss=$parti[6];
			
			ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$fine_sessione,$parti);
			$a_gg=$parti[3];
			$a_mm=$parti[2];
			$a_aa=$parti[1];
			$a_hh=$parti[4];
			$a_m=$parti[5];
			$a_ss=$parti[6];
			
			$inizio_sessione="";
			$dal=mktime($da_hh,$da_m,$da_ss,$da_mm,$da_gg,$da_aa);
			$al=mktime($a_hh,$a_m,$a_ss,$a_mm,$a_gg,$a_aa);
			//echo "$id_utente: $al - $dal <br>";
			$durata=min($al-$dal,1800);
			$sessioni[]=$durata;
			$tot_durata+=$durata;
			//echo "$tot_durata <br>";
	};
			
	if (count($sessioni)) {
		$media_durata=$tot_durata/count($sessioni);
	} else {
		$media_durata=0;
	};
	
	$stat_utente[]=$media_durata;
	$stat_utente[]=$tot_durata;	
	
	ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$da_data,$parti);
	$da_gg=$parti[3];
	$da_mm=$parti[2];
	$da_aa=$parti[1];
	$da_hh=$parti[4];
	$da_m=$parti[5];
	$da_ss=$parti[6];
			
	ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$a_data,$parti);
	$a_gg=$parti[3];
	$a_mm=$parti[2];
	$a_aa=$parti[1];
	$a_hh=$parti[4];
	$a_m=$parti[5];
	$a_ss=$parti[6];
	
	$dal=mktime($da_hh,$da_m,$da_ss,$da_mm,$da_gg,$da_aa);
	$al=mktime($a_hh,$a_m,$a_ss,$a_mm,$a_gg,$a_aa);
					
	$query="SELECT COUNT(*) AS n FROM c_messages_archive WHERE username='$id_utente' AND m_time>=$dal AND m_time<=$al";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	$nchat = $riga["n"];

	$query="SELECT COUNT(*) AS n FROM forum_posts WHERE id_autore='$id_utente' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND data_post >= '$da_data' AND data_post <= '$a_data'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	$nposts = $riga["n"];

	$query="SELECT COUNT(*) AS n FROM forum_read WHERE id_utente='$id_utente' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND data_read >= '$da_data' AND data_read <= '$a_data'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();
	$nread = $riga["n"];	
	
	$query = "SELECT count(*) as num_mat FROM log_materiali WHERE id_utente='$id_utente' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND data_log >= '$da_data' AND data_log <= '$a_data'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();

	$nmat=$riga["num_mat"];
	
	$query = "SELECT count(*) as num_test FROM test_compilato WHERE id_utente='$id_utente' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND data_compilazione >= '$da_data' AND data_compilazione <= '$a_data'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();

	$ntest=$riga["num_test"];
	
	$query = "SELECT count(*) as num_sito FROM log_sito WHERE id_utente='$id_utente' AND dettagli<>'login' AND dettagli<>'logout' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND data_log >= '$da_data' AND data_log <= '$a_data'";
	$result=$mysqli->query($query);
	$riga = $result->fetch_array();

	$nsito=$riga["num_sito"];
	
	$stat_utente[]=$nposts;
	$stat_utente[]=$nread;
	$stat_utente[]=$nchat;
	$stat_utente[]=$nmat;
	$stat_utente[]=$ntest;
	$stat_utente[]=$nsito;
	
	return $stat_utente;

};


function get_stats_sessioni($id_utente,$da_data,$a_data) {
	global $DBASE,$DBUSER,$DBPWD,$id_corso_s,$id_edizione_s,$DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
	$sessioni=array();
	$query = "SELECT * FROM log_sito WHERE id_utente='$id_utente' AND data_log >= '$da_data' AND data_log <= '$a_data' ORDER BY data_log";
	$result=$mysqli->query($query);
	
	$inizio_sessione="";
	$fine_sessione="";

	while ($riga = $result->fetch_array()) {
		$dettaglio=$riga["dettagli"];
		$data_log=$riga["data_log"];
		$fine_sessione=$data_log;
		
		if ($dettaglio=='login' and !$inizio_sessione) {
			$inizio_sessione=$data_log;
		} else {
			if (($dettaglio=='login' or $dettaglio=='logout') and $inizio_sessione) {
			ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$inizio_sessione,$parti);
			$da_gg=$parti[3];
			$da_mm=$parti[2];
			$da_aa=$parti[1];
			$da_hh=$parti[4];
			$da_m=$parti[5];
			$da_ss=$parti[6];
			
			ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$fine_sessione,$parti);
			$a_gg=$parti[3];
			$a_mm=$parti[2];
			$a_aa=$parti[1];
			$a_hh=$parti[4];
			$a_m=$parti[5];
			$a_ss=$parti[6];
					
			$dal=mktime($da_hh,$da_m,$da_ss,$da_mm,$da_gg,$da_aa);
			$al=mktime($a_hh,$a_m,$a_ss,$a_mm,$a_gg,$a_aa);
			$durata=min($al-$dal,1800);
			$sessioni[]=$durata."\t".$inizio_sessione;
			if ($dettaglio=='login') {
				$inizio_sessione=$data_log;
			} else {
				$inizio_sessione="";
			};
			};
		};
		
	};
	
	if ($inizio_sessione) {
			ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$inizio_sessione,$parti);
			$da_gg=$parti[3];
			$da_mm=$parti[2];
			$da_aa=$parti[1];
			$da_hh=$parti[4];
			$da_m=$parti[5];
			$da_ss=$parti[6];
			
			ereg("^(.+)-(.+)-(.+) (.+):(.+):(.+)$",$fine_sessione,$parti);
			$a_gg=$parti[3];
			$a_mm=$parti[2];
			$a_aa=$parti[1];
			$a_hh=$parti[4];
			$a_m=$parti[5];
			$a_ss=$parti[6];
			
			$dal=mktime($da_hh,$da_m,$da_ss,$da_mm,$da_gg,$da_aa);
			$al=mktime($a_hh,$a_m,$a_ss,$a_mm,$a_gg,$a_aa);
			//$durata=round(($al-$dal)/60,2);
			$durata=min($al-$dal,1800);
			$sessioni[]=$durata."\t".$inizio_sessione;
			$inizio_sessione="";
	};
			
			
	return $sessioni;

};


function get_stats_forum_scritti($id_utente,$da_data,$a_data) {
	global $DBASE,$DBUSER,$DBPWD,$id_corso_s,$id_edizione_s,$DBHOST;
    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);

	$interventi=array();
	$query = "SELECT * FROM forum_posts WHERE id_autore='$id_utente' AND data_post >= '$da_data' AND data_post <= '$a_data' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY data_post DESC";
	$result=$mysqli->query($query);
	
	while ($riga = $result->fetch_array()) {
		$oggetto=$riga["oggetto"];
		$id_forum=$riga["id_forum"];
		$id_post=$riga["id_post"];
		$data_post=$riga["data_post"];
		
		$interventi[]=$oggetto."\t".$id_forum."\t".$id_post."\t".$data_post;
	
	};
	
			
	return $interventi;

};


function get_stats_forum_letti($id_utente,$da_data,$a_data) {
	global $DBASE,$DBUSER,$DBPWD,$id_corso_s,$id_edizione_s,$DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
		
	$interventi=array();
	$query = "SELECT * FROM forum_read WHERE id_utente='$id_utente' AND data_read >= '$da_data' AND data_read <= '$a_data' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY data_read DESC";
	$result=$mysqli->query($query);
	
	while ($riga = $result->fetch_array()) {
		
		$id_forum=$riga["id_forum"];
		$id_post=$riga["id_post"];
		$data_read=$riga["data_read"];
		
		$query2 = "SELECT * FROM forum_posts WHERE id_post=$id_post";
		$result2=$mysqli->query($query2);
		$riga2 = $result2->fetch_array();
		
		$id_autore=$riga2["id_autore"];
		$oggetto=$riga2["oggetto"];
		$data_post=$riga2["data_post"];
		
		$interventi[]=$id_autore."\t".$oggetto."\t".$id_forum."\t".$id_post."\t".$data_post."\t".$data_read;
	
	};
	
			
	return $interventi;

};


function get_stats_materiali($id_utente,$da_data,$a_data) {
	global $DBASE,$DBUSER,$DBPWD,$id_corso_s,$id_edizione_s,$DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
		
	$materiali=array();
	$query = "SELECT * FROM log_materiali WHERE id_utente='$id_utente' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND data_log >= '$da_data' AND data_log <= '$a_data' ORDER BY data_log DESC";
	$result=$mysqli->query($query);

	while ($riga = $result->fetch_array()) {
		$id_risorsa=$riga["dettagli"];
		$data_log=$riga["data_log"];
		
		$query2 = "SELECT * FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
		$result2=$mysqli->query($query2);
		$riga2 = $result2->fetch_array();
		$titolo=$riga2["titolo"];
		
		$materiali[]=$id_risorsa."\t".$titolo."\t".$data_log;
	
	};
	
			
	return $materiali;

};


function get_stats_risorse($id_utente,$da_data,$a_data) {
	global $DBASE,$DBUSER,$DBPWD,$id_corso_s,$id_edizione_s,$DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
		
	$risorse=array();
	$query = "SELECT * FROM log_sito WHERE id_utente='$id_utente' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND data_log >= '$da_data' AND data_log <= '$a_data' ORDER BY data_log DESC";
	$result=$mysqli->query($query);

	while ($riga = $result->fetch_array()) {
		$id_risorsa=$riga["dettagli"];
		$data_log=$riga["data_log"];
		
		if ($id_risorsa<>'logout') {
			$query2 = "SELECT * FROM risorse WHERE id_risorsa='$id_risorsa'";
			$result2=$mysqli->query($query2);
			$riga2 = $result2->fetch_array();
			mysql_select_db($DBASE,$db);
			$titolo=$riga2["titolo"];
		} else {
			$titolo='logout';
		};
		
		$risorse[]=$id_risorsa."\t".$titolo."\t".$data_log;
	
	};
	
			
	return $risorse;

};

function get_stats_test($id_utente,$da_data,$a_data) {
	global $DBASE,$DBUSER,$DBPWD,$id_corso_s,$id_edizione_s,$stringa,$DBHOST;

    $mysqli = new mysqli($DBHOST, $DBUSER, $DBPWD, $DBASE);
		
	$test=array();
	$query = "SELECT * FROM test_compilato WHERE id_utente='$id_utente' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND data_compilazione >= '$da_data' AND data_compilazione <= '$a_data'";
	$result=$mysqli->query($query);

	while ($riga = $result->fetch_array()) {
		$id_test=$riga["id_test"];
		$id_test_compilato=$riga["id_test_compilato"];
		$data_compilazione=$riga["data_compilazione"];
		$punteggio=$riga["punteggio"];
		$punteggio_max=$riga["punteggio_max"];
		
		$query2 = "SELECT * FROM test WHERE id_test='$id_test'";
		$result2=$mysqli->query($query2);
		$riga2 = $result2->fetch_array();
		$titolo_test=$riga2["titolo"];
		$tipo_test=$riga2["tipo_test"];
		$punteggio_soglia=$riga2["punteggio_soglia"];
		if ($tipo_test==0) {
			$icona="";
			if ($punteggio_soglia>0) {
				if ($punteggio>=$punteggio_soglia) {
					$icona="<img src=img/forum/approvo.gif>";
				} else {
					$icona="<img src=img/forum/disapprovo.gif>";
				};
			};
			$punteggio="$punteggio $stringa[su_max] $punteggio_max $icona";
		} else {
			$punteggio="";
		};
		
		$test[]=$titolo_test."\t".$id_test_compilato."\t".$punteggio."\t".$data_compilazione;
	
	};
	
			
	return $test;

};


function h_m_s($s) {
	$h=0;
	$m=0;
	if ($s>60) {
		$m = floor($s/60);
		$s = $s % 60;
	};
	
	if ($m>60) {
		$h = floor($m/60);
		$m = $m % 60;
	};
	$h=round($h);
	$m=round($m);
	$s=round($s);
	return $h.":".$m.":".$s;
};
?>
