#include "declare.hxx"
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>

#include "checknum.hxx"
#include "error.hxx"

void declaration(bparser::node& sprite, bparser::node& code) {
	// Delare sprite name
	if (code.value == "name") {
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		sprite.find("name")[0].value = code[0].value;
		sprite.find("name")[0].string = true;
	}
	else if (code.value == "x") {
		if (!sprite.exists("x")) throw error("Stage has no \"x\" value");
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (!checknum(code[0].value)) {
			throw error("Invalid value (Expected a number)");
		}
		sprite.find("x")[0].value = code[0].value;
	}
	else if (code.value == "y") {
		if (!sprite.exists("y")) throw error("Stage has no \"y\" value");
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (!checknum(code[0].value)) {
			throw error("Invalid value (Expected a number)");
		}
		sprite.find("y")[0].value = code[0].value;
	}
	else if (code.value == "size") {
		if (!sprite.exists("size")) throw error("Stage has no \"size\" value");
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (!checknum(code[0].value)) {
			throw error("Invalid value (Expected a number)");
		}
		sprite.find("size")[0].value = code[0].value;
	}
	else if (code.value == "direction") {
		if (!sprite.exists("direction")) throw error("Stage has no \"direction\" value");
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (!checknum(code[0].value)) {
			throw error("Invalid value (Expected a number)");
		}
		sprite.find("direction")[0].value = code[0].value;
	}
	else if (code.value == "volume") {
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (!checknum(code[0].value)) {
			throw error("Invalid value (Expected a number)");
		}
		sprite.find("volume")[0].value = code[0].value;
	}
	else if (code.value == "layerOrder") {
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (!checknum(code[0].value)) {
			throw error("Invalid value (Expected a number)");
		}
		sprite.find("layerOrder")[0].value = code[0].value;
	}
	else if (code.value == "visible") {
		if (!sprite.exists("visible")) throw error("Stage has no \"visible\" value");
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (code[0].value != "true" && code[0].value != "false") {
			throw error("Invalid value (Expected \"true\" or \"false\")");
		}
		sprite.find("visible")[0].value = code[0].value;
	}
	else if (code.value == "draggable") {
		if (!sprite.exists("draggable")) throw error("Stage has no \"draggable\" value");
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (code[0].value != "true" && code[0].value != "false") {
			throw error("Invalid value (Expected \"true\" or \"false\")");
		}
		sprite.find("draggable")[0].value = code[0].value;
	}
	else if (code.value == "rotationStyle") {
		if (!sprite.exists("rotationStyle")) throw error("Stage has no \"rotationStyle\" value");
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (code[0].value != "all around" && code[0].value != "left-right" && code[0].value != "don't rotate") {
			throw error("Invalid value (Expected \"all around\", \"left-right\", or \"don't rotate\")");
		}
		sprite.find("rotationStyle")[0].value = code[0].value;
	}
	else if (code.value == "tempo") {
		if (!sprite.exists("tempo")) throw error("Sprite has no \"tempo\" value");
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (!checknum(code[0].value)) {
			throw error("Invalid value (Expected a number)");
		}
		sprite.find("tempo")[0].value = code[0].value;
	}
	else if (code.value == "videoTransparency") {
		if (!sprite.exists("videoTransparency")) throw error("Sprite has no \"videoTransparency\" value");
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (!checknum(code[0].value)) {
			throw error("Invalid value (Expected a number)");
		}
		sprite.find("videoTransparency")[0].value = code[0].value;
	}
	else if (code.value == "videoState") {
		if (!sprite.exists("videoState")) throw error("Sprite has no \"videoState\" value");
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		if (code[0].value != "off" && code[0].value != "on" && code[0].value != "on-flipped") {
			throw error("Invalid videoState (Expected \"on\", \"off\", or \"on-flipped\")");
		}
		sprite.find("videoState")[0].value = code[0].value;
	}
	else if (code.value == "textToSpeechLanguage") {
		if (!sprite.exists("textToSpeechLanguage")) throw error("Sprite has no \"textToSpeechLanguage\" value");
		if (code.size() != 1) {
			throw error("Wrong number of parameters (Expected 1)");
		}
		sprite.find("textToSpeechLanguage")[0].value = code[0].value;
		sprite.find("textToSpeechLanguage")[0].string = true;
	}
	else {
		throw error("Unknown declaration");
	}
}

void declare(bparser::node& sprite, bparser::node& code) {
	for (int i = 0; i < code.size(); i++) {
		try {
			if (code[i].value == "#") continue;
			declaration(sprite, code[i]);
		}
		catch (std::exception& e) {
			throw error(i, code[i].value, e);
		}
	}
}

