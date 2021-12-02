<?php
function multi_strpos($pattern, $sequence) {
  $n = -1;
  while (eregi($pattern, $sequence)) {
    $n++;
    $fragment = split($pattern, $sequence);
    $trimsize = (strlen($fragment[0]))+1;
    $sequence = "*".substr($sequence, $trimsize);
    $position[$n] = (strlen($fragment[0]) + $position[($n-1)]);
   };

  return $position;

};

$stringa="<ul><li>math:-6x-4=3x-2[alt]meno sei ics meno quattro uguale tre ics meno due[/alt]:/math non ÃÂÃÂ¨ un'identitÃÂÃÂ , il primo membro ÃÂÃÂ¨ diverso dal secondo membro</li><li>math:3(x+y)=3x+3y[alt]tre ics aperta tonda ics piÃÂÃÂ¹ ipsilon chiusa tonda uguale tre ics piÃÂÃÂ¹ tre ipsilon[/alt]:/math<br />Sviluppando il prodotto al primo membro si ottieneÃÂÃÂ math:3x+3y=3x+3y[alt]tre ics piÃÂÃÂ¹ tre ipsilon ugualeÃÂÃÂ tre ics piÃÂÃÂ¹ tre ipsilon[/alt]:/math, quindi ÃÂÃÂ¨ un'identitÃÂÃÂ </li><li>math:\frac{x^2}2+3x=x(\frac{x}2 +3)[alt]ics quadro mezzi piÃÂÃÂ¹ tre ics uguale ics aperta tonda ics mezzi piÃÂÃÂ¹ tre chiusa tonda[/alt]:/math<br />Sviluppando il prodotto al secondo membro si ottieneÃÂÃÂ math:\frac{x^2}2+3x=x(\frac{x^2}2 +3x)[alt]ics quadro mezzi piÃÂÃÂ¹ tre ics ugualeÃÂÃÂ ics quadro mezzi piÃÂÃÂ¹ tre ics[/alt]:/math, quindi ÃÂÃÂ¨ un'identitÃÂÃÂ </li><li>math:x^2-2x=x(x+2)[alt]ics quadro meno due ics uguale ics aperta tonda icsÃÂÃÂ piÃÂÃÂ¹ due chiusa tonda[/alt]:/math<br />Sviluppando il prodotto al secondo membro si ottieneÃÂÃÂ math:x^2-2x=x^2+2x[alt]ics quadro meno due ics uguale ics quadro piÃÂÃÂ¹ due ics[/alt]:/mathÃÂÃÂ le espressioni ai due membri sono diverse, quindi non ÃÂÃÂ¨ un'identitÃÂÃÂ </li><li>math:x^2+2(x+1)=x^2+2x+2[alt]ics quadro piÃÂÃÂ¹ due aperta tonda ics piÃÂÃÂ¹ uno chiusa tonda uguale ics quadro piÃÂÃÂ¹ due ics piÃÂÃÂ¹ due[/alt]:/math <br />Sviluppando il prodotto al primo membro si ottieneÃÂÃÂ math:x^2+2x+2=x^2+2x+2[alt]ics quadro piÃÂÃÂ¹ dueÃÂÃÂ ics piÃÂÃÂ¹ÃÂÃÂ due uguale ics quadro piÃÂÃÂ¹ due ics piÃÂÃÂ¹ due[/alt]:/math,ÃÂÃÂ quindi ÃÂÃÂ¨ un'identitÃÂÃÂ </li><li>math:x^3+x(x+1)=x^3+x+1[alt]ics cubo piÃÂÃÂ¹ ics aperta tonda ics piÃÂÃÂ¹ uno chiusa tonda uguale ics cubo piÃÂÃÂ¹ ics piÃÂÃÂ¹ uno[/alt]:/math<br />Sviluppando il prodotto al primo membro si ottiene math:x^3+x^2+x)=x^3+x+1[alt]ics cubo piÃÂÃÂ¹ ics quadro piÃÂÃÂ¹ ics uguale ics cubo piÃÂÃÂ¹ ics piÃÂÃÂ¹ uno[/alt]:/mathÃÂÃÂ le espressioni ai due membri sono diverse, quindi non ÃÂÃÂ¨ un'identitÃÂÃÂ </li><li>math:1-x^{3}+4xy=1+x(4y-x^{2})[alt]uno meno ics alla terza piÃÂÃÂ¹ quattro ics ipsilon uguale uno piÃÂÃÂ¹ aperta tonda quattro ipsilon meno ics alla seconda chiusa tonda[/alt]:/math<br />Sviluppando il prodotto al secondo membro si ottiene math:1-x^{3}+4xy=1+4xy-x^{3}[alt]uno meno ics alla terza piÃÂÃÂ¹ quattro ics ipsilon uguale uno piÃÂÃÂ¹ quattro ics ipsilon meno ics alla terza[/alt]:/math</li></ul>";


	$pattern="math:";
	$position0m = multi_strpos($pattern, $stringa);
	
	$pattern=":/math";
	$position1m = multi_strpos($pattern, $stringa);
	echo count($position0m)."<br>";
	if ($position0m) {
		
  		while (list($index, $pos0) = each($position0m)) {
			$pos1=$position1m[$index];
			$formula=(substr($stringa,$pos0+5,$pos1-$pos0-5));
				
			echo ("formula: ".$formula."<br>");
		
		};
	};
	
?>
