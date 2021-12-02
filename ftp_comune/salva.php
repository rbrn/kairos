<?php
require "./init_sito.inc";
require "./function_admin.inc";
?>
<HTML>
<HEAD><TITLE><?php echo($stringa[salva_file]);?></TITLE>
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
   <?php echo($stringa[salva_file_in]);?></B></FONT> </P>

<?php
$nome=$kairos_cookie[6];
$titolo=$kairos_cookie[7];
?>  
<TABLE border=0 width=461>
<tr></td>
<?php
$indice="salva";
$cartella=$_REQUEST["cartella"];
browse_folder($cartella);
?>
</td></tr>
	  	  
</TABLE>
<br>
<form action=salva_op.php method=post>
<input type=hidden name=cartella value="<?php echo($cartella);?>">
<?php echo($stringa[nome]);?>: <input type=text name=nome size=20 value="<?php echo($nome);?>">.htm<br>
<?php echo($stringa[titolo]);?>: <input type=text name=titolo size=20 value="<?php echo($titolo);?>"><br>
<input type=submit value="<?php echo($stringa[salva]);?>">
</form>
    <BR>
  <HR>

</BODY>
</HTML>
