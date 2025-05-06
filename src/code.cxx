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
			if (param[i].value == "#") continue;
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
		catch (std::exception& e) { throw error(i, e); }
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
	goto_pos.find("inputs").push(&shadow_parameter(sprite, param[0], id, "goto", "motion_goto_menu", "TO"));
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
	glide_pos.find("inputs").push(&shadow_parameter(sprite, param[0], id, "goto", "motion_goto_menu", "TO"));
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
	towards.find("inputs").push(&shadow_parameter(sprite, param[0], id, "towardsmenu", "motion_pointtowards_menu", "TOWARDS"));
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
std::string say_for(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 2) throw error("Expected 2 parameters");
	std::string id = id::get("say");
	bparser::node& say = block(id, "looks_sayforsecs", false);
	say.find("inputs").push(&parameter_string(sprite, code[0], id)).value = "MESSAGE";
	say.find("inputs").push(&parameter_number(sprite, code[1], id)).value = "SECS";
	sprite.find("blocks").push(&say);
	return id;
}
std::string think(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("think");
	bparser::node& think = block(id, "looks_think", false);
	think.find("inputs").push(&parameter_string(sprite, code[0], id)).value = "MESSAGE";
	sprite.find("blocks").push(&think);
	return id;
}
std::string think_for(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 2) throw error("Expected 2 parameters");
	std::string id = id::get("think");
	bparser::node& think = block(id, "looks_thinkforsecs", false);
	think.find("inputs").push(&parameter_string(sprite, code[0], id)).value = "MESSAGE";
	think.find("inputs").push(&parameter_number(sprite, code[1], id)).value = "SECS";
	sprite.find("blocks").push(&think);
	return id;
}
std::string costume(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("costume");
	bparser::node& costume = block(id, "looks_switchcostumeto", false);
	costume.find("inputs").push(&shadow_parameter(sprite, code[0], id, "costume", "looks_costume", "COSTUME"));
	sprite.find("blocks").push(&costume);
	return id;
}
std::string backdrop(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("backdrop");
	bparser::node& backdrop = block(id, "looks_switchbackdropto", false);
	backdrop.find("inputs").push(&shadow_parameter(sprite, code[0], id, "backdrop", "looks_backdrops", "BACKDROP"));
	sprite.find("blocks").push(&backdrop);
	return id;
}
std::string next_costume(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 0) throw error("Expected no parameters");
	std::string id = id::get("nextcostume");
	bparser::node& nextcostume = block(id, "looks_nextcostume", false);
	sprite.find("blocks").push(&nextcostume);
	return id;
}
std::string next_backdrop(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 0) throw error("Expected no parameters");
	std::string id = id::get("nextbackdrop");
	bparser::node& nextbackdrop = block(id, "looks_nextbackdrop", false);
	sprite.find("blocks").push(&nextbackdrop);
	return id;
}
std::string size(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("setsize");
	bparser::node& set_size = block(id, (code.value == "set_size") ? "looks_setsizeto" : "looks_changesizeby", false);
	set_size.find("inputs").push(&parameter_number(sprite, code[0], id)).value = (code.value == "set_size") ? "SIZE" : "CHANGE";
	sprite.find("blocks").push(&set_size);
	return id;
}
std::string effect(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 2) throw error("Expected 2 parameters");
	std::string id = id::get("effect");
	bparser::node& set_effect = block(id, (code.value == "set_effect") ? "looks_seteffectto" : "looks_changeeffectby", false);
	bparser::node& effect = set_effect.find("fields").push(&field_parameter(code[0], {
    {"color", "COLOR"},
    {"fisheye", "FISHEYE"},
    {"whirl", "WHIRL"},
    {"pixelate","PIXELATE"},
    {"mosaic","MOSAIC"},
    {"brightness","BRIGHTNESS"},
    {"ghost","GHOST"}
  }));
	set_effect.find("inputs").push(&parameter_number(sprite, code[1], id)).value = (code.value == "set_effect") ? "VALUE" : "CHANGE";
	sprite.find("blocks").push(&set_effect);
	return id;
}
std::string clear_effects(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 0) throw error("Expected no parameters");
	std::string id = id::get("cleareffects");
	bparser::node& cleareffects = block(id, "looks_cleargraphiceffects", false);
	sprite.find("blocks").push(&cleareffects);
	return id;
}
std::string show(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 0) throw error("Expected no parameters");
	std::string id = id::get("show");
	bparser::node& show = block(id, "looks_show", false);
	sprite.find("blocks").push(&show);
	return id;
}
std::string hide(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 0) throw error("Expected no parameters");
	std::string id = id::get("hide");
	bparser::node& hide = block(id, "looks_hide", false);
	sprite.find("blocks").push(&hide);
	return id;
}
std::string goto_layer(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 1) throw error("Expected 1 parameter");
	if (param[0].value != "front" && param[0].value != "back")
		throw error("Unknown layer (Expected \"front\" or \"back\")");
	std::string id = id::get("layer");
	bparser::node& layer = block(id, "looks_gotofrontback", false);
	bparser::node& field = layer.find("fields").emplace("FRONT_BACK");
	field.emplace(param[0].value);
	field.emplace("null");
	sprite.find("blocks").push(&layer);
	return id;
}
std::string go_layers(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 2) throw error("Expected 2 parameters");
	if (param[0].value != "forward" && param[0].value != "backward")
		throw error("Unknown layer (Expected \"front\" or \"back\")");
	std::string id = id::get("layer");
	bparser::node& layer = block(id, "looks_goforwardbackwardlayers", false);
	bparser::node& field = layer.find("fields").emplace("FORWARD_BACKWARD");
	field.emplace(param[0].value);
	field.emplace("null");
	layer.find("inputs").push(&parameter_number(sprite, param[1], id, false, true)).value = "NUM";
	sprite.find("blocks").push(&layer);
	return id;
}
// Sound
std::string play_sound(bparser::node& sprite, bparser::node& param) {
  if (param.size() != 1) throw error("Expected 1 parameter");
  std::string id = id::get("play");
  bparser::node& play = block(id, ((param.value == "play") ? "sound_play" : "sound_playuntildone"), false);
  play.find("inputs").push(&shadow_parameter(sprite, param[0], id, "soundmenu", "sound_sounds_menu", "SOUND_MENU"));
  sprite.find("blocks").push(&play);
  return id;
}
std::string stop_sounds(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 0) throw error("Expected no parameters");
	std::string id = id::get("hide");
	bparser::node& hide = block(id, "sound_stopallsounds", false);
	sprite.find("blocks").push(&hide);
	return id;
}
std::string volume(bparser::node& sprite, bparser::node& param) {
  if (param.size() != 1) throw error("Expected 1 parameter");
  std::string id = id::get("volume");
  bparser::node& volume = block(id, ((param.value == "set_volume") ? "sound_setvolumeto" : "sound_changevolumeby"), false);
  volume.find("inputs").push(&parameter_number(sprite, param[0], id)).value = "VOLUME";
  sprite.find("blocks").push(&volume);
  return id;
}
// sound effects (sfx) [set_sfx,change_sfx]
std::string sfx(bparser::node& sprite, bparser::node& param) {
  if (param.size() != 2) throw error("Expected 2 parameters");
  std::string id = id::get("effect");
  bparser::node& effect = block(id, ((param.value == "set_sfx") ? "sound_seteffectto" : "sound_changeeffectby"), false);
  // Sound effect name
  effect.find("fields").push(&field_parameter(param[0], {
        {"pitch", "PITCH"},
        {"pan", "PAN"}
  })).value = "EFFECT";
  // Value
  effect.find("inputs").push(&parameter_number(sprite, param[1], id)).value = "VALUE";
  sprite.find("blocks").push(&effect);
  return id;
}
std::string clear_sfx(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 0) throw error("Expected no parameters");
	std::string id = id::get("hide");
	bparser::node& hide = block(id, "sound_cleareffects", false);
	sprite.find("blocks").push(&hide);
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
	if (param.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("wait");
	bparser::node& wait = block(id, "control_wait_until", false);
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
std::string send_broadcast(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("move");
	bparser::node& broadcast = block(id, "event_broadcastandwait", false);
	bparser::node& input = broadcast.find("inputs").emplace("BROADCAST_INPUT");
	input.emplace("1");
	bparser::node& broadcastinput = input.emplace("");
	broadcastinput.emplace("11");
	broadcastinput.emplace(code[0].value).string = true;
	// broadcastinput.emplace(find_broadcast(sprite, code[0].value));
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
	clone.find("inputs").push(&shadow_parameter(sprite, param[0], id, "clonemenu", "control_create_clone_of_menu", "CLONE_OPTION"));
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
	std::string id = id::get("set");
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
	std::string id = id::get("change");
	bparser::node& change = block(id, "data_changevariableby", false);
	bparser::node& variable = change.find("fields").emplace("VARIABLE");
	variable.emplace(code[0].value);
	variable.emplace(find_variable(sprite, code[0].value));
	change.find("inputs").push(&parameter_number(sprite, code[1], id)).value = "VALUE";
	sprite.find("blocks").push(&change);
	return id;
}
// add item to list
std::string add(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 2) throw error("Expected 2 parameters");
	std::string id = id::get("add");
	bparser::node& add = block(id, "data_addtolist", false);
	add.find("inputs").push(&parameter_string(sprite, code[0], id)).value = "ITEM";
	bparser::node& list = add.find("fields").emplace("LIST");
	list.emplace(code[1].value);
	list.emplace(find_list(sprite, code[1].value));
	sprite.find("blocks").push(&add);
	return id;
}
std::string delete_at(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 2) throw error("Expected 2 parameters");
	std::string id = id::get("delete");
	bparser::node& deleteat = block(id, "data_deleteoflist", false);
	deleteat.find("inputs").push(&parameter_number(sprite, code[0], id, true, true)).value = "INDEX";
	bparser::node& list = deleteat.find("fields").emplace("LIST");
	list.emplace(code[1].value);
	list.emplace(find_list(sprite, code[1].value));
	sprite.find("blocks").push(&deleteat);
	return id;
}
std::string delete_all(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("deleteallall");
	bparser::node& deleteall = block(id, "data_deletealloflist", false);
	bparser::node& list = deleteall.find("fields").emplace("LIST");
	list.emplace(code[0].value);
	list.emplace(find_list(sprite, code[0].value));
	sprite.find("blocks").push(&deleteall);
	return id;
}
std::string insert(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 3) throw error("Expected 3 parameters");
	std::string id = id::get("insert");
	bparser::node& insert = block(id, "data_insertatlist", false);
	insert.find("inputs").push(&parameter_string(sprite, code[0], id)).value = "ITEM";
	insert.find("inputs").push(&parameter_number(sprite, code[1], id, true, true)).value = "INDEX";
	bparser::node& list = insert.find("fields").emplace("LIST");
	list.emplace(code[2].value);
	list.emplace(find_list(sprite, code[2].value));
	sprite.find("blocks").push(&insert);
	return id;
}
std::string replace(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 3) throw error("Expected 3 parameters");
	std::string id = id::get("replace");
	bparser::node& replace = block(id, "data_insertatlist", false);
	replace.find("inputs").push(&parameter_number(sprite, code[0], id, true, true)).value = "INDEX";
	bparser::node& list = replace.find("fields").emplace("LIST");
	list.emplace(code[1].value);
	list.emplace(find_list(sprite, code[1].value));
	replace.find("inputs").push(&parameter_string(sprite, code[2], id)).value = "ITEM";
	sprite.find("blocks").push(&replace);
	return id;
}
std::string show_data(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter1");
	bool list;
	if (code.value == "show_variable") list = false;
	else if (code.value == "show_list") list = true;
	else throw error("Expected \"variable\" or \"list\"");
	std::string id = id::get("showdata");
	bparser::node& show = block(id, list ? "data_showlist" : "data_showvariable", false);
	bparser::node& variable = show.find("fields").emplace(list ? "LIST" : "VARIABLE");
	variable.emplace(code[0].value);
	variable.emplace(list ? find_list(sprite, code[0].value) : find_variable(sprite, code[0].value));
	sprite.find("blocks").push(&show);
	return id;
}
std::string hide_data(bparser::node& sprite, bparser::node& code) {
	if (code.size() != 1) throw error("Expected 1 parameter");
	bool list;
	if (code.value == "hide_variable") list = false;
	else if (code.value == "hide_list") list = true;
	else throw error("Expected \"variable\" or \"list\"");
	std::string id = id::get("hidedata");
	bparser::node& hide = block(id, list ? "data_hidelist" : "data_hidevariable", false);
	bparser::node& variable = hide.find("fields").emplace(list ? "LIST" : "VARIABLE");
	variable.emplace(code[0].value);
	variable.emplace(list ? find_list(sprite, code[0].value) : find_variable(sprite, code[0].value));
	sprite.find("blocks").push(&hide);
	return id;
}
// Sensing
std::string ask(bparser::node& sprite, bparser::node& param) {
	if (param.size() != 1) throw error("Expected 1 parameter");
	std::string id = id::get("ask");
	bparser::node& ask = block(id, "sensing_askandwait", false);
	try { ask.find("inputs").push(&parameter_string(sprite, param[0], id)).value = "QUESTION"; }
	catch (std::exception& e) { throw error("question", e); }
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
		else if (code.value == "say_for") return say_for(sprite, code);
		else if (code.value == "think") return think(sprite, code);
		else if (code.value == "think_for") return think_for(sprite, code);
		else if (code.value == "costume") return costume(sprite, code);
		else if (code.value == "backdrop") return backdrop(sprite, code);
		else if (code.value == "next_costume") return next_costume(sprite, code);
		else if (code.value == "next_backdrop") return next_backdrop(sprite, code);
		else if (code.value == "set_size" || code.value == "change_size") return size(sprite, code);
		else if (code.value == "set_effect" || code.value == "change_effect") return effect(sprite, code);
		else if (code.value == "clear_effects") return clear_effects(sprite, code);
		else if (code.value == "show") return show(sprite, code);
		else if (code.value == "hide") return hide(sprite, code);
		else if (code.value == "goto_layer") return goto_layer(sprite, code);
		else if (code.value == "go_layers") return go_layers(sprite, code);
		// Sounds
		else if (code.value == "set_sfx" || code.value == "change_sfx") return sfx(sprite, code);
		else if (code.value == "clear_sfx") return clear_sfx(sprite, code);
		else if (code.value == "set_volume" || code.value == "change_volume") return volume(sprite, code);
		else if (code.value == "play_sound") return play_sound(sprite, code);
		else if (code.value == "stop_sounds") return stop_sounds(sprite, code);
    // Events
		else if (code.value == "broadcast" || code.value == "broadcast_wait") return send_broadcast(sprite, code);
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
		else if (code.value == "add") return add(sprite, code);
		else if (code.value == "delete") return delete_at(sprite, code);
		else if (code.value == "delete_all") return delete_all(sprite, code);
		else if (code.value == "insert") return insert(sprite, code);
		else if (code.value == "replace") return replace(sprite, code);
		else if (code.value == "show_variable" || code.value == "show_list") return show_data(sprite, code);
		else if (code.value == "hide_variable" || code.value == "hide_list") return hide_data(sprite, code);
		// Sensing
		else if (code.value == "ask") return ask(sprite, code);
    // Error
		else throw error("Unknown command");
	}
	catch (std::exception& e) {
		throw error(code.value, e);
	}
}
