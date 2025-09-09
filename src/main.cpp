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
	if (dict.read("data/english.txt")) {
		std::cerr << "ERROR: Failed to read dictionary file!" << std::endl;
		return 1;
	} else {
		std::cerr << zstring::numberFormat(dict.length()) << " words.\n";
	}

	// Create an initial random grid
	wordSearch ws;
	ws.randomize(rows, cols);

	std::cerr << "Permuting the grid until it contains only words of length 2..." << std::endl;

	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(65, 90); // A-Z

	// Narrow down the grid until only 2-letter words remain.
	int count = 0;
	while ((count = ws.scan(dict, 3))) {
		std::cerr << "Found " << count << " words, permuting...\n";

		// Randomly change each letter in each found word
		for (int i = 0; i < count; ++i) {
			ws.mutateMatch(i, [&distribution, &generator](char c) {
				(void)c;
				return distribution(generator);
				return (c == 'Z') ? 'A' : c + 1;
			});
		}

		ws.reset();
	}

	// Print the grid
	ws.print(std::cout);

	return 0;
}
