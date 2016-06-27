function theConectiv(str, id) {
	var newStr = str;
	if (newStr != myReplace(newStr, "~", "¬")) {
		newStr = myReplace(newStr, "~", "¬");
	}
	if (newStr != myReplace(newStr, "^*", "∧")) {
		newStr = myReplace(newStr, "^*", "∧");
	}
	if (newStr != myReplace(newStr, "v*", "∨")) {
		newStr = myReplace(newStr, "v*", "∨");
	}
	if (newStr != myReplace(newStr, "v-", "⊻")) {
		newStr = myReplace(newStr, "v-", "⊻");
	}
	if (newStr != myReplace(newStr, "-->", "→")) {
		newStr = myReplace(newStr, "-->", "→");
	}
	if (newStr != myReplace(newStr, "<->", "↔")) {
		newStr = myReplace(newStr, "<->", "↔");
	}
	if (newStr != myReplace(newStr, "<=>", "⇔")) {
		newStr = myReplace(newStr, "<=>", "⇔");
	}
	if (newStr != myReplace(newStr, "--v", "↓")) {
		newStr = myReplace(newStr, "--v", "↓");
	}
	if (newStr != myReplace(newStr, "--^", "↑")) {
		newStr = myReplace(newStr, "--^", "↑");
	}

	if (str != newStr) $('input#'+id).val(newStr);
}

var letras = [];
var letrasTab = [];
var qtdLetras = 0;
function moreLetras() {
	var moreInput = "<td><input id='letra_"+qtdLetras+"' class='letraP' type='text' onkeyup='validaLetra(this)' data-number="+qtdLetras+"><input type='button' value='x' onclick='removeLetra($(this).prevUntil(&#39;.letrasP&#39;).attr(&#39;id&#39;))'></td>";
	$("table.tabV thead td:last-child").before(moreInput);
	$("input#letra_"+qtdLetras).focus();
	qtdLetras++;
}
moreLetras();

// Validar se a letra proposicional inserida é válida
function validaLetra(object) {
	if (/^[a-z]{1}$/.test($(object).val())) {
		$(object).removeClass("fail");
		letras[$(object).attr('data-number')] = $(object).val();
	} else {
		if ($(object).val() != "") {
			$(object).addClass("fail");
		}
		delete letras[$(object).attr('data-number')];
	}
	validaCalc();
}

function validaCalc() {
	var er = "[ ]?[^ (){}[¬∧∨⊻→↔⇔↓↑";
	for (x in letras) {
		er += letras[x];
	}
	er += "][ ]?";
	re = new RegExp(er, "g");
	if (!re.test($("#calcP").val()) && !/\w{2}/g.test($("#calcP").val())) {
		$("#calcP").removeClass("fail");
		letrasTab['calc'] = [];
		letrasTab['calc']['calc'] = $("#calcP").val();
		tabVHead();
		tabVBody();
	} else {
		$("#calcP").addClass("fail");
	}
}

// Remove uma letra proposicional
function removeLetra(id) {
	delete letras[$('#'+id).attr('data-number')];
	$('#'+id).parent().remove();
	validaCalc();
}

function tabVHead() {
	var tabHead = "<tr>";
	for (x in letras) {
		tabHead += "<td>"+letras[x]+"</td>";
	}
	tabHead += "<td>"+$("#calcP").val()+"</td></tr>";
	//$('table.tabV thead').html(tabHead);
	tabVBody();
}

