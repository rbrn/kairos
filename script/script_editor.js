//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

function button_over(eButton)

	{

	eButton.style.backgroundColor = "#B5BDD6";

	eButton.style.borderColor = "darkblue darkblue darkblue darkblue";

	}

function button_out(eButton)

	{

	eButton.style.backgroundColor = "threedface";

	eButton.style.borderColor = "threedface";

	}

function button_down(eButton)

	{

	eButton.style.backgroundColor = "#8494B5";

	eButton.style.borderColor = "darkblue darkblue darkblue darkblue";

	}

function button_up(eButton)

	{

	eButton.style.backgroundColor = "#B5BDD6";

	eButton.style.borderColor = "darkblue darkblue darkblue darkblue";

	eButton = null; 

	}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



var isHTMLMode=false

var colore_sfondo=false

function inoltra()

	{



	var contenuto=idContent.document.body.innerHTML;

	document.all.testo.value=contenuto;



}



function inoltra_chat()

	{



	var contenuto=idContent.document.body.innerHTML;

	document.all.testo.value=contenuto;

	self.close();



}



function cmdExec(cmd,opt) 

	{

  	if (isHTMLMode){;return;}

  	idContent.document.execCommand(cmd,"",opt);idContent.focus();

	}

	

	

function cambiastato()

	{

	var sTmp;

	if (document.modulo.modalita[0].checked) {

		isHTMLMode=true

	} else {

		isHTMLMode=false

	}

	if (isHTMLMode)

		{

		var testo="HTML";

		sTmp=idContent.document.body.innerHTML;

		idContent.document.body.innerText=sTmp;

		document.all.scambio.value=testo;

		} 

	else 

    	{

  		var testo="Testo";

  		sTmp=idContent.document.body.innerText;

  		idContent.document.body.innerHTML=sTmp;

  		document.all.scambio.value=testo;

		}

  	idContent.focus();

	}

	

function createLink()

	{

	if (isHTMLMode){;return;}

	cmdExec("CreateLink");

	}

	

function ColorPalette_OnClick(colorString){

	if (isHTMLMode){;return;}

	if (colore_sfondo) {

		csfondopick.bgColor=colorString;

		document.all.coloursfondop.value=colorString;

		cambia_sfondo();

		//cmdExec("BackColor",colorString);

	} else {

		cpick.bgColor=colorString;

		document.all.colourp.value=colorString;

		cmdExec("ForeColor",colorString);

	};

}



function foreColor()

	{
if (isHTMLMode){;return;}
	var arr = showModalDialog("selcolore.htm","","font-family:Verdana; font-size:12; dialogWidth:30em; dialogHeight:34em" );

	if (arr != null) cmdExec("ForeColor",arr);	

	}

	

function InserisciImmagine()

	{

if (isHTMLMode){;return;}

	idContent.focus();

	

	var arr=showModalDialog("apri_immagine.php","","font-family:Verdana; font-size:12; dialogWidth:30em; dialogHeight:34em" );



	idContent.focus();

	

	if (arr != null) cmdExec("InsertImage",arr);	



	//var arr=window.clipboardData.getData("Text");

    //if (arr != null) cmdExec("InsertImage",arr);

}





function set_colore(scelta_colore) {

	if (scelta_colore=='testo') {

		colore_sfondo=false

	} else {

		colore_sfondo=true

	}

}



function Table()

{
if (isHTMLMode){;return;}
  win_open('ins_tabella.php','Tabella',500,500);

}



function win_open(URL,titolo,w,h) {

  var iTop=window.screen.height/2-h/2-10;

  var iLeft=window.screen.width/2-w/2-10;

  var windowprops = "location=no,scrollbars=no,menubars=no,toolbars=no,resizable=yes" + ",left=" + iLeft + ",top=" + iTop + ",width=" + w + ",height=" + h;

  popup = window.open(URL,titolo,windowprops);

  popup.focus();

}



function InsertTable(rows, columns, cellpadding, cellspacing, borderwidth, cellwidth, cellheight, color) {

   window.idContent.focus()

   var sel = idContent.document.selection;

   if (sel!=null) {

   var rng = sel.createRange();

   if (rng!=null) {

           table = "<TABLE CELLPADDING="+cellpadding+" CELLSPACING="+cellspacing+" BORDER="+borderwidth;

           if(color != null && color != "")

                   table += " BGCOLOR="+color;

           table += ">";

           for(tr=0; tr<rows; tr++) {

                   table += "<TR>";

                   for(td=0; td<columns; td++) {

                           table += "<TD CLASS=\"testo\" ";

                           if(cellwidth != null && cellwidth != "")

                                   table += " width="+cellwidth;

                           if(cellheight != null && cellheight != "")

                                   table += " height="+cellheight;

                           table += ">&nbsp;</TD>";

                   }

                   table += "</TR>";

           }

           table += "</TABLE>";

   }

    rng.pasteHTML(table);

   }

}



function cambia_sfondo() {
if (isHTMLMode){;return;}
	var Content = window.idContent.document.body.innerHTML ;  

	var coloreSfondo=document.all.coloursfondop.value;

	//window.idContent.document.body.style.backgroundColor=coloreSfondo;

	

    if ( Content.indexOf ('BACKGROUND-COLOR')!= -1)

    { 

      window.idContent.document.body.innerHTML = '';

      var Begin = Content.indexOf ('>')

      Content = Content.substr (Begin+1)

      var End = Content.lastIndexOf ('</DIV>')

      Content = Content.substr (0,End-6)

    };  

	

	window.idContent.document.body.innerHTML = '<div style="background-color:'+ coloreSfondo+'">' + Content + '</div>';

    window.idContent.focus();

    

};  	

	