/************************************************************************/
/* DOCEBO CORE - Framework												*/
/* ============================================							*/
/*																		*/
/* Copyright (c) 2006													*/
/* http://www.docebo.com												*/
/* by Francesco Leonetti - Fabio Pirovano               				*/
/* This program is free software. You can redistribute it and/or modify	*/
/* it under the terms of the GNU General Public License as published by	*/
/* the Free Software Foundation; either version 2 of the License.		*/
/************************************************************************/

var wObjList=Array();

Window = function() {
	this.title=null;
	this.content=null;
	this.id=null;
	this.top=null;
	this.left=null;
	this.width=null;
	this.height=null;
	this.onClose=null;
	this.close_text = 'close';
	this.css_class_name = 'window_object';
	this.buttons = null;
};

Window.prototype.show = function() {
	
	if(wObjList[this.id] != null) destroyWindow(this.id);
	
	var new_div = document.createElement('div');
   	new_div.id = this.id;
   	new_div.style.display = 'block';
   	new_div.style.width = this.width+'px';
   	new_div.style.left 	= Math.round((browserWidth()/2 - (this.width/2) ))+'px';
	
	if (!this.top) {
		//new_div.style.top  	= getTop();
		new_div.style.top  	= 100+getTop()+Math.round((browserHeight()/2 - this.height ))+'px';
	} else {
		//new_div.style.top = this.top;
		new_div.style.top  	= 100+getTop()+Math.round((browserHeight()/2 - this.height ))+'px';
	}	
		
	//new_div.style.top  	= 200+Math.round((browserHeight()/2 - this.height ))+'px';
   	
	new_div.className 	= this.css_class_name;
   	
   	var titlebar = document.createElement('div');
   	new_div.appendChild(titlebar);
   	titlebar.className = 'title_bar';
	titlebar.id = 'wTitleBar';
	wObjList[this.id] = this;
	
	titlebar.innerHTML = '<h1 id="' + this.id + '_titleBar">' + this.title + '</h1>'
		+ '<a class="close_button" href="javascript:;" id="' + this.id + '_close" onclick="callCloseHandler('+"'"+this.id+"'"+');destroyWindow('+"'"+this.id+"'"+');return false;">'
		+ '<span>' + this.close_text +'</span></a>';
	
	var clientArea = document.createElement('div');
   	new_div.appendChild(clientArea);
   	clientArea.className = "w_content";
   	clientArea.style.height = this.height+'px';
   	
	clientArea.innerHTML += this.content;
	
	if(this.buttons != null) {
	
		var buttonArea = document.createElement('div');
	   	new_div.appendChild(buttonArea);
	   	buttonArea.className = "line_for_button";
	    buttonArea.id = this.id+"_btns";
			
		buttonArea.innerHTML += this.buttons;
	}
	document.body.insertBefore(new_div, document.body.nextSibling);
    
	new Draggable(this.id,{scroll:window,handle:'wTitleBar'});
}


function callCloseHandler(name) {
	w=wObjList[name];
	if (w && w.onClose) {
		w.onClose();
	}
}

function destroyWindow(name) {
	var toKill = $(name);
  	toKill.parentNode.removeChild(toKill);
	wObjList[name]=null;
}

function browserWidth() {
   if (self.innerWidth) {
	return self.innerWidth;
   } else if (document.documentElement && document.documentElement.clientWidth) {
	return document.documentElement.clientWidth;
   } else if (document.body) {
	return document.body.clientWidth;
   }
   return 630;
}

function browserHeight() {
   if (self.innerWidth) {
	return self.innerHeight;
   } else if (document.documentElement && document.documentElement.clientWidth) {
	return document.documentElement.clientHeight;
   } else if (document.body) {
	return document.body.clientHeight;
   }
   return 650;
}

var theTop=200;
var old=theTop;
function getTop() {
	if (window.innerHeight)
	{
		  pos = window.pageYOffset
	}
	else if (document.documentElement && document.documentElement.scrollTop)
	{
		pos = document.documentElement.scrollTop
	}
	else if (document.body)
	{
		  pos = document.body.scrollTop
	}
	
	if (pos < theTop) pos = theTop;
	
	return pos;

}