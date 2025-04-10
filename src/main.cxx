// lascra main file

#include <iostream>
#include <fstream>
#include <string>
#include <argh.h>
#include <ZipArchive.h>
#include <ZipFile.h>
#include <bparser/node.hxx>
#include <bparser/json.hxx>
#include <bparser/sexpr.hxx>

#include "compiler.hxx"

int main(int argc, char* argv[]) {
	// Command line parser
	argh::parser cmdl(argc, argv);
	// Help if no arguments or help flag
	if (!cmdl(1) || cmdl[{"-h", "--help"}]) {
		std::cout 
			<< "lascra (help)" << std::endl
			<< "Usage: lascra [sprite3 file] [code files...]" << std::endl;
		return EXIT_SUCCESS;
	}
	// Open sprite3 file
	ZipArchive::Ptr sprite3;
	std::string sprite3filename;
	if (cmdl(1)) {
		cmdl(1) >> sprite3filename;
		std::ifstream* sprite3file = new std::ifstream(sprite3filename, std::ios::binary);
		if (!sprite3file->is_open()) {
			std::cout
				<< "Error: Failed to open sprite3 file! (\"" << sprite3filename << "\" not found)" << std::endl;
			return EXIT_FAILURE;
		}
		sprite3 = ZipArchive::Create(sprite3file, true);
		if (sprite3 == nullptr) {
			std::cout
				<< "Error: Invalid zip archive (Processing failed)" << std::endl;
			return EXIT_FAILURE;
		}
	}
	// Open sprite.json
	ZipArchiveEntry::Ptr spritejson = sprite3->GetEntry("sprite.json");
	if (spritejson == nullptr) {
		std::cout
			<< "Error: Invalid sprite3 file! (Missing \"sprite.json\")" << std::endl;
		return EXIT_FAILURE;
	}
	bparser::node& spriteroot = bparser::json::parse(*spritejson->GetDecompressionStream());
	spritejson->CloseDecompressionStream();
	if (spriteroot.size() != 1) {
		std::cout
			<< "Error: Empty sprite.json!" << std::endl;
		return EXIT_FAILURE;
	}
	bparser::node& sprite = spriteroot[0];

	// Check sprite.json structure
	if (
		!sprite.exists("isStage") ||
		!sprite.exists("name") ||
		!sprite.exists("variables") ||
		!sprite.exists("lists") ||
		!sprite.exists("broadcasts") ||
		!sprite.exists("blocks") ||
		!sprite.exists("comments") ||
		!sprite.exists("currentCostume") ||
		!sprite.exists("costumes") ||
		!sprite.exists("sounds") ||
		!sprite.exists("volume") ||
		!sprite.exists("visible") ||
		!sprite.exists("x") ||
		!sprite.exists("y") ||
		!sprite.exists("size") ||
		!sprite.exists("direction") ||
		!sprite.exists("draggable") ||
		!sprite.exists("rotationStyle") ||
		sprite.size() != 18	// Make sure there are no extra nodes
	) {
		std::cout
			<< "Error: Invalid sprite.json structure! (Missing value)" << std::endl;
		return EXIT_FAILURE;
	}
	std::cout
		<< "Using Sprite: " << sprite.find("name")[0].value << std::endl;
	sprite.find("name")[0].value = "edited sprite file";

	// Remove existing code, broadcasts, variables, and lists
	sprite.find("blocks").clear();
	sprite.find("variables").clear();
	sprite.find("lists").clear();
	sprite.find("broadcasts").clear();

	// Compile files
	if (cmdl.size() <= 2) {
		std::cout
			<< "Error: No code files!" << std::endl;
		return EXIT_FAILURE;
	}
	for (int i = 2; i < cmdl.size(); i++) {
		std::string filename;
		cmdl(i) >> filename;
		std::cout
			<< "Compiling File: " << filename << std::endl;
		std::ifstream file(filename);
		if (!file.is_open()) {
			std::cout
				<< "Error: Failed to open file! (\"" << filename << "\" not found)" << std::endl;
			return EXIT_FAILURE;
		}
		bparser::node& code = bparser::sexpr::parse(file);
		file.close();
		try {
			compile(sprite, code);
		}
		catch (std::exception e) {
			std::cout << "Compile Error: " << filename << ":" << e.what() << std::endl;
			return EXIT_FAILURE;
		}
	}
	std::cout << "Compiled all files!" << std::endl;

	// Update sprite.json
	std::cout << "Updating Sprite file... ";
	std::stringstream newjson;
	bparser::json::encode(spriteroot, newjson);
	if (cmdl[{"-d", "--display"}]) std::cout << newjson.str() << std::endl;
	spritejson->SetCompressionStream(newjson);
	// Save updated file
	ZipFile::SaveAndClose(sprite3, sprite3filename);
	std::cout << "Done!" << std::endl;
	
	return EXIT_SUCCESS;
}
