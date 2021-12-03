var segui = false;
var livello_da_trascinare;
var x0;
var y0;
var target_preso=new pezzo_target();

var id_target=0;
var id_drag=0;
var mio_pezzo;

var i_target=0;
var pezzi_target = new Array();
var pezzi_drag = new Array();

var id_oggetto_dp=0;
var oggetto_dragdrop = new Array();

function pezzo_target() {
	this.nome="";
	this.nome_item='';
	this.id_item=0;
	this.id_item_opzione=0;
	this.w=0;
	this.h=0;
	this.x=0;
	this.y=0;
	this.stato=0;
}
function pezzo() {
	this.id="";
	this.indice_pagina="";
	this.numero=0;
	this.nome_item='';
	this.id_item=0;
	this.id_item_opzione="";
	this.id_item_esatto="";
	this.target_preso="";
	this.punteggio=0;
	this.tipo="";
	this.messaggio="";
	this.f_url="";
	this.x=50;
	this.y=400;
	this.bgtab="#ffffff";
	this.bgtesta="#ffcc00";
	
	this.mostra=mostra;
};
	
function mostra() {
	var codice_drag='';
	var stile_drag='';
	if (this.tipo=='2') {
		var tipo_str='Target ';
	} else {
		var tipo_str='Drag ';
		codice_drag='onmousedown=\"trascina(\''+this.id+'\')\"';
		stile_drag='cursor:hand;';
	};
	
	var codice='<div id=\"'+this.id+'\" style=\"'+stile_drag+'position:absolute; display:none; top:'+this.y+'; left='+this.x+'\" '+codice_drag+'><table border=0 bgcolor='+this.bgtab+'>';

	if (this.f_url) {
		codice += '<tr><td align=left valign=top><img  src='+this.f_url+'></td></tr>';
	};
	
	if (this.messaggio) {
		codice += '<tr><td align=left valign=top><span class=testo>'+this.messaggio+'</span></td></tr>';
	};
	
	
	
	codice += '</table></div>';
	
	document.body.innerHTML += codice;
};


function trascina(p) {

	if (segui) {
		basta_mouse();
	} else {
		window.event.cancelBubble=true;
		segui = true;
		livello_da_trascinare=document.all[p];
		//mio_pezzo=livello_da_trascinare;
		for (var i=1;i<pezzi_drag.length;i++) {
			
			if (pezzi_drag[i].id==p) {
				mio_pezzo=pezzi_drag[i];
				
			};
		};
		x0=livello_da_trascinare.style.left;
		y0=livello_da_trascinare.style.top;
	}
}	



function apri_pezzo(indice_pagina,nome_item,id_item,id_item_opzione,messaggio,f_url,x_p,y_p,tipo,id_item_esatto,punteggio) {
	if (tipo==2) {
		id_p = nome_item+"pezzo_target_"+id_target;
		id_target++;
		numero=id_target;	
	} else {
		id_p = nome_item+"pezzo_drag_"+id_drag;
		id_drag++;
		numero=id_drag;
	};
	mio_pezzo = new pezzo();
	mio_pezzo.id = id_p;
	mio_pezzo.indice_pagina=indice_pagina;
	mio_pezzo.nome_item = nome_item;
	mio_pezzo.id_item = id_item;
	mio_pezzo.id_item_esatto=id_item_esatto;
	mio_pezzo.punteggio=punteggio;
	mio_pezzo.id_item_opzione=id_item_opzione;
	mio_pezzo.messaggio=messaggio;
	mio_pezzo.f_url=f_url;
	mio_pezzo.x=x_p;
	mio_pezzo.y=y_p;
	mio_pezzo.tipo=tipo;
	mio_pezzo.numero=numero;
	mio_pezzo.mostra();
	
	if (tipo==1) {
		pezzi_drag[id_drag]=mio_pezzo;
	}
	oggetto_dragdrop[id_oggetto_dp]=mio_pezzo;
	id_oggetto_dp++;
	
};
	

