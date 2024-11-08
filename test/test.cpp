#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
// change if you choose to use a different header name
#include "AdjacencyList.h"

using namespace std;

// the syntax for defining a test is below. It is important for the name to be
// unique, but you can group multiple tests with [tags]. A test can have
// [multiple][tags] using that syntax.

// You must write 5 unique, meaningful tests for credit on the testing section of this project!

// Helper function to run PageRank and return output as a string
string runPageRank(int n, const vector<pair<string, string>>& edges) {
    AdjacencyList g;
    for (const auto& edge : edges) {
        g.addEdge(edge.first, edge.second);
    }
    return g.PageRank(n);
}

// Helper function to parse input string and convert it to parameters for runPageRank
void parseInput(const string& input, int& power_iterations, vector<pair<string, string>>& edges) {
    stringstream ss(input);
    int no_of_lines;
    ss >> no_of_lines >> power_iterations;

    string from, to;
    for (int i = 0; i < no_of_lines; i++) {
        ss >> from >> to;
        edges.emplace_back(from, to);
    }
}

// Test with two pages, one linking to the other
TEST_CASE("PageRank test 1 with two nodes and one link", "[pagerank]") {
    string input = R"(1 2
amazon.com bloomberg.com)";
    string expectedOutput = R"(amazon.com 0.50
bloomberg.com 0.50)";

    // Parse input for params
    int power_iterations;
    vector<pair<string, string>> edges;
    parseInput(input, power_iterations, edges);

    string actualOutput = runPageRank(power_iterations, edges);
    REQUIRE(actualOutput == expectedOutput);
}

// Test with a cycle A -> B -> C -> A
TEST_CASE("PageRank test 2 with cycle in three nodes", "[pagerank]") {
    string input = R"(3 5
amazon.com bloomberg.com
bloomberg.com citadel.com
citadel.com amazon.com)";
    string expectedOutput = R"(amazon.com 0.33
bloomberg.com 0.33
citadel.com 0.33)";

    // Parse input for params
    int power_iterations;
    vector<pair<string, string>> edges;
    parseInput(input, power_iterations, edges);

    string actualOutput = runPageRank(power_iterations, edges);
    REQUIRE(actualOutput == expectedOutput);
}

// Test with a dangling node, dell.com has no outgoing links
TEST_CASE("PageRank test 3 with dangling node", "[pagerank]") {
    string input = R"(4 5
amazon.com bloomberg.com
bloomberg.com citadel.com
citadel.com amazon.com
dell.com )";
    // Node dell.com has no links, so it should receive a fair share of rank
    string expectedOutput = R"(amazon.com 0.25
bloomberg.com 0.25
citadel.com 0.25
dell.com 0.25)";

    // Parse input for params
    int power_iterations;
    vector<pair<string, string>> edges;
    parseInput(input, power_iterations, edges);

    string actualOutput = runPageRank(power_iterations, edges);
    REQUIRE(actualOutput == expectedOutput);
}

// Test where multiple nodes link to a single node
TEST_CASE("PageRank test 4 with multiple incoming links", "[pagerank]") {
    string input = R"(2 5
amazon.com citadel.com
bloomberg.com citadel.com)";
    string expectedOutput = R"(amazon.com 0.25
bloomberg.com 0.25
citadel.com 0.50)";

    // Parse input for params
    int power_iterations;
    vector<pair<string, string>> edges;
    parseInput(input, power_iterations, edges);

    string actualOutput = runPageRank(power_iterations, edges);
    REQUIRE(actualOutput == expectedOutput);
}

// Test where some nodes are isolated and not linked at all
TEST_CASE("PageRank test 5 with isolated nodes", "[pagerank]") {
    string input = R"(2 10
amazon.com bloomberg.com
citadel.com dell.com)";
    string expectedOutput = R"(amazon.com 0.25
bloomberg.com 0.25
citadel.com 0.25
dell.com 0.25)";

    // Parse input for params
    int power_iterations;
    vector<pair<string, string>> edges;
    parseInput(input, power_iterations, edges);

    string actualOutput = runPageRank(power_iterations, edges);
    REQUIRE(actualOutput == expectedOutput);
}

//// This uses C++ "raw strings" and assumes PageRank outputs a string with the same thing you print.
//TEST_CASE("Example PageRank Output Test", "[flag]") {
//
//  // the following is a "raw string" - you can write the exact input (without any indentation!) and it should work as expected
//  string input = R"(7 2
//google.com gmail.com
//google.com maps.com
//facebook.com ufl.edu
//ufl.edu google.com
//ufl.edu gmail.com
//maps.com facebook.com
//gmail.com maps.com)";
//
//  string expectedOutput = R"(facebook.com 0.20
//gmail.com 0.20
//google.com 0.10
//maps.com 0.30
//ufl.edu 0.20)";
//
//  string actualOutput;
//
//  // somehow pass your input into your AdjacencyList and parse it to call the correct functions, for example:
////    actualOutput = g.getStringRepresentation()
//
//  REQUIRE(actualOutput == expectedOutput);
//}
