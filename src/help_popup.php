<?php
require "./include/init_sito.inc";
?>
<HTML>

<HEAD>
<TITLE><?php echo($stringa[istruzioni_chat]);?></TITLE>
<LINK REL="stylesheet" HREF="./stili/<?php echo($cod_area);?>/style.css" TYPE="text/css">
<SCRIPT TYPE="text/javascript" LANGUAGE="javascript1.1">
function Write_Input(smiley)
{
	window.focus();
	if (window.opener && !window.opener.closed) window.opener.document.Form.riga_chat.value += smiley;
}
</SCRIPT>
</HEAD>

<BODY CLASS=mainframe onLoad="if (window.focus) window.focus();">
<CENTER>


	<TABLE BORDER=0 CELLPADDING=3 CLASS=table>
	<TR>
		<TH  COLSPAN=9><?php echo($stringa[faccine]);?></TH>
	</TR>
	<TR VALIGN=BOTTOM>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input(':)')"><IMG SRC="images/smilies/smile1.gif" WIDTH=15 HEIGHT=15 BORDER=0 ALT=":)"></A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input(':D')"><IMG SRC="images/smilies/smile2.gif" WIDTH=15 HEIGHT=15 BORDER=0 ALT=":D"></A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input(':o')"><IMG SRC="images/smilies/smile3.gif" WIDTH=15 HEIGHT=15 BORDER=0 ALT=":o"></A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input(':(')"><IMG SRC="images/smilies/smile4.gif" WIDTH=15 HEIGHT=15 BORDER=0 ALT=":("></A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input(';)')"><IMG SRC="images/smilies/smile5.gif" WIDTH=15 HEIGHT=15 BORDER=0 ALT=";)"></A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input(':p')"><IMG SRC="images/smilies/smile6.gif" WIDTH=15 HEIGHT=15 BORDER=0 ALT=":p"></A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('8)')"><IMG SRC="images/smilies/smile7.gif" WIDTH=15 HEIGHT=15 BORDER=0 ALT="8)"></A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input(':[')"><IMG SRC="images/smilies/smile8.gif" WIDTH=15 HEIGHT=15 BORDER=0 ALT=":["></A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input(':kill:')"><IMG SRC="images/smilies/smile9.gif" WIDTH=50 HEIGHT=15 BORDER=0 ALT=":kill:"></A></TD>
	</TR>
	<TR>
		<TD ALIGN=CENTER><PRE>:)</PRE></TD>
		<TD ALIGN=CENTER><PRE>:D</PRE></TD>
		<TD ALIGN=CENTER><PRE>:o</PRE></TD>
		<TD ALIGN=CENTER><PRE>:(</PRE></TD>
		<TD ALIGN=CENTER><PRE>;)</PRE></TD>
		<TD ALIGN=CENTER><PRE>:p</PRE></TD>
		<TD ALIGN=CENTER><PRE>8)</PRE></TD>
		<TD ALIGN=CENTER><PRE>:[</PRE></TD>
		<TD ALIGN=CENTER><PRE>:kill:</PRE></TD>
	</TR>
	</TABLE>
   <BR>
	
	

<br>

<TABLE BORDER=0 CELLPADDING=3 CLASS=table>
	<TR>
		<TH COLSPAN=9>Frasi predefinite</TH>
	</TR>
	<TR VALIGN=BOTTOM>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*cucu*')">*cucu*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*interessante*')">*interessante*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*divertente*')">*divertente*</A></TD>
	</TR>
	<TR VALIGN=BOTTOM>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*silenzio*')">*silenzio*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*unoallavolta*')">*unoallavolta*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*cambioargomento*')">*cambioargomento*</A></TD>
	</TR>
	<TR VALIGN=BOTTOM>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*uffa*')">*uffa*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*ciao*')">*ciao*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*evviva*')">*evviva*</A></TD>
	</TR>
	</TABLE>
	
	  <BR><br>
	  
	  
<TABLE BORDER=0 CELLPADDING=3 CLASS=table>
	<TR>
		<TH COLSPAN=9>Suoni predefiniti</TH>
	</TR>
	<TR VALIGN=BOTTOM>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*ahi*')">*ahi*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*ahem*')">*ahem*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*alleluia*')">*alleluia*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*applauso*')">*applauso*</A></TD>
	</TR>
	<TR VALIGN=BOTTOM>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*ops*')">*ops*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*bacio*')">*bacio*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*risata*')">*risata*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*risatina*')">*risatina*</A></TD>
	</TR>
	
		<TR VALIGN=BOTTOM>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*pianto*')">*pianto*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*telefono*')">*telefono*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*tosse*')">*tosse*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*vetro*')">*vetro*</A></TD>
	</TR>
	<TR VALIGN=BOTTOM>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*voila*')">*voila*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*arpa*')">*arpa*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*flauto*')">*flauto*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*citofono*')">*citofono*</A></TD>
	</TR>
	
	<TR VALIGN=BOTTOM>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*dong*')">*dong*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*boing*')">*boing*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*boom*')">*boom*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*trombe*')">*trombe*</A></TD>
	</TR>
	
	<TR VALIGN=BOTTOM>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*cane*')">*cane*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*gatto*')">*gatto*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*papera*')">*papera*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*gallina*')">*gallina*</A></TD>
	</TR>
	
	<TR VALIGN=BOTTOM>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*asino*')">*asino*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*cavallo*')">*cavallo*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*mucca*')">*mucca*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*scacciapensieri*')">*scacciapensieri*</A></TD>
	</TR>
	
	<TR VALIGN=BOTTOM>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*gabbiano*')">*gabbiano*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*grilli*')">*grilli*</A></TD>
		<TD ALIGN=CENTER><A HREF="#" onClick="Write_Input('*uccellino*')">*uccellino*</A></TD>
		
	</TR>
	</TABLE>
	
	  <BR><br>
	  

<TABLE BORDER=0 CELLPADDING=3 WIDTH=574 CLASS=table>
<!--<TR><TH ALIGN=CENTER CLASS=tabtitle COLSPAN=2>Comandi</TH></TR>-->
	<TR><TH ALIGN=LEFT COLSPAN=2><?php echo($stringa[non_verbali]);?></TH></TR>
	<TR>
		<TD WIDTH=10>&nbsp;</TD>
		<TD><?php echo($stringa[non_verbali_guida]);?></TD>
	</TR>	
	
	<TR><TH ALIGN=LEFT COLSPAN=2><?php echo($stringa[immagini_chat]);?></TH></TR>
	<TR>
		<TD WIDTH=10>&nbsp;</TD>
		<TD><?php echo($stringa[immagini_chat_guida]);?>
		
</TD>
	</TR>		
	
	
</TABLE>

</CENTER>
</BODY>

</HTML>
