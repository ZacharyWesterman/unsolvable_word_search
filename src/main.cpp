#include "wordSearch.hpp"
#include <iostream>
#include <random>
#include <z/core/array.hpp>
#include <z/core/string.hpp>
#include <z/util/dictionary.hpp>

int main(int argc, char **argv) {
	if (argc < 3) {
		std::cerr << "Usage: " << argv[0] << " <rows> <cols>" << std::endl;
		return 1;
	}

	const auto rows = zstring(argv[1]).integer();
	const auto cols = zstring(argv[2]).integer();

	std::cerr << "Loading dictionary... ";
	z::util::dictionary dict;
	if (dict.read("/usr/share/dict/words")) {
		std::cerr << "ERROR: Failed to read dictionary file!" << std::endl;
		return 1;
	} else {
		dict = dict.filter([](const zstring &word) { return word.length() >= 3; });
		std::cout << zstring::numberFormat(dict.length()) << " words.\n";
	}

	// Create an initial random grid
	wordSearch ws;
	ws.randomize(rows, cols);

	std::cout << "Permuting grid to exclude dictionary words..." << std::endl;

	// Print the grid
	ws.print(std::cout);

	return 0;
}
