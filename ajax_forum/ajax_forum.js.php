var wroot="<?php echo($_GET["wroot"])?>";
var serverUrl="<?php echo($_GET["serverUrl"])?>";
var cod_area="<?php echo($_GET["cod_area"])?>";
var id_utente="<?php echo($_GET["id_utente"])?>";
var v;
var p;
var idf;
var idp;
var oldIdp=null;

function showPost(idForum,idPost,vista,pagina) {
	v=vista;
	p=pagina;
	idf=idForum;
	idp=idPost;
	
	if (oldIdp) {
		var imgName='preview'+oldIdp;
		$(imgName).src='img/ico_forum_daleggere.gif';
		oldIdp=null;
	}
	
	var imgName='preview'+idp;
	$(imgName).src='img/ico_forum_daleggere_over.gif';
	oldIdp=idp;
	
	var butns='<input type="submit" value="Chiudi" onclick="restoreImg();destroyWindow(\'wPost\')";return false;">';
	
	if (wObjList['wPost']!=null) {
		var w0=$('wPost');
		var el=document.getElementsByClassName("w_content",w0.parentNode);
		el[0].innerHTML="<span class=testo>Aspetta un attimo...</span>";
		$('wPost_btns').innerHTML=butns;
	} else {
		var name="wPost";
		var title="Intervento";
   		
		
   		var w=new Window();
		w.top=getTop();
		w.id=name;
		w.width=600;
		w.height=400;
		w.title=title;
		w.content="<span class=testo>Aspetta un attimo...</span>";
		w.buttons=butns;
		w.onClose=restoreImg;
		w.show();
	}
	
	$('post_'+idPost).innerHTML="";
	
	var data="op=getPost&cod_area="+cod_area+"&id_utente="+id_utente+"&id_forum="+idForum+"&id_post="+idPost;
	var objAjax = new Ajax.Request(
        	serverUrl,
        	{method: 'get', parameters: data, onComplete: viewPost}
    );	
}

function viewPost (ObjReq) {
	var postText = ObjReq.responseText;
	var flag_edit=postText.substr(0,1);
	postText = postText.substr(1,postText.length-1);
	
	var butns='';
	
	if ((flag_edit)==1) 
	butns+='<input type="submit" value="Replica intervento" onclick="document.location.href=\''+wroot+'index.php?risorsa=forum_post&op=replica&id_post_padre='+idp+'&id_forum='+idf+'&vista='+v+'&pagina='+p+'\'">';

	butns+='<input type="submit" value="Chi l\'ha letto" onclick="javascript:apri_scheda(\'forum_storia_msg.php?id_post='+idp+'\',\'myRemoteLetto\',        \'height=500,width=300,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0\',\'myWindowLetto\');"><input type="submit" value="Apri intervento" onclick="document.location.href=\''+wroot+'index.php?risorsa=forum_mostra_post&id_post='+idp+'&id_forum='+idf+'&vista='+v+'&pagina='+p+'\'"><input type="submit" value="Chiudi" onclick="restoreImg();destroyWindow(\'wPost\')";return false;">';

	if (wObjList['wPost']!=null) {
		var w0=$('wPost');
		var el=document.getElementsByClassName("w_content",w0.parentNode);
		el[0].innerHTML=postText;
		$('wPost_btns').innerHTML=butns;
	} else {
		var name="wPost";
		var title="Intervento";
   
   		var w=new Window();
		w.top=getTop();
		w.id=name;
		w.width=600;
		w.height=400;
		w.title=title;
		w.content=postText;
		w.buttons=butns;
		w.onClose=restoreImg;
		w.show();
	}
}

function restoreImg() {
	if (oldIdp) {
		var imgName='preview'+oldIdp;
		$(imgName).src='img/ico_forum_daleggere.gif';
		oldIdp=null;
	}
}

function markPost(idForum,idPost,vista,pagina) {
	v=vista;
	p=pagina;
	idf=idForum;
	idp=idPost;
	
	var data="op=markPost&cod_area="+cod_area+"&id_utente="+id_utente+"&id_forum="+idForum+"&id_post="+idPost;
	var objAjax = new Ajax.Request(
        	serverUrl,
        	{method: 'get', parameters: data, onComplete: postMarked}
    );	
}

function postMarked(ObjReq) {
	var mk = ObjReq.responseText;
	
	var imgName='img_mark_'+idp;
	var imgName2='rigamark_'+idp;
	
	if (mk==0) {
		$(imgName).src='img/ico_forum_segnainteres_fade.gif';
		$(imgName2).src='img/forum/nospunta.gif';
	} else {
		$(imgName).src='img/ico_forum_segnainteres.gif';
		$(imgName2).src='img/forum/spunta.gif';
	}
}


function setPiuma(idPost,livello) {
	idp=idPost;
	
	livello++;
	var data="op=setPiuma&cod_area="+cod_area+"&id_utente="+id_utente+"&id_post="+idPost+"&livello="+livello;
	var objAjax = new Ajax.Request(
        	serverUrl,
        	{method: 'get', parameters: data, onComplete: setPiumaOk}
    );	
}

function setPiumaOk(ObjReq) {
	$('piume'+idp).style.display="none";
}

function alertCoord(e) {
  if( !e ) {
    if( window.event ) {
      //Internet Explorer
      e = window.event;
    } else {
      //total failure, we have no way of referencing the event
      return;
    }
  }
  if( typeof( e.pageX ) == 'number' ) {
    //most browsers
    var xcoord = e.pageX;
    var ycoord = e.pageY;
  } else if( typeof( e.clientX ) == 'number' ) {
    //Internet Explorer and older browsers
    //other browsers provide this, but follow the pageX/Y branch
    var xcoord = e.clientX;
    var ycoord = e.clientY;
    var badOldBrowser = ( window.navigator.userAgent.indexOf( 'Opera' ) + 1 ) ||
     ( window.ScriptEngine && ScriptEngine().indexOf( 'InScript' ) + 1 ) ||
     ( navigator.vendor == 'KDE' )
    if( !badOldBrowser ) {
      if( document.body && ( document.body.scrollLeft || document.body.scrollTop ) ) {
        //IE 4, 5 & 6 (in non-standards compliant mode)
        xcoord += document.body.scrollLeft;
        ycoord += document.body.scrollTop;
      } else if( document.documentElement && ( document.documentElement.scrollLeft || document.documentElement.scrollTop ) ) {
        //IE 6 (in standards compliant mode)
        xcoord += document.documentElement.scrollLeft;
        ycoord += document.documentElement.scrollTop;
      }
    }
  } else {
    //total failure, we have no way of obtaining the mouse coordinates
    return;
  }
  window.alert('Mouse coordinates are ('+xcoord+','+ycoord+')');
}

