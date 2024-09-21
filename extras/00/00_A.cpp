#include <iostream>
#include <vector>
#include <string>

std::vector<int> PrefixFunction(const std::string& word) {
    size_t count_of_symbols = word.length();
    std::vector<int> prefixes(count_of_symbols);

    prefixes[0] = 0;
    for (size_t index = 1; index < count_of_symbols; ++index) {
        auto curr_symbol = word[index];
        size_t curr_prefix = prefixes[index - 1];

        while (curr_prefix > 0 && curr_symbol != word[curr_prefix]) {
            curr_prefix = prefixes[curr_prefix - 1];
        }

        if (curr_symbol == word[curr_prefix]) {
            ++curr_prefix;
        }

        prefixes[index] = curr_prefix;
    }

    return prefixes;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string word;
    std::cin >> word;

    std::vector<int> prefixes = PrefixFunction(word);

    for (auto prefix : prefixes) {
        std::cout << prefix << " ";
    }

    return 0;
}
