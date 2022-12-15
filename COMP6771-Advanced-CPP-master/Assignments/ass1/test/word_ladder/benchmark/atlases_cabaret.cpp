//
//  Copyright UNSW Sydney School of Computer Science and Engineering
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// this test will check the correctness of the benchmark. knowing the solution is 840 words of length 58, both retrieved
// from the known naive solution and other peoples output posted on forums, exact values will be used to do all benchmark
// testing. all tests will assume the ladders produced from the naive solution are correct and verified, based on the
// knowledge from the other tests. This means we will just compare the known output from the naive solution to the optimised
// solution each time.

// This is the benchmark for atlases -> cabaret the hardest case for word ladders.

#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "comp6771/testing/range/same_length.hpp"
#include "comp6771/testing/range/unique_ladders.hpp"

TEST_CASE("atlases -> cabaret") {
	auto const english_lexicon = ::word_ladder::read_lexicon("./english.txt");
    auto const ladders_efficient = ::word_ladder::generate("atlases", "cabaret", english_lexicon);
    auto const ladders_correct = ::word_ladder_slow::generate_accurate("atlases", "cabaret", english_lexicon);

	CHECK(std::size(ladders_correct) == 840);
    CHECK(ladders_correct[0].size() == 58);
    CHECK(testing::ladders_same_length(ladders_correct));
    CHECK(testing::unique_ladders(ladders_correct));
    CHECK(std::is_sorted(ladders_correct.begin(), ladders_correct.begin()));

    CHECK(std::equal(ladders_correct.begin(), ladders_correct.end(), ladders_efficient.begin()));
}
