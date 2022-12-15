// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("connections_basic_case") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4, 5, 6};
    g.insert_edge(1, 2, 5);
    g.insert_edge(1, 1, 5);
    g.insert_edge(1, 2, 4);
    g.insert_edge(1, 3, 3);
    g.insert_edge(1, 4, 3);
    g.insert_edge(1, 5, 3);
    g.insert_edge(1, 6, 3);
    CHECK(g.connections(1) == std::vector<int>{1, 2, 3, 4, 5, 6});
    CHECK(g.erase_edge(1,5,3));
    CHECK(g.connections(1) == std::vector<int>{1, 2, 3, 4, 6});
}

TEST_CASE("connections_error_case") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4, 5, 6};
    g.insert_edge(1, 2, 5);
    g.insert_edge(1, 1, 5);
    g.insert_edge(1, 2, 4);
    g.insert_edge(1, 3, 3);
    g.insert_edge(1, 4, 3);
    g.insert_edge(1, 5, 3);
    g.insert_edge(1, 6, 3);
    CHECK_THROWS_WITH(g.connections(34),
                      "Cannot call gdwg::graph<N, E>::connections if src doesn't exist in the graph");
}
TEST_CASE("empty_tests") {
    using graph = gdwg::graph<int, int>;
    const auto g = graph();
    auto g2 = graph{1,2,3,4,5};
    CHECK(g.empty());
    CHECK(!g2.empty());
    g2.erase_node(1);
    g2.erase_node(2);
    g2.erase_node(3);
    g2.erase_node(4);
    g2.erase_node(5);
    CHECK(g2.empty());
}
TEST_CASE("default_constructor_ints") {
    using graph = gdwg::graph<int, int>;
    using value_type = gdwg::graph<int, int>::value_type;
    auto g = graph{1,2,3,4,5};
    g.insert_edge(1,2,3);
    g.insert_edge(1,2,3);
    g.insert_edge(1,2,4);
    g.insert_edge(1,2,5);
    CHECK(*g.find(1,2,3) == value_type{1,2,3});
    CHECK(*g.find(1,2,4) == value_type{1,2,4});
    CHECK(*g.find(1,2,5) == value_type{1,2,5});
    CHECK(g.find(68,2,3) == g.end());
}
TEST_CASE("normal_case_is_connected") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1,2,3,4,5};
    g.insert_edge(1,2,3);
    g.insert_edge(1,3,3);
    g.insert_edge(1,4,4);
    g.insert_edge(1,1,5);
    CHECK(g.is_connected(1,1));
    CHECK(g.is_connected(1,2));
    CHECK(g.is_connected(1,3));
    CHECK(g.is_connected(1,4));
}

TEST_CASE("error_case") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1,2,3,4,5};
    g.insert_edge(1,2,3);
    g.insert_edge(1,3,3);
    g.insert_edge(1,4,4);
    g.insert_edge(1,1,5);
    CHECK_THROWS_WITH(g.is_connected(1,59), "Cannot call gdwg::graph<N, E>::is_connected if src or dst node don't exist in the graph");
    CHECK_THROWS_WITH(g.is_connected(59,1), "Cannot call gdwg::graph<N, E>::is_connected if src or dst node don't exist in the graph");
    CHECK_THROWS_WITH(g.is_connected(6,59), "Cannot call gdwg::graph<N, E>::is_connected if src or dst node don't exist in the graph");
}
TEST_CASE("is_node_tests") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1,2,3,4,5,6,7,8,9};
    g.insert_edge(1,2,3);
    g.insert_edge(1,2,4);
    g.insert_edge(1,2,5);
    g.insert_edge(2,2,1);
    SECTION("Checking positive and negative cases before deletion") {
        CHECK(g.is_node(1));
        CHECK(g.is_node(2));
        CHECK(g.is_node(3));
        CHECK(g.is_node(4));
        CHECK(g.is_node(5));
        CHECK(g.is_node(6));
        CHECK(g.is_node(7));
        CHECK(g.is_node(8));
        CHECK(g.is_node(9));
        CHECK(!g.is_node(6659));
    }
    SECTION("Removing Node and seeing if it still works") {
        g.erase_node(1);
        CHECK(!g.is_node(1));
        CHECK(g.is_node(2));
        CHECK(g.is_node(3));
        CHECK(g.is_node(4));
        CHECK(g.is_node(5));
        CHECK(g.is_node(6));
        CHECK(g.is_node(7));
        CHECK(g.is_node(8));
        CHECK(g.is_node(9));
    }
}
TEST_CASE("nodes_test") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 3, 2, 4, 6, 5, 7, 8};
    g.insert_edge(1, 2, 3);
    g.insert_edge(1, 2, 4);
    g.insert_edge(1, 2, 5);
    g.insert_edge(2, 2, 1);
    CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
    g.erase_node(1);
    CHECK(g.nodes() == std::vector<int>{2, 3, 4, 5, 6, 7, 8});
}

