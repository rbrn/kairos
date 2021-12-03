var t=0;
function goLights() {
	if (!t) t=setInterval("cambia()",250);
}

function stopLights() {
	if (t) {
		clearInterval(t);
		t=0;
		window.parent.frames['finestra_chat'].window.document.body.style.backgroundColor="#fff";
 	}
}

function toHex(i) {
	runningTotal = ''
	quotient = hexQuotient(i);
	remainder = eval(i + '-(' + quotient + '* 16)')
	runningTotal = charToHex(remainder) + runningTotal;
	while( quotient >= 16) {
		savedQuotient = hexQuotient(quotient);
		remainder = eval(quotient + '-(' + savedQuotient + '* 16)');
		runningTotal = charToHex(remainder) + runningTotal;
		quotient = savedQuotient;
	} 
	return charToHex(quotient) + runningTotal ;
}

function hexQuotient(i) {
	return Math.floor(eval(i +'/ 16'));
}

function charToHex(i) {
	if (i == 0) {
		hexChar = '0' }
	else { if (i == 1) {
		hexChar = '1'}
	else { if (i == 2) {
		hexChar = '2'}
	else { if (i == 3) {
		hexChar = '3' }
	else { if (i == 4) {
		hexChar = '4'}
	else { if (i == 5) {
		hexChar = '5' }
	else { if (i == 6) {
		hexChar = '6'}
	else { if (i == 7) {
		hexChar = '7' }
	else { if (i == 8) {
		hexChar = '8'}
	else { if (i == 9) {
		hexChar = '9'}
	else { if (i ==10) {
		hexChar = 'a'}
	else { if (i ==11) {
		hexChar = 'b'}
	else { if (i ==12) {
		hexChar = 'c'}
	else { if (i ==13) {
		hexChar = 'd'}
	else { if (i ==14) {
		hexChar = 'e'}
	else { if (i ==15) {
		hexChar = 'f'}
	} } } } } } } } } } } } } } }
	return hexChar;
}

function cambia() {
	var r= toHex(Math.round(255*Math.random()));
	var g= toHex(Math.round(255*Math.random()));
	var b= toHex(Math.round(255*Math.random()));
	var colore="#"+r+g+b;	
	window.parent.frames['finestra_chat'].window.document.body.style.backgroundColor=colore;
	//document.body.style.backgroundColor=colore;
}