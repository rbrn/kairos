<?php
$oggetto_img="";
			copia_oggetti($pagina,"src");
			
			if ($oggetto_img) {
				$oggetto_img=substr($oggetto_img,0,strlen($oggetto_img)-1);
				
				$oggetto_lista=split(",",$oggetto_img);
			};
			
			for ($i=0;$i<count($oggetto_lista);$i++) {
				$nome_file=basename($oggetto_lista[$i]);
				$link=$oggetto_lista[$i];
				
				$url_base=substr($link,0,strlen($link)-strlen($nome_file));
				
				$pagina=str_replace($url_base,"img/",$pagina);
			};
			
			$oggetto_link="";
			copia_oggetti($pagina,"href");
			
			if ($oggetto_link) {
				$oggetto_link=substr($oggetto_link,0,strlen($oggetto_link)-1);
				$oggetto_lista=split(",",$oggetto_link);
			};
			
			for ($i=0;$i<count($oggetto_lista);$i++) {
			
				$link=$oggetto_lista[$i];	$nome_file=substr($link,strpos($link,"=")+1,strlen($link)).".htm";
				
				$pagina=str_replace($link,$nome_file,$pagina);
			};
			
			$oggetto_link="";
			copia_oggetti($pagina,"nota");
			
			if ($oggetto_link) {
				$oggetto_link=substr($oggetto_link,0,strlen($oggetto_link)-1);
				$oggetto_lista=split(",",$oggetto_link);
			};
			
			for ($i=0;$i<count($oggetto_lista);$i++) {
			
				$link=$oggetto_lista[$i];					
$nome_file=substr($link,strpos($link,"=")+1,strlen($link)).".htm";
				$pagina=str_replace($link,$nome_file,$pagina);
			};
			
?>
