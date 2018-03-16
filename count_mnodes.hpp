#ifndef __COUNT_MNODES__
#define __COUNT_MNODES__

#include <utility>
#include <vector>
#include <cstdint>
#include <unordered_set>
#include <unordered_map>
#include "edge.hpp"

std::pair<std::unordered_map<std::int32_t, unsigned>, std::vector<unsigned>>
count_mnodes(const std::vector<edge>& edges,
             std::unordered_set<std::int32_t> mut_nodes);

#endif
