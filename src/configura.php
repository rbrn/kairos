<?php 
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";
require "./pagine/$cod_area/colori.inc";
require "./pagine/kairos_demo/colori_default.inc";

$id_utente=$kairos_cookie[0];
if (!$id_utente) {
	$msg=$stringa[errore_no_login];
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};

$ruolo=ruolo_utente($id_utente);
if ($ruolo<>'staff' and $ruolo<>'admin') {
	$msg=$stringa[errore_solo_staff];
	$msg=ereg_replace(" ","%20",$msg);
	Header("Location:index.php?risorsa=msg&msg=$msg");
	exit();
};
header("Cache-Control: no-cache");
header("Pragma: no-cache");
echo "
<html>
<head>
<title>$stringa[personalizza_interfaccia]</title>
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">
";
?>
<script language="JavaScript">
var opzione="colore_testo";
var val_opzione="val_colore_testo";

function imposta_opzione() {
	var opzioni=form1.opzione_colore;
	for (var i=0;i<5;i++) {
		if (opzioni[i].checked) {
			opzione=opzioni[i].value;
		};
	};
	val_opzione="val_"+opzione;
};

function imposta_colori_scelti() {
	var opzioni=form1.opzione_colore;
	document.all.colore_testo.style.background='<?php echo($colore_testo);?>';
	document.all.colore_sfondo.style.background='<?php echo($colore_sfondo);?>';
	document.all.colore_sfondo_testata.style.background='<?php echo($colore_sfondo_testata);?>';
	document.all.colore_bordo.style.background='<?php echo($colore_bordo);?>';
	document.all.colore_testonegativo.style.background='<?php echo($colore_testonegativo);?>';
	document.all.colore_link.style.background='<?php echo($colore_link);?>';
};

function imposta_default(campo) {
	if (campo=='colore_testo') {
		document.all.colore_testo.style.background='<?php echo($colore_testo_default);?>';
		document.all.val_colore_testo.value='<?php echo($colore_testo_default);?>';
	};
	
	if (campo=='colore_sfondo') {
		document.all.colore_sfondo.style.background='<?php echo($colore_sfondo_default);?>';
		document.all.val_colore_sfondo.value='<?php echo($colore_sfondo_default);?>';
	};
	
	if (campo=='colore_sfondo_testata') {
		document.all.colore_sfondo_testata.style.background='<?php echo($colore_sfondo_testata_default);?>';
		document.all.val_colore_sfondo_testata.value='<?php echo($colore_sfondo_testata_default);?>';
	};

	if (campo=='colore_bordo') {
		document.all.colore_bordo.style.background='<?php echo($colore_bordo_default);?>';
		document.all.val_colore_bordo.value='<?php echo($colore_bordo_default);?>';
	};	
	
	if (campo=='colore_testonegativo') {
		document.all.colore_testonegativo.style.background='<?php echo($colore_testonegativo_default);?>';
		document.all.val_colore_testonegativo.value='<?php echo($colore_testonegativo_default);?>';
	};
	
	if (campo=='colore_link') {
		document.all.colore_link.style.background='<?php echo($colore_link_default);?>';
		document.all.val_colore_link.value='<?php echo($colore_link_default);?>';
	};
	
	aggiorna_esempio();
};

function capture (color)  {
	document.all.scelta.style.background=color;
	document.all.val_scelta.value=color;
}
 

function click_select (color)  {
	var obj_opzione = document.all(opzione);

	var obj_val_opzione = document.all(val_opzione);
	obj_opzione.style.background=color;
	obj_val_opzione.value=color;
	aggiorna_esempio();
}

function assegna_valore(oggetto) {
	campo=oggetto.name.substr(4);
	color=oggetto.value;
	obj_campo=document.all(campo);
	obj_campo.style.background=color;
	aggiorna_esempio();
};
	
	
function aggiorna_esempio() {
	document.all.esempio_testo.style.color=document.all.val_colore_testo.value;
	document.all.tab1.style.background=document.all.val_colore_sfondo.value;
	document.all.tab1.style.borderColor=document.all.val_colore_bordo.value;
	document.all.tab2.style.background=document.all.val_colore_sfondo.value;
	document.all.tab2.style.borderColor=document.all.val_colore_bordo.value;
	document.all.casella.style.background=document.all.val_colore_bordo.value;
	document.all.casella.style.borderColor=document.all.val_colore_bordo.value;
	document.all.casella2.style.borderColor=document.all.val_colore_bordo.value;
	document.all.testonegativo_txt.style.color=document.all.val_colore_testonegativo.value;
	document.all.testopiccolo_txt.style.color=document.all.val_colore_testo.value;
	document.all.testo_txt.style.color=document.all.val_colore_testo.value;

};

