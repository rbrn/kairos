<!-- CONTENUTO DELLA PAGINA -->
<script language="javascript">
    function seleziona_corso(targ, id_corso, selObj) {
        var id_edizione = selObj.options[selObj.selectedIndex].value;
        if (id_edizione)  eval(targ + ".location='set_corso.php?id_corso=" + id_corso + "&id_edizione=" + id_edizione + "'");
    }
</script>
<div class="container">
<div>

    <h1>
        <span class="glyphicon glyphicon-home"></span> Dashboard
        <small>
            <i class="icon-double-angle-right"></i>
            overview
        </small>
    </h1>
</div>
<div class="alert alert-block alert-success">
    <button type="button" class="close" data-dismiss="alert">
        <span class="glyphicon glyphicon-remove"/>
    </button>
    <span class="glyphicon glyphicon-ok green"></span>
    Welcome to
    <strong class="green">
        Kairos
        <small>(v2.0)</small>
    </strong>
    , multimedia learning framework for teachers and students
</div>

<table width="100%" border="0" cellspacing=2 cellpadding=0>
<tr>
<!-- PRIMA COLONNA -->

<!-- BOX LOGIN --->
<?php

if (!isset($kairos_cookie[0]) and in_array($cod_area, $kairos_pubblici)) {
    echo "
<td width=\"15%\" valign=\"top\">";

    echo "
 <table width=\"170\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
              <tr> 
                <td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testo\" height=\"21\"> 
		  <span class=testonegativo><b>$stringa[login]</b></span>
		  		</td>

        </tr>";

    echo "
		<tr><td valign=\"top\" align=\"center\">";

    echo "
        <table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
		<tr> 
          <td valign=\"top\">";

    echo "<span class=testopiccolo>Per accedere a quest'area &egrave; necessario essere utenti registrati di <a href=\"http://www.garamond.it\">Garamond</a> ";
    echo " e fare Login dalla relativa <a href=\"\"> Home Page</a></span>";
    echo "</td></tr></table>";

    echo "</td></tr>";


    echo "</table>";

};

if (!isset($kairos_cookie[0]) and !in_array($cod_area, $kairos_pubblici)) {
    echo "
<td width=\"15%\" valign=\"top\">";


    echo "
 <table width=\"170\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
              <tr> 
                <td width=\"100%\" align=\"center\" valign=\"middle\" class=\"testo\" height=\"21\"> 
		  <span class=testonegativo><b>$stringa[login]</b></span>
		  		</td>

        </tr>";

    echo "
		<tr><td valign=\"top\" colspan=\"3\" align=\"center\">";


    echo "
        <table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"100%\">
		<tr> 
          <td valign=\"top\">
		  <form action=login.php method=post name=login id=login>
			<input type=hidden name=risorsa value=\"index\">
            <table width=\"144\" border=\"0\" align=\"center\" bgcolor=\"$colore_sfondo\">
              <tr> 
                <td width=\"23\"> 
                  <div align=\"center\"><span class=testopiccolo><b>$stringa[id]</b></div>
                </td>
               <td width=\"83\"> 
                  <input class=\"testopiccolo\" type=\"text\" name=\"id_utente_form\" size=\"12\">
                </td>
                <td width=\"22\"> </td>
              </tr>
              <tr> 
                <td width=\"23\" height=\"23\"> 
                  <div align=\"center\"><span class=testopiccolo><b>$stringa[pw]</b></div>
                </td>
                <td width=\"83\" height=\"23\"> 
                  <input class=\"testopiccolo\" type=\"password\" name=\"pwd_utente_form\" size=\"12\">
                </td>
                <td width=\"22\" height=\"23\">
				<INPUT class=\"testopiccolo\" TYPE=\"submit\" NAME=\"login\" value=$stringa[ok]>
				</td>
				</form>
              </tr>
               <tr> 
                <td colspan=\"3\"> 
                  <div align=\"center\"><span class=testopiccolo><a href=index.php?risorsa=chiedi_pwd>$stringa[dimenticato_pw]</a></span></div>
					<hr size=1>";
    if ($cod_area <> 'kairos_area_corsi' and $cod_area <> 'kairos_master' and $cod_area <> 'kairos_eprof' and $cod_area <> "kairos_masterunitus") {
        echo "
					<div align=\"center\"><span class=testopiccolo>$stringa[avere_id] <a href=index.php?risorsa=registrazione><b>$stringa[registrarsi]</b></a>.</span></div>";
    };
    if ($cod_area == 'kairos_eprof') {
        echo "
					<div align=\"center\"><span class=testopiccolo><a href=\"\" target=\"_blank\">Mi abbono</a></span></div>";
    };
    echo "
				</td>
              </tr>
            </table>
          </td>
        </tr>
		</td></tr>
		</table>
		";

    echo "
</table>";

    if (($cod_area == "kairos_master" or $cod_area == "kairos_masterunitus") and 0) {
        echo "
<br>
<div align=\"center\">
<a href=\"http://www.amicascuola.it\" target=_blank><img src=\"img/$cod_area/rcs_logo.gif\" width=\"121\" height=\"50\" alt=\"RCS Education\" border=\"0\"></a></div>";
    };

    if ($cod_area == "kairos_librinrete") {
        echo "
<br>
<div align=\"center\">
<a href=\"http://www.garamond.it\" target=_blank><img src=\"img/$cod_area/garamondino.gif\" width=\"100\" height=\"30\" alt=\"Garamond Editoria e Formazione\" border=\"0\"></a></div>";
    };

    echo "
 </td>
 <td valign=top width=1 bgcolor=#cccccc>
	<img src=\"img/pixel.gif\" width=\"1\" height=\"1\" alt=\"\" border=\"0\">
</td>
";
};

