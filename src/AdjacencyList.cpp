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
    for (int i = 1; i < n; i++) {
        // Iterate through each entry where entry first is the page and entry second is the vector of outgoing links
        for (const auto& entry : graph) {
            // Initialize each page rank to 0.0 for that iteration to start
            newRanks[entry.first] = 0.0;
        }
        // Iterate through each entry where entry first is the page and entry second is the vector of outgoing links
        for (const auto& entry : graph) {
            const string& page = entry.first;
            double newRank = 0.0;

            // Find all pages that link to the current page
            for (const auto& linkPage : graph) {
                const string& linkPageName = linkPage.first;
                const vector<string>& outgoingLinks = linkPage.second;

                // Check if linkPage links to pageName
                if (find(outgoingLinks.begin(), outgoingLinks.end(), page) != outgoingLinks.end()) {
                    // Add the rank contribution from linkPage to pageName
                    newRank += pageRanks[linkPageName] / outgoingLinks.size();
                }
            }

            // Store the new rank for pageName
            newRanks[page] = newRank;
        }

        // Update pageRanks with the new ranks for the next iteration
        pageRanks = newRanks;
    }

    // Print result in alphabetical order, rounding to two decimals
    string result;
    // Convert pageRanks to a vector sortedPages with each page having a specific rank to then sort page names alphabetically
    vector<pair<string, double>> sortedPages(pageRanks.begin(), pageRanks.end());
    sort(sortedPages.begin(), sortedPages.end());

    // Print out each sorted entry as "page #.##/n"
    for (size_t i = 0; i < sortedPages.size(); i++) {
        const auto& entry = sortedPages[i];
        cout << entry.first << " " << fixed << setprecision(2) << entry.second << "\n";
        // Format each entry as "page #.##" and append to result
        result += entry.first + " " + to_string(entry.second).substr(0, to_string(entry.second).find('.') + 3);
        // Add a newline only if it's not the last entry
        if (i != sortedPages.size() - 1) {
            result += "\n";
        }
    }
    return result;
}
