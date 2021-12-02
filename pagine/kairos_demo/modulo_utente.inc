<?php
echo "<div class=\"container\">
    <div class=\"row\">
      <div class=\"panel panel-warning\">
        <div class=\"panel-body\">

    ";


$query="SELECT * FROM utenti WHERE id_utente='$id_utente'";
$result=$mysqli->query($query);
$riga = $result->fetch_array();
if (!$riga) {
	Header("Location:index.php?risorsa=index");
	exit();
};

$pwd_utente=$riga["pwd_utente"];
$nome=htmlentities($riga["nome"]);
$cognome=htmlentities($riga["cognome"]);
$indirizzo=htmlentities($riga["indirizzo"]);
$cap=$riga["cap"];
$citta=htmlentities($riga["citta"]);
$prov=$riga["prov"];
$telefono=$riga["telefono"];
$email=$riga["email"];
$ex_email=$email;
$sitoweb=$riga["sitoweb"];
$sesso=$riga["sesso"];
$eta=$riga["eta"];
$interesse=htmlentities($riga["interesse"]);
$biografia=htmlentities($riga["biografia"]);
$scuola=htmlentities($riga["scuola"]);
$materia=htmlentities($riga["materia"]);
$ruolo_scuola=$riga["ruolo_scuola"];
$id_eproffaro=$riga["id_eproffaro"];

$val_sesso1="";
$val_sesso2="";

$val_newletter="";


switch($sesso) {
	case "M":
		$val_sesso1="checked";
		break;
	case "F": 
		$val_sesso2="checked";
		break;
};

$ruolo_scuola1="";
$ruolo_scuola2="";
$ruolo_scuola3="";
$ruolo_scuola4="";
$ruolo_scuola5="";

switch ($ruolo_scuola) {
	case "Dirigente":
		$ruolo_scuola1="selected";
		break;
		
	case "Insegnante":
		$ruolo_scuola2="selected";
		break;
				
	case "Studente":
		$ruolo_scuola3="selected";
		break;
	
	case "Altro":
		$ruolo_scuola4="selected";
		break;
	
	case "Nessuno":
		$ruolo_scuola5="selected";
		break;
};
		
echo "
<table border=0 width=100% cellspacing=10 cellpadding=0>
<tr>
<td valign=top width=100% class=titolodot>".strtoupper($stringa[modifica_profilo])."</td></tr>

<tr>
<td valign=top width=100%>
<a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\"><img border=\"0\" src=\"img/ico_back.gif\" width=\"20\" height=\"20\" align=\"middle\" alt=\"$stringa[indietro]\" name=\"img_back\"></a> <span class=testopiccolo><a href=\"javascript:history.back()\"
onMouseOut=\"MM_swapImgRestore()\" onMouseOver=\"MM_swapImage('img_back','','img/ico_back_over.gif',1)\">$stringa[indietro]</a></span>
</td></tr>
<tr><td>";
?>

<TABLE border=0 cellpadding=10 bgcolor=white>


<TR>
<TD>
<FORM action=modifica_utente.php encType=multipart/form-data method=post>
<INPUT name=MAX_FILE_SIZE type=hidden value=100000>
<input type=hidden name=ex_email value="<?php echo($ex_email);?>">
<input type=hidden name=id_utente value="<?php echo($id_utente);?>">

<span class=testopiccolo>
<?php echo($stringa[modifica_intro]);?>
</span> 
<br>
            <TABLE border=0>
			
			
	<?php			
			if ($cod_area=="kairos_atlanteragazzi" and $id_eproffaro) {
echo "<tr> <TD align=right><span class=testopiccolo><b>ID Insegnante E-Prof di cui sei alunno/a:</b></span></TD>
<td><span class=testopiccolo><b>$id_eproffaro</b></span>";
echo "</td></tr>";
};

			?>
              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[identificativo]);?>:</b></span></TD>
                <TD><span class=testopiccolo><b><?php echo($id_utente);?></b></span></TD></TR>
			 
			<TR>
			<TD valign=bottom align=right><span class=testopiccolo><?php echo($stringa[immagine_profilo]);?>:</span></TD>
		<TD valign=bottom><INPUT name=immagine type=file>
		<?php
$immagine=false;
$file_immagine = $PATH_ROOT_FILE."foto_utenti/$cod_area/".$id_utente.".gif";
$file_immagine = strtolower($file_immagine);

if (file_exists($file_immagine)) {
	$nome_immagine = "$id_utente.gif";
	$nome_immagine = strtolower($nome_immagine);
	$immagine = true;
};

if (!$immagine) {
	$file_immagine = $PATH_ROOT_FILE."foto_utenti/$cod_area/".$id_utente.".jpg";
	$file_immagine = strtolower($file_immagine);
	if (file_exists($file_immagine)) {
		$nome_immagine = "$id_utente.jpg";
		$nome_immagine = strtolower($nome_immagine);
		$immagine = true;
	};
};

if ($immagine) {
	echo "<a href=foto_utenti/$cod_area/$nome_immagine target=_blank title=\"$stringa[immagine_profilo_alt]\"><span class=testo><b>[".$stringa[immagine]."]</b></a>";
};

