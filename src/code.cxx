// lascra code

#include "code.hxx"
#include "error.hxx"
#include "block.hxx"
#include "id.hxx"
#include "find.hxx"
#include "parameter.hxx"

// General
std::string substack(bparser::node& sprite, bparser::node& param, int offset, std::string parentid) {
	std::string startid;
	bparser::node* previf = nullptr;
	bparser::node* rootif = nullptr;
	// Build substack
	bparser::node* prevnode = &sprite.find("blocks").find(parentid);
	std::string previd = parentid;
	for (int i = offset; i < param.size(); i++) {
		try {
			std::string nextid = code(sprite, param[i], previf);
			if (param[i].value != "else" && param[i].value != "elif") {
				next(*prevnode, nextid);
				prevnode = &sprite.find("blocks").find(nextid);
				parent(*prevnode, (rootif == nullptr) ? previd : rootif->value);
				previd = nextid;
			}
			if (param[i].value == "if" || param[i].value == "elif") {
				previf = &sprite.find("blocks").find(nextid);
				if (rootif == nullptr) rootif = previf;
			}
			else {
				previf = nullptr;
				rootif = nullptr;
			}
			if (i == offset) startid = nextid;
		}
		catch (std::exception e) { throw error(i, e); }
	}

	return startid;
}
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
std::string wait(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("wait");
	bparser::node& wait = block(id, "control_wait", false);
	wait.find("inputs").push(&parameter_number(sprite, param[0], id, true)).value = "DURATION";
	sprite.find("blocks").push(&wait);
	return id;
}
std::string wait_until(bparser::node& sprite, bparser::node& param) {
	if (param.size() == 1) throw error("Expected 1 parameter");
	std::string id = id::get("wait");
	bparser::node& wait = block(id, "control_wait", false);
	wait.find("inputs").push(&parameter_bool(sprite, param[0], id)).value = "CONDITION";
	sprite.find("blocks").push(&wait);
	return id;
}
std::string if_then(bparser::node& sprite, bparser::node& param) {
	if (param.size() < 1) throw error("Expected 1 or more parameters");
	std::string id = id::get("if");
	bparser::node& ifthen = block(id, "control_if", false);
	ifthen.find("inputs").push(&parameter_bool(sprite, param[0], id)).value = "CONDITION";
	sprite.find("blocks").push(&ifthen);
	// Build substack
	if (param.size() > 1) {
		bparser::node& sub = ifthen.find("inputs").emplace("SUBSTACK");
		sub.emplace("2");
		sub.emplace(substack(sprite, param, 1, id));
	}
	ifthen.find("next")[0].value = "null";

	return id;
}
std::string elif_then(bparser::node& sprite, bparser::node& param, bparser::node* previf) {
	if (previf == nullptr) throw error("Expected previous \"if\" statement");
	if (param.size() < 1) throw error("Expected 1 or more parameters");
	std::string id = id::get("if");
	bparser::node& ifthen = block(id, "control_if", false);
	parent(ifthen, previf->value);
	ifthen.find("inputs").push(&parameter_bool(sprite, param[0], id)).value = "CONDITION";
	sprite.find("blocks").push(&ifthen);
	// Add to existing if statement
	previf->find("opcode")[0].value = "control_if_else";
	bparser::node& prevsub = previf->find("inputs").emplace("SUBSTACK2");
	prevsub.emplace("2");
	prevsub.emplace(id);
	// Build substack
	if (param.size() > 1) {
		bparser::node& sub = ifthen.find("inputs").emplace("SUBSTACK");
		sub.emplace("2");
		sub.emplace(substack(sprite, param, 1, id));
	}
	ifthen.find("next")[0].value = "null";

	return id;
}
std::string else_then(bparser::node& sprite, bparser::node& param, bparser::node* previf) {
	if (previf == nullptr) throw error("Expected previous \"if\" statement");
	previf->find("opcode")[0].value = "control_if_else";
	// Build substack
	if (param.size() > 0) {
		bparser::node& sub = previf->find("inputs").emplace("SUBSTACK2");
		sub.emplace("2");
		sub.emplace(substack(sprite, param, 0, previf->value));
	}
	previf->find("next")[0].value = "null";
	
	return previf->value;
}
std::string repeat(bparser::node& sprite, bparser::node& param) {
	if (param.size() < 1) throw error("Expected 1 or more parameters");
	std::string id = id::get("repeat");
	bparser::node& repeat = block(id, "control_repeat", false);
	repeat.find("inputs").push(&parameter_number(sprite, param[0], id, true, true)).value = "TIMES";
	sprite.find("blocks").push(&repeat);
	// Build substack
	if (param.size() > 1) {
		bparser::node& sub = repeat.find("inputs").emplace("SUBSTACK");
		sub.emplace("2");
		sub.emplace(substack(sprite, param, 1, id));
	}
	repeat.find("next")[0].value = "null";
	
	return id;
}
std::string repeat_until(bparser::node& sprite, bparser::node& param) {
	if (param.size() < 1) throw error("Expected 1 or more parameters");
	std::string id = id::get("repeat");
	bparser::node& repeat = block(id, "control_repeat_until", false);
	repeat.find("inputs").push(&parameter_bool(sprite, param[0], id)).value = "CONDITION";
	sprite.find("blocks").push(&repeat);
	// Build substack
	if (param.size() > 1) {
		bparser::node& sub = repeat.find("inputs").emplace("SUBSTACK");
		sub.emplace("2");
		sub.emplace(substack(sprite, param, 1, id));
	}
	repeat.find("next")[0].value = "null";

	return id;
}
std::string forever(bparser::node& sprite, bparser::node& param) {
	std::string id = id::get("forever");
	bparser::node& forever = block(id, "control_forever", false);
	sprite.find("blocks").push(&forever);
	// Build substack
	bparser::node& sub = forever.find("inputs").emplace("SUBSTACK");
	sub.emplace("2");
	sub.emplace(substack(sprite, param, 0, id));
	forever.find("next")[0].value = "null";
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
	broadcastinput.emplace(code[0].value).string = true;
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
	broadcastinput.emplace(code[0].value).string = true;
	broadcastinput.emplace(find_broadcast(sprite, code[0].value));
	broadcast.find("inputs").push(&parameter_string(sprite, code[1], id)).value = "VALUE";
	sprite.find("blocks").push(&broadcast);
	return id;
}
std::string stop(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("stop");
	bparser::node& stop = block(id, "control_stop", false);
	bparser::node& option = stop.find("fields").emplace("STOP_OPTION");
	option.emplace(param[0].value).string = true;
	option.emplace("null");
	sprite.find("blocks").push(&stop);
	return id;
}
std::string clone(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("clone");
	bparser::node& clone = block(id, "control_create_clone_of", false);
	sprite.find("blocks").push(&clone);
	bparser::node& option = clone.find("inputs").emplace("CLONE_OPTION");
	option.emplace("1");
	// Shadow block
	std::string menuid = id::get("clonemenu");
	bparser::node& clonemenu = block(menuid, "control_create_clone_of_menu", false, true);
	parent(clonemenu, id);
	bparser::node& menuoption = clonemenu.find("fields").emplace("CLONE_OPTION");
	menuoption.emplace(param[0].value).string = true;
	menuoption.emplace("null");
	sprite.find("blocks").push(&clonemenu);
	option.emplace(menuid);
	return id;
}
std::string delete_clone(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 0) throw error("Expected no parameters");
	std::string id = id::get("deleteclone");
	bparser::node& delete_clone = block(id, "control_delete_this_clone", false);
	sprite.find("blocks").push(&delete_clone);
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
std::string show_variable(bparser::node& sprite, bparser::node& code) {
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
std::string hide_variable(bparser::node& sprite, bparser::node& code) {
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
// Sensing
std::string ask(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("ask");
	bparser::node& ask = block(id, "sensing_askandwait", false);
	try { ask.find("inputs").push(&parameter_string(sprite, param[0], id)).value = "QUESTION"; }
	catch (std::exception e) { throw error("question", e); }
	sprite.find("blocks").push(&ask);
	return id;
}


// Main Code Function
std::string code(bparser::node& sprite, bparser::node& code, bparser::node* previf) {
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
		else if (code.value == "wait") return wait(sprite, code);
		else if (code.value == "wait_until") return wait_until(sprite, code);
		else if (code.value == "if") return if_then(sprite, code);
		else if (code.value == "elif") return elif_then(sprite, code, previf);
		else if (code.value == "else") return else_then(sprite, code, previf);
		else if (code.value == "repeat") return repeat(sprite, code);
		else if (code.value == "repeat_until") return repeat_until(sprite, code);
		else if (code.value == "forever") return forever(sprite, code);
		else if (code.value == "stop") return stop(sprite, code);
		else if (code.value == "clone") return clone(sprite, code);
		else if (code.value == "delete_clone") return delete_clone(sprite, code);
		// Data
		else if (code.value == "set") return set(sprite, code);
		else if (code.value == "change") return change(sprite, code);
		else if (code.value == "show_variable") return show_variable(sprite, code);
		else if (code.value == "hide_variable") return hide_variable(sprite, code);
		// Sensing
		else if (code.value == "ask") return ask(sprite, code);
		else throw error("Unknown command");
	}
	catch (std::exception e) {
		throw error(code.value, e);
	}
}