function segui_mouse() {
	if (segui) {
	/*
		Xpos = window.event.x + document.body.scrollLeft; 
		Ypos = window.event.y + document.body.scrollTop;
	*/	
		Xpos = window.event.x; 
		Ypos = window.event.y;
		
		if (Ypos<189) Ypos=189;
		if (Ypos>484) Ypos=484;
		
		if (Xpos<80) Xpos=80;
		if (Xpos>665) Xpos=665;
		
		livello_da_trascinare.style.pixelLeft = Xpos;
		livello_da_trascinare.style.pixelTop = Ypos;
		mio_pezzo.x=Xpos;
		mio_pezzo.y=Ypos;
	}
}	

function basta_mouse() {
	if (segui) {
		segui=false;
		window.event.cancelBubble=false;
		indice=mio_pezzo.nome_item+'_drag_x_'+mio_pezzo.numero;
		campo=document.all[indice];
		campo.value=mio_pezzo.x;
		
		indice=mio_pezzo.nome_item+'_drag_y_'+mio_pezzo.numero;
		campo=document.all[indice];
		campo.value=mio_pezzo.y;
		
		if (onTarget()) {
			Ypos=1*target_preso.y;
			Xpos=1*target_preso.x;
			livello_da_trascinare.style.left = Xpos;
			livello_da_trascinare.style.top = Ypos;
			mio_pezzo.x=Xpos;
			mio_pezzo.y=Ypos;
			mio_pezzo.target_preso=target_preso;
			campo=target_preso.nome;
			opzione=document.all[campo];
			opzione.value=mio_pezzo.id_item_opzione;
			
			indice=mio_pezzo.nome_item+'_drag_x_'+mio_pezzo.numero;
			campo=document.all[indice];
			campo.value=mio_pezzo.x;
		
			indice=mio_pezzo.nome_item+'_drag_y_'+mio_pezzo.numero;
			campo=document.all[indice];
			campo.value=mio_pezzo.y;
		}
	};
}

function definisci_target(nome,id_item,nome_item,id_item_opzione,w,h,x_p,y_p) {
	var target = new pezzo_target();
	target.nome=nome;
	target.id_item=id_item;
	target.nome_item=nome_item;
	target.id_item_opzione=id_item_opzione;
	target.w=w;
	target.h=h;
	target.x=x_p;
	target.y=y_p;
	target.stato=0;
	pezzi_target[i_target]=target;
	i_target++;
}

function onTarget() {
	var ok=false;
	
	var Xpos=mio_pezzo.x;
	var Ypos=mio_pezzo.y;
	

	for (var i=0;i<pezzi_target.length;i++) {
		var x1=pezzi_target[i].x;
		var w1=1*pezzi_target[i].x+1*pezzi_target[i].w;
	
		var y1=pezzi_target[i].y;
		var h1=1*pezzi_target[i].y+1*pezzi_target[i].h;
		
		if (Xpos>=x1 && Xpos<=w1 && Ypos>=y1 && Ypos<=h1) {
			target_preso=pezzi_target[i];
			ok=true;
		}
		
	}
	
	return ok;
}

/*
function mostra_pezzo(nome_item,id_item,id_item_opzione,messaggio,f_url,x_p,y_p,tipo,id_item_esatto,punteggio) {
	if (tipo==2) {
		id_p = nome_item+"_pezzo_target_"+id_target;
		id_target++;
		numero=id_target;	
	} else {
		id_p = nome_item+"_pezzo_drag_"+id_drag;
		id_drag++;
		numero=id_drag;
	};
	mio_pezzo = new pezzo();
	mio_pezzo.id = id_p;
	mio_pezzo.nome_item = nome_item;
	mio_pezzo.id_item = id_item;
	mio_pezzo.id_item_esatto=id_item_esatto;
	mio_pezzo.punteggio=punteggio;
	mio_pezzo.id_item_opzione=id_item_opzione;
	mio_pezzo.messaggio=messaggio;
	mio_pezzo.f_url=f_url;
	mio_pezzo.x=x_p;
	mio_pezzo.y=y_p;
	mio_pezzo.tipo=tipo;
	mio_pezzo.numero=numero;
	mio_pezzo.mostra();

};
*/