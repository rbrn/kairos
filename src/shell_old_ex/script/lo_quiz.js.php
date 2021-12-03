<?php
require "../../include/init_sito.inc";
function genera_funzione_feedback($nome_item,$id_item) {
	global $db,$DBASE;
	echo "function feedback_".$nome_item."(punteggio) {\n";
	
	echo "var str_feedback='';";
	mysql_select_db($DBASE,$db);	
	$query = "SELECT * FROM lo_test_commento WHERE id_item='$id_item' and tipo_elemento='id_item'";
	$result=$mysqli->query($query);
	while ($riga=$result->fetch_array()) {
		$lim_inf=$riga["lim_inf"];
		$lim_sup=$riga["lim_sup"];
		$commento=addslashes(($riga["commento"]));
		echo "if (punteggio>=".$lim_inf." && punteggio<=".$lim_sup.") str_feedback='".$commento."';";
	};
	echo "return str_feedback;";
	echo "};";

};

function estrai_item($id_risorsa) {
	global $db,$DBASE;
	global $item_id,$max_score;
	
	mysql_select_db($DBASE,$db);	
	$query="SELECT * FROM risorse_materiali WHERE risorsa_padre='$id_risorsa' AND (tipo='201' or tipo='20') ORDER BY posizione";
	$result=$mysqli->query($query);
	
	while ($riga=$result->fetch_array()) {
		$id_risorsa=$riga["id_risorsa"];
		$titolo=$riga["titolo"];
		$tipo_risorsa=$riga["tipo"];

		switch ($tipo_risorsa) {
			case '20':
				estrai_item($id_risorsa);
				break;
			
			case '201':
				$id_item=$riga["id_gruppo"];
				$item_id[]=$id_item;
				$query_o="SELECT punteggio FROM lo_test_item_opzioni WHERE id_item='$id_item'";
				$result_o=$mysqli->query($query_o);
				while ($item_opzione=$result_o->fetch_array()) {
					$max_score += $item_opzione["punteggio"];
				}
				break;
				
		};
	};
}


$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_risorsa=$_REQUEST["id_risorsa"];

$n_item=0;
$max_score=0;

estrai_item($id_risorsa);

$num_domande=count($item_id);

?>

function trim(s) {
  while (s.substring(0,1) == ' ') {
    s = s.substring(1,s.length);
  }
  while (s.substring(s.length-1,s.length) == ' ') {
    s = s.substring(0,s.length-1);
  }
  return s;
}


   var num_domande = <?php echo $num_domande ?>;
   var max_score = <?php echo $max_score ?>;
   var score = 0;

