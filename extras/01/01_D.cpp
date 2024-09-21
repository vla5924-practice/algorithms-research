#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

std::vector<size_t> CreateSuffixArray(const std::string& input_word) {
    const size_t alphabet = 256;
    std::string word = input_word + '\0';
    size_t count_of_symbols = word.size();

    std::vector<size_t> classes(count_of_symbols);
    std::vector<size_t> permutation(count_of_symbols);
    std::vector<size_t> counts(std::max(count_of_symbols, alphabet));

    for (auto& symbol : word) {
        ++counts[symbol];
    }

    for (size_t index = 1; index < alphabet; ++index) {
        counts[index] += counts[index - 1];
    }

    for (size_t index = 0; index < count_of_symbols; ++index) {
        auto curr_symbol = word[index];
        permutation[--counts[curr_symbol]] = index;
    }

    classes[permutation[0]] = 0;
    size_t max_class = 1;
    for (size_t index = 1; index < count_of_symbols; ++index) {
        auto curr_p_val = permutation[index];
        auto prev_p_val = permutation[index - 1];

        if (word[curr_p_val] != word[prev_p_val]) {
            ++max_class;
        }

        classes[curr_p_val] = max_class - 1;
    }


    std::vector<size_t> classes_tmp(count_of_symbols);
    std::vector<size_t> permutation_tmp(count_of_symbols);

    for (size_t power_of_two = 1; power_of_two < count_of_symbols; power_of_two *= 2) {
        for (size_t index = 0; index < count_of_symbols; ++index) {
            if (permutation[index] >= power_of_two) {
                permutation_tmp[index] = permutation[index] - power_of_two;
            } else {
                permutation_tmp[index] = count_of_symbols + permutation[index] - power_of_two;
            }
        }

        std::fill(counts.begin(), counts.begin() + max_class, 0);

        for (auto& p_val : permutation_tmp) {
            ++counts[classes[p_val]];
        }

        for (size_t index = 1; index < max_class; ++index) {
            counts[index] += counts[index - 1];
        }

        for (size_t index = count_of_symbols; index > 0; --index) {
            auto p_val = permutation_tmp[index - 1];
            auto curr_symbol = classes[p_val];
            permutation[--counts[curr_symbol]] = p_val;
        }

        classes_tmp[permutation[0]] = 0;
        max_class = 1;
        for (size_t index = 1; index < count_of_symbols; ++index) {
            size_t curr_p_val = permutation[index];
            size_t prev_p_val = permutation[index - 1];

            size_t curr_middle_p_val = (curr_p_val + power_of_two) % count_of_symbols;
            size_t prev_middle_p_val = (prev_p_val + power_of_two) % count_of_symbols;

            std::pair<size_t, size_t> curr_symbols_pair = {
                classes[curr_p_val],
                classes[curr_middle_p_val]
            };

            std::pair<size_t, size_t> prev_symbols_pair = {
                classes[prev_p_val],
                classes[prev_middle_p_val]
            };

            if (curr_symbols_pair != prev_symbols_pair) {
                ++max_class;
            }

            classes_tmp[curr_p_val] = max_class - 1;
        }

        std::copy(classes_tmp.begin(), classes_tmp.end(), classes.begin());
    }

    return std::vector<size_t>(permutation.begin() + 1, permutation.end());
}

std::vector<size_t> KasaiLCP(const std::string& input_word,
                             const std::vector<size_t>& suffix_array) {
    size_t count_of_elements = suffix_array.size();
    std::vector<size_t> lcp(count_of_elements);
    std::string word = input_word + '\0';

    std::vector<size_t> inverse_suffix_array(count_of_elements);
    for (size_t index = 0; index < count_of_elements; ++index) {
        inverse_suffix_array[suffix_array[index]] = index;
    }

    size_t length_of_lcp = 0;
    for (size_t curr_suffix = 0; curr_suffix < count_of_elements; ++curr_suffix) {
        size_t curr_suffix_idx = inverse_suffix_array[curr_suffix];

        if (curr_suffix_idx == count_of_elements - 1) {
            length_of_lcp = 0;
            continue;
        }

        size_t next_suffix = suffix_array[curr_suffix_idx + 1];

        while ((curr_suffix + length_of_lcp < count_of_elements) &&
               (next_suffix + length_of_lcp < count_of_elements) &&
               (word[curr_suffix + length_of_lcp] == word[next_suffix + length_of_lcp])) {
            ++length_of_lcp;
        }

        lcp[curr_suffix_idx] = length_of_lcp;

        if (length_of_lcp > 0) {
            --length_of_lcp;
        }
    }

    return lcp;
}

size_t GetCountOfDiffSubstrings(const std::string& input_word) {
    std::vector<size_t> suffix_array = CreateSuffixArray(input_word);
    std::vector<size_t> lcp = KasaiLCP(input_word, suffix_array);

    size_t count = suffix_array.size();

    size_t suffixes_sum = 0;
    for (auto& suffix : suffix_array) {
        suffixes_sum += suffix;
    }

    size_t lcp_sum = 0;
    for (auto& lcp_val : lcp) {
        lcp_sum += lcp_val;
    }

    return count * count - suffixes_sum - lcp_sum;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input_word;
    std::cin >> input_word;

    size_t result = GetCountOfDiffSubstrings(input_word);
    std::cout << result;

    return 0;
}
