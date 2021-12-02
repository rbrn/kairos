<?php 
require "../../include/init_sito.inc";
$dir=$_REQUEST[dir];
$base="";
if ($server) $base="kairos/";
if ($server=="localhost") $base="kairos/";
?>
<html>

<head>
  <title>Inserisci File Audio</title>
  <?php 
echo "
<script language=\"JavaScript\" src=\"../../script/funzioni.js\"></script>
<link rel=\"stylesheet\" href=\"../../stili/$cod_area/stile_sito.css\">";
?>
<script type="text/javascript" src="popup.js"></script>

<script type="text/javascript">

I18N = window.opener.HTMLArea.I18N.dialogs;


function i18n(str) {
  return (I18N[str] || str);
};

function Init() {
 __dlg_translate(I18N);
  __dlg_init();
  
  document.getElementById("f_url").focus();
  
};

function onOK() {
  var required = {
    "f_url": "Devi inserire l'URL del file Audio"
  };
  for (var i in required) {
    var el = document.getElementById(i);
    if (!el.value) {
      alert(required[i]);
      el.focus();
      return false;
    }
  }
  // pass data back to the calling window
  var fields = ["f_url"];
  var param = new Object();
  for (var i in fields) {
    var id = fields[i];
    var el = document.getElementById(id);
    param[id] = el.value;
  }
  __dlg_close(param);
  return false;
};

function onCancel() {
  __dlg_close(null);
  return false;
};


function seleziona_immagine() {
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

    var newwin = window.open("/<?php echo($base);?>index.php?risorsa=materiali_cartella&dir=<?php echo($dir);?>&tipo=audio","",""+ settings +" left="+ lx +", top="+ tx +"");
    return false;
}

</script>

<style type="text/css">
html, body {
  background: ButtonFace;
  color: ButtonText;
  font: 11px Tahoma,Verdana,sans-serif;
  margin: 0px;
  padding: 0px;
}
body { padding: 5px; }
table {
  font: 11px Tahoma,Verdana,sans-serif;
}
form p {
  margin-top: 5px;
  margin-bottom: 5px;
}
.fl { width: 9em; float: left; padding: 2px 5px; text-align: right; }
.fr { width: 6em; float: left; padding: 2px 5px; text-align: right; }
fieldset { padding: 0px 10px 5px 5px; }
select, input, button { font: 11px Tahoma,Verdana,sans-serif; }
button { width: 70px; }
.space { padding: 2px; }

.title { background: #ddf; color: #000; font-weight: bold; font-size: 120%; padding: 3px 10px; margin-bottom: 10px;
border-bottom: 1px solid black; letter-spacing: 2px;
}
form { padding: 0px; margin: 0px; }
</style>

</head>

<body onload="Init()">

<div class="title">Inserisci File Audio</div>
<!--- new stuff --->
<form action="" method="get" name="modulo" id="modulo">
<table border="0" width="100%" style="padding: 0px; margin: 0px">
  <tbody>

  <tr>
    <td style="width: 7em; text-align: right">URL del file Audio:</td>
    <td><input type="text" name="url" id="f_url" style="width:75%">
    </td>
  </tr>
  
   <tr>
    <td></td>
	<td><a href="javascript:;" onclick="return seleziona_immagine();"><span><?php echo($stringa[elenco_suoni]);?></span></a></td>
  </tr>
  

  </tbody>
</table>

<p />


<br clear="all" />
<table width="100%" style="margin-bottom: 0.2em">
 <tr>
  <td valign="bottom" style="text-align: right">
    <button type="button" name="ok" onclick="return onOK();">OK</button><br>
    <button type="button" name="cancel" onclick="return onCancel();">Cancel</button>
  </td>
 </tr>
</table>
</form>
</body>
</html>
