<?php

$html_to_convert="<html><head><title>prova</title></head><body>prova <strong>prova</strong></body></html>";

require_once('html2fpdf.php');
require_once('htmltoolkit.php');

$html2pdf = new HTML2FPDF();
$html2pdf->AddPage();
@$html2pdf->WriteHTML($html_to_convert);
$html2pdf->Output();

?>
