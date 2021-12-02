<?php 
require "../../include/init_sito.inc";
$dir=$_REQUEST[dir];
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


function onTargetChanged() {
  var f = document.getElementById("f_other_target");
  if (this.value == "_other") {
    f.style.visibility = "visible";
    f.select();
    f.focus();
  } else f.style.visibility = "hidden";
};

function onTipoChanged() {
  
  var fx = document.getElementById("f_x");
  var fy = document.getElementById("f_y");
  
  if (this.value=="normale") {
  	  fy.style.visibility = "hidden";
  	  fx.style.visibility = "hidden";
  } else {
  	 fx.style.visibility = "visible";
    fx.select();
    fx.focus();
    fy.style.visibility = "visible";
  }	
};


function Init() {
  __dlg_translate(I18N);
  __dlg_init();
  var param = window.dialogArguments;
  var target_select = document.getElementById("f_target");
  var tipo_select = document.getElementById("f_tipo");
  
  if (param) {
      document.getElementById("f_href").value = param["f_href"];
      document.getElementById("f_title").value = param["f_title"];
      comboSelectValue(target_select, param["f_target"]);
      if (target_select.value != param.f_target) {
        var opt = document.createElement("option");
        opt.value = param.f_target;
        opt.innerHTML = opt.value;
        target_select.appendChild(opt);
        opt.selected = true;
      } 
  } else {
      document.getElementById("f_href").value = "http://";
  }
  var opt = document.createElement("option");
  opt.value = "_other";
  opt.innerHTML = I18N["Other"];
  target_select.appendChild(opt);
  target_select.onchange = onTargetChanged;
  tipo_select.onchange = onTipoChanged;
  
  document.getElementById("f_href").focus();
  document.getElementById("f_href").select();
};

function onOK() {
	
  var required = {
    "f_href": "Devi inserire l'URL del link"
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
  var fields = ["f_href", "f_title", "f_target", "f_risorsa", "f_tipo","f_x","f_y"];
  var param = new Object();
  for (var i in fields) {
    var id = fields[i];
    var el = document.getElementById(id);
	param[id] = el.value;
	/*
	if (id=="f_tipo") {
		if (el.checked) {
			param[id]="normale";
		} else {
			param[id]="popup";
		}
	};
    */
	
  }

  if (param.f_target == "_other")
    param.f_target = document.getElementById("f_other_target").value;
	
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
<table border="0" style="width: 100%;">
  <tr>
    <td class="label">URL:</td>
    <td><input type="text" id="f_href" style="width: 100%" /></td>
  </tr>
  
  <tr>
    <td class="label">Risorsa:</td>
    <td><input type="text" id="f_risorsa" style="width: 100%" />
	<?php 
			echo "

[<a href=\"javascript:;\" onclick=\"apri_scheda('../../cerca_pagina_popup.php?campo=f_risorsa&dir=$dir','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]
[<a href=\"javascript:;\" onclick=\"apri_scheda('../../cerca_pagina_popup_op.php?campo=f_risorsa&dir=$dir','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["tutti"]."</a>]
";
?>
	</td>
  </tr>

  
  <tr>
    <td class="label">Title (tooltip):</td>
    <td><input type="text" id="f_title" style="width: 100%" /></td>
  </tr>
  
  <tr>
    <td class="label">Tipo:</td>
    <td><select id="f_tipo">
	<option value="normale"><?php echo($stringa[normale]);?></option>
	<option value="popup"><?php echo($stringa[popup]);?></option>
	</select>
	<input type="text" name="f_x" id="f_x" size="05" value="500" style="visibility: hidden" />
	<input type="text" name="f_y" id="f_y" size="05" value="500"  style="visibility: hidden" />
	
</td>
  </tr>
  
  <tr>
    <td class="label">Target:</td>
    <td><select id="f_target">
      <option value="">Default</option>
      <option value="_blank">New window (_blank)</option>
      <option value="_self">Same frame (_self)</option>
      <option value="_top">Top frame (_top)</option>
    </select>
    <input type="text" name="f_other_target" id="f_other_target" size="10" style="visibility: hidden" />
    </td>
  </tr>
    
</table>

<div id="buttons">
  <button type="button" name="ok" onclick="return onOK();">OK</button>
  <button type="button" name="cancel" onclick="return onCancel();">Cancel</button>
</div>
</form>
</body>
</html>
