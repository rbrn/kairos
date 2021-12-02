<?php
require "./include/init_sito.inc";
require "./include/funzioni_sito.inc";

$id_utente=$kairos_cookie[0];

$id_contatto     =mysql_real_escape_string($_REQUEST[id_contatto]);
$risposta_aperta_1     =mysql_real_escape_string($_REQUEST[risposta_aperta_1]);
$cod_mecc    			 =mysql_real_escape_string($_REQUEST[cod_mecc]);
$risposta_aperta_2     =mysql_real_escape_string($_REQUEST[risposta_aperta_2]);
$risp_voce_3_1		  =$_REQUEST[risp_voce_3_1];
$risp_voce_3_2		  =$_REQUEST[risp_voce_3_2];
$risp_voce_3_3		  =$_REQUEST[risp_voce_3_3];
$risp_voce_3_4		  =$_REQUEST[risp_voce_3_4];
$risp_voce_3_5		  =$_REQUEST[risp_voce_3_5];
$risp_voce_3_6		  =$_REQUEST[risp_voce_3_6];
$risp_voce_3_7		  =$_REQUEST[risp_voce_3_7];
$risp_voce_3_8		  =$_REQUEST[risp_voce_3_8];
$risp_voce_3_9		  =$_REQUEST[risp_voce_3_9];
$risposta_altro_voce_3_9 =$_REQUEST[risposta_altro_voce_3_9];

$risposta_aperta_4     =mysql_real_escape_string($_REQUEST[risposta_aperta_4]);

$query="UPDATE contatti SET
risposta_aperta_1     ='$risposta_aperta_1',
cod_mecc			  ='$cod_mecc',
risposta_aperta_2     ='$risposta_aperta_2',
risp_voce_3_1		  ='$risp_voce_3_1',
risp_voce_3_2		  ='$risp_voce_3_2',
risp_voce_3_3		  ='$risp_voce_3_3',
risp_voce_3_4		  ='$risp_voce_3_4',
risp_voce_3_5		  ='$risp_voce_3_5',
risp_voce_3_6		  ='$risp_voce_3_6',
risp_voce_3_7		  ='$risp_voce_3_7',
risp_voce_3_8		  ='$risp_voce_3_8',
risp_voce_3_9		  ='$risp_voce_3_9',
risposta_altro_voce_3_9 ='$risposta_altro_voce_3_9',
risposta_aperta_4     ='$risposta_aperta_4'
WHERE id_contatto='$id_contatto'
";
$result = $mysqli->query($query);

header("Location:contatti_view.php?id_contatto=$id_contatto");
?>
