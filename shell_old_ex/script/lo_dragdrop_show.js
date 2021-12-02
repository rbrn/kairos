var id_target=0;
var id_drag=0;

function pezzo() {
	this.id="";
	this.numero=0;
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
	var codice='<div id=\"'+this.id+'\" style=\"position:absolute; visibility:visible; top:'+this.y+'; left='+this.x+'\"><table border=0 bgcolor='+this.bgtab+'>';

	if (this.f_url) {
		codice += '<tr><td align=left valign=top><img  src='+this.f_url+'></td></tr>';
	};
	
	if (this.messaggio) {
		codice += '<tr><td align=left valign=top><span class=testo>'+this.messaggio+'</span></td></tr>';
	};
	
	
	
	codice += '</table></div>';
	
	document.body.innerHTML += codice;
};



function mostra_pezzo(messaggio,f_url,x_p,y_p,tipo) {
	if (tipo==2) {
		id_p = "pezzo_target_"+id_target;
		id_target++;
		numero=id_target;	
	} else {
		id_p = "pezzo_drag_"+id_drag;
		id_drag++;
		numero=id_drag;
	};
	mio_pezzo = new pezzo();
	mio_pezzo.id = id_p;
	mio_pezzo.messaggio=messaggio;
	mio_pezzo.f_url=f_url;
	mio_pezzo.x=x_p;
	mio_pezzo.y=y_p;
	mio_pezzo.tipo=tipo;
	mio_pezzo.numero=numero;
	mio_pezzo.mostra();

};