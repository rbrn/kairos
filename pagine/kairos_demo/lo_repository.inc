<?php
echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";
$pagina = $_REQUEST["pagina"];
$pag_size = $_REQUEST["pag_size"];
$filtro = $_REQUEST["filtro"];
$titolo_cerca = trim($_REQUEST["titolo_cerca"]);
$materia_cerca = trim($_REQUEST["materia_cerca"]);

if (!isset($filtro) or $filtro <> "on") {
    $filtro = "";
};

if (!isset($pagina) or empty($pagina)) {
    $pagina = 1;
};


if (!isset($pag_size) or empty($pag_size)) {
    $pag_size = 20;
};


$ruolo = ruolo_utente($id_utente);

$elenco_lo = "";
$query = "SELECT id_lo FROM lo_ordine_lo,lo_ordine_codici WHERE lo_ordine_lo.id_ordine=lo_ordine_codici.id_ordine AND lo_ordine_codici.id_utente='$id_utente'";
$result = $mysqli->query($query);

    while ($result && $riga = $result->fetch_array()) {
        $id_lo = $riga["id_lo"];
        if (strpos($elenco_lo, $id_lo) === false)
            $elenco_lo .= "'$id_lo',";
    };

if ($elenco_lo) $elenco_lo = substr($elenco_lo, 0, strlen($elenco_lo) - 1);

?>

<?php

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>Repository Learning Object</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"index.php?risorsa=lo_repository_cerca\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"index.php?risorsa=lo_repository_cerca\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">Imposta criterio di ricerca</a></span>";

echo "&nbsp;&nbsp;<span class=testopiccolo>[<a href=\"index.php?risorsa=lo_repository_add_licenza\">Inserisci codice di accesso</a>]</span>";

echo "</td></tr>";


echo "<tr><td>";

echo "
<tr><td valign=top>

<table border=0 width=100%>
<tr><td width=80% valign=top>

<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" bgcolor=\"$colore_scuro\">
<tr><td>
<table border=0 cellpadding=0 cellspacing=\"0\" bgcolor=\"$colore_sfondo\" width=\"100%\">
";
?>


<tr>
    <td>
        <!-- elenco risorse -->

        <?php

        $where_s = "";
        if ($titolo_cerca) {
            if ($where_s) $where_s .= " AND ";
            $where_s .= " titolo like '$titolo_cerca%' ";
        };

        if ($materia_cerca) {
            if ($where_s) $where_s .= " AND ";
            $where_s .= " materia like '$materia_cerca%'";
        };

        if ($filtro) {
            if ($elenco_lo) {
                $query = "SELECT id_lo,titolo,lo_tipo,lo_url,width,height,materia,kairos FROM lo_repository WHERE id_lo IN ($elenco_lo) $where_s ORDER BY materia,titolo";
            } else {
                $query = "SELECT * FROM lo_repository WHERE 0=1";
            }

        } else {
            if ($where_s) $where_s = "WHERE " . $where_s;
            $query = "SELECT * FROM lo_repository $where_s ORDER BY materia,titolo";
        };
        $result = $mysqli->query($query);
        //echo $query." ".mysql_error();
        $tot_righe = $result->num_rows;
        $tot_pag = floor($tot_righe / $pag_size);
        if (($tot_righe % $pag_size) <> 0) $tot_pag++;

        $num = $tot_righe;

        $inizio = $pag_size * ($pagina - 1);
        $query .= " LIMIT $inizio,$pag_size";

        $result = $mysqli->query($query);


        $progr = $inizio + 1;
        $righe = 1;
        $continua = true;

        echo "
<table  border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro\" width=\"100%\">
<tr><td>
<table border=0 cellpadding=5 cellspacing=1 bgcolor=\"white\" width=\"100%\">
	";

        echo "<tr bgcolor=\"$colore_scuro\">";
        echo "
<td ><span class=testonegativo><b>Titolo</b></span></td>";


        echo "
