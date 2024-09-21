#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using Number = std::uint_fast64_t;
using Size = std::uint_fast64_t;

void FillVector(std::vector<std::vector<Number>>& out_vec, Size length) {
    for (auto& vec : out_vec) {
        vec.resize(length);
        for (auto& elem : vec) {
            std::cin >> elem;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    Size num_asc = 0u;
    Size num_desc = 0u;
    Size length = 0u;
    std::cin >> num_asc >> num_desc >> length;

    std::vector<std::vector<Number>> vectors_asc(num_asc);
    std::vector<std::vector<Number>> vectors_desc(num_desc);
    FillVector(vectors_asc, length);
    FillVector(vectors_desc, length);

    Size queries = 0u;
    std::cin >> queries;
    std::vector<Size> results;
    results.reserve(queries);
    for (Size query = 0u; query < queries; ++query) {
        Size index_asc = 0;
        Size index_desc = 0;
        std::cin >> index_asc >> index_desc;
        --index_asc;
        --index_desc;
        const auto& asc = vectors_asc[index_asc];
        const auto& desc = vectors_desc[index_desc];
        Size asc_size = asc.size();
        if (asc_size == 1u) {
            results.push_back(1u);
            continue;
        }
        if (asc_size == 2u) {
            if (std::max(asc.front(), desc.front()) >= std::max(asc.back(), desc.back())) {
                results.push_back(2u);
                continue;
            }
            results.push_back(1u);
            continue;
        }

        Size left = 0u;
        Size right = asc_size - 1u;
        Size middle = (left + right) / 2u;
        Size result = middle;

        Number min_max = std::max(asc[middle], desc[middle]);
        Number best_min_max = min_max;

        while (left <= right) {
            middle = (left + right) / 2;
            if (asc[middle] < desc[middle]) {
                left = middle + 1u;
                min_max = desc[middle];
            } else {
                if (middle == 0u) {
                    result = middle;
                    break;
                }
                right = middle - 1u;
                min_max = asc[middle];
            }
            if (min_max <= best_min_max) {
                best_min_max = min_max;
                result = middle;
            }
        }

        results.push_back(result + 1u);
    }

    for (const auto& element : results) {
        std::cout << element << '\n';
    }

    return 0;
}
