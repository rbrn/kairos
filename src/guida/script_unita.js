function mostra_thread(oggetto,id_thread) {
	var blocco = oggetto.all(id_thread);
	var nome_img = 'img_'+id_thread;
	var immagine=oggetto.all(nome_img);
	if (blocco) {
		if (blocco.style.display == "") {
			blocco.style.display = "none";
			immagine.src="img/plus.gif";
		} else {
			blocco.style.display = "";
			immagine.src="img/minus.gif";
		}
	}
}
