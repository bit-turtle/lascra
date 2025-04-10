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
	else if (code.value == "listlength") {
		if (code.size() != 1) throw error("Expected 1 parameter");
		std::string listlengthid = id::get("listlength");
		bparser::node& listlength = block(listlengthid, "data_lengthoflist");
		// Process list
		bparser::node& list = listlength.find("fields").emplace("LIST");
		list.emplace(code[0].value);
		list.emplace(find_list(sprite, code[0].value));
		// Add listlength block
		listlength.find("topLevel")[0].value = "false";
		parent(listlength, parentid);
		sprite.find("blocks").push(&listlength);
		node.emplace(listlengthid);
	}
	else if (code.value == "item") {
		if (code.size() != 2) throw error("Expected 2 parameters");
		std::string itemid = id::get("item");
		bparser::node& item = block(itemid, "data_itemoflist");
		try { item.find("inputs").push(&parameter_number(sprite, code[0], itemid, false, true)).value = "INDEX"; }
		catch (std::exception e) { throw error(0, e); }
		// Process list
		bparser::node& list = item.find("fields").emplace("LIST");
		list.emplace(code[1].value);
		try { list.emplace(find_list(sprite, code[1].value)); }
		catch (std::exception e) { throw error(1, e); }
		// Add item block
		item.find("topLevel")[0].value = "false";
		parent(item, parentid);
		sprite.find("blocks").push(&item);
		node.emplace(itemid);
	}
	else if (code.value == "item#") {
		if (code.size() != 2) throw error("Expected 2 parameters");
		std::string itemid = id::get("item");
		bparser::node& item = block(itemid, "data_itemnumoflist");
		try { item.find("inputs").push(&parameter_string(sprite, code[0], itemid)).value = "ITEM"; }
		catch (std::exception e) { throw error(0, e); }
		// Process list
		bparser::node& list = item.find("fields").emplace("LIST");
		list.emplace(code[1].value);
		try { list.emplace(find_list(sprite, code[1].value)); }
		catch (std::exception e) { throw error(1, e); }
		// Add item block
		item.find("topLevel")[0].value = "false";
		parent(item, parentid);
		sprite.find("blocks").push(&item);
		node.emplace(itemid);
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
		else if (code[0].value == "answer") {
			val = id::get("answer");
			value = &block(val, "sensing_answer");
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
	else if (code.value == "costume") {
		if (code.size() != 1) throw error("Expected 1 parameter");
		std::string costumeid = id::get("costume");
		bparser::node& costume = block(costumeid, "looks_costumenumbername");
		// Process parameter
		bparser::node& numbername = costume.find("fields").emplace("NUMBER_NAME");
		if (code[0].value == "number") numbername.emplace("number");
		else if (code[0].value == "name") numbername.emplace("name");
		else throw error("Expected \"number\" or \"name\"");
		numbername.emplace("null");
		// Add length block
		costume.find("topLevel")[0].value = "false";
		parent(costume, parentid);
		sprite.find("blocks").push(&costume);
		node.emplace(costumeid);
	}
	else if (code.value == "backdrop") {
		if (code.size() != 1) throw error("Expected 1 parameter");
		std::string backdropid = id::get("backdrop");
		bparser::node& backdrop = block(backdropid, "looks_backdropnumbername");
		// Process parameter
		bparser::node& numbername = backdrop.find("fields").emplace("NUMBER_NAME");
		if (code[0].value == "number") numbername.emplace("number");
		else if (code[0].value == "name") numbername.emplace("name");
		else throw error("Expected \"number\" or \"name\"");
		numbername.emplace("null");
		// Add length block
		backdrop.find("topLevel")[0].value = "false";
		parent(backdrop, parentid);
		sprite.find("blocks").push(&backdrop);
		node.emplace(backdropid);
	}
	else if (code.value == "distance") {
		if (code.size() != 1) throw error("Expected 1 parameter");
		std::string distanceid = id::get("distance");
		bparser::node& distance = block(distanceid, "sensing_distanceto");
		// Process parameter
		bparser::node& distanceinput = distance.find("inputs").emplace("DISTANCETOMENU");
		distanceinput.emplace("1");
		std::string distmenuid = id::get("distancemenu");
		distanceinput.emplace(distmenuid);
		// Create shadow block
		bparser::node& distancemenu = block(distmenuid, "sensing_distancetomenu");
		distancemenu.find("topLevel")[0].value = "false";
		distancemenu.find("shadow")[0].value = "true";
		parent(distancemenu, distanceid);
		bparser::node& distfield = distancemenu.find("fields").emplace("DISTANCETOMENU");
		distfield.emplace(code[0].value).string = true;
		distfield.emplace("null");
		sprite.find("blocks").push(&distancemenu);
		// Add distance block
		distance.find("topLevel")[0].value = "false";
		parent(distance, parentid);
		sprite.find("blocks").push(&distance);
		node.emplace(distanceid);
	}
	else if (code.value == "current") {
		if (code.size() != 1) throw error("Expected 1 parameter");
		std::string mathid = id::get("current");
		bparser::node& math = block(mathid, "sensing_current");
		// Process function
		bparser::node& op = math.find("fields").emplace("CURRENTMENU");
		op.emplace(code[0].value);
		op.emplace("null");
		// Add to sprite
		math.find("topLevel")[0].value = "false";
		parent(math, parentid);
		sprite.find("blocks").push(&math);
		node.emplace(mathid);
	}
	else if (code.value == "property") {
		if (code.size() != 2) throw error("Expected 2 parameters");
		std::string propertyid = id::get("of");
		bparser::node& property = block(propertyid, "sensing_of");
		// Process property
		bparser::node& field = property.find("fields").emplace("PROPERTY");
		field.emplace(code[0].value);
		field.emplace("null");
		// Process object
		std::string propertyobjid = id::get("ofobjmenu");
		bparser::node& propertyobj = block(propertyobjid, "sensing_of_object_menu");
		parent(propertyobj, propertyid);
		// Create shadow block
		bparser::node& propertyobjmenu = propertyobj.find("fields").emplace("OBJECT");
		propertyobjmenu.emplace(code[1].value);
		propertyobjmenu.emplace("null");
		propertyobj.find("topLevel")[0].value = "false";
		propertyobj.find("shadow")[0].value = "true";
		sprite.find("blocks").push(&propertyobj);
		// Add shadow block to inputs
		bparser::node& shadow = property.find("inputs").emplace("OBJECT");
		shadow.emplace("1");
		shadow.emplace(propertyobjid);
		// Add to sprite
		property.find("topLevel")[0].value = "false";
		parent(property, parentid);
		sprite.find("blocks").push(&property);
		node.emplace(propertyid);
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
		try { letter.find("inputs").push(&parameter_number(sprite, code[0], letterid, true, true)).value = "LETTER"; }
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
		// Add length block
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
		// Add round block
		round.find("topLevel")[0].value = "false";
		parent(round, parentid);
		sprite.find("blocks").push(&round);
		node.emplace(roundid);
	}
	else if (code.value == "random") {
		if (code.size() != 2) throw error("Expected 2 parameters");
		std::string randomid = id::get("random");
		bparser::node& random = block(randomid, "operator_random");
		try { random.find("inputs").push(&parameter_number(sprite, code[0], randomid)).value = "FROM"; }
		catch (std::exception e) { throw error(0, e); }
		try { random.find("inputs").push(&parameter_number(sprite, code[1], randomid)).value = "TO"; }
		catch (std::exception e) { throw error(1, e); }
		// Add random block
		random.find("topLevel")[0].value = "false";
		parent(random, parentid);
		sprite.find("blocks").push(&random);
		node.emplace(randomid);
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
	else if (code.value == "mod") {
		if (code.size() != 2) throw error("Expected 2 parameters");
		std::string modid = id::get("mod");
		bparser::node& mod = block(modid, "operator_mod");
		try { mod.find("inputs").push(&parameter_number(sprite, code[0], modid)).value = "NUM1"; }
		catch (std::exception e) { throw error(0, e); }
		try { mod.find("inputs").push(&parameter_number(sprite, code[1], modid)).value = "NUM2"; }
		catch (std::exception e) { throw error(1, e); }
		// Add mod block
		mod.find("topLevel")[0].value = "false";
		parent(mod, parentid);
		sprite.find("blocks").push(&mod);
		node.emplace(modid);
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
		try { parameter_generic(sprite, code, node, parentid); }
		catch (std::exception e) { throw error(code.value, e); }
		// Default
		bparser::node& hidden = node.emplace("");
		hidden.emplace("10");
		hidden.emplace("lascra");
	}

	return node;
}
bparser::node& parameter_number(bparser::node& sprite, bparser::node& code, std::string parentid, bool positive, bool integer) {
	bparser::node& node = *(new bparser::node(""));
	// Use value if no subnodes
	if (code.size() == 0) {
		node.emplace("1");
		bparser::node& inner = node.emplace("");
		if (!positive && !integer) {
			inner.emplace("4");
			if (!checknum(code.value)) throw error("Expected number");
		}
		else if (positive && !integer) {
			inner.emplace("5");
			if (!checknum(code.value, true)) throw error("Expected positive number");
		}
		else if (!positive && integer) {
			inner.emplace("7");
			if (!checknum(code.value, false, true)) throw error("Expected integer");
		}
		else if (positive && integer) {
			inner.emplace("6");
			if (!checknum(code.value, true, true)) throw error("Expected positive integer");
		}
		inner.emplace(code.value);
	}
	else {
		node.emplace("3");
		try { parameter_generic(sprite, code, node, parentid); }
		catch (std::exception e) { throw error(code.value, e); }
		// Default
		bparser::node& hidden = node.emplace("");
		if (!positive && !integer) hidden.emplace("4");
		if (positive && !integer) hidden.emplace("5");
		if (!positive && integer) hidden.emplace("7");
		if (positive && integer) hidden.emplace("6");
		hidden.emplace("0");
	}

	return node;
}
