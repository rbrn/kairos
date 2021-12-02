<?php
require "./include/init_sito.inc";

$db = mysql_connect("localhost",$DBUSER,$DBPWD);
mysql_select_db($DBASE,$db);	

$id_cartella=$_REQUEST["id_cartella"];
$risorsa_padre=$_REQUEST["id_cartella"];
$id_item0=$_REQUEST["id_item"];
$op=$_REQUEST["op"];
switch ($op) {
	case "annulla":
		setcookie("kairos_cookie_copia_item","",0,"/");
		break;
		
	case "ok":
		//setcookie("kairos_cookie_copia_item","",0,"/");
		$query="SELECT * FROM lo_test_item WHERE id_item='$id_item0'";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		

		$tipo_item=$riga["tipo_item"];
		$titolo=addslashes($riga["titolo"]);
		$consegna=addslashes($riga["legend"]);
		$mostra_titolo=$riga["mostra_titolo"];
		$domanda=addslashes($riga["domanda"]);
		$id_utente=$kairos_cookie[0];
		$altro=$riga["altro"];
		$peso=$riga["peso"];
		$msg_ok=addslashes($riga["msg_ok"]);
		$msg_ko=addslashes($riga["msg_ko"]);

		$query = "INSERT INTO lo_test_item SET  
		tipo_item='$tipo_item',
		domanda='$domanda',
		titolo='$titolo',
		legend='$consegna',
		mostra_titolo='$mostra_titolo',
		id_editor='$id_utente',
		altro='$altro',
		peso='$peso',
		msg_ok='$msg_ok',
		msg_ko='$msg_ko'";
		$result=$mysqli->query($query);
		
		$id_item=$mysqli->insert_id;

		$query="SELECT max(posizione) AS num_pag FROM risorse_materiali WHERE risorsa_padre='$risorsa_padre' AND (tipo='20' or tipo='200' or tipo='201' or tipo='202')";
		$result=$mysqli->query($query);
		$riga=$result->fetch_array();
		$posizione=$riga[num_pag]+1;

		$id_risorsa=uniqid("item_");
		$query = "INSERT INTO risorse_materiali SET  
		id_risorsa='$id_risorsa',
		tipo='201',
		titolo='$titolo',
		risorsa_padre='$risorsa_padre',
		posizione='$posizione',
		id_editor='$id_utente',
		id_autore='$id_utente',
		data_crea=now(),
		data_mod=now(),
		livello='1',
		id_gruppo='$id_item'
		";
		$result=$mysqli->query($query);

		$query="INSERT INTO materiale_storia SET"
		." id_risorsa='$id_risorsa',"
		." id_utente='$id_utente',"
		." evento='creato',"
		." data_evento=NOW()";
		$mysqli->query($query);
		
		
		switch ($tipo_item) {
			case "1":
			case "2":
			case "3":
			case "4":
			case "5":
			case "6":
			case "7":
			case "8":
			case "9":
				
				$query="SELECT * FROM lo_test_item_opzioni WHERE id_item='$id_item0'";
				$result=$mysqli->query($query);
				while ($riga=$result->fetch_array()) {
					$id_item_opzione=$riga["id_item_opzione"];
					$posizione=$riga["posizione"];
					$risposta_opzione=$riga["risposta_opzione"];
					$tipo_opzione=$riga["tipo_opzione"];
					$punteggio=$riga["punteggio"];
					$risposta_giusta=addslashes($riga["risposta_giusta"]);
					$risposte_lista=addslashes($riga["risposte_lista"]);
					$pull_down=$riga["pull_down"];
					$limite_caratteri=$riga["limite_caratteri"];
					$id_item_esatto=$riga["id_item_esatto"];
					$case_sensitive=$riga["case_sensitive"];
					$id_editor=$id_utente;
					
					$query1="INSERT INTO lo_test_item_opzioni SET "
					."id_item='$id_item',"
					."posizione='$posizione',"
					."risposta_opzione='$risposta_opzione',"
					."tipo_opzione='$tipo_opzione',"
					."punteggio='$punteggio',"
					."risposta_giusta='$risposta_giusta',"
					."risposte_lista='$risposte_lista',"
					."pull_down='$pull_down',"
					."limite_caratteri='$limite_caratteri',"
					."id_item_esatto='$id_item_esatto',"
					."case_sensitive='$case_sensitive',"
					."id_editor='$id_editor'";
					$mysqli->query($query1);
					
					$id_item_opzione_nuovo=$mysqli->insert_id;
					$lista_item["$id_item_opzione"]=$id_item_opzione_nuovo;
				};
				
				if (count($lista_item)) {
					reset($lista_item);
					while (list($chiave, $valore) = each($lista_item)) {
						$id_item_vecchio=$chiave;
						$id_item_nuovo=$valore;
						$query1="UPDATE lo_test_item_opzioni SET id_item_esatto='$id_item_nuovo' WHERE id_item_esatto='$id_item_vecchio' AND id_item='$id_item'";
						$mysqli->query($query1);
					}
				}
				
				break;
			
			case "10":
				$query="SELECT * FROM lo_test_item_cruciverba WHERE id_item='$id_item0'";
				$result=$mysqli->query($query);
				$riga=$result->fetch_array();
				$larghezza=$riga["larghezza"];
				$altezza=$riga["altezza"];
				$query="INSERT INTO lo_test_item_cruciverba SET "
				."id_item='$id_item',"
				."larghezza='$larghezza',"
				."altezza='$altezza'";
				$mysqli->query($query);
				
				$query="SELECT * FROM lo_test_item_opzioni_cruciverba WHERE id_item='$id_item0'";
				$result=$mysqli->query($query);
				while ($riga=$result->fetch_array()) {
					$posizione=$riga["posizione"];
					$etichetta=$riga["etichetta"];
					$verso=$riga["verso"];
					$definizione=addslashes($riga["definizione"]);
					$risposta_giusta=addslashes($riga["risposta_giusta"]);
					$msg_ko=addslashes($riga["msg_ko"]);
					
					$query1="INSERT INTO lo_test_item_opzioni_cruciverba SET "
					."id_item='$id_item',"
					."posizione='$posizione',"
					."etichetta='$etichetta',"
					."verso='$verso',"
					."definizione='$definizione',"
					."risposta_giusta='$risposta_giusta',"
					."msg_ko='$msg_ko'";
					$mysqli->query($query1);
				};
				
			
		};
		break;
		
};


$url="index.php?risorsa=repository_index&id_cartella=$id_cartella";
Header("Location: $url");

?>
