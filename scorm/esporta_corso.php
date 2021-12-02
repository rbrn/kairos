<html>
<head><title>Esporta Corso</title>
</head>
<body>
<?php


$id_corso_esporta=$_REQUEST["id_corso"];
$cod_area=$_REQUEST["cod_area"];


if (!$cod_area) $cod_area="kairos_elombardia";

require "./init_esporta.php";

/*******************************/
// FUNZIONI
/*******************************/


require "./funzioni_esporta.php";


/*******************************/
// INIZIO PROCEDURA 
/*******************************/
$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	
	
$id_corso_s=$id_corso_esporta;

$img1_file=$PATH_MODULO."img/".$id_corso_s."1.gif";
$img1="img/".$id_corso_s."1.gif";
$size=getimagesize($img1_file);
$tag_img1=$size[3];

$img2_file=$PATH_MODULO."img/".$id_corso_s."2.gif";
$img2="img/".$id_corso_s."2.gif";
$size=getimagesize($img2_file);
$tag_img2=$size[3];

if (file_exists($PATH_ROOT."pagine/$cod_area/colori.inc")) 
require $PATH_ROOT."pagine/$cod_area/colori.inc";

$indice_corso .=  "
<html>
<head>
<title>$titolo</title>
<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>";

$indice_corso .= "
<link rel=\"stylesheet\" href=\"stili/stile_sito.css\">
</head>
";

$indice_corso .= "
<body topmargin=\"0\" leftmargin=\"15\" bgcolor=\"#FFFFFF\" link=\"#535190\">";

$size=getimagesize($PATH_MODULO."/img/testata.gif");
$tag_img=$size[3];

$indice_corso .= "
<table width=\"100%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" align=\"center\">
<tr><td>
<!-- TESTATA -->
<table border=0 cellpadding=\"0\" cellspacing=\"0\" width=100% background=\"img/up-bg.gif\">
<tr>
<td >
<div align=\"left\"><img src=\"img/testata.gif\" $tag_img border=0 alt=\"$cod_area\"></div></td>";

$indice_corso .= "
</tr>
</table>
<!-- FINE TESTATA -->
";

$indice_corso .= "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" bgcolor=\"d6f0ef\">
  <tr>
    <td width=\"24%\"><img src=\"$img1\" $tag_img1></td>
    <td width=\"76%\">
	<span class=titolopagina>Materiali</span>
	</td>
  </tr>
</table>
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" bgcolor=\"d6f0ef\">
  <tr> 
    <td width=\"1\" height=\"138\" valign=\"top\"><img src=\"$img2\" $tag_img2></td>
    <td width=\"100%\" height=\"138\" valign=\"top\"> 
      <table width=\"95%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" align=\"left\" bgcolor=\"#FFFFFF\">
        <tr> 
          <td width=\"1\"><img src=\"img/corner-susx.gif\" width=\"12\" height=\"18\"></td>
          <td width=\"100%\">&nbsp;</td>
          <td width=\"1\"> 
            <div align=\"right\"><img src=\"img/corner-sudx.gif\" width=\"12\" height=\"18\"></div>
          </td>
        </tr>
        <tr> 
          <td width=\"1\">&nbsp;</td>
          <td width=\"100%\">";


$query = "SELECT * FROM materiali_sequenza WHERE id_corso='$id_corso_s' ORDER BY ordine";
$result=$mysqli->query($query);


$indice_corso .= "<ul>\n";
while ($risorsa = $result->fetch_array() ) {
	$id_risorsa = $risorsa["id_risorsa"];
	$tipo_risorsa=$risorsa["tipo_risorsa"];

 	switch ($tipo_risorsa) {
			case 2://cartella
				$query2 = "SELECT id_risorsa,id_autore,titolo,descrizione,tipo,file_size,DATE_FORMAT(data_mod,'%d/%m/%Y %H:%i') as data_m FROM risorse_materiali WHERE id_risorsa='$id_risorsa'";
				$result2=$mysqli->query($query2);
				$risorsa2=$result2->fetch_array();
				$id_autore=$risorsa2["id_autore"];
				$titolo=$risorsa2["titolo"];
				$descrizione=$risorsa2["descrizione"];
				$file_size=$risorsa2["file_size"];
				$tipo = $risorsa2["tipo"];
				$data_m = $risorsa2["data_m"];
				
				$id_risorsa0=foglia($id_risorsa);
				if (!$id_risorsa0) $id_risorsa0=$id_risorsa;
				
				$indice_corso .= "<li>\n";
				$indice_corso .= "
			<img src=img/folder.gif width=18 height=16 border=0> <span class=testo><a href=$id_risorsa"."/"."$id_risorsa0".".htm title=\"$titolo\">$titolo</a></span><br>\n";
				$indice_corso .= "</li><br>\n";
				
				$id_modulo=$id_risorsa;
				esporta_modulo();
				break;
		};
	
};
$indice_corso .= "</ul>\n";


$indice_corso .= "

<p>&nbsp;</p>
            
          </td>
          <td width=\"1\">&nbsp;</td>
        </tr>
        <tr> 
          <td width=\"1\"><img src=\"img/corner-giusx.gif\" width=\"12\" height=\"18\"></td>
          <td width=\"100%\">&nbsp;</td>
          <td width=\"1\"> 
            <div align=\"right\"><img src=\"img/corner-giudx.gif\" width=\"12\" height=\"18\"></div>
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <tr> 
    <td colspan=\"2\" height=\"10\" valign=\"top\">&nbsp;</td>
  </tr>
</table>

</body></html>";


$fp=fopen($PATH_MODULO.$id_corso_esporta.".htm","w");
fwrite($fp,$indice_corso);
fclose($fp);

?>
</body>
</html>
