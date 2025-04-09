// lascra scratch parameters

#include "parameter.hxx"
#include "error.hxx"
#include "checknum.hxx"
#include "find.hxx"
#include "block.hxx"
#include "id.hxx"

#include <string>

void parameter_generic(bparser::node& sprite, bparser::node& code, bparser::node& node, std::string parentid) {
	// Type
	if (code.value == "variable") {
		if (code.size() != 1) throw error("Expected 1 parameter");
		bparser::node& var = node.emplace("");
		var.emplace("12");
		var.emplace(code[0].value);
		var.emplace(find_variable(sprite, code[0].value));
	}
	else if (code.value == "list") {
		if (code.size() != 1) throw error("Expected 1 parameter");
		bparser::node& list = node.emplace("");
		list.emplace("13");
		list.emplace(code[0].value);
		list.emplace(find_list(sprite, code[0].value));
	}
	else if (code.value == "value") {
		if (code.size() != 1) throw error("Expected 1 parameter");
		std::string val = "";
		bparser::node* value;
		if (code[0].value == "x_pos") {
			val = id::get("xpos");
			value = &block(val, "motion_xposition");
		}
		else if (code[0].value == "y_pos") {
			val = id::get("ypos");
			value = &block(val, "motion_yposition");
		}
		else if (code[0].value == "direction") {
			val = id::get("direction");
			value = &block(val, "motion_direction");
		}
		else if (code[0].value == "size") {
			val = id::get("size");
			value = &block(val, "looks_size");
		}
		else if (code[0].value == "volume") {
			val = id::get("volume");
			value = &block(val, "sound_volume");
		}
		else if (code[0].value == "mouse_x") {
			val = id::get("mousex");
			value = &block(val, "sensing_mousex");
		}
		else if (code[0].value == "mouse_y") {
			val = id::get("mousey");
			value = &block(val, "sensing_mousey");
		}
		else if (code[0].value == "loudness") {
			val = id::get("loudness");
			value = &block(val, "sensing_loudness");
		}
		else if (code[0].value == "timer") {
			val = id::get("timer");
			value = &block(val, "sensing_timer");
		}
		else if (code[0].value == "days_since_2000") {
			val = id::get("dayssince2000");
			value = &block(val, "sensing_dayssince2000");
		}
		else if (code[0].value == "username") {
			val = id::get("username");
			value = &block(val, "sensing_username");
		}
		else if (code[0].value == "music_tempo") {
			val = id::get("musictempo");
			value = &block(val, "music_getTempo");
		}
		else if (code[0].value == "translate_language") {
			val = id::get("transatelanguage");
			value = &block(val, "translate_getViewerLanguage");
		}
		else if (code[0].value == "ev3_distance") {
			val = id::get("ev3distance");
			value = &block(val, "ev3_getDistance");
		}
		else if (code[0].value == "ev3_brightness") {
			val = id::get("ev3brightness");
			value = &block(val, "ev3_getBrightness");
		}
		else if (code[0].value == "wedo_distance") {
			val = id::get("wedodistance");
			value = &block(val, "wedo2_getDistance");
		}
		else if (code[0].value == "go_force") {
			val = id::get("goforce");
			value = &block(val, "gdxfor_getForce");
		}
		else throw error("Unknown value");
		value->find("topLevel")[0].value = "false";
		parent(*value, parentid);
		sprite.find("blocks").push(value);
		node.emplace(val);
	}
	else if (code.value == "join") {
		if (code.size() != 2) throw error("Expected 2 parameters");
		std::string joinid = id::get("join");
		bparser::node& join = block(joinid, "operator_join");
		// Parameters
		try { join.find("inputs").push(&parameter_string(sprite, code[0], joinid)).value = "STRING1"; }
		catch (std::exception e) { throw error(0, e); }
		try { join.find("inputs").push(&parameter_string(sprite, code[1], joinid)).value = "STRING2"; }
		catch (std::exception e) { throw error(1, e); }
		// Add join block
		join.find("topLevel")[0].value = "false";
		parent(join, parentid);
		sprite.find("blocks").push(&join);
		node.emplace(joinid);
	}
	else if (code.value == "letter") {
		if (code.size() != 2) throw error("Expected 2 parameters");
		std::string letterid = id::get("letter");
		bparser::node& letter = block(letterid, "operator_letter_of");
		try { letter.find("inputs").push(&parameter_number(sprite, code[0], letterid, true)).value = "LETTER"; }
		catch (std::exception e) { throw error(0, e); }
		try { letter.find("inputs").push(&parameter_string(sprite, code[1], letterid)).value = "STRING"; }
		catch (std::exception e) { throw error(1, e); }
		// Add letter block
		letter.find("topLevel")[0].value = "false";
		parent(letter, parentid);
		sprite.find("blocks").push(&letter);
		node.emplace(letterid);
	}
	else if (code.value == "length") {
		if (code.size() != 1) throw error("Expected 1 parameter");
		std::string lengthid = id::get("length");
		bparser::node& length = block(lengthid, "operator_length");
		try { length.find("inputs").push(&parameter_string(sprite, code[0], lengthid)).value = "STRING"; }
		catch (std::exception e) { throw error(0, e); }
		// Add letter block
		length.find("topLevel")[0].value = "false";
		parent(length, parentid);
		sprite.find("blocks").push(&length);
		node.emplace(lengthid);
	}
	else if (code.value == "round") {
		if (code.size() != 1) throw error("Expected 1 parameter");
		std::string roundid = id::get("round");
		bparser::node& round = block(roundid, "operator_round");
		try { round.find("inputs").push(&parameter_number(sprite, code[0], roundid)).value = "NUM"; }
		catch (std::exception e) { throw error(0, e); }
		// Add letter block
		round.find("topLevel")[0].value = "false";
		parent(round, parentid);
		sprite.find("blocks").push(&round);
		node.emplace(roundid);
	}
	// Math operators
	else if (code.value == "+" || code.value == "-" || code.value == "*" || code.value == "/") {
		if (code.size() != 2) throw error("Expected 2 parameters");
		std::string mathid = id::get("math");
		bparser::node* math;
		if (code.value == "+") math = &block(mathid, "operator_add");
		else if (code.value == "-") math = &block(mathid, "operator_subtract");
		else if (code.value == "*") math = &block(mathid, "operator_multiply");
		else if (code.value == "/") math = &block(mathid, "operator_divide");
		else throw error("Unknown math operator");
		// Process parameters
		try { math->find("inputs").push(&parameter_number(sprite, code[0], mathid)).value = "NUM1"; }
		catch (std::exception e) { throw error(0, e); }
		try { math->find("inputs").push(&parameter_number(sprite, code[1], mathid)).value = "NUM2"; }
		catch (std::exception e) { throw error(1, e); }
		// Add operator
		math->find("topLevel")[0].value = "false";
		parent(*math, parentid);
		sprite.find("blocks").push(math);
		node.emplace(mathid);
	}
	// Math functions e.g. (math abs 2.5)
	else if (code.value == "math") {
		if (code.size() != 2) throw error("Expected 2 parameters");
		std::string mathid = id::get("math");
		bparser::node& math = block(mathid, "operator_mathop");
		// Process function
		bparser::node& op = math.find("fields").emplace("OPERATOR");
		op.emplace(code[0].value);
		op.emplace("null");
		// Parameter
		try { math.find("inputs").push(&parameter_number(sprite, code[1], mathid)).value = "NUM"; }
		catch (std::exception e) { throw error(1, e); }
		// Add to sprite
		math.find("topLevel")[0].value = "false";
		parent(math, parentid);
		sprite.find("blocks").push(&math);
		node.emplace(mathid);
	}
	else throw error("Unknown type");
}