function tabVBody() {
	var i = 0;
	var steps = [''];
	for (x in letras) {
		steps[i] = "F";
		i++;
	}
	
	for (var j = 0; j < Math.pow(2, i); j++) {
		var k = 0;
		for (x in letras) {
			if (!Array.isArray(letrasTab[k])) letrasTab[k] = [];

			letrasTab[k]['letra'] = letras[x];
			letrasTab[k][j] = steps[k];

			if (k+1 != i) {
				var check = 0;
				for (var a = k+1; a < i; a++) {
					if (steps[a] == "V") {
						check++;
					}
				}

				if (check == i-(k+1)) {
					if (steps[k] == "F") {
						steps[k] = "V";
					} else if (steps[k] == "V") {
						steps[k] = "F";
					}
				}
			}

			if (k+1 == i) {
				if (steps[k] == "F") {
					steps[k] = "V";
				} else if (steps[k] == "V") {
					steps[k] = "F";
				}
			}

			k++;						
		}
	}
	for (y in letrasTab) {
		if (y != "calc") {

			for (z in letrasTab[y]) {
				if (z != "letra") {
					if (!letrasTab['calc'][z]) letrasTab['calc'][z] = letrasTab['calc']['calc'];
					letrasTab['calc'][z] = calcProp(myReplace(letrasTab['calc'][z], letrasTab[y]['letra'], letrasTab[y][z]));
				}
			}

		}
	}
	var tabBody = "";
	var para = false;
	var c = 0, l = 0;
	while (!para) {
		if (l == 0 && c == 0) tabBody += "<tr>";
		
		if (c < i && l < Math.pow(2, i)) {
			tabBody += "<td>"+letrasTab[c][l]+"</td>";
			c++;
			
			if (c == i) tabBody += "<td>"+letrasTab['calc'][l]+"</td></tr>";
		} else {
			l++;
			c = 0;
		}

		if (l > Math.pow(2, i)) {
			para = true;
		}
	}

	$('table.tabV tbody').html(tabBody);
}

function myReplace(str, search, newStr) {
	while (str != str.replace(search, newStr)) {
		str = str.replace(search, newStr);
	}
	return str;
}

function calcProp(prop) {
	var str = prop;

	if (/\w/g.test(str)) {
		var para = false;
		for (var i = 0; !para; i++) {
			if (str == "F" || str == "V" || i == 20) para = true;

			str = str.replace("{F}", "F");
			str = str.replace("{V}", "V");

			str = str.replace("[F]", "F");
			str = str.replace("[V]", "V");

			str = str.replace("(F)", "F");
			str = str.replace("(V)", "V");

			str = str.replace("¬F", "V");
			str = str.replace("¬V", "F");

			str = str.replace("F ∧ F", "F");
			str = str.replace("F ∧ V", "F");
			str = str.replace("V ∧ F", "F");
			str = str.replace("V ∧ V", "V");

			str = str.replace("F ∨ F", "F");
			str = str.replace("F ∨ V", "V");
			str = str.replace("V ∨ F", "V");
			str = str.replace("V ∨ V", "V");

			str = str.replace("F ⊻ F", "F");
			str = str.replace("F ⊻ V", "V");
			str = str.replace("V ⊻ F", "V");
			str = str.replace("V ⊻ V", "F");

			str = str.replace("F → F", "¬F ∨ F");
			str = str.replace("F → V", "¬F ∨ V");
			str = str.replace("V → F", "¬V ∨ F");
			str = str.replace("V → V", "¬V ∨ V");

			str = str.replace("F ↔ F", "(¬F ∨ F) ∧ (F ∨ ¬F)");
			str = str.replace("F ↔ V", "(¬F ∨ V) ∧ (F ∨ ¬V)");
			str = str.replace("V ↔ F", "(¬V ∨ F) ∧ (V ∨ ¬F)");
			str = str.replace("V ↔ V", "(¬V ∨ V) ∧ (V ∨ ¬V)");

			str = str.replace("F ⇔ F", "F ↔ F");
			str = str.replace("F ⇔ V", "F ↔ V");
			str = str.replace("V ⇔ F", "V ↔ F");
			str = str.replace("V ⇔ V", "V ↔ V");

			str = str.replace("F ↓ F", "¬F ∧ ¬F");
			str = str.replace("F ↓ V", "¬F ∧ ¬V");
			str = str.replace("V ↓ F", "¬V ∧ ¬F");
			str = str.replace("V ↓ V", "¬V ∧ ¬V");

			str = str.replace("F ↑ F", "¬F ∨ ¬F");
			str = str.replace("F ↑ V", "¬F ∨ ¬V");
			str = str.replace("V ↑ F", "¬V ∨ ¬F");
			str = str.replace("V ↑ V", "¬V ∨ ¬V");
		}
	}

	return str;
}