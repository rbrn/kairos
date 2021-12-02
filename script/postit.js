var segui = false;
var livello_da_trascinare;
var id = 0;
var mio_postit;

function registra(modulo)
	{
	oggetto=document.all[modulo];
	oggetto.x_p.value=mio_postit.x;
	oggetto.y_p.value=mio_postit.y;
}

function cambia_colore(id_post)
	{
	var rif_modulo="modulo_"+id_post;
	var obj_modulo=document.all[rif_modulo];
	var indice=obj_modulo.colore_post.selectedIndex;
	var col=obj_modulo.colore_post.options[indice].value;

	imposta_colore(id_post,col);

}

function imposta_colore(id_post,col) {
	var rif_tab = "tabella_"+id_post;
	var rif_testa="testata_"+id_post;
	var obj_tab=document.all[rif_tab];
	var obj_testa=document.all[rif_testa];
	
	switch (col) {
		case "giallo":
			obj_tab.style.backgroundColor="#ffffcc";
			obj_testa.style.backgroundColor="#ffcc00";
			break;
		
		case "verde":
			obj_tab.style.background="#99ff99";
			obj_testa.style.background="#00cc66";
			break;
	
		case "rosa":
			obj_tab.style.background="#ffccff";
			obj_testa.style.background="#ff99ff";
			break;
			
		case "grigio":
			obj_tab.style.background="#cccccc";
			obj_testa.style.background="#999999";
			break;
		
		case "viola":
			obj_tab.style.background="#cc99cc";
			obj_testa.style.background="#996699";
			break;
			
		case "blu":
			obj_tab.style.background="#00ccff";
			obj_testa.style.background="#6699ff";
			break;
				
			
	};
	mio_postit.bgtab=obj_tab.style.background;
	mio_postit.bgtesta=obj_testa.style.background;
};

function imposta_colore_obj (oggetto,col) {
	switch (col) {
		case "giallo":
			oggetto.bgtabColor="#ffffcc";
			oggetto.bgtestaColor="#ffcc00";
			break;
		
		case "verde":
			oggetto.bgtab="#99ff99";
			oggetto.bgtesta="#00cc66";
			break;
	
		case "rosa":
			oggetto.bgtab="#ffccff";
			oggetto.bgtesta="#ff99ff";
			break;
			
		case "grigio":
			oggetto.bgtab="#cccccc";
			oggetto.bgtesta="#999999";
			break;
		
		case "viola":
			oggetto.bgtab="#cc99cc";
			oggetto.bgtesta="#996699";
			break;
			
		case "blu":
			oggetto.bgtab="#00ccff";
			oggetto.bgtesta="#6699ff";
			break;
				
			
	};
};

	
function postit() {
	this.id=0;
	this.id_db=0;
	this.id_pagina="";
	this.autore="";
	this.tipo="";
	this.data="";
	this.messaggio="";
	this.x=50;
	this.y=190;
	this.bgtab="#ffffcc";
	this.bgtesta="#ffcc00";
	
	this.mostra=mostra;
	this.mostra_edit=mostra_edit;

};
	
function mostra() {
	document.body.innerHTML += '<div id=\"'+this.id+'\" style=\"position:absolute; visibility:visible; top:'+this.y+'; left='+this.x+'\"><table border=0 bgcolor='+this.bgtab+' width=250><tr align=left bgcolor='+this.bgtesta+'><td><table border=0 width=100%><tr><td align=left><span class=testopiccolo>[<a href=\"postit_cancella.php?id_postit='+this.id_db+'&id_pagina='+this.id_pagina+'\">Cancella</a>]</span></td><td align=right><span class=testopiccolo>[<a href=\"javascript:;\" onclick=\"trascina(\''+this.id+'\')\">Muovi</a>] [<a href=\"javascript:;\" onclick=\"chiudi(\''+this.id+'\')\">Chiudi</a>]</span></td></tr></table></td></tr><tr><td align=left valign=middle><span class=testo>'+this.messaggio+'</span></td></tr><tr><td><hr size=1><span class=testopiccolo>Scritto da: '+this.autore+' il '+this.data+'<br>Tipo: '+this.tipo+'</span></td></tr></table></div>';
};

