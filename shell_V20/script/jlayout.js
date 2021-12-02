/* --- SHELL ACCESSIBILE 2007: FUNZIONI DI MODIFICA DEL LAYOUT --- */

function layouthome(){
	if (dimensionipagina == 1){
		document.getElementById("animazionegioco").style.left = "450px";
		document.getElementById("animazionegioco").style.top = "435px";
		document.getElementById("indice").style.left = "428px";
		document.getElementById("indice").style.top = "359px";
		document.getElementById("suonoon").style.left = "341px";
		document.getElementById("suonoon").style.top = "359px";
		document.getElementById("suonooff").style.left = "341px";
		document.getElementById("suonooff").style.top = "359px";
	}
	else{
		document.getElementById("animazionegioco").style.left = "600px";
		document.getElementById("animazionegioco").style.top = "585px";
		document.getElementById("indice").style.left = "522px";
		document.getElementById("indice").style.top = "409px";
		document.getElementById("suonoon").style.left = "434px";
		document.getElementById("suonoon").style.top = "409px";
		document.getElementById("suonooff").style.left = "434px";
		document.getElementById("suonooff").style.top = "409px";
	}
}

function layoutuscitahome(){
	document.getElementById("titolo_esci").style.color = "#ffffff";
	if (dimensionipagina == 1){
		document.getElementById("bloccouscita").style.left = "70px";
		document.getElementById("titolo_esci").style.top = "138px";
		document.getElementById("titolo_esci").style.left = "110px";
	}
	else{
		document.getElementById("bloccouscita").style.left = "90px";
		document.getElementById("titolo_esci").style.top = "138px";
		document.getElementById("titolo_esci").style.left = "65px";
	}
}

function layoutuscitastandard(){
	document.getElementById("titolo_esci").style.color = "#161691";
	if (dimensionipagina == 1){
		document.getElementById("bloccouscita").style.left = "30px";
		document.getElementById("titolo_esci").style.top = "48px";
		document.getElementById("titolo_esci").style.left = "65px";
	}
	else{
		document.getElementById("bloccouscita").style.left = "50px";
		document.getElementById("titolo_esci").style.top = "48px";
		document.getElementById("titolo_esci").style.left = "40px";
	}
}