TEST_CASE("nodes_empty") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4, 5, 6, 7, 8, 8};
    CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
    g.insert_edge(1, 2, 3);
    g.insert_edge(1, 2, 4);
    g.insert_edge(1, 2, 5);
    g.insert_edge(2, 2, 1);
    g.erase_node(1);
    CHECK(g.nodes() == std::vector<int>{2, 3, 4, 5, 6, 7, 8});
}
TEST_CASE("weights_normal_case") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2};
    CHECK(g.nodes() == std::vector<int>{1, 2});
    g.insert_edge(1, 2, 4);
    g.insert_edge(1, 2, 9);
    g.insert_edge(1, 2, 9);
    g.insert_edge(1, 2, 3);
    g.insert_edge(2, 2, 1);
    CHECK(g.weights(1,2) == std::vector<int>{3,4,9});
    CHECK(g.weights(2,2) == std::vector<int>{1});
    SECTION("Checking weights are correct after a merge replace") {
        g.merge_replace_node(1, 2);
        CHECK(g.nodes() == std::vector<int>{2});
        CHECK(g.connections(2) == std::vector<int>{2});
        CHECK(g.weights(2, 2) == std::vector<int>{1, 3, 4, 9});
    }
}

TEST_CASE("weights_error_case") {
    using graph = gdwg::graph<int, int>;
    auto g = graph();
    CHECK(g.empty());
    CHECK_THROWS_WITH(g.weights(1,3), "Cannot call gdwg::graph<N, E>::weights if src or dst node don't exist in the graph");
}
TEST_CASE("copy_constructor") {
    using graph = gdwg::graph<std::string, int>;
    const auto g1 = graph{"Hey", "hello", "why", "??", "lol", "Kappa123", "PauseChamp"};
    CHECK(!g1.empty());
    const auto g2 = g1;
    CHECK(g1 == g2);
}
TEST_CASE("copy_equals") {
    using graph = gdwg::graph<std::string, int>;
    const auto g1 = graph{"Hey", "hello", "why", "??", "lol", "Kappa123", "PauseChamp"};
    CHECK(!g1.empty());
    const auto g2 = g1;
    CHECK(g1 == g2);
}
TEST_CASE("default_constructor_ints") {
    using graph = gdwg::graph<int, int>;
    const auto g = graph();
    CHECK(g.empty());
}
TEST_CASE("initialiser_list_constructor") {
    using graph = gdwg::graph<std::string, int>;
    const auto vector_il = std::vector<std::string>{"Hey", "hello", "why", "??", "lol", "Kappa123", "PauseChamp"};
    const auto g = graph{"Hey", "hello", "why", "??", "lol", "Kappa123", "PauseChamp"};
    const auto all_nodes = g.nodes();
    auto sorted_nodes = vector_il;
    std::sort(sorted_nodes.begin(), sorted_nodes.end());
    // wasn't bothered to sort it manually so i let c++ do it for me
    CHECK(!g.empty());
    CHECK(std::is_sorted(all_nodes.begin(), all_nodes.end()));
    CHECK(std::equal(all_nodes.begin(), all_nodes.end(), sorted_nodes.begin()));
}
TEST_CASE("input_iterator_constructor") {
    using graph = gdwg::graph<std::string, int>;
    const auto vector_il = std::vector<std::string>{"Hey", "hello", "why", "??", "lol", "Kappa123", "PauseChamp"};
    const auto g = graph(vector_il.begin(), vector_il.end());
    const auto all_nodes = g.nodes();
    auto sorted_nodes = vector_il;
    std::sort(sorted_nodes.begin(), sorted_nodes.end());
    CHECK(!g.empty());
    CHECK(std::is_sorted(all_nodes.begin(), all_nodes.end()));
    CHECK(std::equal(all_nodes.begin(), all_nodes.end(), sorted_nodes.begin()));
}
TEST_CASE("move_constructor") {
    using graph = gdwg::graph<std::string, int>;
    auto g1 = graph{"Hey", "hello", "why", "??", "lol", "Kappa123", "PauseChamp"};
    const auto all_nodes1 = g1.nodes();
    CHECK(!g1.empty());
    const auto g2 = graph(std::move(g1));
    const auto all_nodes2 = g2.nodes();
    CHECK(g1.empty());
    CHECK(std::equal(all_nodes1.begin(), all_nodes1.end(), all_nodes2.begin(), all_nodes2.end()));
}
TEST_CASE("move_equals") {
    using graph = gdwg::graph<std::string, int>;
    auto g1 = graph{"Hey", "hello", "why", "??", "lol", "Kappa123", "PauseChamp"};
    const auto all_nodes1 = g1.nodes();
    CHECK(!g1.empty());
    const auto g2 = std::move(g1);
    const auto all_nodes2 = g2.nodes();
    CHECK(g1.empty());
    CHECK(std::equal(all_nodes1.begin(), all_nodes1.end(), all_nodes2.begin(), all_nodes2.end()));
}
TEST_CASE("empty_graph_with_nodes") {
    using graph = gdwg::graph<int, int>;
    const auto g1 = graph();
    CHECK(g1.begin() == g1.end());
    const auto g2 = graph{1,2,3,4,5};
    CHECK(g2.nodes() == std::vector<int>{1,2,3,4,5});
    CHECK(g2.begin() == g2.end());

}

