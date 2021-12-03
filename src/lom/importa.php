<html> 
<head> 
<title>Importa Asset RCS</title> 
<body> 

<?php
$xml_file=$_FILES["xml_file"]["tmp_name"];
$xml_file_size=$_FILES["xml_file"]["size"];
$xml_file_name=$_FILES["xml_file"]["name"];

echo "
	<form action=importa.php method=post encType=multipart/form-data>
	File XML: <input type=file name=xml_file> 
	<input type=submit value=importa>
	</form>
	";
	
if ($xml_file) {

$contesto="";
$id_lom="";

$parser=xml_parser_create();
xml_set_element_handler($parser,"startElement","endElement"); xml_set_character_data_handler($parser, "characterData"); 

if (!($filehandler = fopen($xml_file, "r"))) { 
  die("non riesco ad aprire il file XML"); 
};


while ($data = fread($filehandler, 4096)) { 
  if (!xml_parse($parser, $data, feof($filehandler))) { 
    die(sprintf("XML error:%s at line %d", 
      xml_error_string(xml_get_error_code($parser)), 
      xml_get_current_line_number($parser))); 
  } 
}; 

fclose($filehandler); 

xml_parser_free($parser); 


};

?> 
</body> 
</html> 

<?php 

// Functions 

// When the parser encounters the start element of a tag 
function startElement($parser_instance, $element_name, $attrs) 
{ 
	global $contesto;
	global $id_lom;

	echo "$element_name <br>";
	switch($element_name) { 
		case "LOM" : 
			break;
	
		case "STRING":
			echo "language: $attrs[LANGUAGE]<br>";
			break;
		
		case "LANGSTRING":
			/*
			while (list($key,$value)=each($attrs)) {
				echo "$key : $value<br>";
			};
			*/
			echo "language: ".$attrs["XML:LANG"]."<br>";
			break;
		
    } 
};
 
// When the parser encounters the data within the start and end tag 
function characterData($parser_instance, $xml_data) { 
  echo $xml_data; 
  } 
  
// When the parser encounters the end element of a tag 
function endElement($parser_instance, $element_name) { 
echo "/$element_name<br>";
switch($element_name) { 
case "RCS_COMMON_METADATI" :   echo "</p>"; 
	break; 
case "RCS_OPERA_METADATI" :   echo "</p>"; 
	break; 
  } 
} 
?>

 
  
