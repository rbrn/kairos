<?php
require "./include/funzioni_materiali.inc";
$id_cartella=$_REQUEST["id_cartella"];
$repertorio=$_REQUEST["repertorio"];

if (!isset($id_cartella)) {
    $id_cartella="root";
};

$query="SELECT * FROM contesto_cartella WHERE id_utente='$id_utente' AND id_cartella='$id_cartella'";
$result=$mysqli->query($query);
$presente=$result->num_rows;
$riga=$result->fetch_array();

if (!$pagina) $pagina=$riga[pagina];
if (!$repertorio) $repertorio=$riga[stato];

if (!$pagina) $pagina=1;
if (!$repertorio) $repertorio="nascondi";

if ($presente) {
    $query="UPDATE contesto_cartella SET pagina=$pagina,stato='$repertorio'  WHERE id_utente='$id_utente' AND id_cartella='$id_cartella'";
} else {
    $query="INSERT INTO contesto_cartella SET id_utente='$id_utente', id_cartella='$id_cartella',pagina=$pagina,stato='$repertorio'";
};
$mysqli->query($query);



$ruolo=ruolo_utente($id_utente);
$editabile=true;

if ($id_cartella<>"root") {
    mysql_select_db($DBASE);
    $query="select * FROM risorse_materiali WHERE id_risorsa='$id_cartella'";
$result=$mysqli->query($query);
    $riga=$result->fetch_array();
    $titolo=$riga[titolo];
    $id_cartella_sup=$riga["risorsa_padre"];

    if ($ruolo<>"admin") {
        if ($id_utente <> $riga[id_autore] and $id_utente <> $riga[id_editor]) {
            $id_editor_gruppo=$riga[id_editor_gruppo];
            if ($id_editor_gruppo) {
                $query="SELECT * FROM editor_gruppo_utenti WHERE id_utente='$id_utente' AND id_editor_gruppo='$id_editor_gruppo'";
$result=$mysqli->query($query);
                if (!$result->num_rows) $editabile=false;
            } else {
                $editabile=false;
            };
        };
    };

    $path_cartella=path_cartella($id_cartella_sup)."/".$titolo;
} else {
    $titolo="";
    $id_cartella_sup="";
    $path_cartella=$titolo;
};


$editor_lo = true;

$tpl->assign("stringa", $stringa );
$tpl->assign("ruolo", $ruolo);
$tpl->assign("id_cartella_sup", $id_cartella_sup);
$tpl->assign("titolo", $titolo);
$tpl->assign("path_cartella", $path_cartella);
$tpl->assign("editabile", $editabile);
$tpl->assign("riga", $riga);
$tpl->assign("editor_lo", $editor_lo);

// draw the template
$tpl->draw( "materiali_index_template");

thread_risorse($id_cartella, $pagina);

echo "</div>
</div>
</div>

<!-- /widget-main -->
</div>
<!-- /widget-body -->
</div><!-- /widget-box -->";
