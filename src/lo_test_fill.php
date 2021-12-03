<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$campo=$_REQUEST[campo];
$id_item=$_REQUEST[id_item];
$posizione=$_REQUEST[posizione];
?>
<HTML>
<HEAD>
<TITLE>Seleziona</TITLE>
<?php 
echo "
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">";
?>
<SCRIPT language="JavaScript">
function scelta(opzione) {
	opener.document.getElementById("campo_<?php echo $campo ?>").innerHTML=opzione;
	opener.document.getElementById("<?php echo $campo ?>").value=opzione;			
	self.close();
};
</script>
</HEAD>
<body  bgcolor=<?php echo($colore_sfondo_neutro);?> topmargin="10" bottommargin="10" leftmargin="10" rightmargin="10">
<TABLE border="0" cellpadding="0" cellspacing="0" width="100%" align="center">
<TR><TD valign="top">


   <TABLE width="100%" border="0" cellspacing="0" cellpadding="10">
     <TR><TD valign="top" class="testo">

<?php
	
$query2="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND posizione='$posizione'";
$result2=$mysqli->query($query2);
$opzione=$result2->fetch_array();
$risposte_lista=($opzione[risposte_lista]);
$opt_list=split("\n",$risposte_lista);
for ($k=0;$k<count($opt_list);$k++) {
	$opt=trim(addslashes($opt_list[$k]));
	if ($opt) {
		echo "<input type=\"radio\" name=\"voce\" onclick=\"scelta('$opt')\";>$opt<br><br>";
	 };
};
?>

	   </TD>
     </TR>
   </TABLE>
   <!-- testo della pagina --> 


</TD></TR>
</TABLE>


</BODY>
</HTML>

