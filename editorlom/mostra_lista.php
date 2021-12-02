<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>Untitled</title>
</head>

<body>
<?php


require "./variabili.php";
function mostra($lista) {
	for ($i=0;$i<count($lista);$i++) {
		echo $lista[$i]."<br>";
	};
	echo "<hr size=1>";
};

mostra($opt_lang);
mostra($opt_structure);
mostra($opt_structure);
mostra($opt_aggrlevel);
mostra($opt_status);
mostra($opt_role);
mostra($opt_role_mm);
mostra($opt_format);
mostra($opt_type);
mostra($opt_name);
mostra($opt_intertype);
mostra($opt_learestype);
mostra($opt_interlevel);
mostra($opt_ieurole);
mostra($opt_context);
mostra($opt_difficulty);
mostra($opt_yn);
mostra($opt_kind);
mostra($opt_purpose);


?>


</body>
</html>
