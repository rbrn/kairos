<?php 
require "../../include/init_sito.inc";
$risorsa_padre=$_REQUEST["risorsa_padre"];
?>
<html>

<head>
  <title>Insert/Modify Link</title>
  <?php 
echo "
<script language=\"JavaScript\" src=\"../../script/funzioni.js\"></script>
<link rel=\"stylesheet\" href=\"../../stili/$cod_area/stile_sito.css\">";
?>

  <script type="text/javascript" src="popup.js"></script>
  <script type="text/javascript">
   // window.resizeTo(400, 200);


I18N = window.opener.HTMLArea.I18N.dialogs;


function i18n(str) {
  return (I18N[str] || str);
};


function Init() {
  __dlg_translate(I18N);
  __dlg_init();
  var param = window.dialogArguments;


};

function onOK() {
	
  var required = {
    "f_risorsa": "Devi selezionare la pagina da linkare"
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
  var fields = ["f_title", "f_risorsa", "f_tipo"];
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
select, input, button { font: 11px Tahoma,Verdana,sans-serif; }
button { width: 70px; }
table .label { text-align: right; width: 8em; }

.title { background: #ddf; color: #000; font-weight: bold; font-size: 120%; padding: 3px 10px; margin-bottom: 10px;
border-bottom: 1px solid black; letter-spacing: 2px;
}

#buttons {
      margin-top: 1em; border-top: 1px solid #999;
      padding: 2px; text-align: right;
}
</style>

</head>

<body  onload="Init()">
<div class="title">Insert/Modify Link</div>

<form name="form1" id="form1">
<input type="hidden" name="f_tipo" id="f_tipo">
<table border="0" style="width: 100%;">
  <tr>
    <td class="label">Pagina:</td>
    <td><input type="text" id="f_str_risorsa" style="width: 100%" readonly />
	<input type="hidden" name="f_risorsa" id="f_risorsa" />
	<?php 
			echo "

[<a href=\"javascript:;\" onclick=\"apri_scheda('../../index.php?risorsa=repository_cartella&id_cartella=$risorsa_padre','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]
";
?>
	</td>
  </tr>

  
  <tr>
    <td class="label">Title (tooltip):</td>
    <td><input type="text" id="f_title" style="width: 100%" /></td>
  </tr>
  

 
</table>

<div id="buttons">
  <button type="button" name="ok" onclick="return onOK();">OK</button>
  <button type="button" name="cancel" onclick="return onCancel();">Cancel</button>
</div>
</form>
</body>
</html>
