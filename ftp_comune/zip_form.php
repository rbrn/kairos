<?php
require "./init_sito.inc";
$cartella=$_REQUEST["cartella"];
?>
<HTML>
<HEAD><TITLE><?php echo($stringa[archivio_zip]);?></TITLE>
</HEAD>
<BODY bgColor=white>
<ul>
<FONT face=verdana><B><br>
<?php echo($stringa[archivio_zip]);?> </B></FONT>
 </P>

 <FONT face=verdana size=-1>[<a href=index.php?cartella=<?php echo($cartella);?>><?php echo($stringa[indietro]);?></a>]</font><br>
<P> 

<FORM action=zip_carica.php encType=multipart/form-data method=post>
<INPUT name=MAX_FILE_SIZE type=hidden value=5097150>
<input type=hidden name=cartella value="<?php echo($cartella);?>">
<FONT face=verdana size=-1><STRONG><?php echo($stringa[file_caricare]);?> (.zip):</STRONG></FONT><br>

<INPUT type="file" name=file size=40>

    <BR>
    <P> 
      <INPUT type=submit value="<?php echo($stringa[carica]);?>">
    </P>
  </FORM>
  <HR>

</ul>
</BODY>
</HTML>