<td ><span class=testonegativo><b>Materia</b></span></td>";
        /*
        echo "<td align=center><span class=testonegativo><b>Demo</b></span></td>";
        echo "<td align=center><span class=testonegativo><b>Acquista</b></span></td>";
        */
        echo "<td align=center><span class=testonegativo><b>Esegui</b></span></td>";
        echo "<td align=center><span class=testonegativo><b>Download</b></span></td>";
        if ($ruolo == "admin") {

            echo "<td>&nbsp;</td>";

        };
        echo "</tr>\n";

        $colore = $colore_sfondo;

        while ($result && $riga_lo = $result->fetch_array()) {


            echo "<tr bgcolor=\"$colore\">";

            $id_lo = $riga_lo["id_lo"];
            $titolo = $riga_lo["titolo"];
            $lo_tipo = $riga_lo["lo_tipo"];
            $lo_url = $riga_lo["lo_url"];
            $width = $riga_lo["width"];
            $height = $riga_lo["height"];
            $materia = $riga_lo["materia"];
            $kairos = $riga_lo["kairos"];

            $tipo_lancio = "lo";

            $stato_ordine = "2";

            if (strpos($elenco_lo, $id_lo) === false) $stato_ordine = "0";

            echo "<td><span class=testopiccolo><b>$titolo</b> </span></td>";

            echo "<td><span class=testopiccolo><b>$materia</b> </span></td>";


            $query2 = "SELECT * FROM lo_purchase WHERE id_utente='$kairos_cookie[0]' AND id_lo='$id_lo' LIMIT 1";
            $result2 = $mysqli->query($query2);


            if ($result2->num_rows) {
                $riga_ordine = $result2->fetch_array();
                $stato_ordine = $riga_ordine["stato_ordine"];
            };


            if ($stato_ordine == '2' or ($ruolo == "staff" or $ruolo == "admin")) {
                echo "<td align=center><a href=\"javascript:;\" title=\"Esegui Learning Object online\" onclick=\"javascript:apri_scheda('sco_viewer.php?id_risorsa=$id_lo&tipo=$tipo_lancio&kairos=$kairos','myRemoteLO',        'height=$height,width=$width,alwaysLowered=0,alwaysRaised=0,channelmode=0,dependent=0,directories=0,fullscreen=0,hotkeys=1,location=0,menubar=0,resizable=0,scrollbars=0,status=0,titlebar=1,toolbar=0,z-lock=0','myWindowLO');\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_lo_lancia_$id_lo','','img/ico_lo_lancia_over.gif',1)\"><img src=\"img/ico_lo_lancia.gif\" width=\"20\" height=\"20\" alt=\"Esegui Learning Object online\" border=\"0\" name=\"img_lo_lancia_$id_lo\"></a></td>";
            } else {
                echo "<td>&nbsp;</td>";
            };


            if ($stato_ordine == '2' or ($ruolo == "staff" or $ruolo == "admin")) {
                echo "<td align=center><a href=\"lo_viewer.php?risorsa=$id_lo&esporta=1&kairos=$kairos\" title=\"scarica Learning Object\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_aprilo_$id_lo','','img/ico_apri_over.gif',1)\"><img src=\"img/ico_apri.gif\" width=\"20\" height=\"20\" alt=\"scarica Learning Object\" border=\"0\" name=\"img_aprilo_$id_lo\"></a></td>";
            } else {
                echo "<td>&nbsp;</td>";
            };


            if ($ruolo == "admin") {
                $query3 = "SELECT id_lo FROM lo_ordine_lo WHERE id_lo='$id_lo' LIMIT 1";
                $result3 = $mysqli->query($query3);
                if (!$result3->num_rows) {
                    echo "<td align=center><a href=index.php?risorsa=msg&msg=conf_canc&pagina=lo_repository_cancella.php&id_lo=$id_lo&pag=$pagina&pag_size=$pag_size&titolo_cerca=$titolo_cerca&materia_cerca=$materia_cerca&filtro=$filtro title=\"$stringa[cancella]\" onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_del_$id_lo','','img/ico_cancella_over.gif',1)\"><img src=\"img/ico_cancella.gif\" width=\"20\" height=\"20\" alt=\"$stringa[cancella]\" border=\"0\" name=\"img_del_$id_lo\"></a></td>";
                } else {
                    echo "<td>&nbsp;</td>";
                }
            };

            echo "</tr>";

        };

        echo "</table>\n";

        echo "
</td></tr>
</table>";

        ?>

        <!-- fine elenco risorse -->
    </td>
</tr></table>

</td>
</tr></table>


</td>
<td valign=top width="20%">

    <?php



    echo "
<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"1\" bgcolor=\"$colore_scuro_neutro\">

<tr> 
<td width=\"100%\" align=\"center\" valign=\"middle\"> 
<span class=testo><b>Amministrazione</b></span>
</td>
</tr>

<tr><td>
<table border=0 cellpadding=5 bgcolor=\"$colore_sfondo_neutro\" width=\"100%\">
\n";

    if ($ruolo == "admin") {
        /*
        echo "<tr><td>
        <span class=testopiccolo><a href=\"index.php?risorsa=lo_ordini_attesa&pagina=$i&pag_size=$pag_size&titolo_cerca=$titolo_cerca&materia_cerca=$materia_cerca&filtro=$filtro\" title=\"elenca ordini di LO ancora da confermare\">Ordini da confermare</a></span></td></tr>";
        */
        echo "<tr><td>
<span class=testopiccolo><a href=\"index.php?risorsa=lo_ordini_carica&pagina=$i&pag_size=$pag_size&titolo_cerca=$titolo_cerca&materia_cerca=$materia_cerca&filtro=$filtro\" title=\"carica un ordine e genera codici\">Carica Ordine</a></span></td></tr>";

        echo "<tr><td>
<span class=testopiccolo><a href=\"index.php?risorsa=lo_repository_importa\" title=\"importa LO da altri Kairos\">Importa da repository</a></span></td></tr>";
    } else {

        if (!$filtro) {
            echo "<tr><td>
<span class=testopiccolo><a href=\"index.php?risorsa=lo_repository&filtro=on\" title=\"mostra solo i learning object di cui hai licenza\">I miei Learning Object</a></span></td></tr>";

        } else {
            echo "<tr><td>
<span class=testopiccolo><a href=\"index.php?risorsa=lo_repository\" title=\"mostra tutti i learning object\"> Mostra tutti i LO</a></span></td></tr>";
        };


    };
    echo "</table>";


    ?>


</td>

</td></tr></table>

</td>
</tr></table>

<?php

echo "<br><span class=testopiccolo>$stringa[pagine]:&nbsp;";
$i = 1;
while ($i <= $tot_pag) {
    if ($i == $pagina) {
        echo "[<b>$i</b>]";
    } else {
        echo "
		[<a href=index.php?risorsa=lo_repository&pagina=$i&pag_size=$pag_size&titolo_cerca=$titolo_cerca&materia_cerca=$materia_cerca&filtro=$filtro>$i</a>]
		";
    };
    $i++;
};
echo "</span><br>";

?>
</td></tr></table>
<br>

<?php
echo "                </div>
            </div>
        </div>
    </div>
</div>";

?>

