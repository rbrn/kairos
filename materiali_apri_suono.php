<?php 
require "./include/init_sito.inc";
$dir=$_REQUEST[dir];
?>
<html>
<head>
	<title><?php echo($stringa[inserisci_suono]);?></title>
	<link rel="stylesheet" href="stili/stile_sito.css">
<script language=javascript>
function invia() {
/*
	if (modulo.immagine.value=='') {
		alert('Devi indicare l\'indirizzo di un file suono');
		return false;
	};
*/
	
	window.opener.InsertSound(modulo.immagine.value); 			
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
<span class=testo><b><?php echo($stringa[inserisci_suono]);?></b></span>
</p>
<form name=modulo>
<span class=testo><b><?php echo($stringa[indirizzo_file_suono]);?>:</b></span> <input type=text name=immagine size=40><br>
<input type=button value="<?php echo($stringa[inserisci]);?>" onclick="invia()"> <input type=button value="<?php echo($stringa[incolla]);?>" onclick="incolla_indirizzo()"><br>
<span class=testopiccolo><?php echo($stringa[indirizzo_file_suoni_guida]);?>
</span>
</form>
<p>
<span class=testo>[<a href="#" title="<?php echo($stringa[elenco_suoni_alt]);?>" onclick="apri_scheda('index.php?risorsa=materiali_cartella&dir=<?php echo($dir);?>&tipo=audio&cartella=','myRemoteUtente',        'height=400,width=550,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');"><?php echo($stringa[elenco_suoni]);?></a>]</span>
</p>
</td></tr>
</table>
</body>
</html>
