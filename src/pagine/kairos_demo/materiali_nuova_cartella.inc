<?php
$cartella=$_REQUEST["cartella"];
$tipo_file=$_REQUEST["tipo"];
$dir=$_REQUEST["dir"];
$contesto=$_REQUEST["contesto"];
$nome_campo=$_REQUEST["nome_campo"];
?>
<P><FONT face=verdana><B><br>
    <?php echo($stringa[nuova_cartella]);?></B></FONT> </P>
 <FONT face=verdana size=-1>[<a href="javascript:history.back()"><?php echo($stringa[indietro]);?></a>]</font><br>
  <P> 
  <form action=materiali_cartella_add.php method=post>
  <input type=hidden name=cartella value="<?php echo($cartella);?>">
  <input type=hidden name=tipo value="<?php echo($tipo_file);?>">
  <input type=hidden name=dir value="<?php echo($dir);?>">
  <input type=hidden name=contesto value="<?php echo($contesto);?>">
  <input type=hidden name=nome_campo value="<?php echo($nome_campo);?>">
    <TABLE border=0 width=461>
      <TR> 
        <TD colSpan=2></TD>
      </TR>
  
      <TR> 
        <TD align=right><FONT face=verdana 
            size=-1><STRONG><?php echo($stringa[cartella]);?>:</STRONG></FONT></TD>
        <TD> 
			<INPUT type="text" maxLength=200 name=id_cartella size=20>
        </TD>
      </TR>
      
	  	  
    </TABLE>
    <BR>
    <P align=center> 
      <INPUT type=submit value="<?php echo($stringa[ok]);?>">
    </P>
  </FORM>
  <HR>