TEST_CASE("graph_with_edges") {
    using graph = gdwg::graph<int, int>;
    using value_type = gdwg::graph<int, int>::value_type;
    auto g = graph{1,2,3,4,5};
    CHECK(g.nodes() == std::vector<int>{1,2,3,4,5});
    CHECK(g.begin() == g.end());
    g.insert_edge(1,2,3);
    CHECK(*g.begin() == value_type{1,2,3});
}
TEST_CASE("decrement_pre") {
    using graph = gdwg::graph<int, int>;
    using value_type = gdwg::graph<int,int>::value_type;
    auto g = graph{1,2,3,4,5};
    g.insert_edge(1,2,3);
    g.insert_edge(1,2,7);
    g.insert_edge(1,2,4);
    g.insert_edge(1,2,6);
    auto it_original = g.begin();
    auto it = g.begin();
    CHECK(*it == value_type{1,2,3});
    it = it++;
    CHECK(*it == value_type{1,2,4});
    it = it--;
    CHECK(*it == value_type{1,2,3});
    CHECK(it == it_original);
    CHECK(it_original == g.begin());
}

TEST_CASE("decrement_post") {
    using graph = gdwg::graph<int, int>;
    using value_type = gdwg::graph<int,int>::value_type;
    auto g = graph{1,2,3,4,5};
    g.insert_edge(1,2,3);
    g.insert_edge(1,2,7);
    g.insert_edge(1,2,4);
    g.insert_edge(1,2,6);
    auto it_original = g.begin();
    auto it = g.begin();
    CHECK(*it == value_type{1,2,3});
    it = it++;
    CHECK(*it == value_type{1,2,4});
    --it;
    CHECK(*it == value_type{1,2,3});
    CHECK(it == it_original);
    CHECK(it_original == g.begin());
}
TEST_CASE("dereference_value") {
    using graph = gdwg::graph<int, int>;
    using value_type = gdwg::graph<int, int>::value_type;
    auto g = graph{1, 2, 3, 4, 5};
    g.insert_edge(1, 2, 3);
    CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4, 5});
    CHECK(*g.begin() == value_type{1, 2, 3});
}

