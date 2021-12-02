<?php
$cod_area=$kairos_cookie[4];
$risorsa_padre = $_REQUEST['risorsa_padre'];
$contesto = $_REQUEST['contesto'];
if (!$cod_area) $cod_area="kairos_demo";
require "../pagine/$cod_area/colori.inc";
$server=$_SERVER["SERVER_NAME"];

$base="";
if ($server) $base="kairos/";
if ($server=="localhost") $base="kairos/";
?>


var editor = null;
function initEditor() {

  editor = new HTMLArea("testo");

  var cfg = editor.config; 
  //cfg.hideSomeButtons(" htmlmode ");  
  

<?php
  switch ($contesto) 	{

	case "lo": 
?>
	cfg.pageStyle = "body { background-color: #ffffff; color:<?php echo($colore_testo);?>;}";
  	cfg.hideSomeButtons(" underline strikethrough createlink inserttable "); 
<?php break;?>

<?php
	case "news": 
?>
	cfg.pageStyle = "body { background-color: #ffffff; color:<?php echo($colore_testo);?>;}";
  	cfg.hideSomeButtons(" underline strikethrough createlink inserttable "); 
<?php break;?>

<?php }; ?>


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
