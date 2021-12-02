<?php

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

$id_risorsa=$_REQUEST["id_risorsa"];
mysql_select_db($DBASE,$db);	
$query = "SELECT * FROM risorse_materiali where id_risorsa='$id_risorsa'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$risorsa_padre=$riga["risorsa_padre"];		
$titolo_risorsa=htmlentities($riga["titolo"]);
$id_autore=$riga["id_autore"];		

$id_editor_gruppo="";
if ($risorsa_padre<>"root") {
$query_p = "SELECT id_editor_gruppo FROM risorse_materiali where id_risorsa='$risorsa_padre'";
$result_p=$mysqli->query($query_p);
$riga_p=$result_p->fetch_array();
$id_editor_gruppo=$riga_p["id_editor_gruppo"];	
};
     
if ($ruolo=='admin') {
$query="SELECT id_risorsa,titolo FROM risorse_materiali WHERE tipo='20' AND url is NULL ORDER BY id_risorsa ";
} else {
$query="SELECT id_risorsa,titolo FROM risorse_materiali WHERE tipo='20' AND url is NULL AND (id_editor='$id_utente' or id_autore='$id_utente') ORDER BY id_risorsa ";
};

$result=$mysqli->query($query);

$elenco_cartelle = "";
while ($riga=$result->fetch_array()) {
	$cartella = $riga["id_risorsa"];
	$titolo = $riga["titolo"];
	
	if ($cartella<>$id_risorsa) {
	if ($risorsa_padre==$cartella) {
		$elenco_cartelle .= "<OPTION VALUE=\"$cartella\" selected>$titolo</OPTION>\n";
	} else {
		$elenco_cartelle .= "<OPTION VALUE=\"$cartella\">$titolo</OPTION>\n";	
	};
	};
};  

if ($ruolo=='admin') {
	$query="SELECT editor_gruppo.* FROM editor_gruppo ORDER BY descrizione";
} else {
	$query="SELECT editor_gruppo.*  FROM editor_gruppo,editor_gruppo_utenti WHERE editor_gruppo.id_editor_gruppo=editor_gruppo_utenti.id_editor_gruppo AND editor_gruppo_utenti.id_utente='$id_utente'";
};

$result=$mysqli->query($query);

if ($id_editor_gruppo=='') {
	$elenco_gruppo_editor = "<OPTION VALUE=\"\" selected></OPTION>\n";
} else {
	$elenco_gruppo_editor = "<OPTION VALUE=\"\"></OPTION>\n";
};

while ($riga=$result->fetch_array()) {
	$id_ed_gr=$riga["id_editor_gruppo"];
	$descrizione_gr = $riga["descrizione"];

	if ($id_editor_gruppo==$id_ed_gr) {
		$elenco_gruppo_editor .= "<OPTION VALUE=\"$id_ed_gr\" selected>$descrizione_gr</OPTION>\n";
	} else {
		$elenco_gruppo_editor .= "<OPTION VALUE=\"$id_ed_gr\">$descrizione_gr</OPTION>\n";
	};
};

if ($risorsa_padre=="root") {
	$query="SELECT * FROM lo WHERE id_lo='$id_risorsa'";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$lo_skin=$riga["lo_skin"];
	$lo_url=$riga["lo_url"];
	$lo_tipo_lom=$riga["lo_tipo_lom"];
	$materia=htmlentities($riga["materia"]);
	$fruitore=htmlentities($riga["fruitore"]);
	$obiettivi=htmlentities($riga["obiettivi"]);
	$argomenti=htmlentities($riga["argomenti"]);
	$profilo_ingresso=htmlentities($riga["profilo_ingresso"]);
	$lo_licenza=htmlentities($riga["lo_licenza"]);
	$file_audio=$riga["file_audio"];
	$lo_modocontinua=$riga["lo_modocontinua"];
	$lo_bloccoavanzamento=$riga["lo_bloccoavanzamento"];
	$lo_shell=$riga["lo_shell"];	
	$path_file=$PATH_ROOT_FILE."materiali/$cod_area/".$id_risorsa."_credits.txt";
	if (file_exists($path_file)) {
	$nomi_credits_file=join('',file($path_file));
	$nomi_credits=explode("\t",$nomi_credits_file);
	$nome_autore_credits=$nomi_credits[0];
	$nome_coordinatore_credits=$nomi_credits[1];
	};
};
?>

<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[gestione_contenuti])."</td></tr>

";