TEST_CASE("Equal_iterators") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4, 5};
    g.insert_edge(1, 2, 3);
    CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4, 5});
    auto first_it = g.begin();
    ++first_it;
    auto second_it = g.begin();
    ++second_it;
    CHECK(first_it == second_it);
    --second_it;
    CHECK(!(second_it == first_it));
    CHECK(second_it == g.begin());
}
TEST_CASE("increment_post") {
    using graph = gdwg::graph<int, int>;
    using value_type = gdwg::graph<int,int>::value_type;
    auto g = graph{1,2,3,4,5};
    g.insert_edge(1,2,3);
    g.insert_edge(1,2,7);
    g.insert_edge(1,2,4);
    g.insert_edge(1,2,6);
    auto it = g.begin();
    CHECK(*it == value_type{1,2,3});
    it = it++;
    CHECK(*it == value_type{1,2,4});
}

TEST_CASE("increment_pre") {
    using graph = gdwg::graph<int, int>;
    using value_type = gdwg::graph<int,int>::value_type;
    auto g = graph{1,2,3,4,5};
    g.insert_edge(1,2,3);
    g.insert_edge(1,2,7);
    g.insert_edge(1,2,4);
    g.insert_edge(1,2,6);
    auto it = g.begin();
    CHECK(*it == value_type{1,2,3});
    ++it;
    CHECK(*it == value_type{1,2,4});
}
TEST_CASE("clear_graphs") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1,2,3,4,5,6,7,8,0, 9};
    CHECK(g.nodes() == std::vector<int>{0,1,2,3,4,5,6,7,8,9});
    g.clear();
    CHECK(g.empty());
}
TEST_CASE("remove_edges_default") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    g.insert_edge(1, 2, 9);
    SECTION("Checking graph before erase conditions") {
        CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4});
        CHECK(g.connections(1) == std::vector<int>{2});
        CHECK(g.weights(1, 2) == std::vector<int>{9});
        CHECK(g.connections(2) == std::vector<int>{});
        CHECK(g.connections(3) == std::vector<int>{});
        CHECK(g.connections(4) == std::vector<int>{});
    }
    SECTION("Removing the edge and checking graph post conditions"){
        CHECK(g.erase_edge(1, 2, 9));
        CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4});
        CHECK(g.connections(1) == std::vector<int>{});
        CHECK(g.weights(1, 2) == std::vector<int>{});
        CHECK(g.connections(2) == std::vector<int>{});
        CHECK(g.connections(3) == std::vector<int>{});
        CHECK(g.connections(4) == std::vector<int>{});
    }
}

TEST_CASE("remove_edges_errors") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    g.insert_edge(1, 2, 9);
    SECTION("Check graph is made properly") {
        CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4});
        CHECK(g.connections(1) == std::vector<int>{2});
        CHECK(g.weights(1, 2) == std::vector<int>{9});
        CHECK(g.connections(2) == std::vector<int>{});
        CHECK(g.connections(3) == std::vector<int>{});
        CHECK(g.connections(4) == std::vector<int>{});
    }
    SECTION("erase edge returns false for nodes that exist") {
        CHECK(!g.erase_edge(1, 2, 99));
        CHECK(!g.erase_edge(1, 3, 99));
        CHECK(!g.erase_edge(2, 2, 99));
        CHECK(!g.erase_edge(2, 2, 9));
    }
    SECTION("erase edge throws exception when nodes either from and to dont exist") {
        CHECK_THROWS_WITH(g.erase_edge(2, 29, 9),
                          "Cannot call gdwg::graph<N, E>::erase_edge on src or dst if they don't exist in the graph");
        CHECK_THROWS_WITH(g.erase_edge(29, 2, 9),
                          "Cannot call gdwg::graph<N, E>::erase_edge on src or dst if they don't exist in the graph");
        CHECK_THROWS_WITH(g.erase_edge(82, 29, 9),
                          "Cannot call gdwg::graph<N, E>::erase_edge on src or dst if they don't exist in the graph");
    }
    SECTION("Check graph is unmodified from these fail cases above") {
        CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4});
        CHECK(g.connections(1) == std::vector<int>{2});
        CHECK(g.weights(1, 2) == std::vector<int>{9});
        CHECK(g.connections(2) == std::vector<int>{});
        CHECK(g.connections(3) == std::vector<int>{});
        CHECK(g.connections(4) == std::vector<int>{});
    }
}

