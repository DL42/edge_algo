#include <utility>
#include <vector>
#include <cstdint>
#include <unordered_set>
#include <iostream>
#include <queue>
#include <algorithm>
#include "edge.hpp"
using namespace std;

pair<unsigned, vector<unsigned>>
count_mnodes(const vector<edge>& edges, unordered_set<int32_t> mut_nodes)
{
    unsigned nmuts_on_root = 0;
    vector<unsigned> mcounts(edges.size(), 0);
    while (!mut_nodes.empty())
        {
            std::cout << mut_nodes.size() << " mutation nodes left...\n";
            auto most_ancient_mut_node_itr
                = std::max_element(mut_nodes.begin(), mut_nodes.end());
            int32_t most_ancient_mut_node = *most_ancient_mut_node_itr;
            cout << "most ancient mut node is " << most_ancient_mut_node
                 << '\n';
            // these are the nodes containing mutations:
            vector<size_t> tips;
            queue<vector<edge>::const_iterator> eprocessor;

            // Where in edges each parent
            // appears as a child (on the marginal tree):
            vector<size_t> cindexes(edges.size(),
                                    numeric_limits<size_t>::max());
            // "Mutation counts", which means
            // tips descending from elements
            // in mut_nodes

            auto b = lower_bound(
                edges.cbegin(), edges.cend(), most_ancient_mut_node,
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
                            size_t d = static_cast<size_t>(
                                distance(edges.cbegin(), i));
                            tips.push_back(static_cast<size_t>(d));
                        }
                    else
                        {
                            e = upper_bound(
                                b, edges.cend(), i->child,
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

            unordered_set<int32_t> to_remove;
            for (auto& tip : tips)
                {
                    auto i = tip;
                    if (mut_nodes.find(edges[i].child) != mut_nodes.end())
                        {
                            to_remove.insert(edges[i].child);
                            ++mcounts[i];
                        }
                    while (cindexes[i] != numeric_limits<size_t>::max())
                        {
                            cout << "m: " << i << ' ' << cindexes[i] << " | "
                                 << edges[i].parent << ' ' << edges[i].child
                                 << ' ' << edges[cindexes[i]].parent << ' '
                                 << edges[cindexes[i]].child << '\n';
                            if (mut_nodes.find(edges[i].parent)
                                != mut_nodes.end())
                                {
                                    to_remove.insert(edges[i].parent);
                                    ++mcounts[cindexes[i]];
                                }
                            i = cindexes[i];
                            if (cindexes[i] == numeric_limits<size_t>::max())
                                ++nmuts_on_root;
                        }
                }
            for (auto& tr : to_remove)
                {
                    mut_nodes.erase(tr);
                }
            if (mut_nodes.find(most_ancient_mut_node) != mut_nodes.end())
                {
                    mut_nodes.erase(most_ancient_mut_node);
                }
            cout << "After this round:\n";
            X = 0;
            for (auto& e : edges)
                {
                    cout << e.parent << ' ' << e.child << ' ' << cindexes[X++]
                         << '\n';
                }
        }
    return std::make_pair(nmuts_on_root, std::move(mcounts));
}