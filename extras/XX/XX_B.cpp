#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<size_t> Z2P(const std::vector<size_t>& z_values) {
    size_t count_of_symbols = z_values.size();
    std::vector<size_t> prefixes(count_of_symbols);

    for (size_t index = 1; index < count_of_symbols; ++index) {
        for (size_t z_value = z_values[index];
             (z_value > 0) && (!prefixes[index + z_value - 1]);
             --z_value) {
            prefixes[index + z_value - 1] = z_value;
        }
    }

    return prefixes;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t count_of_elements;
    std::cin >> count_of_elements;

    std::vector<size_t> z_values(count_of_elements);
    std::copy_n(
        std::istream_iterator<size_t>(std::cin),
        count_of_elements,
        z_values.data()
    );

    std::vector<size_t> prefixes = Z2P(z_values);
    for (auto prefix : prefixes) {
        std::cout << prefix << " ";
    }

    return 0;
}
