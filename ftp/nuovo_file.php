<?php
require "./init_sito.inc";
$cartella=$_REQUEST["cartella"];
?>
<HTML>
<HEAD><TITLE><?php echo($stringa[nuovo_file]);?></TITLE>
</HEAD>
<BODY bgColor=white>
<ul>
  <P align=left><FONT face=verdana><B><br>
    <?php echo($stringa[nuovo_file]);?></B></FONT> </P>
 <FONT face=verdana size=-1>[<a href=index.php?cartella=<?php echo($cartella);?>><?php echo($stringa[indietro]);?></a>]</font><br>
  <P> 
<FORM action=nuovo_file_add.php encType=multipart/form-data method=post>
<INPUT name=MAX_FILE_SIZE type=hidden value=5097150>
 <input type=hidden name=cartella value="<?php echo($cartella);?>">
 
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
          <INPUT type="file" name=file size=60>
          </FONT></TD>
      </TR>

  	   
	  	  
    </TABLE>
    <BR>
    <P align=center> 
      <INPUT type=submit value="<?php echo($stringa[carica]);?>">
    </P>
  </FORM>
  <HR>
</ul>
</BODY>
</HTML>
