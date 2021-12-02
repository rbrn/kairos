<?php 
require "./init_sito.inc";
if (file_exists("../pagine/$cod_area/colori.inc")) 
require "../pagine/$cod_area/colori.inc";
?>
<html>
<head>
<title><?php echo($stringa[istruzioni]);?></title>
<link rel="stylesheet" href="../stili/<?php echo($cod_area);?>/stile_sito.css">
</head>

<body bgcolor=<?php echo($colore_sfondo);?>>
<span class=testo>
<p><b>Istruzioni per l'uso dell'Area di Lavoro</b></p>
<p>
<b>Cartella principale "web root"</b><br>
Quando aprite l'area di lavoro vi trovate nella sua "cartella principale".<br>
Corrisponde alla vostra "web root" ed ÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ qui che dovete mettere il file della homepage, e tutti gli eventuali file e cartelle a cui l'homepage si riferisce.
<br>
L'indirizzo della vostra web root dall'esterno sarÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ del tipo:<br>
<i><?php echo($PATH_ROOT);?>index.htm</i>
<br> 
o, piÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ brevemente:<br>
<i><?php echo($PATH_ROOT);?></i>
</p> 
<p>
<b>Caricamento di file</b><br>
Per caricare file nella cartella in cui vi trovate cliccate sull'icona "nuovo file" <img src=img/new_file.gif> e quindi dal modulo che segue cliccate su "Sfoglia..." e individuate (come se voleste aprirlo) il file che intendete caricare. E' possibile caricare solo <b>un file per volta</b>.
<br><br>
Per caricare <b>piÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ di un file</b> per volta, comprimete i file nel vostro computer usando WinZip e quindi caricate l'unico file .zip ottenuto cliccando sull'icona "archivio .zip" <img src=img/new_file_zip.gif>. <br>I file verranno automaticamente decompressi nella cartella corrente.
</p>
<p>
<b>Cancellazione di file e cartelle</b><br>
Per cancellare uno o piÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ file dalla cartella in cui vi trovate "spuntate" i file che intendete cancellare e quindi cliccate sul pulsante "Cancella elementi selezionati". <br>
Potete "spuntare" anche una cartella, ma per poter essere cancellata questa deve essere <b>vuota</b> (nel caso quindi dovrete prima entrare nella cartella e cancellarne il contenuto).

</p>
 
<p>
<b>Nomi dei file</b>
<br>
I nomi dei file HTML devono avere estensione <b>.htm</b>;<br>
I nomi dei file PHP devono avere estensione <b>.php</b>;<br>
<br>
I nomi dei file <b>non devono contenere spazi</b>;
<br>
si consiglia vivamente di scrivere nomi tutto in <b>minuscolo</b>.
<br><br>
Esempio di nomi di file corretti:<br>
prova.htm, logo.gif, chi_siamo.htm, index.php
<br><br>
Esempio di nomi di file non corretti:<br>
prova.html, logo.GIF, chi siamo.htm
</p>
<p><b>Il file index.htm (o anche index.php)</b><br>
al primo livello della vostra area di lavoro (il cosÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½detto "web root") deve essere caricato un file di nome <b>index.htm</b> a rappresentare la vostra home page. Se non inserite questo file il tentativo di accedere al vostro sito con indirizzo del tipo <i><?php echo($PATH_ROOT);?></i> produrrÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ un errore di <b>Forbidden</b>.
</p>

<p><b>Le cartelle</b><br>
Nella vostra area di lavoro potete creare nuove cartelle cliccando sull'icona "nuova cartella" <img src=img/new_folder.gif>. La cartella verrÃÂÃÂ¯ÃÂÃÂ¿ÃÂÃÂ½ creata all'interno della cartella in cui in quel momento vi trovate (all'inizio vi trovate nella cartella principale "web root").
Per poter caricare file all'interno della cartella dove prima entrarci e da qui cliccare sull'icona "nuovo file" <img src=img/new_file.gif> o sull'icona "nuova cartella" per creare eventuali sottocartelle.<br>
Ad esempio nella cartella principale potete creare una cartella di nome "img" e qui metterci il file "logo.gif". <br>
Nel file "index.htm" per poter riferire quell'immagine dovrete specificare il percorso <i>img/logo.gif</i>.
</p>

<p align=center><font size="-1">[<a href="javascript:window.close()"><?php echo($stringa[chiudi]);?></a>]</font></b></p>
  
</span>
  
</body>
</html>
