#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<size_t> ZFunction(const std::string& word) {
    size_t count_of_symbols = word.length();
    std::vector<size_t> z_values(count_of_symbols);

    z_values[0] = count_of_symbols;
    for (size_t left = 0, right = 0, index = 1; index < count_of_symbols; ++index) {
        size_t curr_z = 0;

        if (index <= right) {
            curr_z = std::min(right - index + 1, z_values[index - left]);
        }

        while (index + curr_z < count_of_symbols && word[curr_z] == word[index + curr_z]) {
            curr_z++;
        }

        if (index + curr_z - 1 > right) {
            left = index;
            right = index + curr_z - 1;
        }

        z_values[index] = curr_z;
    }

    return z_values;
}

int MaxPeriod(const std::vector<size_t> &z_values) {
    size_t count = z_values.size();

    for (size_t index = 1; index < count; ++index) {
        size_t curr_z = z_values[index];

        if (index + curr_z == count && count % index == 0) {
            return count / index;
        }
    }

    return 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string word;
    std::cin >> word;

    std::vector<size_t> z_values = ZFunction(word);
    size_t result = MaxPeriod(z_values);

    std::cout << result;

    return 0;
}
