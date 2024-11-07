#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include "AdjacencyList.h"
using namespace std;

// Adds directed edge from 'from' page to 'to' page
void AdjacencyList::addEdge(const string& from, const string& to) {
    graph[from].push_back(to);
    outDeg[from]++;

    // Ensure 'to' is also in the graph, even with no outgoing links
    if (graph.find(to) == graph.end()) {
        graph[to] = {};
    }
}

// Initializes PageRank values
void AdjacencyList::initializePR() {
    // Starting rank of each page
    double in_rank = 1.0 / graph.size();
    // Iterate through each entry in graph map, entry first is webpage, second is vector of outgoing links
    for (const auto& entry : graph) {
        // Stores initial rank for each page in map
        pageRanks[entry.first] = in_rank;
    }
}

// Prints the PageRank of all pages after p powerIterations in ascending alphabetical order of webpages and rounding rank to two decimal places
string AdjacencyList::PageRank(int n){
    // Initialize pageRanking
    initializePR();
    map<string, double> newRanks;

    // Iterate through graph to update PageRank values based on current graph structure and ranks them from previous iteration
    for (int i = 0; i < n; i++) {
        // Iterate through each entry where entry first is the page and entry second is the vector of outgoing links
        for (const auto& entry : graph) {
            // Initialize each page rank to 0.0 for that iteration to start
            newRanks[entry.first] = 0.0;
        }
        // Iterate through each entry where entry first is the page and entry second is the vector of outgoing links
        for (const auto& entry : graph) {
            const string& page = entry.first;
            double rankShare;

            // Calculate the RankShare each outgoing link receives from page
            if (outDeg[page] > 0) {
                // Calculate rankShare by dividing # of outgoing links
                rankShare = pageRanks[page] / outDeg[page];
            }
            else {
                // For pages with no outgoing links, distribute rank equally among pages
                rankShare = pageRanks[page] / graph.size();
            }

            // Rank distribution for graph
            if (graph[page].empty()) {
                // Distribute rank to all pages if no outgoing links
                for (auto& rankEntry : newRanks) {
                    rankEntry.second += rankShare / graph.size();
                }
            }
            else {
                // Distribute rank to linked pages
                for (auto& linkedPage : graph[page]) {
                    newRanks[linkedPage] += rankShare;
                }
            }
        }
        // Update pageRanks to current rank values
        pageRanks = newRanks;
    }

    // Print result in alphabetical order, rounding to two decimals
    string result;
    // Convert pageRanks to a vector sortedPages with each page having a specific rank to then sort page names alphabetically
    vector<pair<string, double>> sortedPages(pageRanks.begin(), pageRanks.end());
    sort(sortedPages.begin(), sortedPages.end());

    // Print out each sorted entry as "page #.##/n"
    for (const auto& entry : sortedPages) {
        cout << entry.first << " " << fixed << setprecision(2) << entry.second << "\n";
        // Format each entry as "page #.##" and append to result
        result += entry.first + " " + to_string(entry.second).substr(0, to_string(entry.second).find('.') + 3) + "\n";
    }
    return result;
}
