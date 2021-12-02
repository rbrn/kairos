function MM_swapImgRestore() { //v3.0
  var i,x,a=document.MM_sr; for(i=0;a&&i<a.length&&(x=a[i])&&x.oSrc;i++) x.src=x.oSrc;
}

function MM_preloadImages() { //v3.0
  var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
    var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++)
    if (a[i].indexOf("#")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}}
}

function MM_findObj(n, d) { //v3.0
  var p,i,x;  if(!d) d=document; if((p=n.indexOf("?"))>0&&parent.frames.length) {
    d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
  if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
  for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document); return x;
}

function MM_swapImage() { //v3.0
  var i,j=0,x,a=MM_swapImage.arguments; document.MM_sr=new Array; for(i=0;i<(a.length-2);i+=3)
   if ((x=MM_findObj(a[i]))!=null){document.MM_sr[j++]=x; if(!x.oSrc) x.oSrc=x.src; x.src=a[i+2];}
}



function toggleMenu(source) {

	submenu = source.all("menu2");

	handle = source.all(0);

	if (submenu.style.display == "") {

		submenu.style.display = "None";

		handle.src = "img/folder_apri.gif"

	} else {	

		submenu.style.display = "";

		handle.src = "img/folder_chiudi.gif";

	};

};



function toggleMenu1(source) {

	submenu = source.all("menu2");

	handle = source.all(0);

	if (submenu.style.display == "") {

		submenu.style.display = "None";

		handle.src = "img/sx-softw1.gif"

	} else {	

		submenu.style.display = "";

		handle.src = "img/sx-softw2.gif";

	};

};



function toggleMenu2(source) {

	submenu = source.all("menu2");

	handle = source.all(0);

	if (submenu.style.display == "") {

		submenu.style.display = "None";

		handle.src = "img/sx-testi1.gif"

	} else {	

		submenu.style.display = "";

		handle.src = "img/sx-testi2.gif";

	};

};



function toggleMenu3(source) {

	submenu = source.all("menu2");

	handle = source.all(0);

	if (submenu.style.display == "") {

		submenu.style.display = "None";

		handle.src = "img/sx-offerte1.gif"

	} else {	

		submenu.style.display = "";

		handle.src = "img/sx-offerte2.gif";

	};

};



function apri_scheda(newURL, newName, newFeatures, orgName) {

  var remote = open(newURL, newName, newFeatures);

  if (remote.opener == null)

    remote.opener = window;

  remote.opener.name = orgName;

  return remote;

}



function whosonline() {

	apri_scheda('whosonline.php', 'corsi_online',        'height=450,width=600,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','corsi_online_win');

}



function whosonline1() {

	apri_scheda('../whosonline.php', 'corsi_online',        'height=450,width=600,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','corsi_online_win');

}



function nota(url,x,y) {

  dimensione="toolbar=no,menubar=no,directories=no,status=no,resizable=yes,scrollbars=yes,width="+x+",height="+y

 window.open(url,"f",dimensione);



}



function mostra_thread(oggetto,id_thread) {

	var blocco = oggetto.all(id_thread);

	var nome_img = 'img_'+id_thread;

	var immagine=oggetto.all(nome_img);

	if (blocco) {

		if (blocco.style.display == "") {

			blocco.style.display = "none";

			document.cookie='thread['+id_thread+']='+'0';

			immagine.src="img/forum/piu.gif";

		} else {

			blocco.style.display = "";

			document.cookie='thread['+id_thread+']='+'1';

			immagine.src="img/forum/meno.gif";

		}

	}

}



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

function mostra_capitolo_cd(oggetto,id_capitolo) {

	var blocco = oggetto.all(id_capitolo);

	var nome_img = 'img_'+id_capitolo;

	var immagine=oggetto.all(nome_img);

	if (blocco) {

		if (blocco.style.display == "") {

			blocco.style.display = "none";

			document.cookie='capitolo['+id_capitolo+']='+'0';

			immagine.src="img/piu.gif";

		} else {

			blocco.style.display = "";

			document.cookie='capitolo['+id_capitolo+']='+'1';

			immagine.src="img/meno.gif";

		}

	}

}


function inserisci_indirizzo(url) {

	opener.document.modulo.immagine.value=url;
	self.close();

};

function inserisci_indirizzo_wh(url,w,h) {

	
	opener.document.modulo.immagine.value=url;
	opener.document.modulo.larghezza.value=w;
	opener.document.modulo.altezza.value=h;
	self.close();

};


function inserisci_indirizzo_n(url) {

	opener.document.modulo.f_url.value=url;
	self.close();

};

function inserisci_indirizzo_wh_n(url,w,h) {

	opener.document.modulo.f_url.value=url;
	opener.document.modulo.f_w.value=w;
	opener.document.modulo.f_h.value=h;
	
	self.close();

};


