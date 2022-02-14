#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdlib>

struct gridNode {
    int x;
    int y;
};

namespace  std {
    template <> struct hash<gridNode> {
        std::size_t operator()(const gridNode& id) const noexcept {
            // NOTE: better to use something like boost hash_combine
            return std::hash<int>()(id.x ^ (id.y << 16));
        }
    };

}