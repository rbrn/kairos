<?php 
require "../../include/init_sito.inc";
$dir=$_REQUEST[dir];
$base="";
if ($server) $base="kairos/";
if ($server=="localhost") $base="kairos/";
?>
<html>

<head>
  <title>Insert Image</title>
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
  
  var param = window.dialogArguments;
  if (param) {
      document.getElementById("f_url").value = param["f_url"];
      document.getElementById("f_alt").value = param["f_alt"];
      document.getElementById("f_border").value = param["f_border"];
      document.getElementById("f_align").value = param["f_align"];
      document.getElementById("f_vert").value = param["f_vert"];
      document.getElementById("f_horiz").value = param["f_horiz"];
      window.ipreview.location.replace(param.f_url);
  }
  document.getElementById("f_url").focus();
  
};

function onOK() {
  var required = {
    "f_url": "Devi inserire l'URL dell'immagine"
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
  var fields = ["f_url", "f_alt", "f_align", "f_border",
                "f_horiz", "f_vert"];
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

function onPreview() {
  var f_url = document.getElementById("f_url");
  var url = f_url.value;
  if (!url) {
    alert("Devi prima inserire l'URL dell'immagine");
    f_url.focus();
    return false;
  }
  window.ipreview.location.replace(url);
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

    var newwin = window.open("/<?php echo($base);?>index.php?risorsa=materiali_cartella&dir=<?php echo($dir);?>&tipo=img","",""+ settings +" left="+ lx +", top="+ tx +"");
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

<div class="title">Insert Image</div>
<!--- new stuff --->
<form action="" method="get" name="modulo" id="modulo">
<table border="0" width="100%" style="padding: 0px; margin: 0px">
  <tbody>

  <tr>
    <td style="width: 7em; text-align: right">Image URL:</td>
    <td><input type="text" name="url" id="f_url" style="width:75%">
      <button name="preview" onclick="return onPreview();">Preview</button>
    </td>
  </tr>
  
   <tr>
    <td></td>
	<td><a href="javascript:;" onclick="return seleziona_immagine();"><span>Select/Upload Image on server</span></a></td>
  </tr>
  
 
  
  <tr>
    <td style="width: 7em; text-align: right">Alternate Text:</span></td>
    <td><input type="text" name="alt" id="f_alt" style="width:100%"/></td>
  </tr>

  </tbody>
</table>

<p />

<fieldset style="float: left; margin-left: 5px;">
<legend>Layout</legend>

<div class="space"></div>

<div class="fl">Alignment:</div>
<select size="1" name="align" id="f_align"
  title="Positioning of this image">
  <option value=""                             >Not set</option>
  <option value="left"                         >Left</option>
  <option value="right"                        >Right</option>
  <option value="texttop"                      >Texttop</option>
  <option value="absmiddle"                    >Absmiddle</option>
  <option value="baseline" selected="1"        >Baseline</option>
  <option value="absbottom"                    >Absbottom</option>
  <option value="bottom"                       >Bottom</option>
  <option value="middle"                       >Middle</option>
  <option value="top"                          >Top</option>
</select>

<p />

<div class="fl">Border thickness:</div>
<input type="text" name="border" id="f_border" size="5" />

<div class="space"></div>

</fieldset>

<fieldset style="float:right; margin-right: 5px;">
<legend><span>Spacing</span></legend>

<div class="space"></div>

<div class="fr">Horizontal:</div>
<input type="text" name="horiz" id="f_horiz" size="5" />

<p />

<div class="fr">Vertical:</div>
<input type="text" name="vert" id="f_vert" size="5" />

<div class="space"></div>

</fieldset>
<br clear="all" />
<table width="100%" style="margin-bottom: 0.2em">
 <tr>
  <td valign="bottom">
    Image Preview:<br />
    <iframe name="ipreview" id="ipreview" frameborder="0" style="border : 1px solid gray;" height="200" width="300" src=""></iframe>
  </td>
  <td valign="bottom" style="text-align: right">
    <button type="button" name="ok" onclick="return onOK();">OK</button><br>
    <button type="button" name="cancel" onclick="return onCancel();">Cancel</button>
  </td>
 </tr>
</table>
</form>
</body>
</html>
