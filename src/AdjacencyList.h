#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;

class AdjacencyList {
    private:
    // Adjacency list to store links between pages
    map<string, vector<string>> graph;
    // PageRank values for each page
    map<string, double> pageRanks;
    // Store out degree for each page
    map<string, double> outDeg;

    public:
    // Adds directed edge from 'from' to 'to' and updates outDeg for rank distribution
    void addEdge(const string& from, const string& to);
    // Initialize PageRank values
    void initializePR();
    // Update ranks over n iterations, formats result alphabetically with rank number to two decimal places
    string PageRank(int n);
};
