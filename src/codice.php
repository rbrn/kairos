<?php
$path_file="/var/www/html/prototipo/kairos/utenti/kairos_area_corsi/".$utente."/".$file;

if (file_exists($path_file)) {
	//$codice = htmlentities(implode ('', file ($path_file)));
	$nome=basename($path_file);
	if ($nome=="connessione_db.php") {
		$codice="Non puoi visualizzare il codice di questo file";
	} else {
		$codice = implode ('', file ($path_file));
	
		//$codice=str_replace("\n","<br>",$codice);
	};
	
} else {
	$codice = "Non trovo il file indicato: $utente/$file";
};

function my_highlight($text,$numeri){  
       $text2 = stripslashes($text);
       $text_split = split("\n", $text2);  
       $mv = count($text_split);  
       
       /*for design reasons */
       if($mv < 100){
       $width = "14";
       }elseif($mv < 1000){
       $width = "22";
       }elseif($mv < 10000){
       $width = "30";
       }else{
       $width = "14";
       }
       /*--------------------*/
       echo "<table cellspacing=\"0\" width=\"100%\">";  

       //$text_split2 = highlight_string($text2, true);
	   $colore_riga="#ccffff";  
       for($i = 0; $i < $mv; $i++){  
           $t = $i + 1;  
		   $text = highlight_string($text_split[$i],true);
           echo "<tr bgcolor=\"$colore_riga\">";
		   
		   if ($numeri) echo " <td bgcolor=\"#ffffcc\" width=$width><div align=right><font face=\"verdana\" size=\"1\">".$t."</font></div></td>"; 
		
		  
           echo "<td style=\"padding-left: 5px\" valign=\"top\">".$text."</td>";  

           echo "</tr>";     
		   if ($colore_riga=="#ccffff") {
		   		$colore_riga="#ffffff";
		  } else {
		   		$colore_riga="#ccffff";
		  };
       } 
       echo"</table>";
};

echo "
<html>
<head><title>Codice	$utente/$file</title></head>
<body bgcolor=white>
<h2>Codice: $utente/$file</h2>
";

if (!$numeri) { 
	echo " [<a href=codice.php?utente=$utente&file=$file&numeri=1>Mostra numeri di riga</a>]";
} else {
	echo " [<a href=codice.php?utente=$utente&file=$file&numeri=0>Nascondi numeri di riga</a>]";
};

echo "<hr size=1>";

my_highlight($codice,$numeri);

echo "<hr size=1>
</body>
</html>
";
?>



