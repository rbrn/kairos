// $Id: dialog.js,v 1.11 2004/08/22 09:16:16 julmis Exp $
// Though "Dialog" looks like an object, it isn't really an object.  Instead
// it's just namespace for protecting global symbols.

function Dialog(url, action, init) {
    if (typeof init == "undefined") {
        init = window;  // pass this window object by default
    }
    Dialog._geckoOpenModal(url, action, init);
	
};

Dialog._parentEvent = function(ev) {
    if (Dialog._modal && !Dialog._modal.closed) {
        Dialog._modal.focus();
        HTMLArea._stopEvent(ev);
    }
};

// should be a function, the return handler of the currently opened dialog.
Dialog._return = null;

// constant, the currently opened dialog
Dialog._modal = null;

// the dialog will read it's args from this variable
Dialog._arguments = null;

Dialog._geckoOpenModal = function(url, action, init) {

    var file = url.substring(url.lastIndexOf('/') + 1, url.lastIndexOf('.'));
    var x,y;
	
    switch(file) {
        case "link":     x = 420; y = 200; break;
		case "link_contenuti":     x = 420; y = 400; break;
		case "link_contenuti_coll":     x = 420; y = 400; break;
		case "insert_image_contenuti":     x = 420; y = 400; break;
		case "insert_image_coll":     x = 420; y = 400; break;
		case "insert_flash_contenuti":     x = 420; y = 400; break;
		case "insert_flash_coll":     x = 420; y = 400; break;
		case "insert_audio_contenuti":     x = 420; y = 400; break;
		case "insert_audio_coll":     x = 420; y = 400; break;
		case "insert_video_contenuti":     x = 420; y = 400; break;
		case "insert_video_coll":     x = 420; y = 400; break;
		case "insert_image": x = 420; y = 400; break;
		case "insert_table": x = 420; y = 400; break;
		case "insert_flash": x = 420; y = 400; break;
        default: x = 420; y = 200;
    }

    var lx = (screen.width - x) / 2;
    var tx = (screen.height - y) / 2;
    var dlg = window.open(url, "ha_dialog", "toolbar=no,menubar=no,personalbar=no, width="+ x +",height="+ y +",scrollbars=no,resizable=yes, left="+ lx +", top="+ tx +"");

    Dialog._modal = dlg;
    Dialog._arguments = init;

	
	
    // capture some window's events
    function capwin(w) {
        HTMLArea._addEvent(w, "click", Dialog._parentEvent);
        HTMLArea._addEvent(w, "mousedown", Dialog._parentEvent);
        HTMLArea._addEvent(w, "focus", Dialog._parentEvent);
    };
    // release the captured events
    function relwin(w) {
        HTMLArea._removeEvent(w, "click", Dialog._parentEvent);
        HTMLArea._removeEvent(w, "mousedown", Dialog._parentEvent);
        HTMLArea._removeEvent(w, "focus", Dialog._parentEvent);
    };
    capwin(window);
    // capture other frames
    if(document.all) {
        for (var i = 0; i < window.frames.length; capwin(window.frames[i++]));
    }
    // make up a function to be called when the Dialog ends.
    Dialog._return = function (val) {
        if (val && action) {
            action(val);
        }
        relwin(window);
        // capture other frames
        if(document.all) {
            for (var i = 0; i < window.frames.length; relwin(window.frames[i++]));
        }
        Dialog._modal = null;
    };
	
	
	
	if (!document.all) {
		this.focus();
	}
	
};

