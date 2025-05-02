// lascra when

#include "when.hxx"

#include "id.hxx"
#include "block.hxx"
#include "error.hxx"
#include "find.hxx"

#include "code.hxx"
#include "parameter.hxx"

#include <bparser/node.hxx>
#include <string>

void when(bparser::node& sprite, bparser::node& params) {
	if (params.size() == 0) {
		throw error("Expected at least one argument");
	}
	// Different events
	std::string eventid = "";
	bparser::node* event;
	if (params[0].value == "flag") {
		eventid = id::get("flag");
		event = &block(eventid, "event_whenflagclicked");
	}
	else if (params[0].value == "clicked") {
		eventid = id::get("clicked");
		event = &block(eventid, "event_whenthisspriteclicked");
	}
	else if (params[0].value == "clone") {
		eventid = id::get("clone");
		event = &block(eventid, "control_start_as_clone");
	}
	else if (params[0].value == "pressed") {
		if (params[0].size() != 1) throw error("Expected key name");
		eventid = id::get("received");
		event = &block(eventid, "event_whenkeypressed");
		bparser::node& pressed = event->find("fields").emplace("KEY_OPTION");
		pressed.emplace(params[0][0].value).string = true;
		pressed.emplace("null");
	}
	else if (params[0].value == "backdrop") {
		if (params[0].size() != 1) throw error("Expected backdrop name");
		eventid = id::get("received");
		event = &block(eventid, "event_whenkeypressed");
		bparser::node& pressed = event->find("fields").emplace("BACKDROP");
		pressed.emplace(params[0][0].value).string = true;
		pressed.emplace("null");
	}
	else if (params[0].value == "received") {
		if (params[0].size() != 1) throw error("Expected broadcast name");
		eventid = id::get("received");
		event = &block(eventid, "event_whenbroadcastreceived");
		bparser::node& broadcast = event->find("fields").emplace("BROADCAST_OPTION");
		broadcast.emplace(params[0][0].value).string = true;
		try { broadcast.emplace(find_broadcast(sprite, params[0][0].value)); }
		catch (std::exception& e) { throw error("received", e); }
	}
	else if (params[0].value == "loudness" || params[0].value == "timer") {
		if (params[0].size() != 1) throw error("Expected 1 parameter");
		eventid = id::get("greater");
		event = &block(eventid, "event_whengreaterthan");
		bparser::node& greater = event->find("fields").emplace("WHENGREATERTHANMENU");
		greater.emplace((params[0].value == "loudness") ? "LOUDNESS" : "TIMER");
		greater.emplace("null");
		try { event->find("inputs").push(&parameter_string(sprite, params[0][0], eventid)).value = "VALUE"; }
		catch (std::exception& e) { throw error(params[0].value, e); }
	}
	sprite.find("blocks").push(event);
	// Code in event
	substack(sprite, params, 1, eventid);
}