function modificalayout(){
	var nomepagina = new String;
	document.getElementById("paginahelp").style.backgroundImage="url(../immagini/layout_"+modofruizione+"/copertina_servizio"+dimensionipagina+".jpg)"
	document.getElementById("paginacredits").style.backgroundImage="url(../immagini/layout_"+modofruizione+"/copertina_servizio"+dimensionipagina+".jpg)"
	document.getElementById("sommario").style.backgroundImage="url(../immagini/layout_"+modofruizione+"/copertina_servizio"+dimensionipagina+".jpg)"
	switch (modofruizione){
		case 2:
			if (dimensionipagina == 1){
				document.getElementById("animazionegioco").style.left = "672px";
				document.getElementById("animazionegioco").style.top = "230px";
				document.getElementById("avanti").style.left = "748px";
				document.getElementById("avanti").style.top = "460px";
				document.getElementById("indietro").style.left = "668px";
				document.getElementById("indietro").style.top = "459px";
				document.getElementById("history").style.left = "670px";
				document.getElementById("history").style.top = "512px";
				document.getElementById("home").style.left = "707px";
				document.getElementById("home").style.top = "422px";
				document.getElementById("indice").style.left = "709px";
				document.getElementById("indice").style.top = "494px";
				document.getElementById("ingrandisci").style.left = "640px";
				document.getElementById("ingrandisci").style.top = "384px";
				document.getElementById("rimpicciolisci").style.left = "640px";
				document.getElementById("rimpicciolisci").style.top = "428px";
				document.getElementById("suonoon").style.left = "725px";
				document.getElementById("suonoon").style.top = "355px";
				document.getElementById("suonooff").style.left = "725px";
				document.getElementById("suonooff").style.top = "355px";
				document.getElementById("tornaindietrocredits").style.left = "668px";
				document.getElementById("tornaindietrocredits").style.top = "511px";
				document.getElementById("tornaindietrohelp").style.left = "668px";
				document.getElementById("tornaindietrohelp").style.top = "511px";
				document.getElementById("tornaindietrosommario").style.left = "668px";
				document.getElementById("tornaindietrosommario").style.top = "511px";
			}
			else{
				document.getElementById("animazionegioco").style.left = "890px";
				document.getElementById("animazionegioco").style.top = "234px";
				document.getElementById("avanti").style.left = "961px";
				document.getElementById("avanti").style.top = "494px";
				document.getElementById("indietro").style.left = "884px";
				document.getElementById("indietro").style.top = "494px";
				document.getElementById("history").style.left = "883px";
				document.getElementById("history").style.top = "546px";
				document.getElementById("home").style.left = "921px";
				document.getElementById("home").style.top = "457px";
				document.getElementById("indice").style.left = "922px";
				document.getElementById("indice").style.top = "529px";
				document.getElementById("ingrandisci").style.left = "863px";
				document.getElementById("ingrandisci").style.top = "384px";
				document.getElementById("rimpicciolisci").style.left = "863px";
				document.getElementById("rimpicciolisci").style.top = "428px";
				document.getElementById("suonoon").style.left = "935px";
				document.getElementById("suonoon").style.top = "360px";
				document.getElementById("suonooff").style.left = "935px";
				document.getElementById("suonooff").style.top = "360px";
				document.getElementById("tornaindietrocredits").style.left = "886px";
				document.getElementById("tornaindietrocredits").style.top = "497px";
				document.getElementById("tornaindietrohelp").style.left = "886px";
				document.getElementById("tornaindietrohelp").style.top = "497px";
				document.getElementById("tornaindietrosommario").style.left = "886px";
				document.getElementById("tornaindietrosommario").style.top = "497px";
			}
			for(var i=0;i < successione[0].length;i++){;
				nomepagina = successione[0][i];
				if (document.getElementById("pulsantetest_"+nomepagina))
					document.getElementById("pulsantetest_"+nomepagina).style.visibility="hidden";
				if (document.getElementById("punteggio_"+nomepagina)){
					document.getElementById("punteggio_"+nomepagina).style.color="#ffffff";
					if (dimensionipagina == 1){
						document.getElementById("punteggio_"+nomepagina).style.left="670px";
						document.getElementById("punteggio_"+nomepagina).style.top="178px";
					}
					else{
						document.getElementById("punteggio_"+nomepagina).style.left="890px";
						document.getElementById("punteggio_"+nomepagina).style.top="178px";
					}
				}
				if (document.getElementById("numero_"+nomepagina)){
					document.getElementById("numero_"+nomepagina).style.color="#ffffff";
					if (dimensionipagina == 1){
						document.getElementById("numero_"+nomepagina).style.left="690px";
						document.getElementById("numero_"+nomepagina).style.top="140px";
					}
					else{
						document.getElementById("numero_"+nomepagina).style.left="920px";
						document.getElementById("numero_"+nomepagina).style.top="140px";
					}
				}
			}
		break;
		case 1:
			if (dimensionipagina == 1){
				document.getElementById("avanti").style.left = "546px";
				document.getElementById("avanti").style.top = "507px";
				document.getElementById("indietro").style.left = "505px";
				document.getElementById("indietro").style.top = "512px";
				document.getElementById("history").style.left = "465px";
				document.getElementById("history").style.top = "516px";
				document.getElementById("home").style.left = "684px";
				document.getElementById("home").style.top = "477px";
				document.getElementById("indice").style.left = "724px";
				document.getElementById("indice").style.top = "461px";
				document.getElementById("ingrandisci").style.left = "664px";
				document.getElementById("ingrandisci").style.top = "271px";
				document.getElementById("rimpicciolisci").style.left = "664px";
				document.getElementById("rimpicciolisci").style.top = "338px";
				document.getElementById("suonoon").style.left = "587px";
				document.getElementById("suonoon").style.top = "501px";
				document.getElementById("suonooff").style.left = "587px";
				document.getElementById("suonooff").style.top = "501px";
				document.getElementById("tornaindietrocredits").style.left = "465px";
				document.getElementById("tornaindietrocredits").style.top = "516px";
				document.getElementById("tornaindietrohelp").style.left = "465px";
				document.getElementById("tornaindietrohelp").style.top = "516px";
				document.getElementById("tornaindietrosommario").style.left = "465px";
				document.getElementById("tornaindietrosommario").style.top = "516px";
			}
			else{
				document.getElementById("avanti").style.left = "782px";
				document.getElementById("avanti").style.top = "647px";
				document.getElementById("indietro").style.left = "741px";
				document.getElementById("indietro").style.top = "655px";
				document.getElementById("history").style.left = "701px";
				document.getElementById("history").style.top = "661px";
				document.getElementById("home").style.left = "909px";
				document.getElementById("home").style.top = "611px";
				document.getElementById("indice").style.left = "949px";
				document.getElementById("indice").style.top = "599px";
				document.getElementById("ingrandisci").style.left = "883px";
				document.getElementById("ingrandisci").style.top = "330px";
				document.getElementById("rimpicciolisci").style.left = "883px";
				document.getElementById("rimpicciolisci").style.top = "397px";
				document.getElementById("suonoon").style.left = "822px";
				document.getElementById("suonoon").style.top = "637px";
				document.getElementById("suonooff").style.left = "822px";
				document.getElementById("suonooff").style.top = "637px";
				document.getElementById("tornaindietrocredits").style.left = "701px";
				document.getElementById("tornaindietrocredits").style.top = "661px";
				document.getElementById("tornaindietrohelp").style.left = "701px";
				document.getElementById("tornaindietrohelp").style.top = "661px";
				document.getElementById("tornaindietrosommario").style.left = "701px";
				document.getElementById("tornaindietrosommario").style.top = "661px";
			}
			for(var i=0;i < successione[0].length;i++){;
				nomepagina = successione[0][i];
				if (document.getElementById("pulsantetest_"+nomepagina))
					document.getElementById("pulsantetest_"+nomepagina).style.visibility="visible";
				if (document.getElementById("punteggio_"+nomepagina)){
					document.getElementById("punteggio_"+nomepagina).style.color="#ffffff";
					if (dimensionipagina == 1){
						document.getElementById("punteggio_"+nomepagina).style.left="700px";
						document.getElementById("punteggio_"+nomepagina).style.top="227px";
					}
					else{
						document.getElementById("punteggio_"+nomepagina).style.left="927px";
						document.getElementById("punteggio_"+nomepagina).style.top="470px";
					}
				}
				if (document.getElementById("numero_"+nomepagina)){
					document.getElementById("numero_"+nomepagina).style.color="#161691";
					if (dimensionipagina == 1){
						document.getElementById("numero_"+nomepagina).style.left="694px";
						document.getElementById("numero_"+nomepagina).style.top="150px";
					}
					else{
						document.getElementById("numero_"+nomepagina).style.left="905px";
						document.getElementById("numero_"+nomepagina).style.top="150px";
					}
				}
			}
		break;
	}
}
