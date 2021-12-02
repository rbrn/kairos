<?php

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

?>
<?php
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>" . strtoupper($stringa[area_admin]) . "</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>" . strtoupper($stringa[gestione_utenti]) . "</b></span>
</td></tr>

<tr>
<td valign=top width=100%><span class=testo><b>" . strtoupper($stringa[registrazione_manuale]) . "</b></span>
</td></tr>
";


echo "
<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>";


echo "<tr><td>";
?>

<TABLE border=0 width=500>
    <TR>
        <TD>
            <FORM action=registra_manuale.php method=post>
<span class=testopiccolo>
<?php echo($stringa[modifica_intro]); ?>
</span>
                <TABLE border=0>
                    <TR>
                        <TD colSpan=2></TD>
                    </TR>
                    <TR>
                        <TD colSpan=2></TD>
                    </TR>
                    <TR>
                        <TD colSpan=2></TD>
                    </TR>
                    <TR>
                        <TD align=right><span class=testopiccolo><b><?php echo($stringa[identificativo]); ?></b></span>
                        </TD>
                        <TD><INPUT name=id_utente size=10><br><span
                                class=testopiccolo> <i><?php echo($stringa[id_guida]); ?></i></span></TD>
                    </TR>

                    <TR>
                        <TD align=right><span class=testopiccolo><b><?php echo($stringa[password]); ?></b></span></TD>
                        <TD><INPUT name=pwd_utente size=10></TD>
                    </TR>


                    <TR>
                        <TD align=right><span class=testopiccolo><b><?php echo($stringa[stato]); ?></b></span></TD>
                        <TD>
                            <select name="stato">
                                <option value=1 selected><?php echo($stringa[utente]); ?></option>
                                <option value=2><?php echo($stringa[staff]); ?></option>
                                <option value=3><?php echo($stringa[admin]); ?></option>
                            </select>
                        </TD>
                    </TR>


                    <TR>
                        <TD align=right><span class=testopiccolo><b><?php echo($stringa[nome]); ?></b></span></TD>
                        <TD>
                            <INPUT name=nome size=35></TD>
                    </TR>
                    <TR>
                        <TD align=right><span class=testopiccolo><b><?php echo($stringa[cognome]); ?></b></span></TD>
                        <TD><INPUT name=cognome size=35></TD>
                    </TR>

                    <TR>
                        <TD align=right><span class=testopiccolo><b><?php echo($stringa[email]); ?></b></span></TD>
                        <TD><INPUT name=email size=35></TD>
                    </TR>


                    <?php
                    if ($cod_area == 'kairos_larimart') require "./include/seleziona_gruppo_larimart.inc";
                    ?>


                    <?php
                    if ($cod_area <> "kairos_larimart") {
                        ?>



                        <TR>
                            <TD align=right vAlign=top><span
                                    class=testopiccolo><b><?php echo($stringa[indirizzo]); ?></b></span></TD>
                            <TD><INPUT name=indirizzo size=35></TD>
                        </TR>


                        <TR>
                            <TD align=right><span class=testopiccolo><b><?php echo($stringa[cap]); ?></b></span></TD>
                            <TD><INPUT maxLength=5 name=cap size=5></span></TD>
                        </TR>
                        <TR>
                            <TD align=right><span class=testopiccolo><b><?php echo($stringa[citta]); ?></b></span></TD>
                            <TD><INPUT name=citta size=35></TD>
                        </TR>
                        <TR>
                            <TD align=right><span class=testopiccolo><b><?php echo($stringa[prov]); ?></b></span></TD>
                            <TD><INPUT maxLength=2 name=prov size=2></TD>
                        </TR>
                        <TR>
                        <TR>
                            <TD align=right><span class=testopiccolo><b><?php echo($stringa[scuola]); ?></b></span></TD>
                            <TD><INPUT name=scuola size=35></TD>
                        </TR>
                        <TR>
                            <TD align=right><span class=testopiccolo><b><?php echo($stringa[telefono]); ?></b></span>
                            </TD>
                            <TD><INPUT name=telefono size=35></TD>
                        </TR>


                        <TR>
                        <TR>
                            <TD align=right><span class=testopiccolo><?php echo($stringa[sitoweb]); ?></span></TD>
                            <TD><INPUT name=sitoweb size=35 value="http://"></span></TD>
                        </TR>
                        <TR>
                            <TD align=right><span class=testopiccolo><?php echo($stringa[sesso]); ?></span></TD>
                            <TD><INPUT name=sesso type=radio value="M"><span
                                    class=testopiccolo><?php echo($stringa[m]); ?></span><INPUT name=sesso type=radio
                                                                                                value="F"><span
                                    class=testopiccolo><?php echo($stringa[f]); ?></span></TD>
                        </TR>
                        <TR>
                            <TD align=right><span class=testopiccolo><?php echo($stringa[eta]); ?></span></TD>
                            <TD><INPUT name=eta size=10>
                            </TD>
                        </TR>

                        <TR>
                            <TD align=right><span class=testopiccolo><?php echo($stringa[interessi]); ?></span></TD>
                            <TD><INPUT name=interesse size=35></TD>
                        </TR>

                        <?php
                        echo "
				<TR>
                <TD align=right><span class=testopiccolo><b>$stringa[ruolo_scuola]</b></span></TD>
                <TD><SELECT name=ruolo_scuola size=1> 
					<OPTION value=\"Dirigente\">$stringa[dirigente]</OPTION>
					<OPTION selected value=\"Insegnante\">$stringa[insegnante]</OPTION> 
					<OPTION value=\"Studente\">$stringa[studente]</OPTION>
					<OPTION value=\"Altro\">$stringa[altro]</OPTION>
					<OPTION value=\"Nessuno\">$stringa[nessun_ruolo]</OPTION>
					</SELECT>
			  </TD>
			  </TR>
			  
			  <TR>
               <TD align=right valign=top> 
                   <span class=testopiccolo>$stringa[materia_insegnata]</span>
				</TD>	
                <TD><INPUT name=materia size=50>
				<br><span class=testopiccolo>($stringa[guida_materia_insegnata])</span></TD>
				</TR>
			  ";
                        ?>

                        <?php
                        if ($cod_area == 'kairos_fortic') {
                            ?>
                            <TR>
                                <TD align=right><INPUT type=checkbox name=tutor_fortic></TD>
                                <TD><span class=testopiccolo><b>Sono tutor di un corso ForTIC</b> presso:</span><input
                                        type=text name=scuola_fortic size=20></TD>
                            </TR>
                        <?php }; ?>

                    <?php
                    };
                    ?>

                    <?php
                    if ($cod_area <> 'kairos_larimart') require "./include/seleziona_corso.inc";
                    ?>

                    <TR>
                        <TD align=left colspan=2 valign=top>
			<span class=testopiccolo>
<?php echo($stringa[registrazione_man_guida]); ?>
</span>
                        </TD>
                    </TR>
                    <TR>
                        <TD align=center colspan=2 valign=top>
                            <INPUT type=submit value="<?php echo($stringa[ok]); ?>">
                        </TD>
                    </TR>
                </TABLE>
                <BR>
            </FORM>

        </TD>
    </TR>
</TABLE>

</td></tr>
</table>
<br>

<?php

echo "</div>
</div>
</div>
</div>
</div>";

?>
