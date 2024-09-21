#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<size_t> P2Z(const std::vector<size_t>& prefixes) {
    size_t count_of_symbols = prefixes.size();
    std::vector<size_t> z_values(count_of_symbols);

    z_values[0] = count_of_symbols;
    for (size_t index = 1; index < count_of_symbols; ++index) {
        size_t prefix_curr = prefixes[index];
        if (prefix_curr != 0) {
            z_values[index - prefix_curr + 1] = prefix_curr;
        }
    }

    size_t first_z_value = z_values[1];
    if (first_z_value != 0) {
        for (size_t index = 1; index < first_z_value; ++index) {
            z_values[index + 1] = first_z_value - index;
        }
    }

    for (size_t index = first_z_value + 1; index < count_of_symbols - 1; ++index) {
        size_t z_value_curr = z_values[index];
        size_t z_value_next = z_values[index + 1];

        if ((z_value_curr != 0) && (z_value_next == 0)) {
            size_t length = 1;

            while ((length < z_value_curr) && (z_values[index + length] <= z_values[length])) {
                z_values[index + length] = std::min(z_values[length], z_value_curr - length);
                ++length;
            }

            index += --length;
        }
    }

    return z_values;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t count_of_elements;
    std::cin >> count_of_elements;

    std::vector<size_t> prefixes(count_of_elements);
    std::copy_n(
        std::istream_iterator<size_t>(std::cin),
        count_of_elements,
        prefixes.data()
    );

    std::vector<size_t> z_values = P2Z(prefixes);
    for (auto z_value : z_values) {
        std::cout << z_value << " ";
    }

    return 0;
}
