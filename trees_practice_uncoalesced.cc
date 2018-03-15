#include <vector>
#include <iostream>
#include <cstdint>
#include <tuple>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <limits>

#include "edge.hpp"
#include "count_mnodes.hpp"

using namespace std;

int
main(int argc, char** argv)
{
    vector<edge> edges;

    edges.emplace_back(0, 1, 8, 7);
    edges.emplace_back(0, 1, 7, 6);
    edges.emplace_back(0, 1, 7, 2);
    edges.emplace_back(0, 1, 6, 0);
    edges.emplace_back(0, 1, 6, 1);
    edges.emplace_back(0, 1, 5, 3);
    edges.emplace_back(0, 1, 5, 4);

    // these are the nodes containing mutations:
    unordered_set<int32_t> mut_nodes({ 7, 5, 3, 4 });

    auto res = count_mnodes(edges,mut_nodes);

    cout << "Muts on root node = " << res.first << '\n';

    unsigned X=0;
    for(auto & e : edges)
    {
        cout << e.parent << ' ' << e.child << ' ' << res.second[X++] << '\n';
    }
}

