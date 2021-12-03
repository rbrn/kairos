<?php
require "./config.php";
require "./variabili.php";

function esporta_lom($id_lo, $id_profile, $id_lom_sup = 0, $id_rep_sup = 0)
{
    global $opt_lang;
    global $db;
    global $xml;
    global $encode;
    global $mysqli;

    $query = "SELECT * FROM lo_schema WHERE id_lom_sup='$id_lom_sup' AND id_profile='$id_profile' ORDER BY id_lom";
    $result = $mysqli->query($query);

    while ($riga = $result->fetch_array()) {
        $id_lom = $riga[id_lom];
        $nome = htmlentities(trim($riga[nome]));
        $nome = str_replace(" ", "", $nome);

        switch ($encode) {
            case "LOM":
                break;
            case "IMS":
                $nome = strtolower($nome);
                break;
        };


        $size = $riga[size];
        $tipocampo = $riga[tipocampo];
        $valuespace = $riga[valuespace];
        $langstring = $riga[langstring];
        $datetype = $riga[datetype];
        $valdefault = $riga[valdefault];
        $obbligatorio = $riga[obbligatorio];
        $commento = $riga[commento];

        $query1 = "SELECT * FROM lo_metadata WHERE id_lom='$id_lom' AND id_lo='$id_lo' AND id_rep_sup='$id_rep_sup' ORDER BY id_rep";
        $result1 = $mysqli->query($query1);

        if ($result1->num_rows) {
            while ($riga1 = $result1->fetch_array()) {
                $id_rep = $riga1[id_rep];
                $lang = trim($riga1[lang]);
                $valore = trim($riga1[valore]);

                if ($nome == "identifier") {
                    switch ($encode) {
                        case "LOM":
                            break;

                        case "IMS":
                            $nome = "catalogentry";
                            break;
                    };
                };

                $xml .= "<$nome>\n";

                $query2 = "SELECT * FROM lo_schema WHERE id_lom_sup='$id_lom'  AND id_profile='$id_profile' ORDER BY id_lom";
                $result2 = $mysqli->query($query2);
                if ($result2->num_rows) {
                    esporta_lom($id_lo, $id_profile, $id_lom, $id_rep);
                } else {
                    if ($langstring) {
                        switch ($encode) {
                            case "LOM":
                                $xml .= "<string language=\"$lang\">$valore</string>\n";
                                break;
                            case "IMS":
                                $xml .= "<langstring xml:lang=\"$lang\">$valore</langstring>\n";
                                break;
                        };

                        $query_l = "SELECT * FROM lo_metadata_valore WHERE id_rep='$id_rep' ORDER BY n";
                        $result_l = $mysqli->query($query_l);
                        $k = 1;
                        while ($riga_l = $result_l->fetch_array()) {
                            $lang = trim($riga_l[lang]);
                            $valore = trim($riga_l[valore]);

                            switch ($encode) {
                                case "LOM":
                                    $xml .= "<string language=\"$lang\">$valore</string>\n";
                                    break;
                                case "IMS":
                                    $xml .= "<langstring xml:lang=\"$lang\">$valore</langstring>\n";
                                    break;
                            };
                            $k++;
                        };

                    } else {
                        switch ($tipocampo) {
                            case "text":
                                switch ($encode) {
                                    case "LOM":
                                        $xml .= "$valore\n";
                                        break;
                                    case "IMS":
                                        if ($nome == "entry") {
                                            $xml .= "<langstring xml:lang=\"en\">$valore</langstring>\n";
                                        } else {
                                            $xml .= "$valore\n";
                                        };
                                        break;
                                };

                                break;

                            case "textarea":
                                switch ($encode) {
                                    case "LOM":
                                        $xml .= "$valore\n";
                                        break;
                                    case "IMS":
                                        if ($nome == "entry") {
                                            $xml .= "<langstring xml:lang=\"en\">$valore</langstring>\n";
                                        } else {
                                            $xml .= "$valore\n";
                                        };
                                        break;
                                };
                                break;

                            case "select":
                                if (strtolower($nome) <> "language" and strtolower($nome) <> "format") {
                                    switch ($encode) {
                                        case "IMS":
                                            $valore = strtoupper(substr($valore, 0, 1)) . substr($valore, 1, strlen($valore));
                                            $xml .= "<source>\n<langstring xml:lang=\"en\">LOMv1.0</langstring>\n</source>\n<value>\n<langstring xml:lang=\"x-none\">$valore</langstring>\n</value>\n";
                                            break;
                                        case "LOM":
                                            $xml .= "<source>LOMv1.0</source>\n<value>$valore</value>";
                                            break;
                                    };
                                } else {
                                    $xml .= "$valore\n";
                                };
                                break;
                        };
                    };


                }
                $xml .= "</$nome>\n";

            };
        };
    };

}

;

$id_lo = $_REQUEST[id_lo];
$encode = $_REQUEST[encode];
if (!$id_lo) {
    $msg = "Nessun LO";
    Header("Location:msg.php?msg=$msg");
    exit();
};
$query = "SELECT * FROM lo WHERE id_lo='$id_lo'";
$result = $mysqli->query($query);
$riga = $result->fetch_array();
$id_profile = $riga[id_profile];

if (!$encode) $encode = "LOM";

switch ($encode) {
    case "LOM":

        $xml = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>
<lom xmlns=\"http://ltsc.ieee.org/xsd/LOM\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchemainstance\" xsi:schemaLocation=\"http://ltsc.ieee.org/xsd/LOM http://ltsc.ieee.org/xsd/lomv1.0/lom.xsd\">\n";
        break;

    case "IMS":
        $xml = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>
<lom xmlns=\"http://www.imsglobal.org/xsd/imsmd_v1p2\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.imsglobal.org/xsd/imsmd_v1p2 imsmd_v1p2p2.xsd\">\n";
        break;
};

esporta_lom($id_lo, $id_profile);

$xml .= "</lom>";

$filename = $id_lo . ".xml";
header("Content-Type: text/xml");

header("Content-Disposition: attachment; filename=$filename");

echo($xml);
?>
