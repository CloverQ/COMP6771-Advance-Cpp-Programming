#include "comp6771/word_ladder.hpp"
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>
// Write your implementation here
namespace word_ladder {

	auto lexi_sort(std::vector<std::string> v1, std::vector<std::string> v2) -> bool {
		auto const length = v1.size();
		for (unsigned int i = 0; i < length; ++i) {
			if (v1[i] != v2[i]) {
				return v1[i] < v2[i];
			}
		}

		return 0;
	}

	auto compare(std::string const& word1, std::string const& word2) -> bool {
		auto ct = 0;
		for (unsigned int i = 0; i < word1.size(); ++i) {
			if (word1[i] != word2[i]) {
				ct++;
			}
		}
		return ct == 1;
	}

	auto get_route(std::vector<std::vector<std::string>> levels,
	               int hops,
	               std::string const& to,
	               std::vector<std::string> route,
	               std::vector<std::vector<std::string>>& contain)
	   -> std::vector<std::vector<std::string>> {
		if (hops >= 0) {
			auto temp = route;
			auto column = levels[static_cast<std::size_t>(hops)];
			for (auto iter = column.begin(); iter != column.end(); ++iter) {
				route = temp;
				if (compare(*iter, to)) {
					route.emplace(route.begin(), *iter);

					if (hops == 0) {
						contain.emplace(contain.begin(), route);
					}

					get_route(levels, hops - 1, *iter, route, contain);
				}
			}
		}
		return contain;
	}

	auto generate(std::string const& from,
	              std::string const& to,
	              std::unordered_set<std::string> const& lexicon)
	   -> std::vector<std::vector<std::string>> {
		auto const len = from.size();
		auto words = std::unordered_set<std::string>{};
		auto result_level = 0;
		for (auto iter = lexicon.begin(); iter != lexicon.end(); ++iter) {
			// std::cout<<*iter<<"\n"
			auto letter = *iter;
			if (letter.size() == len) {
				words.emplace(letter);
			}
		}
		auto current = std::queue<std::string>{}; // words in current queue
		auto levels = std::unordered_map<std::string, int>{}; // level of words
		auto levels_elements = std::vector<std::vector<std::string>>{};
		levels.emplace(from, 0);
		levels_elements.emplace_back(std::vector<std::string>{from});
		current.push(from);

		auto flag_find = 1; // if the word have been find
		while (!current.empty() and flag_find == 1) { // while queue not empty

			for (auto iter1 = words.begin(); iter1 != words.end(); ++iter1) {
				auto letter = *iter1;

				if (compare(letter, current.front())) { // find words similar

					if (levels.find(letter) == levels.end()) { // if letter has not been visited

						current.push(letter);
						auto lv_of_front = static_cast<std::size_t>(levels[current.front()]);
						levels.emplace(letter, lv_of_front + 1);
						if (levels_elements.size() <= lv_of_front + 1) {
							levels_elements.emplace_back(std::vector<std::string>{letter});
						}
						else {
							// std::cout<<lv_of_front<<levels_elements.size()<<"\n";
							levels_elements[lv_of_front + 1].emplace_back(letter);
						}
					}
					if (letter == to) {
						flag_find = 0;
						result_level = levels[current.front()];
						break;
					}
				}
			}

			current.pop();
		}

		auto result = std::vector<std::vector<std::string>>{std::vector<std::string>{}};

		result = get_route(levels_elements, result_level, to, std::vector<std::string>{to}, result);
		result.pop_back();
		std::sort(result.begin(), result.end(), lexi_sort);

		return result;
	}

} // namespace word_ladder
