<?php
require "./config.php";
require "./variabili.php";
function cancella_metadata($id_rep,$id_lo) {
	global $db;
	$query="DELETE FROM lo_metadata WHERE id_rep='$id_rep' AND id_lo='$id_lo'";
	$result=$mysqli->query($query);
	$query="DELETE FROM lo_metadata_valore WHERE id_rep='$id_rep'";
	$result=$mysqli->query($query);
	$query="SELECT * FROM lo_metadata WHERE id_rep_sup='$id_rep' AND id_lo='$id_lo'";
	$result=$mysqli->query($query);
	if ($result->num_rows) {
		while ($riga=$result->fetch_array()) {
			$id_rep=$riga[id_rep];
			cancella_metadata($id_rep,$id_lo);
		};
	};
};

function mostra_lom($id_lo,$id_profile,$id_lom_sup=0,$id_rep_sup=0) {
	global $opt_lang;
	global $db;
	global $win_ie,$opera,$mozilla,$firefox;
	
	$query="SELECT * FROM lo_schema WHERE id_lom_sup='$id_lom_sup' AND id_profile='$id_profile' ORDER BY id_lom";
	$result=$mysqli->query($query);
	
		while ($riga=$result->fetch_array()) {
			$id_lom=$riga[id_lom];
			$nome=htmlentities($riga[nome]);
			$size=$riga[size];
			$tipocampo=$riga[tipocampo];
			$valuespace=$riga[valuespace];
			$langstring=$riga[langstring];
			$datetype=$riga[datetype];
			$valdefault=$riga[valdefault];
            $obbligatorio=$riga[obbligatorio];
            $commento=$riga[commento];
			
			$nome=strtoupper(substr($nome,0,1)).substr($nome,1,strlen($nome));
			
            if ($obbligatorio) $nome="<b>".$nome."</b>";
			
			$query1="SELECT * FROM lo_metadata WHERE id_lom='$id_lom' AND id_lo='$id_lo' AND id_rep_sup='$id_rep_sup' ORDER BY id_rep";
			$result1=$mysqli->query($query1);
	
			$icona_meno="";
			$icona_piu="";
			if ($result1->num_rows) {
				while ($riga1=$result1->fetch_array()) {
					$id_rep=$riga1[id_rep];
					$lang=trim($riga1[lang]);
					$valore=trim($riga1[valore]);
					
					$id_campo=$id_rep_sup."_".$id_rep."_".str_replace(".","-",$id_lom);
					
					$sezione=$id_rep_sup."_".$id_lom;
					
					$icona_meno="<input name=\"del\" value=\"-\" onclick=\"invia_azione('del','$id_campo','$sezione');\" type=\"submit\">";
		
					if ($result1->num_rows<$size) {
						$icona_piu="<input name=\"add\" value=\"+\" onclick=\"invia_azione('add','$id_campo','$sezione');\" type=\"submit\">";
					} else {
						$icona_piu="";
					};
					
					echo "
				<table>
	<tr><td><a name=\"$sezione\">";
					if ($win_ie) {
						echo "<fieldset style=\"float: left; margin-left: 5px;\">";
					} else {
						echo "<ul><li>";
					};
					echo "<legend>$id_lom.$nome $icona_meno $icona_piu ";
	
					if (trim($commento)) {
						echo "[<A href=\"javascript:;\" onClick=\"popup('mostra_commento.php?id_lom=$id_lom&id_profile=$id_profile','guida',500,400,1,0);\">?</a>]";
					};
					echo "</legend>";
	
					$query2="SELECT * FROM lo_schema WHERE id_lom_sup='$id_lom'  AND id_profile='$id_profile' ORDER BY id_lom";
					$result2=$mysqli->query($query2);
					if ($result2->num_rows) {
						mostra_lom($id_lo,$id_profile,$id_lom,$id_rep);
					} else {
                        echo "<table border=\"0\">
                        <tr><td valign=\"top\"> 
                        ";
						if ($langstring) {
							$opzioni="";
						
							for ($i=0;$i<count($opt_lang);$i++) {
								$sel="";
								if ($lang==$opt_lang[$i]) $sel="selected";
								$opzioni.="<option value=\"$opt_lang[$i]\" $sel>$opt_lang[$i]</option>";
							};
							
							$id_campo_l=$id_campo."_lang_0";
							
							echo "<table border=\"0\">
                        	<tr><td valign=\"top\">
                    	    ";
							
							echo "<select  name=\"$id_campo_l\">$opzioni</select>
							";
							
							echo "</td>";
							echo "<td valign=\"top\">";
							switch ($tipocampo) {
							case "text":
								echo "<input type=\"text\" name=\"$id_campo\" value=\"$valore\" size=\"50\">";
								break;
							
							case "textarea":
								echo "<textarea cols=\"50\" rows=\"05\" name=\"$id_campo\">$valore</textarea>";
								break;
								
							case "select":
								$opzioni="";
								$lista=explode("\n",$valuespace);
								for ($i=0;$i<count($lista);$i++) {
									$sel="";
									if ($valore==$lista[$i]) $sel="selected";
									$opzioni.="<option value=\"$lista[$i]\" $sel>$lista[$i]</option>";
								};
								echo "<select  name=\"$id_campo\">$opzioni</select>";
								break;
							};
							echo "</td>
							<td valign=\"top\">
							<input name=\"addlang\" value=\"+\" onclick=\"invia_azione('addlang','$id_campo','$sezione');\" type=\"submit\">
							</td></tr></table><br>";
							
							$query_l="SELECT * FROM lo_metadata_valore WHERE id_rep='$id_rep' ORDER BY n";
							$result_l=$mysqli->query($query_l);
							$k=1;
							while ($riga_l=$result_l->fetch_array()) {
								$lang=trim($riga_l[lang]);
								$valore=trim($riga_l[valore]);
								$id_campo=$id_rep_sup."_".$id_rep."_".str_replace(".","-",$id_lom)."_".$k;
							
								$opzioni="";
								for ($i=0;$i<count($opt_lang);$i++) {
									$sel="";
									if ($lang==$opt_lang[$i]) $sel="selected";
									$opzioni.="<option value=\"$opt_lang[$i]\" $sel>$opt_lang[$i]</option>";
								};
							
								$id_campo_l=$id_rep_sup."_".$id_rep."_".str_replace(".","-",$id_lom)."_lang_".$k;
								
								echo "<table border=\"0\">
                        		<tr><td valign=\"top\">
                    	    	";
								echo "<select  name=\"$id_campo_l\">$opzioni</select>";
							
								echo "</td>";
								echo "<td valign=\"top\">";
							
								switch ($tipocampo) {
								case "text":
									echo "<input type=\"text\" name=\"$id_campo\" value=\"$valore\" size=\"50\">";
									break;
							
								case "textarea":
									echo "<textarea cols=\"50\" rows=\"05\" name=\"$id_campo\">$valore</textarea>";
									break;
								
								case "select":
									$opzioni="";
									$lista=explode("\n",$valuespace);
									for ($i=0;$i<count($lista);$i++) {
										$sel="";
										if ($valore==trim($lista[$i])) $sel="selected";
										$opzioni.="<option value=\"$lista[$i]\" $sel>$lista[$i]</option>";
									};
									echo "<select  name=\"$id_campo\">$opzioni</select>";
									break;
								};
								echo "
								</td>
								<td valign=\"top\">
								<input name=\"dellang\" value=\"-\" onclick=\"invia_azione('dellang','$id_campo','$sezione');\" type=\"submit\"></td></tr></table><br>";
								$k++;
							};
							
						} else {
							switch ($tipocampo) {
							case "text":
								echo "<input type=\"text\" name=\"$id_campo\" value=\"$valore\" size=\"50\">";
								break;
							
							case "textarea":
								echo "<textarea cols=\"50\" rows=\"05\" name=\"$id_campo\">$valore</textarea>";
								break;
								
							case "select":
								$opzioni="";
								$lista=explode("\n",$valuespace);
								for ($i=0;$i<count($lista);$i++) {
									$sel="";
									if ($valore==trim($lista[$i])) $sel="selected";
									$opzioni.="<option value=\"$lista[$i]\" $sel>$lista[$i]</option>";
								};
								echo "<select  name=\"$id_campo\">$opzioni</select>";
								break;
							};
						};	
						echo "</td></tr></table>";
						
					}
					if ($win_ie) {
						echo "</fieldset>";
					} else {
						echo "</li></ul>";
					};
					echo "</a></td></tr>
				</table>\n";
				
				};
			} else {
				$id_rep=0;
				$id_campo=$id_rep_sup."_".$id_rep."_".str_replace(".","-",$id_lom);
				
				$sezione=$id_rep_sup."_".$id_lom;
				
				$icona_meno="";
		
				$icona_piu="<input name=\"add\" value=\"+\" onclick=\"invia_azione('add','$id_campo','$sezione');\" type=\"submit\">";
				
				
				echo "
				<table>
	<tr><td><a name=\"$sezione\">";
		
				if ($win_ie) {
					echo "<fieldset style=\"float: left; margin-left: 5px;\">";
				} else {
					echo "<ul><li>";
				};
				echo "<legend>$id_lom.$nome $icona_meno $icona_piu ";
				
				if (trim($commento)) {
					echo "[<A href=\"javascript:;\" onClick=\"popup('mostra_commento.php?id_lom=$id_lom&id_profile=$id_profile','guida',500,400,1,0);\">?</a>]";
				};
					
				echo "</legend>";
	
					
				if ($win_ie) {
					echo "</fieldset>";
				} else {
					echo "</li></ul>";
				};
				echo "</a></td></tr>
			</table>\n";
			};
		};

};




