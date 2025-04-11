// lascra code

#include "code.hxx"
#include "error.hxx"
#include "block.hxx"
#include "id.hxx"
#include "find.hxx"
#include "parameter.hxx"

// Motion
std::string move(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("move");
	bparser::node& move = block(id, "motion_movesteps", false);
	move.find("inputs").push(&parameter_number(sprite, code[0], id)).value = "STEPS";
	sprite.find("blocks").push(&move);
	return id;
}
// Looks
std::string say(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("say");
	bparser::node& say = block(id, "looks_say", false);
	say.find("inputs").push(&parameter_string(sprite, code[0], id)).value = "MESSAGE";
	sprite.find("blocks").push(&say);
	return id;
}
// Control
std::string repeat(bparser::node& sprite, bparser::node& param) {
	if (param.size() < 1) throw error("Expected 1 or more parameters");
	std::string id = id::get("repeat");
	bparser::node& repeat = block(id, "control_repeat", false);
	repeat.find("inputs").push(&parameter_number(sprite, param[0], id, true, true)).value = "TIMES";
	sprite.find("blocks").push(&repeat);
	// Build substack
	bparser::node* prevnode;
	std::string previd;
	for (int i = 1; i < param.size(); i++) {
		try {
			if (i == 1) {
				bparser::node& substack = repeat.find("inputs").emplace("SUBSTACK");
				substack.emplace("2");
				previd = substack.emplace(code(sprite, param[i])).value;
				prevnode = &sprite.find("blocks").find(previd);
				parent(*prevnode, id);
			}
			else {
				std::string nextid = code(sprite, param[i]);
				next(*prevnode, nextid);
				prevnode = &sprite.find("blocks").find(previd);
				parent(*prevnode, previd);
				previd = nextid;
			}
		}
		catch (std::exception e) { throw error(i-1, e); }
	}
	return id;
}
std::string forever(bparser::node& sprite, bparser::node& param) {
	std::string id = id::get("forever");
	bparser::node& forever = block(id, "control_forever", false);
	sprite.find("blocks").push(&forever);
	// Build substack
	bparser::node* prevnode;
	std::string previd;
	for (int i = 0; i < param.size(); i++) {
		try {
			if (i == 0) {
				bparser::node& substack = forever.find("inputs").emplace("SUBSTACK");
				substack.emplace("2");
				previd = substack.emplace(code(sprite, param[i])).value;
				prevnode = &sprite.find("blocks").find(previd);
				parent(*prevnode, id);
			}
			else {
				std::string nextid = code(sprite, param[i]);
				next(*prevnode, nextid);
				prevnode = &sprite.find("blocks").find(previd);
				parent(*prevnode, previd);
				previd = nextid;
			}
		}
		catch (std::exception e) { throw error(i-1, e); }
	}
	return id;
}
// Events
std::string broadcast(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("move");
	bparser::node& broadcast = block(id, "event_broadcast", false);
	bparser::node& input = broadcast.find("inputs").emplace("BROADCAST_INPUT");
	input.emplace("1");
	bparser::node& broadcastinput = input.emplace("");
	broadcastinput.emplace("11");
	broadcastinput.emplace(code[0].value);
	broadcastinput.emplace(find_broadcast(sprite, code[0].value));
	broadcast.find("inputs").push(&parameter_string(sprite, code[0], id)).value = "VALUE";
	sprite.find("blocks").push(&broadcast);
	return id;
}
std::string waitbroadcast(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("move");
	bparser::node& broadcast = block(id, "event_broadcastandwait", false);
	bparser::node& input = broadcast.find("inputs").emplace("BROADCAST_INPUT");
	input.emplace("1");
	bparser::node& broadcastinput = input.emplace("");
	broadcastinput.emplace("11");
	broadcastinput.emplace(code[0].value);
	broadcastinput.emplace(find_broadcast(sprite, code[0].value));
	broadcast.find("inputs").push(&parameter_string(sprite, code[1], id)).value = "VALUE";
	sprite.find("blocks").push(&broadcast);
	return id;
}
// Data
std::string set(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 2) throw error("Expected 2 parameters");
	std::string id = id::get("move");
	bparser::node& set = block(id, "data_setvariableto", false);
	bparser::node& variable = set.find("fields").emplace("VARIABLE");
	variable.emplace(code[0].value);
	variable.emplace(find_variable(sprite, code[0].value));
	set.find("inputs").push(&parameter_string(sprite, code[1], id)).value = "VALUE";
	sprite.find("blocks").push(&set);
	return id;
}
std::string change(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 2) throw error("Expected 2 parameters");
	std::string id = id::get("move");
	bparser::node& change = block(id, "data_changevariableby", false);
	bparser::node& variable = change.find("fields").emplace("VARIABLE");
	variable.emplace(code[0].value);
	variable.emplace(find_variable(sprite, code[0].value));
	change.find("inputs").push(&parameter_number(sprite, code[1], id)).value = "VALUE";
	sprite.find("blocks").push(&change);
	return id;
}
std::string show(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 2) throw error("Expected 2 parameters");
	bool list;
	if (code[0].value == "variable") list = false;
	else if (code[0].value == "list") list = true;
	else throw error("Expected \"variable\" or \"list\"");
	std::string id = id::get("move");
	bparser::node& show = block(id, list ? "data_showlist" : "data_showvariable", false);
	bparser::node& variable = show.find("fields").emplace(list ? "LIST" : "VARIABLE");
	variable.emplace(code[1].value);
	variable.emplace(list ? find_list(sprite, code[1].value) : find_variable(sprite, code[1].value));
	sprite.find("blocks").push(&show);
	return id;
}
std::string hide(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 2) throw error("Expected 2 parameters");
	bool list;
	if (code[0].value == "variable") list = false;
	else if (code[0].value == "list") list = true;
	else throw error("Expected \"variable\" or \"list\"");
	std::string id = id::get("move");
	bparser::node& hide = block(id, list ? "data_hidelist" : "data_hidevariable", false);
	bparser::node& variable = hide.find("fields").emplace(list ? "LIST" : "VARIABLE");
	variable.emplace(code[1].value);
	variable.emplace(list ? find_list(sprite, code[1].value) : find_variable(sprite, code[1].value));
	sprite.find("blocks").push(&hide);
	return id;
}

// Main Code Function
std::string code(bparser::node& sprite, bparser::node& code) {
	std::string id;
	try {
		// Motion
		if (code.value == "move") return move(sprite, code);
		// Looks
		else if (code.value == "say") return say(sprite, code);
		// Events
		else if (code.value == "broadcast") return broadcast(sprite, code);
		else if (code.value == "waitbroadcast") return waitbroadcast(sprite, code);
		// Control
		else if (code.value == "repeat") return repeat(sprite, code);
		else if (code.value == "forever") return forever(sprite, code);
		// Data
		else if (code.value == "set") return set(sprite, code);
		else if (code.value == "change") return change(sprite, code);
		else if (code.value == "show") return show(sprite, code);
		else if (code.value == "hide") return hide(sprite, code);
		else throw error("Unknown command");
	}
	catch (std::exception e) {
		throw error(code.value, e);
	}
}
