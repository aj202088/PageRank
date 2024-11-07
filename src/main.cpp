#include <iostream>
#include "AdjacencyList.h"
using namespace std;

int main() {
    int no_of_lines, power_iterations;
    string from, to;
    cin >> no_of_lines;
    cin >> power_iterations;
    // Create graph object
    AdjacencyList Created_Graph;

    for (int i = 0; i < no_of_lines; i++) {
        cin >> from;
        cin >> to;
        // Add new directed edge from 'from' to 'to'
        Created_Graph.addEdge(from, to);
    }

    // Compute PageRank and print out alphabetically
    Created_Graph.PageRank(power_iterations);
    return 0;
}