function mostra_edit() {
	document.body.innerHTML += '<div id=\"'+this.id+'\" style=\"position:absolute; visibility:visible; top:'+this.y+'; left='+this.x+'\"><form action=postit.php method=post name=\"modulo_'+this.id+'\" id=\"modulo_'+this.id+'\" onsubmit=\"registra(\'modulo_'+this.id+'\');return true\"><input type=hidden name=id_db value='+this.id_db+'><input type=hidden name=id_pagina value='+this.id_pagina+'><input type=hidden name=x_p><input type=hidden name=y_p><input type=hidden name=colore><table id=\"tabella_'+this.id+'\" border=0 bgcolor='+this.bgtab+' width=250><tr id=\"testata_'+this.id+'\" bgcolor='+this.bgtesta+'><td align=right><span class=testopiccolo>[<a href=\"javascript:;\" onclick=\"trascina(\''+this.id+'\')\">Muovi</a>] [<a href=\"javascript:;\" onclick=\"chiudi(\''+this.id+'\')\">Chiudi</a>] </span></td></tr><tr><td align=left valign=top height=150><table border=0><tr><td align=right><span class=testopiccolo><b>Colore:</b></span></td><td><select name=colore_post onchange=\"cambia_colore(\''+this.id+'\')\"><option value=\"giallo\">giallo<option value=\"verde\">verde<option value=\"rosa\">rosa<option value=\"grigio\">grigio<option value=\"viola\">viola<option value=\"blu\">blu</select></td></tr><tr><td align=right><span class=testopiccolo><b>Tipo:</b></span></td><td><select name=tipo_post><option value=\"0\" selected>pubblico<option value=\"2\">personale</select></td></tr><tr><td colspan=2><textarea name=msg_postit cols=40 rows=5>'+this.messaggio+'</textarea></td></tr></table></td></tr><tr><td align=center><input type=submit value=Salva></td></tr></table></form></div>';
};

	
function chiudi(oggetto_id) {
	var oggetto_livello=document.all[oggetto_id];
	oggetto_livello.style.visibility="hidden";
};
	
function trascina(p) {
	if (segui) {
		basta_mouse();
	} else {
		window.event.cancelBubble=true;
		segui = true;
		livello_da_trascinare=document.all[p];
	}
}	

	
function nuovo_postit(id_pagina) {
	id_p = "postit_"+id;
	id++;
		
	mio_postit = new postit();
	mio_postit.id = id_p;
	mio_postit.id_pagina=id_pagina;
	mio_postit.messaggio="scrivi qui il testo del tuo post-it";
	mio_postit.mostra_edit();
};
	
function apri_postit(id_pagina,autore,data,id_db,messaggio,x_p,y_p,colore,tipo) {
	id_p = "postit_"+id;
	id++;
	mio_postit = new postit();
	mio_postit.id = id_p;
	mio_postit.id_pagina=id_pagina;
	mio_postit.id_db=id_db;
	mio_postit.autore=autore;
	mio_postit.data=data;
	mio_postit.messaggio=messaggio;
	mio_postit.x=x_p;
	mio_postit.y=y_p;
	mio_postit.tipo=tipo;
	imposta_colore_obj(mio_postit,colore);
	mio_postit.mostra();
};
	

function segui_mouse() {
	
	if (segui) {
		Xpos = window.event.x + document.body.scrollLeft-50; 
		Ypos = window.event.y + document.body.scrollTop-50;
		if (Ypos<190) Ypos=190;
		
		livello_da_trascinare.style.left = Xpos;
		livello_da_trascinare.style.top = Ypos;
		mio_postit.x=Xpos;
		mio_postit.y=Ypos;
		
	}
}	

function basta_mouse() {
	if (segui) {
		segui=false;
		window.event.cancelBubble=false;
		
	};
}