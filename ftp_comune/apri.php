<?php
require "./init_sito.inc";
require "./function_admin.inc";
$cartella=$_REQUEST["cartella"];
?>
<HTML>
<HEAD><TITLE><?php echo($stringa[apri_file]);?></TITLE>
<script language="JavaScript">

function nota(url,x,y) {
  dimensione="toolbar=no,menubar=no,directories=no,status=no,resizable=no,scrollbars=yes,width="+x+",height="+y
 window.open(url,"f",dimensione);

}
</script>

</HEAD>
<BODY bgColor=white>
<font face=verdana size=-1>[<a href="../atlante_editor.php"><?php echo($stringa[indietro]);?></a>]</a></font>
<hr size=1>
  <P><FONT face=verdana><B><br>
   <?php echo($stringa[apri_file]);?></B></FONT> </P>
<?php
echo "
<form action=apri_op.php method=post>
<input type=hidden name=cartella value=\"$cartella\">
<input type=submit value=\"$stringa[apri_file_selezionato]\">";
?>  
<TABLE border=0 width=461>
<tr></td>
<?php
$indice="apri";
browse_folder($cartella);
?>
</td></tr>
	  	  
</TABLE>
</form>
    <BR>
  <HR>

</BODY>
</HTML>
