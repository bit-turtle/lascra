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
std::string turn_right(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("turn");
	bparser::node& turn_right = block(id, "motion_turnright", false);
	turn_right.find("inputs").push(&parameter_number(sprite, code[0], id)).value = "DEGREES";
	sprite.find("blocks").push(&turn_right);
	return id;
}
std::string turn_left(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("turn");
	bparser::node& turn_left = block(id, "motion_turnleft", false);
	turn_left.find("inputs").push(&parameter_number(sprite, code[0], id)).value = "DEGREES";
	sprite.find("blocks").push(&turn_left);
	return id;
}
std::string set_x(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("setx");
	bparser::node& setx = block(id, "motion_setx", false);
	setx.find("inputs").push(&parameter_number(sprite, code[0], id)).value = "X";
	sprite.find("blocks").push(&setx);
	return id;
}
std::string set_y(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Eypected 1 parameter");
	std::string id = id::get("sety");
	bparser::node& sety = block(id, "motion_sety", false);
	sety.find("inputs").push(&parameter_number(sprite, code[0], id)).value = "Y";
	sprite.find("blocks").push(&sety);
	return id;
}
std::string change_x(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("changex");
	bparser::node& changex = block(id, "motion_changexby", false);
	changex.find("inputs").push(&parameter_number(sprite, code[0], id)).value = "DX";
	sprite.find("blocks").push(&changex);
	return id;
}
std::string change_y(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("changey");
	bparser::node& changey = block(id, "motion_changeyby", false);
	changey.find("inputs").push(&parameter_number(sprite, code[0], id)).value = "DY";
	sprite.find("blocks").push(&changey);
	return id;
}
std::string goto_pos(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("goto");
	bparser::node& goto_pos = block(id, "motion_goto", false);
	sprite.find("blocks").push(&goto_pos);
	bparser::node& option = goto_pos.find("inputs").emplace("TO");
	option.emplace("1");
	// Shadow block
	std::string menuid = id::get("goto_posmenu");
	bparser::node& goto_posmenu = block(menuid, "motion_goto_menu", false, true);
	parent(goto_posmenu, id);
	bparser::node& menuoption = goto_posmenu.find("fields").emplace("TO");
	menuoption.emplace(param[0].value).string = true;
	menuoption.emplace("null");
	sprite.find("blocks").push(&goto_posmenu);
	option.emplace(menuid);
	return id;
}
std::string goto_xy(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 2) throw error("Expected 2 parameters");
	std::string id = id::get("goto");
	bparser::node& gotoxy = block(id, "motion_gotoxy", false);
	gotoxy.find("inputs").push(&parameter_number(sprite, code[0], id)).value = "X";
	gotoxy.find("inputs").push(&parameter_number(sprite, code[1], id)).value = "Y";
	sprite.find("blocks").push(&gotoxy);
	return id;
}
std::string glide_pos(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 2) throw error("Expected 2 parameters");
	std::string id = id::get("glide");
	bparser::node& glide_pos = block(id, "motion_glideto", false);
	glide_pos.find("inputs").push(&parameter_number(sprite, param[0], id)).value = "SECS";
	sprite.find("blocks").push(&glide_pos);
	bparser::node& option = glide_pos.find("inputs").emplace("TO");
	option.emplace("1");
	// Shadow block
	std::string menuid = id::get("glide_posmenu");
	bparser::node& glide_posmenu = block(menuid, "motion_glideto_menu", false, true);
	parent(glide_posmenu, id);
	bparser::node& menuoption = glide_posmenu.find("fields").emplace("TO");
	menuoption.emplace(param[1].value).string = true;
	menuoption.emplace("null");
	sprite.find("blocks").push(&glide_posmenu);
	option.emplace(menuid);
	return id;
}
std::string glide_xy(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 3) throw error("Expected 3 parameters");
	std::string id = id::get("glide");
	bparser::node& glidexy = block(id, "motion_glidesecstoxy", false);
	glidexy.find("inputs").push(&parameter_number(sprite, code[0], id)).value = "SECS";
	glidexy.find("inputs").push(&parameter_number(sprite, code[1], id)).value = "X";
	glidexy.find("inputs").push(&parameter_number(sprite, code[2], id)).value = "Y";
	sprite.find("blocks").push(&glidexy);
	return id;
}
std::string point_direction(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("direction");
	bparser::node& direction = block(id, "motion_pointindirection", false);
	direction.find("inputs").push(&parameter_number(sprite, code[0], id, false, false, true)).value = "DIRECTION";
	sprite.find("blocks").push(&direction);
	return id;
}
std::string point_towards(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("towards");
	bparser::node& towards = block(id, "motion_pointtowards", false);
	sprite.find("blocks").push(&towards);
	bparser::node& option = towards.find("inputs").emplace("TOWARDS");
	option.emplace("1");
	// Shadow block
	std::string menuid = id::get("towardsmenu");
	bparser::node& towardsmenu = block(menuid, "motion_pointtowards_menu", false, true);
	parent(towardsmenu, id);
	bparser::node& menuoption = towardsmenu.find("fields").emplace("TOWARDS");
	menuoption.emplace(param[0].value).string = true;
	menuoption.emplace("null");
	sprite.find("blocks").push(&towardsmenu);
	option.emplace(menuid);
	return id;
}
std::string if_on_edge_bounce(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 0) throw error("Didn't expect any parameters");
	std::string id = id::get("bounce");
	bparser::node& changey = block(id, "motion_ifonedgebounce", false);
	sprite.find("blocks").push(&changey);
	return id;
}
std::string set_rotation_style(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	if (code[0].value != "all around" && code[0].value != "left-right" && code[0].value != "don't rotate") {
		throw error("Invalid value (Expected \"all around\", \"left-right\", or \"don't rotate\")");
	}
	std::string id = id::get("rotationstyle");
	bparser::node& rotstyle = block(id, "motion_setrotationstyle", false);
	bparser::node& style = rotstyle.find("fields").emplace("STYLE");
	style.emplace(code[0].value);
	style.emplace("null");
	sprite.find("blocks").push(&rotstyle);
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
std::string broadcast_wait(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("move");
	bparser::node& broadcast = block(id, "event_broadcastandwait", false);
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
		if (code.value == "goto") return goto_pos(sprite, code);
		if (code.value == "goto_xy") return goto_xy(sprite, code);
		if (code.value == "glide") return glide_pos(sprite, code);
		if (code.value == "glide_xy") return glide_xy(sprite, code);
		if (code.value == "turn_right") return turn_right(sprite, code);
		if (code.value == "turn_left") return turn_left(sprite, code);
		if (code.value == "set_x") return set_x(sprite, code);
		if (code.value == "set_y") return set_y(sprite, code);
		if (code.value == "change_x") return change_x(sprite, code);
		if (code.value == "change_y") return change_y(sprite, code);
		if (code.value == "point_direction") return point_direction(sprite, code);
		if (code.value == "point_towards") return point_towards(sprite, code);
		if (code.value == "set_rotation_style") return set_rotation_style(sprite, code);
		if (code.value == "if_on_edge_bounce") return if_on_edge_bounce(sprite, code);
		// Looks
		else if (code.value == "say") return say(sprite, code);
		// Events
		else if (code.value == "broadcast") return broadcast(sprite, code);
		else if (code.value == "broadcast_wait") return broadcast_wait(sprite, code);
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
