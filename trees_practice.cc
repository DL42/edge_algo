#include <vector>
#include <iostream>
#include <cstdint>
#include <tuple>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <limits>

using namespace std;

struct edge
{
    double left, right;
    int32_t parent, child;

    edge(double l, double r, int32_t p, int32_t c)
        : left{ l }, right{ r }, parent{ p }, child{ c }
    {
    }
};

int
main(int argc, char** argv)
{
    vector<edge> edges;

    edges.emplace_back(0, 1, 8, 7);
    edges.emplace_back(0, 1, 8, 5);
    edges.emplace_back(0, 1, 7, 6);
    edges.emplace_back(0, 1, 7, 2);
    edges.emplace_back(0, 1, 6, 0);
    edges.emplace_back(0, 1, 6, 1);
    edges.emplace_back(0, 1, 5, 3);
    edges.emplace_back(0, 1, 5, 4);

    // these are the nodes containing mutations:
    unordered_set<int32_t> mut_nodes({ 8, 7, 5, 3, 4 });
    int32_t most_ancient_mut_node = 8;
    vector<size_t> tips;
    queue<vector<edge>::const_iterator> eprocessor;

    // Where in edges each parent
    // appears as a child (on the marginal tree):
    vector<size_t> cindexes(edges.size(), numeric_limits<size_t>::max());
    // "Mutation counts", which means
    // tips descending from elements
    // in mut_nodes
    vector<unsigned> mcounts(edges.size(), 0);

    auto b
        = lower_bound(edges.cbegin(), edges.cend(), most_ancient_mut_node,
                      [](const edge& e, int32_t v) { return e.parent > v; });
    auto e = upper_bound(
        b, edges.cend(), most_ancient_mut_node,
        [](const int32_t v, const edge& e) { return v > e.parent; });
    unsigned X = 0;
    for (auto& e : edges)
        {
            cout << e.parent << ' ' << e.child << ' ' << X++;
            if (mut_nodes.find(e.child) != mut_nodes.end())
                {
                    cout << "*";
                }
            cout << '\n';
        }
    for (auto i = b; i < e; ++i)
        {
            eprocessor.push(i);
        };
    while (!eprocessor.empty())
        {
            auto i = eprocessor.front();
            b = lower_bound(
                i, edges.cend(), i->child,
                [](const edge& e, int32_t v) { return e.parent > v; });
            if (b == edges.end()) // i->child is a tip
                {
                    size_t d
                        = static_cast<size_t>(distance(edges.cbegin(), i));
                    tips.push_back(static_cast<size_t>(d));
                }
            else
                {
                    e = upper_bound(b, edges.cend(), i->child,
                                    [](const int32_t v, const edge& e) {
                                        return v > e.parent;
                                    });
                    for (; b < e; ++b)
                        {
                            size_t d = static_cast<size_t>(
                                distance(edges.cbegin(), b));
                            cindexes[d] = static_cast<size_t>(
                                distance(edges.cbegin(), i));
                            eprocessor.push(b);
                        }
                }
            eprocessor.pop();
        }

    unsigned nmuts_on_root = 0;
    for (auto& tip : tips)
        {
            auto i = tip;
            if (mut_nodes.find(edges[i].child) != mut_nodes.end())
            {
                ++mcounts[i];
            }
            while (cindexes[i] != numeric_limits<size_t>::max())
                {
                    cout << "m: " << i << ' ' << cindexes[i] << " | "
                        << edges[i].parent << ' ' << edges[i].child << ' '
                        << edges[cindexes[i]].parent << ' ' << edges[cindexes[i]].child << '\n';
                    if (mut_nodes.find(edges[i].parent) != mut_nodes.end()) 
                        {
                            ++mcounts[cindexes[i]];
                        }
                    i = cindexes[i];
                    if (cindexes[i] == numeric_limits<size_t>::max())
                        ++nmuts_on_root;
                }
        }
    cout << "No. muts on root node: " << nmuts_on_root << '\n';
    X = 0;
    for (auto& e : edges)
        {
            cout << e.parent << ' ' << e.child << ' ' << X;
            if (mut_nodes.find(e.child) != mut_nodes.end())
                {
                    cout << "*";
                }
            cout << '\t' << mcounts[X++] << '\n';
        }
}