if ($risorsa_padre<>"root") {
echo "<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper("$stringa[modifica] $stringa[cartella]")."</b></span>
</td></tr>
";
} else {
echo "<tr>
<td valign=top width=100%><span class=testo><b>".strtoupper("$stringa[modifica] $stringa[lo]")."</b></span>
</td></tr>
";
};

echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";

echo "
<tr><td>";
?>

<form action=lo_folder_mod_ok.php method=post name=modulo id=modulo>
<input type=hidden name=id_risorsa value="<?php echo($id_risorsa);?>">
<input type=hidden name=ex_risorsa_padre value="<?php echo($risorsa_padre);?>">
    <TABLE border=0 width=461>
	<?php if ($risorsa_padre<>"root") { ?>
     <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[cartella_sup]);?>:</STRONG></span></TD>
        <TD>
			<SELECT NAME="risorsa_padre">
			<?php echo($elenco_cartelle);?>
			</SELECT> 
          </TD>
      </TR>	 
	<?php } else { ?>
	
	<input type=hidden name=risorsa_padre value="<?php echo($risorsa_padre);?>">	
	
	<?php }; ?>
	
	<!--
      <TR> 
        <TD colSpan=2></TD>
      </TR>
      <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[id_cartella]);?>:</STRONG></span></TD>
        <TD> 
			<INPUT type="text" maxLength=200 name=id_risorsa 
            size=20 value="<?php echo($id_risorsa);?>">			
	    </TD>
      </TR>
	
	
	  <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[id_gruppo]);?>:</STRONG></span></TD>
        <TD> 
			<SELECT NAME="id_editor_gruppo">
			<?php echo($elenco_gruppo_editor);?>
			</SELECT> 
        </TD>
      </TR>
	  -->
      <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[titolo]);?>:</STRONG></span></TD>
        <TD> 
			<INPUT type="text"  name=titolo size=60 value="<?php echo($titolo_risorsa);?>">			
	    </TD>
      </TR>	  
	  
	   <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[autore]);?>:</STRONG></span></TD>
        <TD>
          <INPUT type="text" name=id_autore size=20 value="<?php echo($id_autore);?>">
          
		  <?php 
			echo "
<span class=\"testopiccolo\">
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup.php?ruolo=tutti&campo=id_autore','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup_op.php?ruolo=tutti&campo=id_autore','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["tutti"]."</a>]
</span>";
?>
		  </TD>
      </TR> 

	  <TR> 
        <TD align=right><span class=testo><STRONG>Nome e cognome autore:</STRONG></span></TD>
        <TD> 
			<INPUT type="text"  name="nome_autore_credits" size="60" value="<?php echo($nome_autore_credits);?>">
        </TD>
      </TR>
	  
	  <TR> 
        <TD align=right><span class=testo><STRONG>Nome e cognome coordinatore disciplinare:</STRONG></span></TD>
        <TD> 
			<INPUT type="text"  name="nome_coordinatore_credits" size="60" value="<?php echo($nome_coordinatore_credits);?>">
        </TD>
      </TR>
	  
