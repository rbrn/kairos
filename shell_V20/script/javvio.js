/* --- SHELL ACCESSIBILE 2007: FISTRUZIONI DI AVVIO --- */

/* -- ISTRUZIONI INIZIALI -- */

/* -- Identificazione browser -- */
switch (navigator.appName){
	case "Microsoft Internet Explorer":
		tipobrowser = 1;
		plugin_fl = 1;
		document.writeln("<script language='VBscript'>");
		document.writeln("on error resume next");
		document.writeln('plugin_wm = IsObject(CreateObject("MediaPlayer.MediaPlayer.1"))');
		document.writeln('plugin_rp = IsObject(CreateObject("rmocx.RealPlayer G2 Control"))');
		document.writeln('plugin_rp = IsObject(CreateObject("RealPlayer.RealPlayer(tm) ActiveX Control (32-bit)"))');
		document.writeln('plugin_rp = IsObject(CreateObject("RealVideo.RealVideo(tm) ActiveX Control (32-bit)"))');
		document.writeln('plugin_sw = IsObject(CreateObject("SWCtl.SWCtl"))');
		document.writeln("qtime = false");
		document.writeln('Set qtime = CreateObject("QuickTimeCheckObject.QuickTimeCheck.1")');
		document.writeln("If IsObject(qtime) Then");
		document.writeln("If qtime.IsQuickTimeAvailable(0) Then");
		document.writeln("plugin_qt = 1");
		document.writeln("End If");
		document.writeln("End If");
		document.writeln('plugin_ja = IsObject(CreateObject("JavaWebStart.isInstalled"))');
		document.writeln('plugin_ja = IsObject(CreateObject("JavaWebStart.isInstalled.1.4.2.0"))');
		document.writeln('plugin_ja = IsObject(CreateObject("JavaWebStart.isInstalled.1.5.0.0"))');
		document.writeln("</script>");
		break;
	case "Netscape":
		tipobrowser = 2;
		cercaplugin();
		break;
	case "Opera":
		tipobrowser = 3;
		cercaplugin();
		break;
	default: 
		tipobrowser = 3;
		cercaplugin();
		break;
}

/* -- Configurazione ambiente -- */
acquisisciparametri();
window.moveTo(0,0);
if (dimensionipagina==2){
	document.write("<link rel='stylesheet' href='../stili/tutoriale2.css' type='text/css'>");
	window.resizeTo(1024,755);
}
else{
	document.write("<link rel='stylesheet' href='../stili/hidden.css' type='text/css'>");
	window.resizeTo(800,600);
}

/* -- Predisposizione delle pagine -- */
predisponipagine();

/* -- Caricamento file multimediali di sistema -- */
caricamedia("messaggio.mp3","globale",1,0);
caricamedia("ok.mp3","globale",2,0);
caricamedia("ko.mp3","globale",3,0);

/* -- Avvio -- */
window.onload = inizializza;
window.onunload = traccia;
