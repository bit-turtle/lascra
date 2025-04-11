// lascra when

#include "when.hxx"

#include "id.hxx"
#include "block.hxx"
#include "error.hxx"
#include "find.hxx"

#include "code.hxx"

#include <bparser/node.hxx>
#include <string>

void when(bparser::node& sprite, bparser::node& params) {
	if (params.size() == 0) {
		throw error("Expected at least one argument");
	}
	// Different events
	std::string previd = "";
	bparser::node* prevblock;
	if (params[0].value == "flag") {
		previd = id::get("flag");
		prevblock = &block(previd, "event_whenflagclicked");
	}
	else if (params[0].value == "clicked") {
		previd = id::get("clicked");
		prevblock = &block(previd, "event_whenthisspriteclicked");
	}
	else if (params[0].value == "received") {
		if (params[0].size() != 1) throw error("Expected broadcast name");
		previd = id::get("received");
		prevblock = &block(previd, "event_whenbroadcastreceived");
		bparser::node& broadcast = prevblock->find("fields").emplace("BROADCAST_OPTION");
		broadcast.emplace(params[0][0].value);
		try { broadcast.emplace(find_broadcast(sprite, params[0][0].value)); }
		catch (std::exception e) { throw error("received", e); }
	}
	sprite.find("blocks").push(prevblock);
	// Code in event
	for (int i = 1; i < params.size(); i++) {
		try {
			std::string id = code(sprite, params[i]);
			next(*prevblock, id);
			prevblock = &sprite.find("blocks").find(id);
			parent(*prevblock, previd);
			previd = id;
		}
		catch (std::exception e) {
			throw error(i-1, e);
		}
	}
	
}
