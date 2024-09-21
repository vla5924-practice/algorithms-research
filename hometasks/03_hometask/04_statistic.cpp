#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdint>
#include <vector>
#include <string>
#include <cstring>

using Number = std::uint32_t;

int main() {
    std::ios_base::sync_with_stdio(false);
    Number num_count = 0;
    Number act_count = 0;
    Number nth = 0;
    std::cin >> num_count >> act_count >> nth;
    --nth;
    std::vector<Number> numbers(num_count);
    std::vector<Number> reserved(num_count);
    auto res_begin = reserved.begin();
    Number *res_ptr = reserved.data();
    auto res_needle = std::next(res_begin, nth);
    // Number *needle_ptr = res_ptr + nth;
    for (auto &el : numbers) {
        std::cin >> el;
    }
    std::string actions(act_count, ' ');
    std::cin >> actions;
    auto l_iter = numbers.begin();
    Number *l_ptr = numbers.data();
    auto r_iter = std::next(l_iter);
    Number *r_ptr = l_ptr + 1;
    Number range = 1;
    for (Number act = 0; act < act_count; ++act) {
        if (actions[act] == 'R') {
            ++r_iter;
            ++r_ptr;
            ++range;
        } else {
            ++l_iter;
            ++l_ptr;
            --range;
        }
        if (range <= nth) {
            std::cout << -1 << std::endl;
            continue;
        }
        std::memcpy(res_ptr, l_ptr, range * sizeof(Number));
        // std::copy(l_iter, r_iter, res_begin);
        std::nth_element(res_begin, res_needle, std::next(res_begin, range));
        std::cout << *res_needle << std::endl;
    }

    return 0;
}
