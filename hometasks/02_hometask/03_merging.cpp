#include <algorithm>
#include <cstdint>
#include <iostream>
#include <utility>
#include <stack>
#include <vector>

using Number = std::int32_t;

int main() {
    unsigned count, length;
    std::cin >> count >> length;
    std::vector<std::stack<Number>> arrays;

    std::vector<std::pair<Number, size_t>> heap;

    for (unsigned index_i = 0; index_i < count; ++index_i) {
        std::stack<Number> queue;
        for (unsigned index_j = 0; index_j < length; ++index_j) {
            Number elem = 0;
            std::cin >> elem;
            queue.push(elem);
        }
        heap.push_back({queue.top(), index_i});
        queue.pop();
        arrays.push_back(queue);
    }

    std::vector<Number> results;
    size_t size = count * length;
    results.reserve(size);

    std::make_heap(heap.begin(), heap.end());

    for (unsigned index = 0; index < size; ++index) {
        auto max = heap.front();
        results.push_back(max.first);
        std::pop_heap(heap.begin(), heap.end());
        heap.pop_back();
        if (!arrays[max.second].empty()) {
            heap.push_back({arrays[max.second].top(), max.second});
            arrays[max.second].pop();
            std::push_heap(heap.begin(), heap.end());
        }
    }

    for (auto iter = results.crbegin(); iter != results.crend(); ++iter) {
        std::cout << *iter << ' ';
    }

    return 0;
}
