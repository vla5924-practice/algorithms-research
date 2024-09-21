#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<size_t> PrefixFunction(const std::string& word) {
    size_t count_of_symbols = word.length();
    std::vector<size_t> prefixes(count_of_symbols);

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

size_t RepetitionsCount(const std::string& word) {
    size_t count_of_repetitions = 1;

    for (size_t start_index = 0; start_index < word.length(); ++start_index) {
        std::vector<size_t> prefixes = PrefixFunction(word.substr(start_index));

        for (size_t length = 2; length <= prefixes.size(); ++length) {
            std::string substring = word.substr(start_index, length);

            // Suppose the 'substring' is a K-repetition (each repetition contains N symbols).
            // Set: L is substring.length(); p[.] is prefix function
            // Two facts follow from this assumption:
            // * L must be equal K * N  ==>  K must be equal L // N,
            // * p[L - 1] must be equal (K - 1) * N,
            // So: L - p[L - 1] must be equal N  ==>  K is L // (L - p[L - 1])
            // But: if L % (L - p[L - 1]) != 0  ==>  the 'substring' is not a K-repetition

            size_t count_of_symbols = length - prefixes[length - 1];

            if (length % count_of_symbols == 0) {
                count_of_repetitions = std::max(count_of_repetitions, length / count_of_symbols);
            }
        }
    }

    return count_of_repetitions;
}

size_t RepetitionsCountFast(const std::string& word) {
    size_t count_of_repetitions = 1;

    for (size_t start_index = 0; start_index < word.length(); ++start_index) {
        std::string suffix_word = word.substr(start_index);
        std::vector<size_t> prefixes(suffix_word.length());
        prefixes[0] = 0;

        for (size_t index = 1; index < suffix_word.length(); ++index) {
            auto curr_symbol = suffix_word[index];
            size_t curr_prefix = prefixes[index - 1];

            while (curr_prefix > 0 && curr_symbol != suffix_word[curr_prefix]) {
                curr_prefix = prefixes[curr_prefix - 1];
            }

            if (curr_symbol == suffix_word[curr_prefix]) {
                ++curr_prefix;
            }

            prefixes[index] = curr_prefix;


            size_t length = index + 1;
            size_t count_of_symbols = length - curr_prefix;

            if (length % count_of_symbols == 0) {
                count_of_repetitions = std::max(count_of_repetitions, length / count_of_symbols);
            }
        }
    }

    return count_of_repetitions;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string word;
    std::cin >> word;

    size_t result = RepetitionsCountFast(word);
    std::cout << result;

    return 0;
}
