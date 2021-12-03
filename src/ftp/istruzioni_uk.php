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
<p><b>How to manage your personal web space</b></p>
<p>
<b>Main folder: "web root"</b><br>
When you open your personal web space you are located in its main folder.<br>
That is the "web root" of your site and there you have to start uploading the homepage, subfolders and all its contents.
<br>
The URL of your site will be:
<br>
<i><?php echo($PATH_ROOT);?>index.htm</i>
<br> 
or shortly:<br>
<i><?php echo($PATH_ROOT);?></i>
</p> 
<p>
<b>Uploading file</b><br>
To upload a new file simply click on the "new file" icon <img src=img/new_file.gif> and then "Browse..." you computer in order to select the file you want to upload. The file will be uploaded on the current folder of your area.
<br><br>
To upload <b>more than one file</b> at the time you can "zip" your file using utilities such as WinZip then upload the resulting .zip file clicking on "upload .zip file" icon <img src=img/new_file_zip.gif>. <br>The zip archive will be automatically uncompressed in the current folder.
</p>
<p>
<b>Deleting file and folder</b><br>
To delete one or more files simply check the corresponding box and then click on "Delete selected items" button. <br>
You do the same also to delete folders, but be sure that they are empty.
</p>
 
<p>
<b>File naming</b>
<br>
HTML file must have <b>.htm</b> extesions;<br>
HTML file must have <b>.php</b> extesions;<br>
<br>
<b>No spaces</b> are allowed for a file name;
<br>
we strongly suggest you to <b>lowercase</b> the file name.
<br><br>
Good file names are:<br>
test.htm, logo.gif, about_us.htm, index.php
<br><br>
Bad file names are:<br>
test.html, logo.GIF, about us.htm
</p>
<p><b>The file index.htm (or index.php)</b><br>
Do not forget to put a file named <b>index.htm</b> (or index.php if you use PHP code) in your web root. Otherwise the users who try to access you site <i><?php echo($PATH_ROOT);?></i> will have a "<b>Forbidden</b>" error from the server.
</p>

<p><b>Folders</b><br>
You can create as many folders as you like in your space simply by clickin on 
 "new folder" icon <img src=img/new_folder.gif>. The folder will be created on the current folder. 
If you want to upload files in a specific folder you have first to click on the folder making it the "current" folder.
</p>

<p align=center><font size="-1">[<a href="javascript:window.close()"><?php echo($stringa[chiudi]);?></a>]</font></b></p>
  
</span>
  
</body>
</html>