<?php 
if ($risorsa_padre=="root" ) {
?>

	<?php 
	$query="SELECT * FROM lo_schema WHERE id_lom='05.02' AND id_profile='lom_garamond' LIMIT 1";
	$result=$mysqli->query($query);
	$riga=$result->fetch_array();
	$valuespace=$riga[valuespace];
	$opzioni="";
	$lista=explode("\n",$valuespace);
	for ($i=0;$i<count($lista);$i++) {
		$sel="";
		if (trim($lo_tipo_lom)==trim($lista[$i])) $sel="selected";
		$opzioni.="<option value=\"$lista[$i]\" $sel>$lista[$i]</option>";
	};
	
	?>  
	 
	<TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[lo_tipo_lom]);?>:</STRONG></span></TD>
        <TD> 
			<select name="lo_tipo_lom" size="1"><?php echo $opzioni ?></select>
        </TD>
     </TR>
	 	  
   <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[materia]);?>:</STRONG></span></TD>
        <TD> 
			<INPUT type="text"  name="materia" size="60" value="<?php echo($materia);?>">
        </TD>
      </TR>
	  
	  <TR> 
        <TD align=right valign=top><span class=testo><STRONG><?php echo($stringa[fruitore]);?>:</STRONG></span></TD>
        <TD valign=top> 
			<textarea name="fruitore" rows="05" cols="60"><?php echo($fruitore);?></textarea>
        </TD>
      </TR>
	 
	  
	   <TR> 
        <TD align=right valign=top><span class=testo><STRONG><?php echo($stringa[argomenti]);?>:</STRONG></span></TD>
        <TD  valign=top> 
			<textarea name="argomenti" rows="05" cols="60"><?php echo($argomenti);?></textarea>
        </TD>
      </TR>
	  
	  <TR> 
        <TD align=right valign=top><span class=testo><STRONG><?php echo($stringa[obiettivi_didattici]);?>:</STRONG></span></TD>
        <TD valign=top> 
			<textarea name="obiettivi" rows="05" cols="60"><?php echo($obiettivi);?></textarea>
        </TD>
      </TR>
	  
	  
	 <TR> 
        <TD align=right valign=top><span class=testo><STRONG><?php echo($stringa[competenze_ingresso]);?>:</STRONG></span></TD>
        <TD valign=top> 
			<textarea name="profilo_ingresso" rows="05" cols="60"><?php echo($profilo_ingresso);?></textarea>
        </TD>
      </TR>  
	 
	 
	  <TR> 
        <TD align=right valign=top><span class=testo><STRONG>Licenza:</STRONG></span></TD>
        <TD valign=top> 
			<textarea name="lo_licenza" rows="15" cols="60"><?php echo($lo_licenza);?></textarea>
        </TD>
      </TR>  
	<TR> 
        <TD align=right><span class=testo><STRONG>Shell:</STRONG></span></TD>
        <TD> 
			<select name="lo_shell" size="1"><option value="0">Versione 1.0</option><option value="1">Versione 2.0 (in costruzione)</option></select>
        </TD>
     </TR>	  
	<?php 
	if ($cod_area<>"kairos_eprof") {
	$dir_path=$PATH_ROOT_FILE."shell/skins/";
	$d = dir($dir_path);
	$elenco_skin="";
	while ($nomefile=$d->read()) {
		
		if (($nomefile != '.') && ($nomefile != '..')) { 
			if (is_dir($dir_path.$nomefile)) {
				$skin=basename($nomefile);
				$sel="";
				if ($skin==$lo_skin) $sel="selected";
				$prendi=true;
				if (($skin=="trevi_mat" or $skin=="trevi_ita") and $cod_area<>"kairos_tdm") $prendi=false;
				if (($skin=="orione") and $cod_area<>"kairos_capuiano") $prendi=false;
				if (($cod_area=="kairos_concorsocontenuti07")) {
					$prendi=false;
					if ($skin=="bibliotecadigitale")
						$prendi=true;
				}
				if ($prendi) $elenco_skin.="<option value=\"$skin\" $sel>$skin</option>";
			};
		};
	}
	$d->close();
	} else {
		$elenco_skin="<option value=\"default\">default</option>";
	}
	?>  

	 
	<TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[lo_tema_grafico]);?>:</STRONG></span></TD>
        <TD> 
			<select name="lo_skin" size="1"><?php echo $elenco_skin ?></select>
        </TD>
     </TR>
	 <?php
	 $check="";
	 if ($lo_modocontinua=="1") $check="checked";
	 ?>
	 <TR> 
        <TD align=right></TD>
        <TD> 
			<input type="checkbox" name="lo_modocontinua" <?php echo($check);?>> <span class=testo><STRONG><?php echo($stringa[lo_modocontinua]);?></STRONG></span>
        </TD>
     </TR>
	 
	 
	  <?php
	 $check="";
	 if ($lo_bloccoavanzamento=="1") $check="checked";
	 ?>
	 <TR> 
        <TD align=right></TD>
        <TD> 
			<input type="checkbox" name="lo_bloccoavanzamento" <?php echo($check);?>> <span class=testo><STRONG><?php echo($stringa[lo_bloccoavanzamento]);?></STRONG></span>
        </TD>
     </TR>
	 
	 <?php 
	 echo "<tr>
<td align=right valign=top><span class=testo><b>$stringa[audio_opzionale]:</b></span></td>
<td><input type=\"text\" name=\"file_audio\" id=\"file_audio\" readonly value=\"$file_audio\" size=\"60\"><br>
<a href=\"javascript:;\" onclick=\"return lo_seleziona_media('gruppo','audio','file_audio');\"><span class=testopiccolo>$stringa[elenco_suoni]</span></a><br>
<input type=\"checkbox\" name=\"elimina_audio\" id=\"elimina_audio\"> <span class=testopiccolo>Elimina audio</span></td>
</tr>";
	?>

<?php }; ?>	  
	  	  
    </TABLE>
    <BR>
    <P align=center> 
      <INPUT type=submit value="<?php echo($stringa[modifica]);?>">
    </P>
  </FORM>
  
</td></tr></table>
<br>


echo "                </div>
</div>
</div>
</div>
</div>"

?>
