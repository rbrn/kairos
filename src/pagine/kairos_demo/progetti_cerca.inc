<?php
$tipo_contributo=array("racconto","poesia/filastrocca","ricetta","gioco","tradizioni","disegno/fotografia","audio");

$elenco_tipo="";

for ($i=0;$i<count($tipo_contributo);$i++) {
	$elenco_tipo.="<option value=\"$tipo_contributo[$i]\">$tipo_contributo[$i]";
};

require "./include/province.inc";

$elenco_province="";

for ($i=0;$i<count($province);$i++) {
	$elenco_province.="<option value=\"$province[$i]\">$province[$i]";
};

$elenco_regioni="";

for ($i=0;$i<count($regioni);$i++) {
	$elenco_regioni.="<option value=\"$regioni[$i]\">$regioni[$i]";
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

$elenco_classi="<option value=XX>qualunque";
for ($i=1;$i<=count($classe_str);$i++) {
	$sel="";
	if ($id_corso_s==$i) $sel="selected";
	$elenco_classi .= "<option value=\"$i\" $sel>$classe_str[$i]";
};


$elenco_argomenti="<option value=XX>qualunque";
for ($i=1;$i<=count($argomento[$id_corso_s]);$i++) {
	$arg_str=$argomento[$id_corso_s][$i];
	if (!ereg("^\[titolo\](.+)$",$arg_str)) {
		$sel="";
		if ($arg==$i) $sel="selected";
		$elenco_argomenti .= "<option value=\"$i\" $sel>$arg_str";
	};
};

$elenco_argomenti .= "<option value=\"lab\">Laboratori espressivi";
$elenco_argomenti .= "<option value=\"mat\">Matematica";
$elenco_argomenti .= "<option value=\"alt\">Altro";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td>";

if ($cod_area=="kairos_amicosole") {
	$titolo="CONTRIBUTI AMICO SOLE";
};

if ($cod_area=="kairos_oppla") {
	$titolo="CONTRIBUTI OPPLA'";
};


if ($cod_area=="kairos_bandaingamba") {
	$titolo="CONTRIBUTI BANDA IN GAMBA'";
};

echo "
<table border=0 width=100% cellspacing=0 cellpadding=0>
<tr>
<td valign=top width=77% class=titolodot>";
echo "$titolo</td>";

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=20%>&nbsp;</td>";
echo "</tr>";

echo "<tr><td valign=top width=77%>";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>&nbsp;&nbsp;<span class=titolopagina>CERCA</span></td></tr>";


echo "
<tr><td>";
?>
 
<FORM action=index.php method=get>
<input type=hidden name=risorsa value="progetti_lista">

    <TABLE border=0 width=461>
      <TR> 
        <TD colSpan=2></TD>
      </TR>
  
<?php 
if ($ruolo=="admin" or $ruolo=="staff") {
 echo "
 <TR> 
        <TD align=right><span class=testo><STRONG>Stato:</STRONG></span></TD>
        <TD><SELECT name=\"stato_progetto\"><option value=\"1\">in attesa di approvazione
		<option value=\"2\" selected>approvato</select></TD>
      </TR>
	";  

};
?>     
	    <TR> 
        <TD align=right><span class=testo><STRONG>Autore/i:</STRONG></span></TD>
        <TD><INPUT type="text" name="autori" size="40"></TD>
      </TR>

		
		<TR> 
        <TD align=right><span class=testo><STRONG>Classe:</STRONG></span></TD>
        <TD><select name="classe"><?php echo($elenco_classi);?></select></TD>
      </TR>
	  
      <TR> 
        <TD align=right><span class=testo><STRONG>Scuola:</STRONG></span></TD>
        <TD><INPUT type="text" name="nome_scuola" size="40"></TD>
      </TR>
	 
	 <TR> 
        <TD align=right><span class=testo><STRONG>CittÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½:</STRONG></span></TD>
        <TD><INPUT type="text" name="citta_scuola" size="40"></TD>
      </TR>
	  
	  <TR> 
        <TD align=right><span class=testo><STRONG>Prov.:</STRONG></span></TD>
        <TD><SELECT name="prov_scuola" size="1">
		<OPTION VALUE="XX" SELECTED>qualunque
		<?php echo($elenco_province);?>
		</SELECT>
</TD>
      </TR>
	  
	<TR> 
        <TD align=right><span class=testo><STRONG>Regione:</STRONG></span></TD>
        <TD><SELECT name="regione_scuola" size="1">
		<OPTION VALUE="XX" SELECTED>qualunque
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
        <TD><INPUT type="text" name="titolo" size="40"></TD>
      </TR>
	  
	  <TR> 
        <TD align=right><span class=testo><STRONG>Tipo:</STRONG></span></TD>
        <TD><SELECT name="tipo" size="1">
		<OPTION VALUE="" SELECTED>qualunque
		<?php echo($elenco_tipo);?>
		</SELECT>
</TD>
      </TR>
  
    </TABLE>
    <BR>
    <P align=center> 
      <INPUT type=submit value="<?php echo($stringa[cerca]);?>">
    </P>
  </FORM>
<br>
</td></tr></table>
<br>
<?php

echo "<td valign=top width=3%>&nbsp;</td>";

echo "<td valign=top width=20%>";

echo "		
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">

<tr> 
<td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testonegativo\" height=\"21\"> 
<img height=20 hspace=5 src=\"img/kairos_amicosole/solepiccolo.gif\" width=20 align=absMiddle><span class=titolo>&nbsp;<b>CONTRIBUTI</b></span>
</td>
</tr>

<tr><td>";

echo "
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
<tr><td align=center>
<span class=\"testopiccolo\">[<a href=index.php?risorsa=progetti_file_form_add>NUOVO</a>]
</span>
</td></tr>
</table>";

echo "</td></tr></table>";
echo "</td></tr></table>";
echo "<br>";

?>
