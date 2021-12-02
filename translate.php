<?php

if (isset($_POST['language'])) {
    $langfile = "translation/stringhe_" . $_POST['language'] . ".inc";

    $handle = fopen($langfile, 'w') or die('Cannot open file:  ' . $langfile);
    $contents = '<?php';
    $contents .= "\n";
    foreach ($_POST as $key => $value) {
        $contents .= '$stringa[' . $key . ']= "' . $value . '"; ';
        $contents .= "\n";
    }
    $contents .= "?>";

    fwrite($handle, $contents);
    echo "Language saved!";
    exit;
}

?>

<html>
<body>

<form action="translate.php" method="post">
    <p>Language abb: <input type="text" name="language"></p>
    <?php

    include_once 'include/properties.php';

    include_once 'include/init_sito.inc';
    $file_lingua = $PATH_ROOT_FILE . "/include/stringhe_" . $lingua . ".inc";

    foreach ($stringa as $key => $value) {
        echo "<p> $key :<input type=\"text\" name=\"$key\" value=\"$value\"></p>";
    }

    ?>

    <input type="submit">
</form>

</body>
</html>
