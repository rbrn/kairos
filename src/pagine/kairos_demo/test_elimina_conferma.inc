<?php
$id_test=$_REQUEST["id_test"];

echo "<p align=center><span class=testo><b>$id_test</b>: $stringa[conferma_del_test]
<br><br>
[<a href=test_elimina.php?id_test=$id_test>$stringa[si]</a>]   [<a href=index.php?risorsa=test_index>$stringa[no]</a>]</span></p>";
?>
