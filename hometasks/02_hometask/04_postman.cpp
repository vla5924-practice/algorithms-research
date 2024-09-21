#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using Number = std::uint32_t;

Number cur = 0;

Number NextRand24(Number first, Number second) {
    cur = cur * first + second;
    return cur >> 8;
}

Number NextRand32(Number first, Number second) {
    Number aa = NextRand24(first, second);
    Number bb = NextRand24(first, second);
    return (aa << 8) ^ bb;
}

Number UnsignedDiff(Number first, Number second) {
    if (first > second) {
        return first - second;
    }
    return second - first;
}

int main() {
    Number count = 0, first = 0, second = 0;
    std::cin >> count >> first >> second;
    std::vector<Number> houses;
    houses.reserve(count);

    for (auto index_i = 0u; index_i < count; ++index_i) {
        houses.push_back(NextRand32(first, second));
    }

    auto mid = houses.begin() + houses.size() / 2;
    std::nth_element(houses.begin(), mid, houses.end());
    Number optima = *(houses.begin() + houses.size() / 2);

    std::uint64_t result = 0;

    for (auto index_i = 0u; index_i < count; ++index_i) {
        result += UnsignedDiff(optima, houses[index_i]);
    }

    std::cout << result;

    return 0;
}