bparser::node& parameter_string(bparser::node& sprite, bparser::node& code, std::string parentid) {
	bparser::node& node = *(new bparser::node(""));
	// Use value if no subnodes
	if (code.size() == 0) {
		node.emplace("1");
		bparser::node& inner = node.emplace("");
		inner.emplace("10");
		inner.emplace(code.value).string = true;
	}
	else {
		node.emplace("3");
		parameter_generic(sprite, code, node, parentid);
		// Default
		bparser::node& hidden = node.emplace("");
		hidden.emplace("10");
		hidden.emplace("lascra");
	}

	return node;
}
bparser::node& parameter_number(bparser::node& sprite, bparser::node& code, std::string parentid, bool posint) {
	bparser::node& node = *(new bparser::node(""));
	// Use value if no subnodes
	if (code.size() == 0) {
		node.emplace("1");
		bparser::node& inner = node.emplace("");
		inner.emplace(posint ? "6" : "4");
		if (!posint && !checknum(code.value)) throw error("Expected number");
		if (posint && !checkint(code.value, true)) throw error("Expected positive integer");
		inner.emplace(code.value);
	}
	else {
		node.emplace("3");
		parameter_generic(sprite, code, node, parentid);
		// Default
		bparser::node& hidden = node.emplace("");
		hidden.emplace("4");
		hidden.emplace("0");
	}

	return node;
}
