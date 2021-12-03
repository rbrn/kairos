<?php
require "../../include/init_sito.inc";
?>
html, body {
  background: <?php echo $colore_sfondo_neutro ?>;
  color: <?php echo $colore_testo ?>;
  font: 12px Verdana, Arial, Helvetica, sans-serif;
  margin: 0px;
  padding: 0px;
}

body { padding: 0px; }
table {
  font: 12px Verdana, Arial, Helvetica, sans-serif;
}

select, input, button { font: 11px Verdana, Arial, Helvetica, sans-serif; }
button { width: 20px; }
table .label { text-align: right; width: 8em; }

#buttons {
      margin-top: 1em; border-top: 1px solid #999;
      padding: 2px; text-align: right;
}

.title { background: <?php echo $colore_scuro ?>; color: <?php echo $colore_testonegativo ?>; font-weight: bold; font-size: 12px; padding: 3px 10px; margin-bottom: 10px;
border-bottom: 1px solid black; 
}

.testonegativo { color: <?php echo $colore_testonegativo ?> }
