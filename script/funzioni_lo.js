function mostra_capitolo(oggetto,id_capitolo) {
	var blocco = oggetto.all(id_capitolo);
	var nome_img = 'img_'+id_capitolo;
	var immagine=oggetto.all(nome_img);

	if (blocco) {
		if (blocco.style.display == "") {
			blocco.style.display = "none";
			document.cookie='capitolo['+id_capitolo+']='+'0';
			immagine.src="img/forum/piu.gif";

		} else {
			blocco.style.display = "";
			document.cookie='capitolo['+id_capitolo+']='+'1';
			immagine.src="img/forum/meno.gif";
		}
	}
}

function nota(url,x,y) {
 var dimensione="toolbar=no,menubar=no,directories=no,status=no,resizable=yes,scrollbars=yes,width="+x+",height="+y
 window.open(url,"f",dimensione);
}

function apri_scheda(newURL, newName, newFeatures, orgName) {
  var remote = open(newURL, newName, newFeatures);
  if (remote.opener == null)
    remote.opener = window;
  remote.opener.name = orgName;
  return remote;
}