// lascra procedure

#include "procedure.hxx"

#include "id.hxx"
#include "block.hxx"
#include "error.hxx"
#include "find.hxx"

#include "code.hxx"
#include "parameter.hxx"

#include <bparser/node.hxx>
#include <string>
#include <sstream>
#include <iostream>

/* ls_procedures structure (sprite->ls_procedures)
 * - ls_procedures
 *   - procedure_name
 *     - arguments
 *       - argument_name
 *         - argument_type
 *         - argument_id
 *     - mutations (Same as scratch)
 * */


bool inproc = false;

bool inProcedure() { return inproc; }

void procedure(bparser::node& sprite, bparser::node& params) {
	bool warp = (params.value == "function") ? true : false;  // function is a procedure that runs
                                                            // without screen refresh (warp)
  if (params.size() < 2) {
		throw error("Expected at least two arguments");
	}
  // Create Lascra Procedure List
  if (!sprite.exists("ls_procedures"))
    sprite.emplace("ls_procedures");
  else if (sprite.find("ls_procedures").exists(params[0].value))
    throw error(0, "procedure","Procedure redefinition!");
  else if (params[0].size() != 0)
    throw error(0, "procedure", "Expected string");
  // Procedure Entry
  bparser::node& entry = sprite.find("ls_procedures").emplace(params[0].value);
  bparser::node& arguments = entry.emplace("arguments");
  bparser::node& mutation = entry.emplace("mutation");
  // Prepare Blocks
  bparser::node& definition = sprite.find("blocks").push(&block(id::get("definition"), "procedures_definition"));
  bparser::node& prototype = sprite.find("blocks").push(&block(id::get("prototype"), "procedures_prototype", false, true));
  parent(prototype, definition.value);
  bparser::node& ref = definition.find("inputs").emplace("custom_block");
  ref.emplace("1");
  ref.emplace(prototype.value);
  bparser::node& protomut = prototype.emplace("mutation");
  // Process Parameters
  std::ostringstream proccode;
  std::ostringstream argumentids;
  std::ostringstream argumentnames;
  std::ostringstream argumentdefaults;
  try {
    proccode << params[1].value;
    argumentids << "[";
    argumentnames << "[";
    argumentdefaults << "[";
    bool first = true;
    for (int i = 0; i < params[1].size(); i++) {
      if (params[1][i].size() == 0) {
        proccode << " " << params[1][i].value;
        continue;
      }
      // Arguments
      if (params[1][i].value == "string" || params[1][i].value == "number" || params[1][i].value == "boolean") {
        if (params[1][i].size() != 1) throw error("Expected 1 parameter");
        if (params[1][i][0].size() != 0) throw error("Expected String");
        bparser::node& arg = arguments.emplace(params[1][i][0].value);
        arg.emplace(((params[1][i].value == "boolean") ? "boolean" : "string"));
        arg.emplace(id::get("arg"));
        proccode << ((params[1][i].value == "boolean") ? " %b" : " %s");
        argumentids << ((first) ? "\"" : ",\"") << arg[1].value << "\"";
        argumentnames << ((first) ? "\"" : ",\"") << params[1][i][0].value << "\"";
        argumentdefaults << ((first) ? "\"" : ",\"") << ((params[1][i].value == "boolean") ? "false\"" : "\"");
        // Create Argument Reporter
        bparser::node& reporter = block(id::get("protoarg"),((params[1][i].value == "boolean") ? "argument_reporter_boolean" : "argument_reporter_string_number"),false,true);
        parent(reporter, prototype.value);
        bparser::node& value = reporter.find("fields").emplace("VALUE");
        value.emplace(arg.value).string = true;
        value.emplace("null");
        sprite.find("blocks").push(&reporter);
        bparser::node& input = prototype.find("inputs").emplace(arg[1].value);
        input.emplace("1");
        input.emplace(reporter.value);
      }
      else throw error(i, params[1][i].value, "Unknown Argument Type");
      first = false;
    }
    // Finalize values
    argumentids << "]";
    argumentnames << "]";
    argumentdefaults << ((first) ? "\"\"" : ",\"\"") << "]";
    // General Mutations
    mutation.emplace("proccode").emplace(proccode.str());
    mutation.emplace("argumentids").emplace(argumentids.str());
    mutation.emplace("argumentnames").emplace(argumentnames.str());
    mutation.emplace("warp").emplace((warp) ? "true" : "false").string = true;
    // Procedure mutations
    protomut.emplace("tagName").emplace("mutation");
    protomut.emplace("children").emplace("");
    protomut.emplace("proccode").emplace(proccode.str());
    protomut.emplace("argumentids").emplace(argumentids.str());
    protomut.emplace("argumentnames").emplace(argumentnames.str());
    protomut.emplace("argumentdefaults").emplace(argumentdefaults.str());
    protomut.emplace("warp").emplace((warp) ? "true" : "false").string = true;
  }
  catch (std::exception& e) {
    throw error(1, "procedure", e);
  }

	// Code in procedure
	inproc = true;
  substack(sprite, params, 2, definition.value);
  inproc = false;
}
