<?php 
require "./include/init_sito.inc";
$dir=$_REQUEST[dir];
?>
<html>
<head>
	<title><?php echo($stringa[inserisci_flash]);?></title>
	<link rel="stylesheet" href="stili/stile_sito.css">
<script language=javascript>
function invia() {
/*
	if (modulo.immagine.value=='') {
		alert('Devi indicare l\'indirizzo di un file flash');
		return false;
	};
	
	if (modulo.larghezza.value=='') {
		alert('Devi indicare la larghezza del file flash');
		return false;
	};
	
	if (modulo.altezza.value=='') {
		alert('Devi indicare l\'altezza del file flash');
		return false;
	};
*/

	window.opener.InsertFlash(modulo.immagine.value,modulo.larghezza.value,modulo.altezza.value); 			
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
<span class=testo><b><?php echo($stringa[inserisci_flash]);?></b></span>
</p>
<form name=modulo>
<table border=0 width=100%>
<tr><td align=right><span class=testo><b><?php echo($stringa[indirizzo_file_flash]);?>:</b></span></td><td><input type=text name=immagine size=40></td></tr>
<tr><td align=right><span class=testo><b><?php echo($stringa[larghezza]);?>:</b></span></td><td><input type=text name=larghezza size=10></td></tr>
<tr><td align=right><span class=testo><b><?php echo($stringa[altezza]);?>:</b></span></td><td><input type=text name=altezza size=10></td></tr>
<tr><td align=right><input type=checkbox checked name=auto><span class=testo>Rileva automaticamente larghezza e altezza</span></td><td></td></tr>
</table>
<input type=button value="<?php echo($stringa[inserisci]);?>" onclick="invia()"> <input type=button value="<?php echo($stringa[incolla]);?>" onclick="incolla_indirizzo()"><br>
<span class=testopiccolo><?php echo($stringa[indirizzo_file_flash_guida]);?>
</span>
</form>
<p>
<span class=testo>[<a href="#" title="<?php echo($stringa[elenco_flash_alt]);?>" onclick="apri_scheda('index.php?risorsa=materiali_cartella&dir=<?php echo($dir);?>&tipo=flash&cartella=','myRemoteUtente',        'height=400,width=550,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');"><?php echo($stringa[elenco_flash]);?></a>]</span>
</p>
</td></tr>
</table>
</body>
</html>
