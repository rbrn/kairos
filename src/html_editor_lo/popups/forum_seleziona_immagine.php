<?php
require "../../include/init_sito.inc";
require "../../include/funzioni_sito.inc";
$ruolo=ruolo_utente($kairos_cookie[0]);
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
<head>
<title><?php echo($stringa[elenco_img]);?></title>
<meta http-equiv="Content-Type" content="text/html;" />
<script language="javascript" type="text/javascript">

function onCancel() {
  window.close();
  return false;
};


function inserisci(nome_img) {
	var url='<?php echo($PATH_ROOT);?>/immagini/<?php echo($cod_area);?>/'+nome_img;
	opener.document.modulo.f_url.value = url;
	window.close();
	return false;
};



</script>
<style type="text/css">
html, body { background-color: rgb(212,208,200); }
.title {
background-color: #ddddff;
padding: 5px;
border-bottom: 1px solid black;
font-family: Tahoma, sans-serif;
font-weight: bold;
font-size: 14px;
color: black;
}
input,select { font-family: Tahoma, sans-serif; font-size: 11px; }
legend { font-family: Tahoma, sans-serif; font-size: 11px; }
p { margin-left: 10px;
background-color: transparent; font-family: Tahoma, sans-serif;
font-size: 11px; color: black; }
td { font-family: Tahoma, sans-serif; font-size: 11px; }
button { width: 70px; font-family: Tahoma, sans-serif; font-size: 11px; }
#imodified,#itype,#isize {
background-color: rgb(212,208,200);
border: none;
font-family: Tahoma, sans-serif;
font-size: 11px;
color: black;
}
.space { padding: 2px; }
form { margin-bottom: 1px; margin-top: 1px; }
</style>
</head>
<body>
<table border=0 width=100%>



<tr>

<td width=5>&nbsp;</td>

<td bgcolor=white>

<!-- CONTENUTO DELLA PAGINA -->



<TABLE BORDER=0 ALIGN=CENTER width=90%>

<tr>

<td>



<?php

//vedo se ci sono immagini...

$dir_path=$PATH_ROOT_FILE."immagini/$cod_area";

$d = dir($dir_path);

$i=0;

while ($nomefile=$d->read()) {

	if (($nomefile != '.') && ($nomefile != '..')) { 

		$file_img[$i] = strtolower($nomefile);

		$i++;

	};

}

$d->close();



echo "

<p>

<span class=sottotitolopagina>

$stringa[elenco_img]

</span>

</p>



<form action=add_immagini_op.php encType=multipart/form-data method=post>

<INPUT name=MAX_FILE_SIZE type=hidden value=100000>

<TABLE BORDER=0 cellspacing=0 cellpadding=3 bgcolor=#ffffcc>

<TR>

<TD align=right><span class=testo>$stringa[immagine_profilo]:</span></TD>

<TD><INPUT name=nome_file type=file></TD>

</TR>

</table>		

<input type=submit value=\"$stringa[carica]\">

</form>
<p>&nbsp;</p>
";



if (count($file_img)) {
	sort($file_img);
	while (list($key, $val) = each($file_img)) {
		if (ereg("^(.+)\.(.+)$",$val,$parte)) {
		$max_img_size=80;
		
		$size=getimagesize($PATH_ROOT."immagini/$cod_area/$val");
		$w=$size[0];
		$h=$size[1];
	
		while ($w>$max_img_size or $h>$max_img_size) {
			if ($w>$max_img_size) {
				$h=floor($h*$max_img_size/$w);
				$w=$max_img_size;
			};
		
			if ($h>$max_img_size) {
				$w=floor($w*$max_img_size/$h);
				$h=$max_img_size;
			};
		
		};
			
		
		/*echo "<span class=testo><a href=\"".$PATH_ROOT."immagini/$cod_area/$val\" target=_blank><img src=\"".$PATH_ROOT."immagini/$cod_area/$val\" width=\"$w\" height=\"$h\" border=0 alt=\"anteprima: $val\"></a> <a href=\"javascript:;\" onclick=\"inserisci('$val');\">$stringa[seleziona]</a> 
</span>";*/
		
		echo "<span class=testo><a href=\"".$PATH_ROOT."immagini/$cod_area/$val\" target=_blank>$val</a> [<a href=\"javascript:;\" onclick=\"inserisci('$val');\">$stringa[seleziona]</a>] 
</span>";
		
		if ($ruolo=="staff" or $ruolo=="admin") {
			$file="immagini/$cod_area/$val";
			echo "<span class=testo>[<a href=$PATH_ROOT"."cancella.php?file=$file&ritorno=$PATH_ROOT/html_editor/popups/"."forum_seleziona_immagine.php>Cancella</a>]</span>";
		};
		echo "<br>";
		};
	};
};
?>
</td>
</tr>
</table>	
<!-- FINE CONTENUTO DELLA PAGINA -->
</td>
</tr>
</table>

<p>&nbsp;</p>
</body>
</html>
