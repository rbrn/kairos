<?php
require "./include/funzioni_repository.inc";
$id_cartella=$_REQUEST["id_cartella"];
$tipo_browse=$_REQUEST["tipo_browse"];
?>  
<TABLE border=0 width=461>
<tr></td>
<?php
browse_folder($id_cartella);
?>
</td></tr>
	  	  
</TABLE>
<HR>
