

#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>

#include "catch2/catch.hpp"
// When there is no word ladder between two words.
TEST_CASE("Various examples") {
	SECTION("There is no ladder between two words") {
		auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
		auto const ladders = word_ladder::generate("tricycle", "airplane", english_lexicon);

		CHECK(std::size(ladders) == 0);
	}
	SECTION("isolated from") {
		auto const english_lexicon = std::unordered_set<std::string>{"aaaa", "abbb", "abbc,abcd"};
		auto const ladders = word_ladder::generate("aaaa", "abcd", english_lexicon);

		CHECK(std::size(ladders) == 0);
	}
	SECTION("isolated to") {
		auto const english_lexicon = std::unordered_set<std::string>{"aaaa", "abaa", "abca", "aabd"};
		auto const ladders = word_ladder::generate("aaaa", "aabd", english_lexicon);

		CHECK(std::size(ladders) == 0);
	}

	SECTION("Only one ladder") {
		auto const english_lexicon = std::unordered_set<std::string>{"aaaa", "abaa", "abca", "abcd"};
		auto const ladders = word_ladder::generate("aaaa", "abcd", english_lexicon);

		CHECK(std::size(ladders) == 1);
		CHECK(std::count(ladders.begin(),
		                 ladders.end(),
		                 std::vector<std::string>{"aaaa", "abaa", "abca", "abcd"})
		      == 1);
	}
}