function inserisci_indirizzo_lo_n(url,campo) {
	var obj_campo=opener.document.getElementById(campo);
	obj_campo.value=url;
	self.close();

};

function inserisci_indirizzo_wh_lo_n(url,w,h,campo) {
	var obj_campo=opener.document.getElementById(campo);
	obj_campo.value=url;
	//opener.document.modulo.f_w.value=w;
	//opener.document.modulo.f_h.value=h;
	
	self.close();
};

function assegna_id_lo(id,tipo,stringa) {
		self.close();
		opener.document.form1.f_risorsa.value=id;
		opener.document.form1.f_str_risorsa.value=stringa;
		opener.document.form1.f_tipo.value=tipo;
		opener.focus();
};

function assegna_id_lo_lnktut(id,stringa) {
		self.close();
		opener.document.modulo.link_tutoriale.value=id;
		opener.document.modulo.titolo_pagina.value=stringa;
		opener.focus();
};

function assegna_id_lo_lnktutpost(id,stringa) {
		self.close();
		opener.document.modulo.link_tutoriale_post.value=id;
		opener.document.modulo.titolo_pagina_post.value=stringa;
		opener.focus();
};

function assegna_id_lo_lnktutref(id,stringa) {
		self.close();
		opener.document.modulo.link_tutoriale_ref.value=id;
		opener.document.modulo.titolo_pagina_ref.value=stringa;
		opener.focus();
};

function assegna_id_lo_lnktest(id,stringa) {
		self.close();
		opener.document.modulo.id_alternativo.value=id;
		opener.document.modulo.titolo_test.value=stringa;
		opener.focus();
};
	
function copia_indirizzo(url) {

	window.clipboardData.setData("Text",url);
	self.close();
};


function SHLayers() { 
  var  visStr, args, theObj, whatDiv;
  args = SHLayers.arguments;
    whatDiv= args[0];
    visStr   = args[1];
   if (navigator.appName == 'Netscape' && document.layers != null) {
     theObj = document.layers[whatDiv];
      if (theObj) 
          theObj.visibility = visStr;
    } else if (document.all != null) { 
      if (visStr == 'show') visStr = 'visible'; 
      if (visStr == 'hide') visStr = 'hidden';
      theObj = document.all[whatDiv];
      if (theObj) theObj.style.visibility = visStr;
    } 
}

function scheda_utente(id){
	window.open("utente_modifica_form.php?id_utente0=" + id, "Scheda", "toolbar=no, menubar=no, status=no, scrollbars=1, resizable=1, width=600, height=500");
};

function suona(nomesuono) {
	var obj;
	if (navigator.appName == "Netscape") {
		obj=nomesuono;
	} else {
		obj=document.all(nomesuono);
	};
	
	var stato=obj.hidden;

	if (stato == 'true') {
		obj.play();
		obj.hidden=false;
	} else {
		obj.stop();
		obj.hidden=true;
	};
};

function faq_view(id_faq) {
	apri_scheda('faq_view.php?id_faq='+id_faq, 'faq',        'height=450,width=600,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','faq_win');
}

function apri_cartella_utente(id_cartella) {
	if (window.opener.opener) {
	window.opener.opener.location='index.php?risorsa=lab_materiali_index&id_cartella='+id_cartella
	} else {
	window.opener.location='index.php?risorsa=lab_materiali_index&id_cartella='+id_cartella
	};
};

function SetAllCheckBoxes(FormName, FieldName, CheckValue)
{
	if(!document.forms[FormName])
		return;
	var objCheckBoxes = document.forms[FormName].elements[FieldName];
	if(!objCheckBoxes)
		return;
	var countCheckBoxes = objCheckBoxes.length;
	if(!countCheckBoxes)
		objCheckBoxes.checked = CheckValue;
	else
		// set the check value for all check boxes
		for(var i = 0; i < countCheckBoxes; i++)
			objCheckBoxes[i].checked = CheckValue;
}

function lo_seleziona_media(dir,tipo,nome_campo) {
    var lx = (screen.width - 470) / 2;
    var tx = (screen.height - 400) / 2;

    var settings = "toolbar=no,";
    settings += " location=no,";
    settings += " directories=no,";
    settings += " status=no,";
    settings += " menubar=no,";
    settings += " scrollbars=yes,";
    settings += " resizable=no,";
    settings += " width=470,";
    settings += " height=400,";

    var newwin = window.open("index.php?risorsa=materiali_cartella&contesto=lo&nome_campo="+nome_campo+"&dir="+dir+"&tipo="+tipo+"","",""+ settings +" left="+ lx +", top="+ tx +"");
    return false;
}

function imposta_immagine_layout() {
	var layout=document.modulo.posizione.value
	var immagine='img/layout'+layout+'.gif';
	document.img_layout.src=immagine;
	
	//MM_swapImage('img_layout','',immagine,1);
};

