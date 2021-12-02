<?php
require "./config.php";
?>
html, body {
  background: <?php echo $colore_sfondo ?>;
  color: <?php echo $colore_testo ?>;
  font: 11px Verdana, Arial, Helvetica, sans-serif;
  margin: 0px;
  padding: 0px;
}

body { padding: 5px; }
table {
  font: 11px Verdana, Arial, Helvetica, sans-serif;
}

select, input, button { font: 11px Verdana, Arial, Helvetica, sans-serif; }
button { width: 20px; }
table .label { text-align: right; width: 8em; }

.title { background: <?php echo $colore_scuro ?>; color: <?php echo $colore_testonegativo ?>; font-weight: bold; font-size: 120%; padding: 3px 10px; margin-bottom: 10px;
border-bottom: 1px solid black; letter-spacing: 2px;
}

#buttons {
      margin-top: 1em; border-top: 1px solid #999;
      padding: 2px; text-align: right;
}