TEST_CASE("default_delete_iterator") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    CHECK(g.insert_edge(1, 2, 3));
    CHECK(g.weights(1, 2) == std::vector<int>{3});
    auto iterator_begin = g.begin();
    CHECK(*iterator_begin == gdwg::graph<int, int>::value_type{1, 2, 3});
    auto next_iterator = g.erase_edge(iterator_begin);
    CHECK(next_iterator == g.end());
    CHECK(g.weights(1, 2) == std::vector<int>{});
}

TEST_CASE("multiple_iterator_erase_few") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    CHECK(g.insert_edge(1, 2, 3));
    CHECK(g.insert_edge(1, 3, 3));
    CHECK(g.insert_edge(1, 4, 3));
    CHECK(g.weights(1, 2) == std::vector<int>{3});
    auto iterator_begin = g.begin();
    auto iterator_end = iterator_begin++;
    auto next_iterator = g.erase_edge(iterator_begin, iterator_end);
    CHECK(*next_iterator == gdwg::graph<int, int>::value_type{1, 3, 3});
    // check graph is reset
    CHECK(*g.begin() == gdwg::graph<int, int>::value_type{1, 3, 3});
}

TEST_CASE("multiple_iterator_erase_all") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    CHECK(g.insert_edge(1, 2, 3));
    CHECK(g.insert_edge(1, 3, 3));
    CHECK(g.insert_edge(1, 4, 3));
    CHECK(g.weights(1, 2) == std::vector<int>{3});
    auto iterator_begin = g.begin();
    auto iterator_end = g.end();
    auto next_iterator = g.erase_edge(iterator_begin, iterator_end);
    CHECK(next_iterator == g.end());
    // check graph is reset
    CHECK(g.begin() == g.end());
    CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4});
}

TEST_CASE("remove_node_default") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    g.insert_edge(1, 2, 9);
    CHECK(g.erase_node(1));
    CHECK(g.nodes() == std::vector<int>{2, 3, 4});
    CHECK(g.connections(2) == std::vector<int>{});
    CHECK(g.connections(3) == std::vector<int>{});
    CHECK(g.connections(4) == std::vector<int>{});
}

TEST_CASE("remove_node_false_cases") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    g.insert_edge(1, 2, 9);
    CHECK(!g.erase_node(69));
    CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4});
    CHECK(g.connections(1) == std::vector<int>{2});
    CHECK(g.weights(1, 2) == std::vector<int>{9});
    CHECK(g.connections(2) == std::vector<int>{});
    CHECK(g.connections(3) == std::vector<int>{});
    CHECK(g.connections(4) == std::vector<int>{});
}
TEST_CASE("insert_edge_default") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    auto inserted = g.insert_edge(1, 2, 900);
    CHECK(inserted);
    inserted = g.insert_edge(1, 2, 4);
    CHECK(inserted);
    inserted = g.insert_edge(1, 2, 4);
    CHECK(!inserted);
    inserted = g.insert_edge(1, 3, 5);
    CHECK(inserted);
    CHECK(g.connections(1) == std::vector<int>{2, 3});
    // checks weights sorted
    CHECK(g.weights(1, 2) == std::vector<int>{4, 900});
}

