<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>&nbsp;&nbsp;
<span class=titolopagina>MODIFICA CONTRIBUTO</span></td></tr>";


echo "
<tr><td>";
?>


<?php
$id_progetto=$_REQUEST["id_progetto"];
mysql_select_db($DBASE,$db);	
$query = "SELECT * FROM progetti WHERE id_progetto=$id_progetto";
$result=$mysqli->query($query);
$riga=$result->fetch_array();

$titolo=htmlentities($riga["titolo"]);		
$autori=htmlentities($riga["autori"]);
$nome_scuola=htmlentities($riga["nome_scuola"]);
$citta_scuola=htmlentities($riga["citta_scuola"]);
$prov_scuola=htmlentities($riga["prov_scuola"]);
$regione_scuola=htmlentities($riga["regione_scuola"]);
$classe=htmlentities($riga["classe"]);
$unita=htmlentities($riga["unita"]);
$allegato_name=htmlentities($riga["allegato"]);
$allegato_size=$riga["allegato_size"];	
$tipo=$riga["tipo"];

$tipo_contributo=array("racconto","poesia/filastrocca","ricetta","gioco","tradizioni","disegno/fotografia","audio");

$elenco_tipo="";

for ($i=0;$i<count($tipo_contributo);$i++) {
	$sel="";
	if ($tipo_contributo[$i]==$tipo) $sel="selected";
	$elenco_tipo.="<option value=\"$tipo_contributo[$i]\" $sel>$tipo_contributo[$i]";
};


require "./include/province.inc";

$elenco_province="";

for ($i=0;$i<count($province);$i++) {
	$sel="";
	if ($province[$i]==$prov_scuola) $sel="selected";
	$elenco_province.="<option value=\"$province[$i]\" $sel>$province[$i]";
};

$elenco_regioni="";

for ($i=0;$i<count($regioni);$i++) {
	$sel="";
	if ($regioni[$i]==$regione_scuola) $sel="selected";
	$elenco_regioni.="<option value=\"$regioni[$i]\" $sel>$regioni[$i]";
};

require "./pagine/$cod_area/argomenti.inc";

$classe_str[1]="Prima";
$classe_str[2]="Seconda";
$classe_str[3]="Terza";


if ($cod_area=="kairos_oppla") {
$classe_str[4]="Quarta linguaggi";
$classe_str[5]="Quarta discipline";
$classe_str[6]="Quinta linguaggi";
$classe_str[7]="Quinta discipline";
};

$elenco_classi="";
for ($i=1;$i<=count($classe_str);$i++) {
	$sel="";
	if ($classe==$i) $sel="selected";
	$elenco_classi .= "<option value=\"$i\" $sel>$classe_str[$i]";
};

$elenco_argomenti="";
for ($i=1;$i<=count($argomento[$id_corso_s]);$i++) {
	$arg_str=$argomento[$id_corso_s][$i];
	if (!ereg("^\[titolo\](.+)$",$arg_str)) {
		$sel="";
		if ($unita==$i) $sel="selected";
		$elenco_argomenti .= "<option value=\"$i\" $sel>$arg_str";
	};
};

$sel="";
if ($unita=="lab") $sel="selected";
$elenco_argomenti .= "<option value=\"lab\" $sel>Laboratori espressivi";
$sel="";
if ($unita=="mat") $sel="selected";
$elenco_argomenti .= "<option value=\"mat\">Matematica";
$sel="";
if ($unita=="alt") $sel="selected";
$elenco_argomenti .= "<option value=\"alt\">Altro";
?>

<form action=progetti_file_mod_ok.php encType=multipart/form-data method=post>
<INPUT name=MAX_FILE_SIZE type=hidden value=5097150>
<input type=hidden name=id_progetto value="<?php echo($id_progetto);?>">
<input type=hidden name=ex_allegato_name value="<?php echo($allegato_name);?>">
<input type=hidden name=ex_allegato_size value="<?php echo($allegato_size);?>">

    <TABLE border=0 width=461>
      <TR> 
        <TD colSpan=2></TD>
      </TR>
       
	   

	  <TR> 
        <TD align=right><span class=testo><STRONG>Autore/i:</STRONG></span></TD>
        <TD><INPUT type="text" name="autori" size="40" value="<?php echo($autori);?>"></TD>
      </TR>
	  
      <TR> 
        <TD align=right><span class=testo><STRONG>Classe:</STRONG></span></TD>
        <TD><select name="classe"><?php echo($elenco_classi);?></select></TD>
      </TR>

      <TR> 
        <TD align=right><span class=testo><STRONG>Scuola:</STRONG></span></TD>
        <TD><INPUT type="text" name="nome_scuola" size="40" value="<?php echo($nome_scuola);?>"></TD>
      </TR>
	 
	 <TR> 
        <TD align=right><span class=testo><STRONG>CittÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½:</STRONG></span></TD>
        <TD><INPUT type="text" name="citta_scuola" size="40" value="<?php echo($citta_scuola);?>"></TD>
      </TR>
	  
	 <TR> 
        <TD align=right><span class=testo><STRONG>Prov.:</STRONG></span></TD>
        <TD><SELECT name="prov_scuola" size="1">
		<OPTION VALUE="XX" SELECTED>Scegli la provincia
		<?php echo($elenco_province);?>
		</SELECT>
</TD>
      </TR>
	  
	<TR> 
        <TD align=right><span class=testo><STRONG>Regione:</STRONG></span></TD>
        <TD><SELECT name="regione_scuola" size="1">
		<OPTION VALUE="XX" SELECTED>Scegli la regione
		<?php echo($elenco_regioni);?>
		</SELECT>
</TD>
      </TR>
	  
	  
	    <TR> 
        <TD align=right><span class=testo><STRONG>Argomento:</STRONG></span></TD>
        <TD><select name="unita"><?php echo($elenco_argomenti);?></select></TD>
      </TR>
	  
	   <TR> 
        <TD align=right><span class=testo><STRONG>Titolo:</STRONG></span></TD>
        <TD><INPUT type="text" name="titolo" size="40" value="<?php echo($titolo);?>"></TD>
      </TR>
	  
	  <TR> 
        <TD align=right><span class=testo><STRONG>Tipo:</STRONG></span></TD>
        <TD><SELECT name="tipo" size="1">
		<?php echo($elenco_tipo);?>
		</SELECT>
</TD>
      </TR>
	  
	    <TR> 
        <TD align=right><span class=testo><STRONG><?php echo($stringa[file_caricare]);?>:</STRONG></span></TD>
        <TD><INPUT type="file" name=allegato></TD>
      </TR>
	  
    </TABLE>
    <BR>
    <P align=center> 
      <INPUT type=submit value="<?php echo($stringa[modifica]);?>">
    </P>
  </FORM>
<br>
</td></tr></table>
<br>	
