<?php
/* registro i valori di tutti i campi del lo */
	$query="SELECT * FROM lo_metadata WHERE id_lo='$id_lo'";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$id_lom_r=$riga[id_lom];
		$id_rep_sup_r=$riga[id_rep_sup];
		$id_rep_r=$riga[id_rep];
		
		$query1="SELECT * FROM lo_schema WHERE id_lom='$id_lom_r' AND id_profile='$id_profile'";
		$result1=$mysqli->query($query1);
		$riga1=$result1->fetch_array();
		$tipocampo=$riga1[tipocampo];
		$langstring=$riga1[langstring];
		if ($tipocampo) {
            $id_lom_r=str_replace(".","-",$id_lom_r);
            $id_campo_r=$id_rep_sup_r."_".$id_rep_r."_".$id_lom_r;
			$valore=$_REQUEST[$id_campo_r];
			if ($langstring) {
				$id_campo_r_l=$id_campo_r."_lang_0";
				$lang=$_REQUEST[$id_campo_r_l];
				$query1="UPDATE lo_metadata SET valore='$valore',lang='$lang' WHERE id_rep='$id_rep_r'";
				
				// aggiornare altre lang
				$k=1;
				$id_campo_r_l=$id_campo_r."_lang_".$k;
				$id_campo_r_v=$id_campo_r."_".$k;
				$lang=$_REQUEST[$id_campo_r_l];
				$valore=$_REQUEST[$id_campo_r_v];
				
				while ($lang) {
					$query2="UPDATE lo_metadata_valore SET valore='$valore',lang='$lang' WHERE id_rep='$id_rep_r' AND n='$k'";
					$mysqli->query($query2);			
					$k++;		
					$id_campo_r_l=$id_campo_r."_lang_".$k;
					$id_campo_r_v=$id_campo_r."_".$k;
					$lang=$_REQUEST[$id_campo_r_l];
					$valore=$_REQUEST[$id_campo_r_v];
				};
			
			} else {
				$query1="UPDATE lo_metadata SET valore='$valore' WHERE id_rep='$id_rep_r'";
			};
			$mysqli->query($query1);
		};
	};
/* ---------------- */
?>