function hex(q) {
	hexa="0123456789abcdef";
	return  hexa.charAt(q >> 4 &  0xf)  +  hexa.charAt(q & 0xf);
}

function palette () {
	var q;
	var compteur=1;
	var cons="<table cellpadding='0' cellspacing='0'><tr>"; 
	for (var k=0; k<256; k+=51){
		for (var i=0; i<256; i+=51){
			for (var j=0; j<256; j+=51){
				if (compteur==36) {
					cons+="</tr><tr>";
					compteur=0;
				} else 
					cons+="<td bgcolor='#"+ hex (k)+""+hex (i)+""+hex (j)+"' onMouseOver='capture(this.bgColor)'  onClick='click_select(this.bgColor)'><a href='#' style='text-decoration:none; cursor:crosshair '>&nbsp;</a></td>";
  				compteur=compteur+1;
			}
		}
	}
	cons+="</tr></table>";
	return cons;
}
</script>
</head>



<body bgcolor=white>
<?php
/*
$file_colori_default="./pagine/kairos_demo/colori_default.inc";
$str_colori_default=join('',file($file_colori_default));

ereg("^.+colore_testo=\"(#[0-9a-zA-X]+)\".+$",$str_colori_default,$arg);
$val_colore_testo_default=$arg[1];

ereg("^.+colore_testonegativo=\"(#[0-9a-zA-X]+)\".+$",$str_colori_default,$arg);
$val_colore_testonegativo_default=$arg[1];
*/
?>
<p><span class=titolopagina><?php echo($stringa[personalizza_interfaccia]);?></span></p>

<FORM NAME="form1" action="configura_op.php" encType="multipart/form-data" method="post">
<INPUT name=MAX_FILE_SIZE type=hidden value=5097150>
<TABLE border=0>

<TR> 
<TD ALIGN="RIGHT" valign=top><span class=testo><b><?php echo($stringa[file_gif_testata]);?></b></span></TD>
<TD valign=top> 
<INPUT type="file" name="file[]" size=40>
</TD>
<td valign=top><input type="checkbox" name="img_testata_default"><span class=testo><?php echo($stringa[reimposta_default]);?></span></td>
</TR>

<TR> 
<TD ALIGN="RIGHT" valign=top><span class=testo><b><?php echo($stringa[file_gif_sfondo]);?></b></span></TD>
<TD valign=top> 
<INPUT type="file" name="file[]" size=40>
</TD>
<td valign=top><input type="checkbox" name="img_sfondo_default"><span class=testo><?php echo($stringa[reimposta_default]);?></span></td>
</TR>

<TR> 
<TD ALIGN="RIGHT" valign=top><span class=testo><b><?php echo($stringa[nome_organizzazione]);?></b></span></TD>
<TD colspan=2 valign=top> 
<INPUT type="text" name="val_nome_org" size=30 value="<?php echo($nome_org);?>">
</TD>
</TR>

</table>

<table border=0>

<TR> 
<TD ALIGN="RIGHT" valign=top><span class=testo><b><?php echo($stringa[colore_testo]);?></b></span></TD>
<TD valign=top> 
<input type="button" id="colore_testo" value="   " name="colore_testo">
<input type="text" size="7" id="val_colore_testo" name="val_colore_testo" value="<?php echo($colore_testo);?>" onChange="assegna_valore(this)">
</TD>
<td valign=top>
<input type="radio" name="opzione_colore" id="opzione_colore" value="colore_testo" checked onclick="imposta_opzione()">
<input type="button" value="default" onclick="imposta_default('colore_testo')">
</td>

<td valign=top rowspan=5>
<table border=0>
<tr><td>
<input type="button" id="scelta" value="   "> <input type="text" size="7" name="val_scelta" value="" height="50">
</td></tr>
<tr><td>
<table border="1">
<tr><td> 
<script language="javascript">
document.write(palette());
</script>
</td></tr>
</table>
</td></tr>
</table>
</td>
</TR>

<TR> 
<TD ALIGN="RIGHT" valign=top><span class=testo><b><?php echo($stringa[colore_sfondo]);?></b></span></TD>
<TD valign=top> 
<input type="button" id="colore_sfondo" value="   " name="colore_sfondo">
<input type="text" size="7" id="val_colore_sfondo" name="val_colore_sfondo" value="<?php echo($colore_sfondo);?>"  onChange="assegna_valore(this)">
</TD>
<td valign=top>
<input type="radio" name="opzione_colore" id="opzione_colore" value="colore_sfondo" onclick="imposta_opzione()">
<input type="button" value="default" onclick="imposta_default('colore_sfondo')">
</td>
</TR>