<?php
for ($i=0;$i<$num_domande;$i++) {
	$i1=$i+1;
	$id_item=$item_id[$i];
	$query_i = "SELECT * FROM lo_test_item WHERE id_item='$id_item'";
	$result_i=$mysqli->query($query_i);
				
	$item=$result_i->fetch_array();
	$tipo_item = $item["tipo_item"];
	$nome_item="Q_".$i1;
	
	genera_funzione_feedback($nome_item,$id_item);
	
	switch ($tipo_item) {
	
		case "1"://risposta multipla/scelta singola
			echo "
			function checkAnswer_".$nome_item."()\n
			{\n";
			$query_o="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' ORDER BY posizione";
			$result_o=$mysqli->query($query_o);
			echo "var punti_opzione = new Array();\n";
			$j=0;
			$risposte_corrette="";
			while ($item_opzione=$result_o->fetch_array()) {
				$punteggio=$item_opzione["punteggio"];
				$risposta_opzione=addslashes($item_opzione["risposta_opzione"]);
				if ($punteggio>0) {
					$risposte_corrette.=$risposta_opzione.",";
				};
				echo "
				punti_opzione[$j]='$punteggio';\n";
				$j++;
			};
			$risposte_corrette=substr($risposte_corrette,0,-1);
			echo "
				LMSSetValue(\"cmi.interactions.$i.id\",\"".$nome_item."\");\n
     			LMSSetValue(\"cmi.interactions.$i.type\",\"choice\");\n";
			echo "	LMSSetValue(\"cmi.interactions.$i.correct_responses.0.pattern\",\"".$risposte_corrette."\");\n";
			
			echo "
				var score_item=0;
				var risposta='';\n
				var icona='';\n
				var domanda='Q_".$i1."';\n
				var elementi=document.getElementsByName(domanda);\n
				for (var i=0; i<elementi.length; i++) {\n
					elementi[i].disabled=true;\n
					if (elementi[i].checked) {\n
						risposta=elementi[i].value;\n
						LMSSetValue(\"cmi.interactions.$i.student_response\",risposta);\n
						var k=i+1;\n
						var opzione=domanda+'_opzione'+k;\n
						var span=document.getElementById(opzione);\n
						if (punti_opzione[i]>0) {\n
							span.className='giusto';\n
							icona='&nbsp;<img src=\"shell/img/approvo.gif\" alt=\"ok\">';\n
							score+=1*punti_opzione[i];\n
							score_item+=1*punti_opzione[i];\n
							LMSSetValue(\"cmi.interactions.$i.result\",\"correct\");\n
						} else {\n
							span.className='sbagliato';\n
							icona='&nbsp;<img src=\"shell/img/disapprovo.gif\" alt=\"sbagliato\">';\n
							LMSSetValue(\"cmi.interactions.$i.result\",\"wrong\");\n
						};\n
						var codice=span.innerHTML;\n
						codice += icona;\n
						span.innerHTML=codice;\n
					};\n
				};\n
				var pulsante=document.getElementById('verifica$i1');\n
				pulsante.style.display=\"none\";\n
				var msg=feedback_".$nome_item."(score_item);
				inviamessaggio(msg,'$nome_item');\n
				
				";
				
				
			break;
			
			
		case "2"://risposta multipla/scelta multipla
			echo "
			function checkAnswer_".$nome_item."()\n
			{\n";
			$query_o="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' ORDER BY posizione";
			$result_o=$mysqli->query($query_o);
			$n_opzioni=$result_o->num_rows;
			echo "var punti_opzione = new Array();\n";
			$j=0;
			$risposte_corrette="";
			while ($item_opzione=$result_o->fetch_array()) {
				$punteggio=$item_opzione["punteggio"];
				$risposta_opzione=addslashes($item_opzione["risposta_opzione"]);
				if ($punteggio>0) {
					$risposte_corrette.=$risposta_opzione.",";
				};
				echo "
				punti_opzione[$j]='$punteggio';\n";
				$j++;
			};
			$risposte_corrette=substr($risposte_corrette,0,-1);
			echo "
				LMSSetValue(\"cmi.interactions.$i.id\",\"".$nome_item."\");\n
     			LMSSetValue(\"cmi.interactions.$i.type\",\"choice\");\n";
			echo "	LMSSetValue(\"cmi.interactions.$i.correct_responses.0.pattern\",\"".$risposte_corrette."\");\n";
			
			echo "
				var risposta='';\n
				var score_item=0;
				var icona='';\n
				var domanda='Q_".$i1."';\n
				var elemento;\n
				var opzione;\n
				var k=0;\n
				for (var i=0; i<".$n_opzioni."; i++) {\n
					k=i+1;\n
					opzione_box='box_'+domanda+'_opzione'+k;\n
					opzione_blocco=domanda+'_opzione'+k;\n
					elemento_box=document.getElementById(opzione_box);\n
					elemento_blocco=document.getElementById(opzione_blocco);\n
					elemento_box.disabled=true;\n
					if (elemento_box.checked) {\n
						risposta+=elemento_box.value+',';\n
						
						if (punti_opzione[i]>0) {\n
							elemento_blocco.className='giusto';\n
							icona='&nbsp;<img src=\"shell/img/approvo.gif\" alt=\"ok\">';\n
							score+=1*punti_opzione[i];\n
							score_item+=1*punti_opzione[i];\n
							LMSSetValue(\"cmi.interactions.$i.result\",\"correct\");\n
						} else {\n
							elemento_blocco.className='sbagliato';\n
							icona='&nbsp;<img src=\"shell/img/disapprovo.gif\" alt=\"sbagliato\" align=\"middle\">';\n
						};\n
						var codice=elemento_blocco.innerHTML;\n
						codice += icona;\n
						elemento_blocco.innerHTML=codice;\n
					};\n
				};\n
				LMSSetValue(\"cmi.interactions.$i.student_response\",risposta);\n
				var pulsante=document.getElementById('verifica$i1');\n
				pulsante.style.display=\"none\";\n
				var msg=feedback_".$nome_item."(score_item);
				inviamessaggio(msg,'$nome_item');\n
				";
				
			break;
			
		case "3"://vero-falso
			echo "
			function checkAnswer_".$nome_item."()\n
			{\n";
			$query_o="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' ORDER BY posizione";
			$result_o=$mysqli->query($query_o);
			echo "var punti_opzione = new Array();\n";
			$j=0;
			$risposte_corrette="";
			while ($item_opzione=$result_o->fetch_array()) {
				$punteggio=$item_opzione["punteggio"];
				$risposta_opzione=addslashes($item_opzione["risposta_opzione"]);
				if ($punteggio>0) {
					$risposte_corrette.=$risposta_opzione.",";
				};
				echo "
				punti_opzione[$j]='$punteggio';\n";
				$j++;
			};
			$risposte_corrette=substr($risposte_corrette,0,-1);
			echo "
				LMSSetValue(\"cmi.interactions.$i.id\",\"".$nome_item."\");\n
     			LMSSetValue(\"cmi.interactions.$i.type\",\"true-false\");\n";
			echo "	LMSSetValue(\"cmi.interactions.$i.correct_responses.0.pattern\",\"".$risposte_corrette."\");\n";
			
			echo "
				var risposta='';\n
				var score_item=0;
				var icona='';\n
				var domanda='Q_".$i1."';\n
				var elementi=document.getElementsByName(domanda);\n
				for (var i=0; i<elementi.length; i++) {\n
					elementi[i].disabled=true;\n
					if (elementi[i].checked) {\n
						risposta=elementi[i].value;\n
						LMSSetValue(\"cmi.interactions.$i.student_response\",risposta);\n
						var k=i+1;\n
						var opzione=domanda+'_opzione'+k;\n
						var span=document.getElementById(opzione);\n
						if (punti_opzione[i]>0) {\n
							span.className='giusto';\n
							icona='&nbsp;<img src=\"shell/img/approvo.gif\" alt=\"ok\">';\n
							score+=1*punti_opzione[i];\n
							score_item+=1*punti_opzione[i];\n
							LMSSetValue(\"cmi.interactions.$i.result\",\"correct\");\n
						} else {\n
							span.className='sbagliato';\n
							icona='&nbsp;<img src=\"shell/img/disapprovo.gif\" alt=\"sbagliato\">';\n
							LMSSetValue(\"cmi.interactions.$i.result\",\"wrong\");\n
						};\n
						var codice=span.innerHTML;\n
						codice += icona;\n
						span.innerHTML=codice;\n
					};\n
				};\n
				var pulsante=document.getElementById('verifica$i1');\n
				pulsante.style.display=\"none\";\n
				var msg=feedback_".$nome_item."(score_item);
				inviamessaggio(msg,'$nome_item');\n
				";
				
				
			break;
			
		case '4':
			echo "
			function checkAnswer_".$nome_item."()\n
			{\n";
			
			$query_o="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' ORDER BY posizione";
			$result_o=$mysqli->query($query_o);
			$n_spazi=$result_o->num_rows;
			echo "var punti_opzione = new Array();\n";
			echo "var risposta_giusta = new Array();\n";
			echo "var case_matters = new Array();\n";
			echo "var popup_list = new Array();\n";
			$j=0;
			$risposte_corrette="";
			while ($item_opzione=$result_o->fetch_array()) {
				$punteggio=$item_opzione["punteggio"];
				$risposta_giusta=(($item_opzione["risposta_giusta"]));
				$case_sensitive = $item_opzione["case_sensitive"];
				$risposte_lista=trim($item_opzione["risposte_lista"]);
				$pull_down=trim($item_opzione["pull_down"]);
				if ($risposte_lista<>'' and !$pull_down) {
					echo "popup_list[$j]='true';\n";
				} else {
					echo "popup_list[$j]='false';\n";
				};
				if (!$case_sensitive) {
					$risposta_giusta=strtolower($risposta_giusta);
					echo "case_matters[$j]='false';\n";
				} else {
					echo "case_matters[$j]='true';\n";
				};
				if ($punteggio>0) {
					$risposte_corrette.=$risposta_giusta.",";
				};
				echo "
				punti_opzione[$j]='$punteggio';\n";
				echo "
				risposta_giusta[$j]='".addslashes(($risposta_giusta))."';\n";
				$j++;
			};
			$risposte_corrette=substr($risposte_corrette,0,-1);
			echo "
				LMSSetValue(\"cmi.interactions.$i.id\",\"".$nome_item."\");\n
     			LMSSetValue(\"cmi.interactions.$i.type\",\"fill-in\");\n";
			echo "	LMSSetValue(\"cmi.interactions.$i.correct_responses.0.pattern\",\"{order_matters=true}".$risposte_corrette."\");\n";
			
			echo "
				var risposta='';\n
				var score_item=0;
				var icona='';\n
				var domanda='Q_".$i1."';\n
				var elemento;\n
				var opzione;\n
				var k=0;\n
				
				for (var i=0; i<".$n_spazi."; i++) {\n
					k=i+1;\n
					spazio='spazio_'+domanda+'_opzione'+k;\n
					blocco=domanda+'_opzione'+k;\n
					
					elemento_spazio=document.getElementById(spazio);\n
					elemento_blocco=document.getElementById(blocco);\n
					elemento_spazio.disabled=true;\n";
					echo "
					var risposta_valore=String(elemento_spazio.value)\n";
					
					echo "
					if (case_matters[i]=='false') {
						risposta_valore=risposta_valore.toLowerCase();\n
					};\n";
					
					echo "
					if (popup_list[i]=='true') {	
						blocco_popup='popup_'+blocco;\n
						elemento_blocco_popup=document.getElementById(blocco_popup);\n
						elemento_blocco_popup.style.display='none';\n
					};\n";
					
					echo "
					risposta+=trim(risposta_valore)+',';\n
					if (trim(risposta_giusta[i])==trim(risposta_valore)) {\n
						elemento_blocco.className='giusto';\n
						icona='&nbsp;<img src=\"shell/img/approvo.gif\" alt=\"ok\">';\n
						score+=1*punti_opzione[i];\n
						score_item+=1*punti_opzione[i];\n
						//LMSSetValue(\"cmi.interactions.$i.result\",\"correct\");\n
					} else {\n
						elemento_blocco.className='sbagliato';\n
						icona='&nbsp;<img src=\"shell/img/disapprovo.gif\" alt=\"sbagliato\">';\n
						//LMSSetValue(\"cmi.interactions.$i.result\",\"wrong\");\n
					};\n
					var codice=elemento_blocco.innerHTML;\n
					codice += icona;\n
					elemento_blocco.innerHTML=codice;\n
				};\n
				LMSSetValue(\"cmi.interactions.$i.student_response\",risposta);\n
				var pulsante=document.getElementById('verifica$i1');\n
				pulsante.style.display=\"none\";\n
				var msg=feedback_".$nome_item."(score_item);
				inviamessaggio(msg,'$nome_item');\n
				";
			break;
		
		case '5':
			//match
			echo "
			function checkAnswer_".$nome_item."()\n
			{\n";
			
			$query_o="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item' AND tipo_opzione='1' ORDER BY posizione";
			$result_o=$mysqli->query($query_o);
			$n_match=$result_o->num_rows;
			echo "var punti_opzione = new Array();\n";
			echo "var elemento_sx = new Array();\n";
			echo "var risposta_giusta = new Array();\n";
			$j=0;
			$risposte_corrette="";
			while ($item_opzione=$result_o->fetch_array()) {
				$punteggio=$item_opzione["punteggio"];
				$id_item_opzione=$item_opzione["id_item_opzione"];
				$id_item_esatto=($item_opzione["id_item_esatto"]);
				if ($punteggio>0) {
					$risposte_corrette.=$id_item_opzione.".".$id_item_esatto.",";
				};
				echo "
				punti_opzione[$j]='$punteggio';\n";
				echo "
				elemento_sx[$j]='".$id_item_opzione."';\n
				risposta_giusta[$j]='".$id_item_esatto."';\n";
				$j++;
			};
			$risposte_corrette=substr($risposte_corrette,0,-1);
			echo "
				LMSSetValue(\"cmi.interactions.$i.id\",\"".$nome_item."\");\n
     			LMSSetValue(\"cmi.interactions.$i.type\",\"matching\");\n";
			echo "	LMSSetValue(\"cmi.interactions.$i.correct_responses.0.pattern\",\"".$risposte_corrette."\");\n";
			
			echo "
				var risposta='';\n
				var score_item=0;
				var icona='';\n
				var domanda='Q_".$i1."';\n
				var elemento;\n
				var opzione;\n
				var k=0;\n
				for (var i=0; i<".$n_match."; i++) {\n
					k=i+1;\n
					coppia='coppia_'+domanda+'_opzione'+k;\n
					blocco=domanda+'_opzione'+k;\n
					elemento_coppia=document.getElementById(coppia);\n
					elemento_blocco=document.getElementById(blocco);\n
					elemento_coppia.disabled=true;\n";
					echo "
					var risposta_valore=String(elemento_coppia.value)\n";
								
					echo "
					risposta+=trim(elemento_sx[i])+'.'+trim(risposta_valore)+',';\n
					if (trim(risposta_giusta[i])==trim(risposta_valore)) {\n
						elemento_blocco.className='giusto';\n
						icona='&nbsp;<img src=\"shell/img/approvo.gif\" alt=\"ok\" align=\"top\">';\n
						score+=1*punti_opzione[i];\n
						score_item+=1*punti_opzione[i];\n
						//LMSSetValue(\"cmi.interactions.$i.result\",\"correct\");\n
					} else {\n
						elemento_blocco.className='sbagliato';\n
						icona='&nbsp;<img src=\"shell/img/disapprovo.gif\" alt=\"sbagliato\" align=\"top\">';\n
						//LMSSetValue(\"cmi.interactions.$i.result\",\"wrong\");\n
					};\n
					var codice=elemento_blocco.innerHTML;\n
					codice += icona;\n
					elemento_blocco.innerHTML=codice;\n
				};\n
				LMSSetValue(\"cmi.interactions.$i.student_response\",risposta);\n
				var pulsante=document.getElementById('verifica$i1');\n
				pulsante.style.display=\"none\";\n
				var msg=feedback_".$nome_item."(score_item);
				inviamessaggio(msg,'$nome_item');\n
				";
			
			break;
		
		case '6':
			echo "
			function checkAnswer_".$nome_item."()\n
			{\n";
			
			$query_o="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item'";
			$result_o=$mysqli->query($query_o);
			$risposte_corrette="";
			$item_opzione=$result_o->fetch_array();
			$punteggio=$item_opzione["punteggio"];
			$case_sensitive=$item_opzione["case_sensitive"];
			$risposta_giusta=addslashes(($item_opzione["risposta_giusta"]));
			if ($case_sensitive) {
				$risposte_corrette="{case_matters=true}$risposta_giusta";
			} else {
				$risposta_giusta=strtolower($risposta_giusta);
				$risposte_corrette="{case_matters=false}$risposta_giusta";
			};
			echo "
				var punti_opzione='$punteggio';\n";
			echo "
				var risposta_giusta='".$risposta_giusta."';\n";
			echo "
				LMSSetValue(\"cmi.interactions.$i.id\",\"".$nome_item."\");\n
     			LMSSetValue(\"cmi.interactions.$i.type\",\"short-answer\");\n";
			echo "	LMSSetValue(\"cmi.interactions.$i.correct_responses.0.pattern\",\"".$risposte_corrette."\");\n";
			
			echo "
				var risposta='';\n
				var score_item=0;
				var icona='';\n
				var domanda='Q_".$i1."';\n
				var elemento;\n
				var opzione;\n
				var k=0;\n

				aperta='aperta_'+domanda;\n
				blocco=domanda+'_blocco';\n
				elemento_aperta=document.getElementById(aperta);\n
				elemento_blocco=document.getElementById(blocco);\n
				elemento_aperta.disabled=true;\n";
				echo "
				var risposta_valore=String(elemento_aperta.value);\n";
				
				if (!$case_sensitive)	{
					echo "risposta_valore=risposta_valore.toLowerCase();\n";
				}			
				echo "
				risposta=trim(risposta_valore);\n
				if (trim(risposta_giusta)==trim(risposta_valore)) {\n
					elemento_blocco.className='giusto';\n
					icona='&nbsp;<img src=\"shell/img/approvo.gif\" alt=\"ok\" align=\"top\">';\n
					score+=1*punti_opzione;\n
					score_item+=1*punti_opzione[i];\n
					LMSSetValue(\"cmi.interactions.$i.result\",\"correct\");\n
				} else {\n
					elemento_blocco.className='sbagliato';\n
					icona='&nbsp;<img src=\"shell/img/disapprovo.gif\" alt=\"sbagliato\" align=\"top\">';\n
					LMSSetValue(\"cmi.interactions.$i.result\",\"wrong\");\n
				};\n
				var codice=elemento_blocco.innerHTML;\n
				codice += icona;\n
				elemento_blocco.innerHTML=codice;\n
				LMSSetValue(\"cmi.interactions.$i.student_response\",risposta);\n
				var pulsante=document.getElementById('verifica$i1');\n
				pulsante.style.display=\"none\";\n
				var msg=feedback_".$nome_item."(score_item);
				inviamessaggio(msg,'$nome_item');\n
				";
			
			break;
			
		case '7':
			echo "
			function checkAnswer_".$nome_item."(ipagina)\n
			{\n";
			
			echo "
				var risposta='';
				for (var i=0;i<oggetto_dragdrop.length;i++) {\n
					if (oggetto_dragdrop[i].tipo==1 && oggetto_dragdrop[i].indice_pagina==ipagina) {\n
						var id_item_esatto=oggetto_dragdrop[i].id_item_esatto;\n
						var id_item_preso=oggetto_dragdrop[i].target_preso.id_item_opzione;\n
						risposta+=id_item_preso+'.'+oggetto_dragdrop[i].id_item+',';
						if (id_item_preso==id_item_esatto) {\n
							icona='&nbsp;<img src=\"shell/img/approvo.gif\" alt=\"ok\">';\n
							score+=1*oggetto_dragdrop[i].punteggio;\n
						} else {\n
							icona='&nbsp;<img src=\"shell/img/disapprovo.gif\" alt=\"sbagliato\">';\n
						};\n
						elemento_blocco=document.getElementById(oggetto_dragdrop[i].id);\n
						var codice=elemento_blocco.innerHTML;\n
						codice += icona;\n
						elemento_blocco.innerHTML=codice;
						elemento_blocco.onmousedown='';\n
					};\n
				};\n
				
				LMSSetValue(\"cmi.interactions.$i.id\",\"".$nome_item."\");\n
     			LMSSetValue(\"cmi.interactions.$i.type\",\"matching\");\n
				LMSSetValue(\"cmi.interactions.$i.student_response\",risposta);\n
				var pulsante=document.getElementById('verifica$i1');\n
				pulsante.style.display=\"none\";\n";		
			break;
			
	};
	if ($i==$num_domande-1) {
		echo "
					LMSSetValue( \"cmi.core.score.max\", max_score );
     				LMSSetValue( \"cmi.core.score.raw\", score );
					var actualScore=0;
					if (max_score > 0) {
						actualScore = (score * 100)/max_score
					}
					if ( actualScore <= 60 ) {
          				LMSSetValue( \"cmi.core.lesson_status\", \"failed\" );
        			} else {
        				LMSSetValue( \"cmi.core.lesson_status\", \"passed\" );
      				};
					
					//alert('punteggio: '+score+' su max: '+$max_score);
					";
	};
				
	echo "
	test_fatto=true;\n
	tipo_blocco[tutorialeattivo]='test_fatto';\n
	return false;\n
	};\n";
};
?>

function textCounter(field,counter,maxlimit,linecounter) {
	
	var fieldWidth =  parseInt(field.offsetWidth);
	var charcnt = field.value.length;        

	
	if (charcnt > maxlimit) { 
		field.value = field.value.substring(0, maxlimit);
	}

	else { 
	
	var percentage = parseInt(100 - (( maxlimit - charcnt) * 100)/maxlimit) ;
	var w=200;
	/*
	if (parseInt((fieldWidth*percentage)/100) > 20) {
		w=parseInt((fieldWidth*percentage)/100);
	};
	*/
	document.getElementById(counter).style.width =  w+"px";
	document.getElementById(counter).innerHTML="Caratteri: "+charcnt+" su max "+maxlimit
	
	setcolor(document.getElementById(counter),percentage,"background-color");
	}
}

function setcolor(obj,percentage,prop){
	obj.style[prop] = "rgb(80%,"+(100-percentage)+"%,"+(100-percentage)+"%)";
}

function update_check(FormName,divName,nome_item,max_risposte) {
	
	
	var div=document.getElementById(divName);
		
		
	var objCheckBoxes = div.getElementsByTagName('input');
	
	if(!objCheckBoxes)
		return;
	
	var countCheckBoxes = objCheckBoxes.length;
	
	if (countCheckBoxes) {
		var n_checked=0;
		for (var i = 0; i < countCheckBoxes; i++) {
			if (objCheckBoxes[i].checked) {
				n_checked++;
				if (n_checked>max_risposte) {
					var msg="massimo "+max_risposte+" risposte";
					inviamessaggio(msg,nome_item);
					objCheckBoxes[i].checked=false;
				}
			}
		}
				
	}
}

function SetAllCheckBoxes(FormName, FieldName, CheckValue)
{
	if(!document.forms[FormName])
		return;
	var objCheckBoxes = document.forms[FormName].elements[FieldName];
	if(!objCheckBoxes)
		return;
	var countCheckBoxes = objCheckBoxes.length;
	if(!countCheckBoxes)
		objCheckBoxes.checked = CheckValue;
	else
		// set the check value for all check boxes
		for(var i = 0; i < countCheckBoxes; i++)
			objCheckBoxes[i].checked = CheckValue;
}

function go(url) {
	self.location.href=url;
}

function popup(url,titolo,w,l,scroll,resizable){
	var winl = (screen.width-w)/2;
    var wint = (screen.height-l)/2;
	window.open(url, titolo, "toolbar=no, menubar=no, status=no, titlebar=yes,scrollbars="+scroll+", resizable="+resizable+", width="+w+", height="+l+", top="+wint+", left="+winl);
};


