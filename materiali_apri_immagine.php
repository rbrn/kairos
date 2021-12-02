<?php 
require "./include/init_sito.inc";
$dir=$_REQUEST[dir];
?>
<html>
<head>
	<title><?php echo($stringa[inserisci_immagine]);?></title>
	<link rel="stylesheet" href="stili/stile_sito.css">
<script language=javascript>
function invia() {
	var arr=new Array();
	
	arr[0]=modulo.immagine.value;
	arr[1]=modulo.alt_text.value;
	arr[2]=modulo.allinea.value;
	window.opener.InsertIMG(arr); 			
	self.close();
	window.opener.idContent.focus();
} 

function incolla_indirizzo() {
	var url=window.clipboardData.getData("Text");
	modulo.immagine.value=url;
} 

function apri_scheda(newURL, newName, newFeatures, orgName) {
  var remote = open(newURL, newName, newFeatures);
  /*
  if (remote.opener == null)
    remote.opener = window;
  remote.opener.name = orgName;
  return remote;
	*/
}

</script>
</head>

<body>
<table border=0 width=100%>

<tr>
<td width=5>&nbsp;</td>
<td>
<!-- CONTENUTO DELLA PAGINA -->
<p>
<span class=testo><b><?php echo($stringa[inserisci_immagine]);?></b></span>
</p>
<form name=modulo>
<span class=testo><b><?php echo($stringa[indirizzo_file_img]);?>:</b></span> <input type=text name=immagine size=40><br>
<span class=testo><b>Testo alternativo:</b></span> <input type=text name=alt_text size=40><br>
<span class=testo><b>Allineamento rispetto al testo:</b></span> <select name=allinea><option value="left">sinistra<option value="right">destra</select><br>
<input type=button value="<?php echo($stringa[inserisci]);?>" onclick="invia()"> <input type=button value="<?php echo($stringa[incolla]);?>" onclick="incolla_indirizzo()"><br>
<span class=testopiccolo><?php echo($stringa[indirizzo_file_img_guida]);?>

</span>
</form>
<p>
<span class=testo>[<a href="#" title="<?php echo($stringa[elenco_img_alt]);?>" onclick="apri_scheda('index.php?risorsa=materiali_cartella&dir=<?php echo($dir);?>&tipo=img&cartella=','myRemoteUtente',        'height=400,width=550,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');"><?php echo($stringa[elenco_img]);?></a>]</span>
</p>
</td></tr>
</table>
</body>
</html>