?>
		</TD>
		</TR>	  
              <TR>
                <TD colSpan=2></TD></TR>
              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[password]);?>:</b></span></TD>
                <TD>
				<INPUT type=password  name=pwd_utente size=35 value="<?php echo($pwd_utente);?>"></TD></TR>				
              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[nome]);?></b></span></TD>
                <TD>
				<INPUT  name=nome size=35 value="<?php echo($nome);?>"></TD></TR>
              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[cognome]);?></b></span></TD>
                <TD><INPUT name=cognome size=35 value="<?php echo($cognome);?>"></TD></TR>

			<TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[email]);?></b></span> </TD>
                <TD><INPUT  name=email size=35 value="<?php echo($email);?>"></TD></TR>
 
<?php
if ($cod_area<>"kairos_larimart") {
?>           
		      <TR>
                <TD align=right vAlign=top><span class=testopiccolo><b><?php echo($stringa[indirizzo]);?></b></span></TD>
                <TD><INPUT  name=indirizzo size=35 value="<?php echo($indirizzo);?>"></TD></TR>
              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[cap]);?></b></span></TD>
                <TD><INPUT maxLength=5 name=cap size=5 value="<?php echo($cap);?>"></span></TD></TR>
              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[citta]);?></b></span></TD>
                <TD><INPUT  name=citta size=35 value="<?php echo($citta);?>"></TD></TR>
              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[prov]);?></b></span></TD>
                <TD><INPUT maxLength=2 name=prov size=2 value="<?php echo($prov);?>"></TD></TR>
				<TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[scuola]);?></b></span></TD>
                <TD><INPUT  name=scuola size=35 value="<?php echo($scuola);?>"></TD></TR>

              <TR>
                <TD align=right><span class=testopiccolo><b><?php echo($stringa[telefono]);?></b></span></TD>
                <TD><INPUT  name=telefono size=35 value="<?php echo($telefono);?>"></TD></TR>
     
              <TR>
                <TD align=right><span class=testopiccolo><?php echo($stringa[sitoweb]);?></span></TD>
                <TD><INPUT  name=sitoweb size=35 value="<?php echo($sitoweb);?>"></span></TD></TR>
                <TR>
                <TD align=right><span class=testopiccolo><?php echo($stringa[sesso]);?></span></TD>
                <TD><INPUT name=sesso type=radio value="M" <?php echo($val_sesso1);?>><span class=testopiccolo><?php echo($stringa[m]);?></span><INPUT name=sesso type=radio value="F" <?php echo($val_sesso2);?>><span class=testopiccolo><?php echo($stringa[f]);?></span></TD></TR>
 <TR>
                <TD align=right><span class=testopiccolo><?php echo($stringa[eta]);?></span></TD>
                <TD><INPUT name=eta size=10 value="<?php echo($eta);?>">
				</TD>
				</TR>			  
							
			  <TR>
                <TD align=right><span class=testopiccolo><?php echo($stringa[interessi]);?></span></TD>
                <TD><INPUT  name=interesse size=35 value="<?php echo($interesse);?>"></TD></TR>	             

				<?php
				echo "
				<TR>
                <TD align=right><span class=testopiccolo><b>$stringa[ruolo_scuola]</b></span></TD>
                <TD><SELECT name=ruolo_scuola size=1> 
					<OPTION value=\"Dirigente\" $ruolo_scuola1>$stringa[dirigente]</OPTION>
					<OPTION value=\"Insegnante\" $ruolo_scuola2>$stringa[insegnante]</OPTION> 
					<OPTION value=\"Studente\" $ruolo_scuola3>$stringa[studente]</OPTION>
					<OPTION value=\"Altro\" $ruolo_scuola4>$stringa[altro]</OPTION>
					<OPTION value=\"Nessuno\" $ruolo_scuola5>$stringa[nessun_ruolo]</OPTION>
					</SELECT>
			  </TD>
			  </TR>
			  
			  <TR>
               <TD align=right valign=top> 
                   <span class=testopiccolo>$stringa[materia_insegnata]</span>
				</TD>	
                <TD><INPUT name=materia size=50 value=\"$materia\">
				<br><span class=testopiccolo>($stringa[guida_materia_insegnata])</span></TD>
				</TR>
			  ";
			  ?>

			  <TR>
                <TD align=right valign=top><span class=testopiccolo><?php echo($stringa[qualcosa_di_me]);?></span></TD>
                <TD><TEXTAREA name=biografia rows=10 cols=30><?php echo($biografia);?></TEXTAREA></TD></TR>	  
              
<?php
};
?>

			<tr>
			<td colspan=2>
			<hr size=1>
			</td>
			</tr>
			<tr>
			<td valign=top colspan=2>
			<?php storia_corsi($id_utente); ?>
			</td>
			</tr>
			<tr>
			<td colspan=2>
			<hr size=1>
			</td>
			</tr>
			
			<TR>
            <TD align=CENTER colspan=2 valign=top> 
			<INPUT type=submit value="<?php echo($stringa[ok]);?>">
		</TABLE>
		<BR>
        </FORM>    
</TD></TR>
</TABLE>

</td></tr></table>
<br>

<?php
echo "                </div>
            </div>
        </div>
    </div>
</div>";
?>