if ($kairos_cookie[0]) {
    echo "
<td width=\"15%\" valign=\"top\">";


    echo "
 <table width=\"170\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
              <tr> 
                <td width=\"10\" valign=\"top\" height=\"21\">&nbsp; </td>
                <td width=\"100%\" valign=\"middle\" class=\"testonegativo\" height=\"21\"> 
                  <div align=\"left\"><img src=\"img/ico_corsobn.gif\" width=\"21\" height=\"16\" align=\"absmiddle\">";

    if ($cod_area == 'kairos_larimart') {
        echo "PROFILI";
    } else {
        echo $stringa[corsi];
    };


    echo "</div>
                </td>
                <td width=\"8\" valign=\"top\" height=\"21\"> 
                  <div align=\"right\"></div>
                </td>
              </tr>
";


    echo "

<tr><td valign=\"top\" colspan=\"3\" >

<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo\" width=\"80%\">
<tr>

<td valign=\"top\">";


    $query = "";

    if ($ruolo <> 'staff' and $ruolo <> 'admin' and ($cod_area <> 'kairos_area_corsi')) {
        $query = "SELECT corso.descrizione,corso.id_corso,iscrizioni_corso.id_edizione,edizioni.descrizione as descr_edizione FROM corso,iscrizioni_corso,edizioni WHERE
corso.id_corso=iscrizioni_corso.id_corso AND iscrizioni_corso.id_corso=edizioni.id_corso AND iscrizioni_corso.id_edizione=edizioni.id_edizione AND 
edizioni.stato='attiva' AND 
iscrizioni_corso.id_utente='$id_utente' ORDER BY corso.id_corso,iscrizioni_corso.id_edizione DESC";
    };


    if ($ruolo == 'staff' or $ruolo == 'admin') {
        $query = "SELECT corso.descrizione,corso.id_corso,edizioni.id_edizione,edizioni.descrizione as descr_edizione FROM corso,edizioni WHERE
corso.id_corso=edizioni.id_corso AND 
edizioni.stato='attiva'  ORDER BY corso.id_corso,edizioni.id_edizione DESC";
    };


    if ($query) {
        $result = $mysqli->query($query);
        while ($riga = $result->fetch_array()) {
            $id_corso = $riga["id_corso"];
            $descrizione = $riga["descrizione"];
            $id_edizione = $riga["id_edizione"];
            $descr_edizione = $riga["descr_edizione"];

            $id_corso_array[] = $id_corso;
            $descrizione_array[] = $descrizione;
            $id_edizione_array[] = $id_edizione;
            $descr_edizione_array[] = $descr_edizione;
        };
    };


    if ($ruolo <> 'staff' and $ruolo <> 'admin' and ($cod_area == 'kairos_area_corsi')) {
        $query = "SELECT corso.descrizione,corso.id_corso,edizioni.id_edizione,edizioni.descrizione as descr_edizione FROM corso,edizioni WHERE
corso.id_corso=edizioni.id_corso AND 
edizioni.stato='attiva'  ORDER BY corso.id_corso,edizioni.id_edizione DESC";
        $result = $mysqli->query($query);


        $corso_att = "";
        $ultima_ed = "";
        while ($riga = $result->fetch_array()) {
            $id_corso = $riga["id_corso"];
            $descrizione = $riga["descrizione"];
            $id_edizione = $riga["id_edizione"];
            $descr_edizione = $riga["descr_edizione"];

            if ($corso_att <> $id_corso) {
                $ultima_ed = $id_edizione;
            };

            $query_i = "SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso' AND id_edizione='$id_edizione' AND id_utente='$id_utente'";
            $result_i = $mysqli->query($query_i);
            $iscritto_edizione = $result_i->num_rows;
            /*
            $query_i="SELECT * FROM iscrizioni_corso WHERE id_corso='$id_corso'  AND id_utente='$id_utente'";
$result_i=$mysqli->query($query_i);
            $iscritto_corso=$result_i->num_rows;
            */

            $query_i = "SELECT edizioni.id_edizione,edizioni.descrizione as descr_edizione FROM iscrizioni_corso,edizioni WHERE iscrizioni_corso.id_corso='$id_corso' AND
iscrizioni_corso.id_corso=edizioni.id_corso AND iscrizioni_corso.id_edizione=edizioni.id_edizione AND iscrizioni_corso.id_utente='$id_utente' AND
edizioni.stato='attiva'";
            $result_i = $mysqli->query($query_i);
            $iscritto_edizione_attiva = $result_i = $mysqli->query($query_i);

            $prendi = false;
            if ($iscritto_edizione_attiva) $prendi = true;

            if ($ultima_ed == $id_edizione) {
                if ($iscritto_edizione) {
                    $prendi = true;
                } else {
                    $prendi = false;
                };
            };
            $corso_att = $id_corso;


            if ($prendi) {
                $id_corso_array[] = $id_corso;
                $descrizione_array[] = $descrizione;
                $id_edizione_array[] = $id_edizione;
                $descr_edizione_array[] = $descr_edizione;
            };
        };

    };


    $corso_att = "";
    for ($i = 0; $i < count($id_corso_array); $i++) {
        $id_corso = $id_corso_array[$i];
        $descrizione = $descrizione_array[$i];
        $id_edizione = $id_edizione_array[$i];
        $descr_edizione = $descr_edizione_array[$i];

        $tag_icona = "";
        if ($ruolo <> 'staff' and $ruolo <> 'admin' and $cod_area == 'kairos_larimart') {
            $icona = verifica_corso($id_utente, $id_corso, $id_edizione);
            if ($icona) {
                $tag_icona = "<img src=\"img/forum/$icona.gif\" width=15 height=15>";
            };
        };

        if ($cod_area <> 'kairos_larimart') {
            if ($corso_att <> $id_corso) {
                if ($corso_att) {
                    echo "
			</select><br><br>
			<div class=\"bordotab\">&nbsp;</div><br>";
                };

                echo "
			<div class=bordo>
			<span class=testopiccolo>
			<b>$descrizione</b>
			</span>
			</div>
			<select class=testopiccolo onChange=\"seleziona_corso('parent','$id_corso',this)\">
			<option value=''>($stringa[seleziona_edizione])";
            };
            $label = $descr_edizione;
            $selected = "";
            if (!$label) $label = $id_edizione;
            if ($id_corso == $id_corso_s and $id_edizione == $id_edizione_s) $selected = "selected";
            echo "<option value=\"$id_edizione\" $selected>$label";
            $corso_att = $id_corso;
        } else {
            echo "<span class=testopiccolo><a href=set_corso.php?id_corso=$id_corso&id_edizione=$id_edizione>$descrizione</a>";
            echo "$tag_icona";
            echo "</span><br>";
        };
    };

    if ($corso_att) {
        echo "
	</select>";
    };

    echo "</td></tr>
</table>";


    echo "
</td></tr>
</table>";



    if ($cod_area == "kairos_librinrete") {
        echo "
<br>
<div align=\"center\">
<a href=\"http://www.garamond.it\" target=_blank><img src=\"img/$cod_area/garamondino.gif\" width=\"100\" height=\"30\" alt=\"Garamond Editoria e Formazione\" border=\"0\"></a></div>";
    };

    echo "
</td>";
    /*
    echo "
    <td valign=top width=1 bgcolor=#cccccc>
    <img src=\"img/pixel.gif\" width=\"1\" height=\"1\" alt=\"\" border=\"0\">
    </td>
    ";
    */

    echo "
<td valign=top width=05>
<img src=\"img/pixel.gif\" width=\"05\" height=\"1\" alt=\"\" border=\"0\">
</td>
";

};

