var wroot="<?php echo($_GET["wroot"])?>";
var serverUrlChat="<?php echo($_GET["serverUrl"])?>";
var cod_area="<?php echo($_GET["cod_area"])?>";
var id_utente="<?php echo($_GET["id_utente"])?>";


function checkInvito() {
		
	var data="cod_area="+cod_area+"&id_utente="+id_utente;
	var objAjax = new Ajax.Request(
        	serverUrlChat,
        	{method: 'get', parameters: data, onComplete: invitoChecked}
    );	
}

function invitoChecked(ObjReq) {
	var resultText = ObjReq.responseText;
	
	var result = resultText.parseJSON();
	
	if (typeof result.stanza!="undefined" && typeof result.id_host!="undefined" && result.id_host!="undefined" && result.stanza!=0 && result.stanza!="undefined") {
	var butns='<input type="submit" value="Accetta" onclick="document.location.href=\''+wroot+'chat_entra.php?stanza='+result.stanza+'\'"><input type="submit" value="Declina" onclick="destroyWindow(\'wChat\')";return false;">';
	
	var mittente="<a class=miolink href=\"javascript:;\" title=\"clicca per sapere chi &egrave;\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente="+result.id_host+"','myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">"+result.id_host+"</a>";
	
	var content='<span class="testo">'+result.data_invito+'<br><br>Hai ricevuto un invito in chat nella stanza: <b>'+result.stanza+'</b><br><br>da <b>'+mittente+'</b></span>';

	


	content+='<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0" width="1" height="1" id="soundeffect" align=""> <param name="movie" value="jazz.swf"> <param name="quality" value="high"> <parame name="bgcolor" value="#FFFFFF"> <embed src="jazz.swf" quality="high" bgcolor="#FFFFFF" name="soundeffect" width="1" height="1" align="" type="application/x-shockwave-flash" pluginspace="http://www.macromedia.com/go/getflashplayer"></embed></object>';

	if (wObjList['wChat']!=null) {
		var w0=$('wChat');
		var el=document.getElementsByClassName("w_content",w0.parentNode);
		el[0].innerHTML=content;
		$('wChat_btns').innerHTML=butns;
	} else {
		var name="wChat";
		var title="Invito in chat";
   
   		var w=new Window();
		w.top=getTop();
		w.id=name;
		w.width=400;
		w.height=200;
		w.title=title;
		w.content=content;
		w.buttons=butns;
		w.show();
	}
	}
}

function startCheckInvito() {
	setInterval("checkInvito()",10000);
}

Event.observe(window,"load",startCheckInvito,false);


