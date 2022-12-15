#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>

#include "catch2/catch.hpp"
TEST_CASE("test case using english.txt") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");

	// work -> play
	auto const ladders_1 = word_ladder::generate("work", "play", english_lexicon);

	CHECK(std::size(ladders_1) == 12);
	// find if the result is sorted
	CHECK(std::is_sorted(ladders_1.begin(), ladders_1.end()));

	CHECK(std::count(ladders_1.begin(),
	                 ladders_1.end(),
	                 std::vector<std::string>{"work", "fork", "form", "foam", "flam", "flay", "play"})
	      == 1);
	CHECK(std::count(ladders_1.begin(),
	                 ladders_1.end(),
	                 std::vector<std::string>{"work", "pork", "perk", "peak", "pean", "plan", "play"})
	      == 1);
	CHECK(std::count(ladders_1.begin(),
	                 ladders_1.end(),
	                 std::vector<std::string>{"work", "pork", "perk", "peak", "peat", "plat", "play"})
	      == 1);
	CHECK(std::count(ladders_1.begin(),
	                 ladders_1.end(),
	                 std::vector<std::string>{"work", "pork", "perk", "pert", "peat", "plat", "play"})
	      == 1);
	CHECK(std::count(ladders_1.begin(),
	                 ladders_1.end(),
	                 std::vector<std::string>{"work", "pork", "porn", "pirn", "pian", "plan", "play"})
	      == 1);
	CHECK(std::count(ladders_1.begin(),//
	                 ladders_1.end(),
	                 std::vector<std::string>{"work", "pork", "port", "pert", "peat", "plat", "play"})
	      == 1);
	CHECK(std::count(ladders_1.begin(),
	                 ladders_1.end(),
	                 std::vector<std::string>{"work", "word", "wood", "pood", "plod", "ploy", "play"})
	      == 1);
	CHECK(std::count(ladders_1.begin(),
	                 ladders_1.end(),
	                 std::vector<std::string>{"work", "worm", "form", "foam", "flam", "flay", "play"})
	      == 1);
	CHECK(std::count(ladders.begin(),
	                 ladders.end(),
	                 std::vector<std::string>{"work", "worn", "porn", "pirn", "pian", "plan", "play"})
	      == 1);
	CHECK(std::count(ladders_1.begin(),
	                 ladders_1.end(),
	                 std::vector<std::string>{"work", "wort", "bort", "boat", "blat", "plat", "play"})
	      == 1);
	CHECK(std::count(ladders_1.begin(),
	                 ladders_1.end(),
	                 std::vector<std::string>{"work", "wort", "port", "pert", "peat", "plat", "play"})
	      == 1);
	CHECK(std::count(ladders_1.begin(),
	                 ladders_1.end(),
	                 std::vector<std::string>{"work", "wort", "wert", "pert", "peat", "plat", "play"})
	      == 1);
	// at -> it
	auto const ladders_2 = word_ladder::generate("at", "it", english_lexicon);

	CHECK(std::size(ladders_2) == 1);
	CHECK(std::is_sorted(ladders_2.begin(), ladders_2.end()));

	CHECK(std::count(ladders_2.begin(), ladders_2.end(), std::vector<std::string>{"at", "it"}) == 1);
	
	//hate -> love
	auto const ladders_3 = word_ladder::generate("hate", "love", english_lexicon);
	CHECK(std::size(ladders_3) == 3);
	CHECK(std::count(ladders_3.begin(),
	                 ladders_3.end(),
	                 std::vector<std::string>{"hate", "have", "hove", "love"}) == 1);
	CHECK(std::count(ladders_3.begin(),
	                 ladders_3.end(),
	                 std::vector<std::string>{"hate", "have", "lave", "love"}) == 1);
	CHECK(std::count(ladders_3.begin(),
	                 ladders_3.end(),
	                 std::vector<std::string>{"hate", "late", "lave", "love"}) == 1);


}