?>
<!-- FINE BOX LOGIN -->


<!-- SECONDA COLONNA -->


<?php

if (!isset($kairos_cookie[0])) {
    echo "<td valign=\"TOP\" width=\"60%\" align=left>";
} else {
    echo "<td valign=\"TOP\" width=\"60%\" align=left>";
};


$link_nuova = "";
if ($ruolo == 'admin' or $ruolo == 'staff') {
    $link_nuova = "[<a href=index.php?risorsa=news_crea&tipo_news=0>$stringa[nuova_news]</a>]";
};

?>
<div class="panel panel-info">
    <div class="panel-heading">
        <h3 class="panel-title"><?=$stringa[news_direzione]?></h3>
    </div>
    <div class="panel-body">

        <?php

        require "./include/hp_news.inc";

        if ($id_corso_s) {
            echo "
		<table border=0 cellspacing=5 cellpadding=0 width=100%>";

            echo "<tr>";
            echo "<td  valign=top>";
            require "./include/hp_lo.inc";
            echo "</td>";
            echo "</tr>";

            echo "<tr><td valign=top>";
            require "./include/hp_cal.inc";
            echo "</td>";
            echo "</tr>";

            echo "
		<tr><td valign=top>";
            require "./include/hp_forum.inc";
            echo "</td></tr>";

            echo "<tr>";
            echo "<td  valign=top>";
            require "./include/hp_lab.inc";
            echo "</td>";
            echo "</tr>";
            echo "</table>";


        };


        ?>
    </div>