TEST_CASE("insert_edge_missing_node") {
    using graph = gdwg::graph<int, int>;
    auto default_graph = graph();
    auto g = graph{1, 2, 3, 4};
    CHECK_THROWS_WITH(g.insert_edge(1, 69, 900),
                      "Cannot call gdwg::graph<N, E>::insert_edge when either from or to node does not exist");
    CHECK_THROWS_WITH(g.insert_edge(69, 1, 900),
                      "Cannot call gdwg::graph<N, E>::insert_edge when either from or to node does not exist");
    CHECK_THROWS_WITH(g.insert_edge(69, 69, 900),
                      "Cannot call gdwg::graph<N, E>::insert_edge when either from or to node does not exist");
}
TEST_CASE("insert_node_no_duplicate") {
    using graph = gdwg::graph<int, int>;
    auto g = graph();
    CHECK(g.empty());
    auto inserted = g.insert_node(1);
    CHECK(g.nodes().size() == 1);
    CHECK(g.nodes().at(0) == 1);
    CHECK(inserted);
}

TEST_CASE("insert_node_with_duplicate") {
    using graph = gdwg::graph<int, int>;
    auto g = graph();
    CHECK(g.empty());
    auto inserted = g.insert_node(1);
    SECTION("check initial insert is okay") {
        CHECK(g.nodes().size() == 1);
        CHECK(g.nodes().at(0) == 1);
        CHECK(inserted);
    }
    SECTION("Check duplicate insert has no effect") {
        inserted = g.insert_node(1);
        CHECK(g.nodes().size() == 1);
        CHECK(g.nodes().at(0) == 1);
        CHECK(!inserted);
    }
}
TEST_CASE("merge_replace_all_covered") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"A", "B", "C", "D"};
    g.insert_edge("A", "B", 1);
    g.insert_edge("A", "A", 1);
    g.insert_edge("A", "A", 5);
    g.insert_edge("A", "C", 2);
    g.insert_edge("C", "A", 9);
    g.insert_edge("A", "D", 3);
    g.insert_edge("B", "B", 9);
    g.merge_replace_node("A", "B");
    SECTION("Check the graph state after merge replace") {
        CHECK(g.nodes() == std::vector<std::string>{"B", "C", "D"});
        CHECK(g.connections("B") == std::vector<std::string>{"B", "C", "D"});
        CHECK(g.connections("C") == std::vector<std::string>{"B"});
        CHECK(g.weights("B", "B") == std::vector<int>{1, 5, 9});
        CHECK(g.weights("B", "C") == std::vector<int>{2});
        CHECK(g.weights("B", "D") == std::vector<int>{3});
        CHECK(g.weights("C", "B") == std::vector<int>{9});
    }
}

TEST_CASE("merge_replace_same") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"A", "B", "C", "D"};
    g.insert_edge("A", "B", 1);
    g.insert_edge("A", "C", 2);
    g.insert_edge("A", "D", 3);
    g.insert_edge("B", "B", 1);
    SECTION("Check graph before merge replace is called") {
        CHECK(g.nodes() == std::vector<std::string>{"A", "B", "C", "D"});
        CHECK(g.connections("A") == std::vector<std::string>{"B", "C", "D"});
        CHECK(g.weights("B", "B") == std::vector<int>{1});
        CHECK(g.weights("B", "C") == std::vector<int>{});
        CHECK(g.weights("B", "D") == std::vector<int>{});
        CHECK(g.weights("A", "B") == std::vector<int>{1});
        CHECK(g.weights("A", "C") == std::vector<int>{2});
        CHECK(g.weights("A", "D") == std::vector<int>{3});
    }
    g.merge_replace_node("A", "A");
    SECTION("Check same state of graph after merge replacing with the same node") {
        CHECK(g.nodes() == std::vector<std::string>{"A", "B", "C", "D"});
        CHECK(g.connections("A") == std::vector<std::string>{"B", "C", "D"});
        CHECK(g.weights("B", "B") == std::vector<int>{1});
        CHECK(g.weights("B", "C") == std::vector<int>{});
        CHECK(g.weights("B", "D") == std::vector<int>{});
        CHECK(g.weights("A", "B") == std::vector<int>{1});
        CHECK(g.weights("A", "C") == std::vector<int>{2});
        CHECK(g.weights("A", "D") == std::vector<int>{3});
    }
}

