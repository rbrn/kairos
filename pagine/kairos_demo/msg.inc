<?php

echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";

echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr><td>";

if ($msg == "conf_canc") {
    $pagina = $_REQUEST["pagina"];
    $link_si = $pagina . "?" . $_SERVER["QUERY_STRING"];
    echo "
<div class=\"panel panel-default\" style='padding-top: 20px;'>
  <div class=\"panel-body\">
	<div class=\"alert alert-danger\">
  <a href=\"#\" class=\"alert-link\">
        <span class=testo >
    $stringa[conf_canc] [<a href = $link_si > $stringa[si]</a >] [<a href = javascript:history . back() > $stringa[no]</a >]</span >
 </a >
    </div >
      </div>
</div>
    ";
} else {
    echo "
	<span class=testo >
	<p > ";
    ereg_replace(" % 20", " ", $msg);
    $msg = stripslashes($msg);
    echo($msg);
    echo "
    </p >

	<p > ";

    if ($url) {
        $url = $PATH_ROOT . $url;
        echo "
	<a href = $url > [" . $stringa[indietro] . "]</a >
    ";
    } else {
        if ($risorsa_back) {
            $url = $PATH_ROOT . "index . php ? risorsa = $risorsa_back & arg = $arg";
            echo "
        < a href = $url > [" . $stringa[ok] . "]</a >
    ";
        } else {
            echo "
		<a href = javascript:history . back() > [" . $stringa[indietro] . "]</a > ";
        };
    };
    echo "
	</p >
	</span > ";
};
echo "</td ></tr ></table > ";
echo "                </div>
            </div>
        </div>
    </div>
</div>";
?>
