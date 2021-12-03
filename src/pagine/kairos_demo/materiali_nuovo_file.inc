<?php
$cartella=$_REQUEST["cartella"];
$tipo_file=$_REQUEST["tipo"];
$dir=$_REQUEST["dir"];
$contesto=$_REQUEST["contesto"];
$nome_campo=$_REQUEST["nome_campo"];
?>
<P><FONT face=verdana><B><br>
    <?php echo($stringa[nuovo_file]);?> </B></FONT> </P>
 <FONT face=verdana size=-1>[<a href="javascript:history.back()"><?php echo($stringa[indietro]);?></a>]</font><br>
  <P> 
<FORM action=materiali_nuovo_file_add.php encType=multipart/form-data method=post>
<INPUT name=MAX_FILE_SIZE type=hidden value=5097150>
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
        <TD><FONT face=verdana size=-1> 
				<?php echo($cartella);?>
          </FONT></TD>
      </TR>	  	  

	  <TR> 
        <TD align=right><FONT face=verdana 
            size=-1><STRONG><?php echo($stringa[file_caricare]);?>:</STRONG></FONT></TD>
        <TD><FONT face=verdana size=-1> 
          <INPUT type="file" name=file size=40>
          </FONT></TD>
      </TR>

  	   
	  	  
    </TABLE>
    <BR>
    <P align=center> 
      <INPUT type=submit value="<?php echo($stringa[carica]);?>">
    </P>
  </FORM>
  <HR>