<TR> 
<TD ALIGN="RIGHT" valign=top><span class=testo><b><?php echo($stringa[colore_sfondo_testata]);?></b></span></TD>
<TD valign=top> 
<input type="button" id="colore_sfondo_testata" value="   " name="colore_sfondo_testata">
<input type="text" size="7" id="val_colore_sfondo_testata" name="val_colore_sfondo_testata" value="<?php echo($colore_sfondo_testata);?>"  onChange="assegna_valore(this)">
</TD>
<td valign=top>
<input type="radio" name="opzione_colore" id="opzione_colore" value="colore_sfondo_testata" onclick="imposta_opzione()">
<input type="button" value="default" onclick="imposta_default('colore_sfondo_testata')">
</td>
</TR>

<TR> 
<TD ALIGN="RIGHT" valign=top><span class=testo><b><?php echo($stringa[colore_bordi]);?></b></span></TD>
<TD valign=top> 
<input type="button" id="colore_bordo" value="   " name="colore_bordo">
<input type="text" size="7" id="val_colore_bordo" name="val_colore_bordo" value="<?php echo($colore_bordo);?>"  onChange="assegna_valore(this)">
</TD>
<td valign=top>
<input type="radio" name="opzione_colore" id="opzione_colore" value="colore_bordo" onclick="imposta_opzione()">
<input type="button" value="default" onclick="imposta_default('colore_bordo')">
</td>
</TR>

<TR> 
<TD ALIGN="RIGHT" valign=top><span class=testo><b><?php echo($stringa[colore_testo_negativo]);?></b></span></TD>
<TD valign=top> 
<input type="button" id="colore_testonegativo" value="   " name="colore_testonegativo">
<input type="text" size="7" id="val_colore_testonegativo" name="val_colore_testonegativo" value="<?php echo($colore_testonegativo);?>"  onChange="assegna_valore(this)">
</TD>
<td valign=top>
<input type="radio" name="opzione_colore" id="opzione_colore" value="colore_testonegativo" onclick="imposta_opzione()">
<input type="button" value="default" onclick="imposta_default('colore_testonegativo')">
</td>
</TR>

<TR> 
<TD ALIGN="RIGHT" valign=top><span class=testo><b><?php echo($stringa[colore_link]);?></b></span></TD>
<TD valign=top> 
<input type="button" id="colore_link" value="   " name="colore_link">
<input type="text" size="7" id="val_colore_link" name="val_colore_link" value="<?php echo($colore_link);?>"  onChange="assegna_valore(this)">
</TD>
<td valign=top>
<input type="radio" name="opzione_colore" id="opzione_colore" value="colore_link" onclick="imposta_opzione()">
<input type="button" value="default" onclick="imposta_default('colore_link')">
</td>
</TR>
</TABLE>
<BR>
<INPUT TYPE="submit" NAME="submit" VALUE="<?php echo($stringa[ok]);?>">
</FORM>

<hr size=1>

<span class=testo id="esempio_testo"><?php echo($stringa[str1]);?></span>
<br>
<table width=100% border=0 cellspacing=2 cellpadding=0>
<tr><td align=left>
<table id="tab1" width="152" border="1" cellpadding="0" cellspacing="0" bgcolor="<?php echo($colore_sfondo);?>" bordercolor="<?php echo($colore_bordo);?>">
<tr> 
<td id="casella" height="27" valign="top" align=center bgcolor=<?php echo($colore_scuro);?> >
<span class=testopiccolonegativo id="testonegativo_txt"><b><?php echo($stringa[str2]);?></b></span>
</td>
</tr>

<tr> 
<td valign="top" id="casella2">
<table id="tab2" width="144" border="0" align="center" bgcolor="<?php echo($colore_sfondo);?>">
<tr> 
<td> 
<span class=testopiccolo id="testopiccolo_txt"><b><?php echo($stringa[str3]);?></b>
</td>
</tr>
<tr>
<td> 
<span class=testo id="testo_txt"><?php echo($stringa[str4]);?></span>
</td>
</tr>
</table>
</td>
</tr>
</table>
</td></tr>
</table>
<script language="javascript">
imposta_colori_scelti()
</script>
</body>
</html>