function imposta_immagine_test() {
	var layout=document.modulo.tipo_item.value
	var immagine='img/test_'+layout+'.gif';
	document.img_test.src=immagine;
	
	//MM_swapImage('img_layout','',immagine,1);
};


function findRootWin(win)
{
   while ((win.opener != null) && (win.opener != win))
   {
            
      win = win.opener;

   }
   return win;
}


function getRootWin()
{
   var theRoot = findRootWin(window.opener);
   
   return theRoot;
}

function goLocation(url) {
	var win=getRootWin();
	win.document.location.href=url;
}

function accendiPiume(id_post,i) {
	for (var k=0;k<=i;k++) {
		var id_piuma="piuma_"+id_post+"_"+k;
		var id=document.getElementById(id_piuma);
		id.src="img/piuma_on.gif";
	}
}

function spegniPiume(id_post,i) {
	for (var k=0;k<=i;k++) {
		var id_piuma="piuma_"+id_post+"_"+k;
		var id=document.getElementById(id_piuma);
		id.src="img/piuma.gif";
	}
}

function toggle_forum(id) {
	var elemento=document.getElementById(id);
	var id_img="img_"+id;
	var img_t=document.getElementById(id_img);
	if (elemento.style.display=="none") {
		elemento.style.display="block";
		img_t.src='img/minus.gif';
	} else {
		elemento.style.display="none";
		img_t.src='img/plus.gif';
	}
}
	
function carica_immagini() {
	MM_preloadImages(
	'img/ico_news_nuova_over.gif',
	'img/ico_utente_over.gif',
	'img/ico_appunti_over.gif',
	'img/ico_stat_over.gif',
	'img/ico_portfolio_over.gif',
	'img/flag_eng_over.gif',
	'img/ico_esci_over.gif',
	'img/ico_forum_faq_over.gif',
	'img/ico_forum_nuovo_post_over.gif',
	'img/ico_forum_view_sintetico_over.gif',
	'img/ico_forum_view_crono_over.gif',
	'img/ico_forum_view_interes_over.gif',
	'img/ico_forum_view_esteso_over.gif',
	'img/ico_forum_prec_over.gif',
	'img/ico_forum_succ_over.gif',
	'img/ico_forum_indice_over.gif',
	'img/ico_forum_cancella_over.gif',
	'img/ico_forum_chiletto_over.gif',
	'img/ico_forum_indice_over.gif',
	'img/ico_forum_daleggere_over.gif',
	'img/ico_forum_modifica_over.gif',
	'img/ico_forum_replica_over.gif',
	'img/ico_forum_ricopiafaq_over.gif',
	'img/ico_forum_segnainteres_over.gif',
	'img/ico_mail_nuovo_over.gif',
	'img/ico_mail_elimina_over.gif',
	'img/ico_mailfold_inv_over.gif',
	'img/ico_mailfold_arr_over.gif',
	'img/ico_modifica_over.gif',
	'img/ico_cancella_over.gif',
	'img/ico_cart_sup_over.gif',
	'img/ico_back_over.gif',
	'img/ico_indietro_over.gif',
	'img/ico_test_over.gif',
	'img/ico_flag_it_over.gif',
	'img/ico_flag_en_over.gif',
	'img/ico_avanti_over.gif',
	'img/ico_cal_nuovo_over.gif',
	'img/ico_duplicatest_over.gif',
	'img/ico_aggiungidomanda_over.gif',
	'img/ico_apri_over.gif',
	'img/ico_aggiungidomanda_over.gif',
	'img/ico_cerca_over.gif',
	'img/ico_staff_over.gif',
	'img/ico_iscrivicorso_over.gif',
	'img/ico_grupponuovo_over.gif',
	'img/ico_corsonuovo_over.gif',
	'img/ico_forumnuovo_over.gif',
	'img/ico_duplicagenerico_over.gif',
	'img/ico_nuovaedizione_over.gif',
	'img/forum_no_inoltra2.gif',
	'img/forum_inoltra2.gif',
	'img/ico_forumreport2.gif',
	'img/icotop_pausa2.gif',
	'img/attinente_2.gif',
	'img/ico_lom_over.gif',
	'img/ico_lo_export_over.gif',
	'img/ico_profile_over.gif',
	'img/ico_flag_cy_over.gif',
	'img/layout1.gif',
	'img/layout2.gif',
	'img/layout3.gif',
	'img/layout4.gif',
	'img/layout5.gif',
	'img/layout6.gif',
	'img/layout7.gif',
	'img/layout8.gif',
	'img/layout9.gif',
	'img/layout10.gif',
	'img/test_1.gif',
	'img/test_2.gif',
	'img/test_3.gif',
	'img/test_4.gif',
	'img/test_5.gif',
	'img/test_6.gif',
	'img/piuma_on.gif'
	);
};

