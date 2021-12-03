<?php
echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

$padre = $_REQUEST["padre"];

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>" . strtoupper($stringa[gestione_repository]) . "</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>" . strtoupper($stringa[importa_lo]) . "</b></span>
</td></tr>
";

echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";

echo "
<tr><td>";
?>


    <FORM action="lo_scorm_importa.php" encType=multipart/form-data method=post name=modulo id=modulo>
        <INPUT name=MAX_FILE_SIZE type=hidden value=5097150>
        <TABLE border=0 width=600>
            <TR>
                <TD colSpan=2></TD>
            </TR>


            <TR>
                <TD align=right><span class=testo><STRONG><?php echo($stringa[file_caricare]); ?>:</STRONG></span></TD>
                <TD>
                    <INPUT type="file" name="file">
                </TD>
            </TR>

            <TR>
                <TD align=right><span class=testo><STRONG><?php echo($stringa[url]); ?>:</STRONG></span></TD>
                <TD>
                    <INPUT type="text" name=url size=60>
                </TD>
            </TR>

            <TR>
                <TD align=right><span class=testo><STRONG><?php echo($stringa[titolo]); ?>:</STRONG></span></TD>
                <TD>
                    <INPUT type="text" name=titolo size=60>
                </TD>
            </TR>

            <TR>
                <TD align=right><span class=testo><STRONG><?php echo($stringa[autore]); ?>:</STRONG></span></TD>
                <TD>
                    <INPUT type="text" name=id_autore size=20 value="<?php echo($id_utente); ?>">


                    <?php
                    echo "
<span class=\"testopiccolo\">
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup.php?ruolo=tutti&campo=id_autore','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">" . $stringa["cerca"] . "</a>]
[<a href=\"javascript:;\" onclick=\"apri_scheda('cerca_utenti_popup_op.php?ruolo=tutti&campo=id_autore','cerca_popup','height=450,width=600,alwaysLowered=0,alwaysRaised=1,channelmode=0,dependent=1,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=1','win_cerca_popup')\">" . $stringa["tutti"] . "</a>]
</span>";
                    ?>

                </TD>
            </TR>


            <TR>
                <TD align=right><span class=testo><STRONG><?php echo($stringa[larghezza_finestra]); ?>:</STRONG></span>
                </TD>
                <TD>
                    <INPUT type="text" maxLength=200 name=width
                           size=10 value=800>
                </TD>
            </TR>

            <TR>
                <TD align=right><span class=testo><STRONG><?php echo($stringa[altezza_finestra]); ?>:</STRONG></span>
                </TD>
                <TD>
                    <INPUT type="text" maxLength=200 name=height
                           size=10 value=620>
                </TD>
            </TR>

        </TABLE>
        <BR>

        <P align=center>
            <INPUT type=submit value="<?php echo($stringa[carica]); ?>">
        </P>
    </FORM>
    </td></tr></table>
    <br>

<?php

echo "</div>
</div>
</div>
</div>
</div>";

?>