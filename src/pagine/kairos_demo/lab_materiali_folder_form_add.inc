<?php
$padre=$_REQUEST["padre"];

mysql_select_db($DBASE,$db);	
$id_utente=$kairos_cookie[0];
$query="SELECT DISTINCT id_risorsa,titolo FROM lab_materiali WHERE tipo='2' AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' AND id_autore='$id_utente' ORDER BY titolo,id_risorsa ";
$result=$mysqli->query($query);
/*
if ($padre==0) {
	$elenco_cartelle = "<OPTION VALUE=\"0\" selected>$stringa[principale]</OPTION>\n";
} else {
	$elenco_cartelle = "<OPTION VALUE=\"0\">$stringa[principale]</OPTION>\n";	
};
*/
while ($riga=$result->fetch_array()) {
	$cartella = $riga["id_risorsa"];
	$nome_cartella=$riga["titolo"];
	
	if ($padre==$cartella) {
		$elenco_cartelle .= "<OPTION VALUE=\"$cartella\" selected>$nome_cartella</OPTION>\n";
	} else {
		$elenco_cartelle .= "<OPTION VALUE=\"$cartella\">$nome_cartella</OPTION>\n";	
	};

};

?>
<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[nuova_cartella])."</td></tr>";
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


  <P> 
  <form action=lab_materiali_folder_add.php method=post>
    <TABLE border=0 width=461>
      <TR> 
        <TD colSpan=2></TD>
      </TR>
      <TR> 
        <TD align=right> <span class=testo><STRONG><?php echo($stringa[cartella]);?>:</STRONG></span></TD>
        <TD><SELECT NAME="risorsa_padre">
			<?php echo($elenco_cartelle);?>
			</SELECT> </TD>
      </TR>	  	  

      <TR> 
        <TD align=right> <span class=testo><STRONG><?php echo($stringa[titolo]);?>:</STRONG></span></TD>
        <TD> 
			<INPUT type="text"  name=titolo size=20>
        </TD>
      </TR>

      
	  	  
    </TABLE>
    <BR>
    <P align=center> 
      <INPUT type=submit value="<?php echo($stringa[inserisci]);?>">
    </P>
  </FORM>
<br>
</td></tr></table>
<br>