</div>


</td>
<!-- FINE SECONDA COLONNA -->

<td valign=top width=05>
    <img src="img/pixel.gif" width="05" height="1" alt="" border="0">
</td>



<?php
if (!isset($kairos_cookie[0])) {
    echo "<td valign=\"TOP\" width=\"30%\" align=left>";
} else {
    echo "<td valign=\"TOP\" width=\"30%\" align=left>";
};

echo "
 <table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\">
              <tr>
                <td width=\"100%\" valign=\"middle\" class=\"testonegativo\" height=\"21\">";


?>

<div class="panel panel-success">
    <div class="panel-heading">
        <h3 class="panel-title"><span class="glyphicon glyphicon-user"></span> <?=$stringa[news_iscritti]?></h3>
    </div>
    <div class="panel-body">
        <p class=testopiccolo><?=$stringa[modifica_sezione]?></p>
        <a href="index.php?risorsa=news_crea&tipo_news=1" style="padding-top: 20px;">
            <span class="glyphicon glyphicon-edit"></span> <?=$stringa[nuova_news]?></a>
    </div>

</div>


<?php

echo "</div>
                </td>
              </tr>
";

echo "
<td valign=\"top\">";


if ($id_corso_s) {
    $query = "SELECT id_news,url,url_label,testo,id_utente,date_format(data_news,\"%d/%m/%Y\") as data_n FROM hp_news where tipo=1 AND id_corso='$id_corso_s' AND id_edizione='$id_edizione_s' ORDER BY data_news DESC";
    $result = $mysqli->query($query);

    $news = 1;
    while (($item_news = $result->fetch_array(MYSQLI_ASSOC)) and $news <= 5) {
        $id_news = $item_news["id_news"];
        $titolo = $item_news["url_label"];
        $url = $item_news["url"];
        $testo = $item_news["testo"];
        $id_autore = $item_news["id_utente"];
        $data_news = $item_news["data_n"];

        //$testo = str_replace("\n","<br>",$testo);
        //$testo = parse_link($testo);

        echo "
				<span class=testopiccolo>";

        echo "
				<b><a class=miolink href=\"javascript:;\" title=\"$stringa[clicca_per_sapere_chi]\" onclick=\"javascript:apri_scheda('scheda_utente.php?id_utente=$id_autore',                   'myRemoteUtente',        'height=450,width=500,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=1,scrollbars=1,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowUtente');\">($id_autore)</a></b>
				";

        echo "<br>$data_news";
        if (($id_autore == $id_utente) or $ruolo == 'admin') {
            echo "<a href=index.php?risorsa=news_mod&tipo_news=1&id_news=$id_news onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_mod_$id_news','','img/ico_modifica_over.gif',1)\"><img src=\"img/ico_modifica.gif\" width=\"20\" height=\"20\" alt=\"$stringa[modifica]\" border=\"0\" name=\"img_mod_$id_news\" vspace=\"5\"></a>&nbsp;
            <a href=index.php?risorsa=msg&msg=conf_canc&pagina=news_delete.php&tipo_news=1&id_news=$id_news onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_news','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_news\" vspace=\"5\"></a>\n";
        };

        echo "<br>";

        if ($url) {
            if (!eregi("^http://", $url)) {
                $url = "http://" . $url;
            };
            echo "
					<b><a href=$url target=_blank>$titolo</a></b>";
        } else {
            echo "
					<b>$titolo</b>";
        };

        echo "
				<br>$testo<br>";

        echo "</span><br>";
        $news++;
    };
};


?>
</td>
</tr>
</table>
</td>
</tr>
</table>
</td>
</tr>
</table>

</div> <!--end of container-->

<!-- FINE CONTENUTO DELLA PAGINA -->