TEST_CASE("merge_replace_errors") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"A", "B", "C", "D"};
    g.insert_edge("A", "B", 1);
    g.insert_edge("A", "C", 2);
    g.insert_edge("A", "D", 3);
    g.insert_edge("B", "B", 1);
    CHECK_THROWS_WITH(g.merge_replace_node("A", "F"),
                        "Cannot call gdwg::graph<N, E>::merge_replace_node on old or new data if they don't exist in the graph");
    CHECK_THROWS_WITH(g.merge_replace_node("G", "F"),
                        "Cannot call gdwg::graph<N, E>::merge_replace_node on old or new data if they don't exist in the graph");
    CHECK_THROWS_WITH(g.merge_replace_node("B", "F"),
                        "Cannot call gdwg::graph<N, E>::merge_replace_node on old or new data if they don't exist in the graph");
}
TEST_CASE("replace_node_success") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"hello", "replace me"};
    g.insert_edge("hello", "replace me", 5);
    auto replaced = g.replace_node("hello", "replaced_hello");
    CHECK(replaced);
    auto is_connected = g.is_connected("replaced_hello", "replace me");
    CHECK(is_connected);
    replaced = g.replace_node("replace me", "replaced");
    CHECK(replaced);
    is_connected = g.is_connected("replaced_hello", "replaced");
    CHECK(is_connected);
    CHECK(g.nodes() == std::vector<std::string>{"replaced", "replaced_hello"});
    CHECK(g.connections("replaced_hello") == std::vector<std::string>{"replaced"});
    CHECK(g.weights("replaced_hello", "replaced") == std::vector<int>{5});
}

TEST_CASE("replace_node_errors") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"hello", "replace me"};
    CHECK_THROWS_WITH(g.replace_node("helloWRONG", "replaced"), "Cannot call gdwg::graph<N, E>::replace_node on a node that doesn't exist");
}

TEST_CASE("replace_node_fail") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"hello", "replace me"};
    auto replaced = g.replace_node("hello", "replace me");
    CHECK(!replaced);
    CHECK(g.nodes() == std::vector<std::string>{"hello", "replace me"});
}
TEST_CASE("equals_test") {
    using graph = gdwg::graph<int, int>;
    const auto g1 = graph();
    const auto g2 = graph();
    auto g3 = graph{3,2};
    g3.insert_edge(3,2,4);
    const auto g4 = graph(g3);
    CHECK(g1 == g2);
    CHECK(!(g1 == g3));
    CHECK(g3 == g4);
    CHECK(g3.weights(3,2) == g4.weights(3,2));
}
TEST_CASE("default_constructor_ints") {
    using graph = gdwg::graph<int, int>;
    auto const v = std::vector<graph::value_type>{
            {4, 1, -4},
            {3, 2, 2},
            {2, 4, 2},
            {2, 1, 1},
            {6, 2, 5},
            {6, 3, 10},
            {1, 5, -1},
            {3, 6, -8},
            {4, 5, 3},
            {5, 2, 7},
    };

    auto g = graph{};
    for (const auto &x : v) {
        g.insert_node(x.from);
        g.insert_node(x.to);
        g.insert_edge(x.from, x.to, x.weight);
    };

    g.insert_node(64);
    auto out = std::ostringstream{};
    out << g;
    auto const expected_output = std::string_view(R"(1 (
  5 | -1
)
2 (
  1 | 1
  4 | 2
)
3 (
  2 | 2
  6 | -8
)
4 (
  1 | -4
  5 | 3
)
5 (
  2 | 7
)
6 (
  2 | 5
  3 | 10
)
64 (
)
)");
    CHECK(out.str() == expected_output);
}