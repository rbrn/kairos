<?php
$cod_area=$kairos_cookie[4];
if (!$cod_area) $cod_area="kairos_demo";
require "../pagine/$cod_area/colori.inc";
$server=$_SERVER["SERVER_NAME"];

$base="";
if ($server) $base="kairos/";
if ($server=="localhost") $base="kairos/";
?>


<?php
if ($contesto=="contenuti" or $contesto=="contenuti_coll" ) {
?>
HTMLArea.loadPlugin("TableOperations");
<?php }; ?>

var editor = null;
function initEditor() {

  editor = new HTMLArea("testo");

  <?php
	if ($contesto=="contenuti" or $contesto=="contenuti_coll" ) {
  ?>
  	editor.registerPlugin(TableOperations);
  <?php }; ?>
  
  var cfg = editor.config; 
  cfg.hideSomeButtons(" showhelp popupeditor about ");  
  

<?php
  switch ($contesto) 	{

	case "forum":	
  ?>
  	 cfg.pageStyle = "body { background-color: <?php echo($colore_sfondo);?>; color:<?php echo($colore_testo);?>; }";
	 cfg.hideSomeButtons(" createlink_contenuti createlink_coll createlink_lo insertimage_contenuti insertimage_coll insertflash_contenuti insertflash_coll insertaudio_contenuti insertaudio_coll insertvideo_contenuti insertvideo_coll "); 

<?php break;

	case "news":	
  ?>
  	 cfg.pageStyle = "body { background-color: #ffffff; color:<?php echo($colore_testo);?>; }";
	 cfg.hideSomeButtons(" createlink_contenuti createlink_coll createlink_lo insertimage_contenuti insertimage_coll insertflash_contenuti insertflash_coll insertaudio_contenuti insertaudio_coll insertvideo_contenuti insertvideo_coll "); 

<?php break;

	case "chat":
 ?>
	cfg.pageStyle = "body { background-color: #ffffff; }";
  	cfg.hideSomeButtons(" createlink_contenuti createlink_coll createlink_lo insertimage_contenuti insertimage_coll insertflash_contenuti insertflash_coll insertaudio_contenuti insertaudio_coll insertvideo_contenuti insertvideo_coll "); 

<?php break;

	case "contenuti":
 ?>
	cfg.pageStyle = "body { background-color: #ffffff; color:<?php echo($colore_testo);?>;}";
  	cfg.hideSomeButtons(" createlink createlink_coll createlink_lo insertimage insertimage_coll insertflash_coll insertaudio_coll insertvideo_coll ");
<?php break;

	case "contenuti_coll": 
?>
	cfg.pageStyle = "body { background-color: #ffffff; color:<?php echo($colore_testo);?>;}";
  	cfg.hideSomeButtons(" createlink createlink_contenuti createlink_lo insertimage insertimage_contenuti insertflash_contenuti insertaudio_contenuti insertvideo_contenuti ");

<?php break;

	case "lo": 
?>
	cfg.pageStyle = "body { background-color: #ffffff; color:<?php echo($colore_testo);?>;}";
  	cfg.hideSomeButtons(" fontname fontsize lefttoright righttoleft hilitecolor createlink insertimage createlink_contenuti createlink_coll insertimage_contenuti insertimage_coll insertflash_contenuti insertflash_coll insertaudio_contenuti insertaudio_coll insertvideo_contenuti insertvideo_coll "); 
<?php break;?>

<?php }; ?>

  if (HTMLArea.is_ie) {
  cfg.toolbar.push(["citazione"]); // add the new button to the toolbar
  cfg.registerButton("citazione", "Inserisci tag per citazione", _editor_url+"images/ed_quote.gif", false, citazione);
  }
  
  editor.generate();
}


function insertHTML() {
  var html = prompt("Enter some HTML code here");
  if (html) {
    editor.insertHTML(html);
  }
}

function highlight() {
  editor.surroundHTML('<span style="background-color: yellow">', '</span>');
}

function citazione() {
	var sel = editor._getSelection();
	var range = editor._createRange(sel);
	var etichetta=range.text;
	var testo='[citazione]'+etichetta+'[/citazione]';		
	if (HTMLArea.is_ie) {
		range.pasteHTML(testo);
	} else {
		editor.insertHTML(testo);
	}
}