$id_lo=$_REQUEST[id_lo];
if (!$id_lo) {
	$id_lo="demo";
	//$id_lo=uniqid("");
};

$azione=$_REQUEST[azione];
$id_campo=$_REQUEST[id_campo];



$db=mysql_connect($DBHOST,$DBUSER,$DBPWD);
mysql_select_db($DBASE);
list($id_rep_sup,$id_rep,$id_lom,$n)=split("_",$id_campo);
$id_lom=str_replace("-",".",$id_lom);

$query="SELECT * FROM lo WHERE id_lo='$id_lo'";
$result=$mysqli->query($query);
$riga=$result->fetch_array();
$id_profile=$riga[id_profile];

switch ($azione) {
	case "addlang":
	require "./registro_lo.inc";
	
	$val_default="03.04";
	$query1="SELECT * FROM lo_metadata WHERE id_lom='$val_default' AND id_lo='$id_lo' ";
	$result1=$mysqli->query($query1);
	$riga1=$result1->fetch_array();
	$lang=trim($riga1[valore]);
	
	
	$query1="SELECT COUNT(*) AS n_istanze FROM lo_metadata_valore WHERE id_rep='$id_rep'";
	$result1=$mysqli->query($query1);
	$riga1=$result1->fetch_array();
	$n_istanze=$riga1[n_istanze]+1;
	
	$query="INSERT INTO lo_metadata_valore SET
		id_rep='$id_rep',
		n='$n_istanze',
		lang='$lang',
		valore=''";
		$mysqli->query($query);
	break;
	
	case "dellang":
	require "./registro_lo.inc";
	$query1="SELECT COUNT(*) AS n_istanze FROM lo_metadata_valore WHERE id_rep='$id_rep'";
	$result1=$mysqli->query($query1);
	$riga1=$result1->fetch_array();
	$n_istanze=$riga1[n_istanze]+1;
	$query="DELETE FROM lo_metadata_valore WHERE id_rep='$id_rep' AND n='$n'";
	$mysqli->query($query);
	$i=1;
	$query1="SELECT * FROM lo_metadata_valore WHERE id_rep='$id_rep' ORDER BY n";
	$result1=$mysqli->query($query1);
	while ($riga1=$result1->fetch_array()) {
		$n2=$riga1[n];
		$query2="UPDATE lo_metadata_valore SET n='$i' WHERE id_rep='$id_rep' AND n='$n2'";
		$mysqli->query($query2);
		$i++;
	};
	break;
	
	
	case "add":
	
	require "./registro_lo.inc";
	
	$query1="SELECT * FROM lo_schema WHERE id_lom='$id_lom' AND id_profile='$id_profile'";
	$result1=$mysqli->query($query1);
	$riga1=$result1->fetch_array();
	$size=$riga1[size];
	$val_default=trim($riga1[val_default]);
	$langstring=trim($riga1[langstring]);
	
	$lang="";
	$valore="";
	if ($val_default or $langstring) {
		if ($langstring) $val_default="03.04";
		$query1="SELECT * FROM lo_metadata WHERE id_lom='$val_default' AND id_lo='$id_lo' ";
		$result1=$mysqli->query($query1);
		$riga1=$result1->fetch_array();
		if ($langstring) {
			$lang=trim($riga1[valore]);
		} else {
			$valore=trim($riga1[valore]);
		};
	};
	
	
	$query1="SELECT COUNT(*) AS n_istanze FROM lo_metadata WHERE id_lom='$id_lom' AND id_lo='$id_lo' AND id_rep_sup='$id_rep_sup'";
	$result1=$mysqli->query($query1);
	$riga1=$result1->fetch_array();
	$n_istanze=$riga1[n_istanze];
	
	if ($size>$n_istanze) {
		$query="INSERT INTO lo_metadata SET
		id_lo='$id_lo',
		id_profile='$id_profile',
		id_rep_sup='$id_rep_sup',
		lang='$lang',
		valore='$valore',
		id_lom='$id_lom'";
		$mysqli->query($query);
	};
	break;
	
	case "del":
	require "./registro_lo.inc";
	cancella_metadata($id_rep,$id_lo);
	break;
	
	case "ok":
	require "./registro_lo.inc";
	
	/* controllo obbligatorietÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ */
	$query="SELECT * FROM lo_schema WHERE obbligatorio=1  AND id_profile='$id_profile' ORDER BY id_lom";
	$result=$mysqli->query($query);
	$errore="";
	while ($riga=$result->fetch_array()) {
        $id_lom=$riga[id_lom];
        $nome=$riga[nome];
        $query1="SELECT * FROM lo_metadata WHERE id_lom='$id_lom' AND id_lo='$id_lo'";
$result1=$mysqli->query($query1);
        if (!$result1->num_rows){
          $errore.="Manca metadato obbligatorio: $id_lom $nome<br>";
        };
    };
    if ($errore) {
        Header("Location:msg.php?msg=$errore&id_lo=$id_lo");
        exit();
    }
	
	break;

	default: 
		//echo "niente <br>";
		break;
};

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>LOM Editor</title>

	<link rel="stylesheet" href="stile_lom.css.php">
	
