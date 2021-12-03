<?php 
require "./include/init_sito.inc";
$dir=$_REQUEST[dir];
?>
<head>
	<title><?php echo($stringa[crea_link]);?></title>

<?php 
echo "
<script language=\"JavaScript\" src=\"script/funzioni.js\"></script>
<link rel=\"stylesheet\" href=\"stili/$cod_area/stile_sito.css\">";
?>
	
</head>
<body bgcolor=white>
<font face="Verdana, Arial, Helvetica, sans-serif" size="2">
<B><?php echo($stringa[crea_link]);?></B></font><BR>

<FORM NAME="form1">

  <TABLE>

    <TR> 

      <TD ALIGN="RIGHT"><font face="Verdana, Arial, Helvetica, sans-serif" size="2">URL:</font></TD>

      <TD> 

        <INPUT TYPE="text" NAME="url" VALUE="http://" SIZE="50">

      </TD>

    </TR>

	<TR> 

      <TD ALIGN="RIGHT"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><?php echo($stringa[id_risorsa]);?>:</font></TD>

      <TD> 

        <INPUT TYPE="text" NAME="risorsa" VALUE="" SIZE="30">
<?php 
			echo "
<span class=\"testopiccolo\">
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_pagina_popup.php?campo=risorsa&dir=$dir','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["cerca"]."</a>]
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_pagina_popup_op.php?campo=risorsa&dir=$dir','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">".$stringa["tutti"]."</a>]
</span>";
?>
		
      </TD>

    </TR>

    <TR> 

      <TD ALIGN="RIGHT"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><?php echo($stringa[tipo]);?>:</font></TD>

      <TD> 

        <INPUT TYPE="radio" NAME="tipo" VALUE="normale" checked><?php echo($stringa[normale]);?>

		<INPUT TYPE="radio" NAME="tipo" VALUE="popup"><?php echo($stringa[popup]);?>

      </TD>

    </TR>

	

    <TR> 

      <TD ALIGN="RIGHT"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><?php echo($stringa[larghezza_finestra]);?>:</font></TD>

      <TD> 

       <INPUT TYPE="text" NAME="x" VALUE="500" SIZE="20">

      </TD>

    </TR>

	

	<TR> 

      <TD ALIGN="RIGHT"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><?php echo($stringa[altezza_finestra]);?>:</font></TD>

      <TD> 

       <INPUT TYPE="text" NAME="y" VALUE="500" SIZE="20">

      </TD>

    </TR>

	

    <TR> 

      <TD ALIGN="RIGHT" VALIGN="top"><font face="Verdana, Arial, Helvetica, sans-serif" size="2"><?php echo($stringa[apro_link]);?>:</font></TD>

      <TD> 

	  <INPUT TYPE="radio" NAME="mio_target" VALUE="_top" checked><?php echo($stringa[stessa_finestra]);?><br>

        <INPUT TYPE="radio" NAME="mio_target" VALUE="_blank"><?php echo($stringa[altra_finestra]);?><br>

     </TD>

    </TR>

    

  </TABLE>



<BR>

<CENTER>

<INPUT TYPE="submit" NAME="submit" VALUE="<?php echo($stringa[crea_link]);?>" 

	onclick="window.opener.InsertLink(form1.url.value,form1.risorsa.value, form1.tipo[0].checked,form1.tipo[1].checked, form1.x.value, form1.y.value, form1.mio_target[0].checked,form1.mio_target[1].checked); window.close();  window.opener.idContent.focus(); ">

<INPUT TYPE="button" NAME="cancel" VALUE="<?php echo($stringa[annulla]);?>" onclick="window.close()">

</center></FORM>





</body>

</html>