<script language="javascript">
function invia_azione(azione,id_campo,sezione) {
	document.modulo.action="#"+sezione;
	document.modulo.azione.value=azione;
	document.modulo.id_campo.value=id_campo;
	return true;
}

function popup(url,titolo,w,l,scroll,resizable){
	var winl = (screen.width-w)/2;
    var wint = (screen.height-l)/2;
	window.open(url, titolo, "toolbar=no, menubar=no, status=no, titlebar=yes,scrollbars="+scroll+", resizable="+resizable+", width="+w+", height="+l+", top="+wint+", left="+winl);
};


</script>
</head>

<body>
<div class="title">Editor LOM</div>
[<a href="editorprofile/index.php">LOM Application Profile Editor</a>]
<form action="" method="post" name="modulo" id="modulo">
<input type="hidden" name="id_lo" value="<?php echo($id_lo);?>">
<input type="hidden" name="azione">
<input type="hidden" name="id_campo">

<?php
mostra_lom($id_lo,$id_profile,"0");
?>


<br clear="all" />


<p>
<input type="submit" value="OK" onclick="invia_azione('ok','','0');"> [<a href="esporta.php?id_lo=<?php echo $id_lo ?>&encode=IMS">Esporta IMS LOM</a>] [<a href="esporta.php?id_lo=<?php echo $id_lo ?>&encode=LOM">Esporta IEEE LTSC LOM</a>]
</p>
</form>
<hr size=1>
LOM Editor & Metadata Generator - &copy;2005 - <a href="http://ec2-54-229-184-60.eu-west-1.compute.amazonaws.com/kairos" target="_blank">Garamond</a>
</body>
</html>
