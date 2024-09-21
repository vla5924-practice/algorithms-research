#include <cstdint>
#include <iostream>
#include <vector>

using Number = int_fast64_t;
using Size = uint_fast64_t;

enum TypeBranchTree { LEFT, RIGHT };

void ChangeIndexSum(std::vector<Number>& segment_tree, Size index, TypeBranchTree type) {
    if (type == TypeBranchTree::LEFT) {
        segment_tree.front() = index;
    } else if (type == TypeBranchTree::RIGHT) {
        segment_tree.back() = index;
    }
}

std::vector<Number> MergeVectorByOrder(const std::vector<Number>& vec, Size left_, Size pivot_,
                                       Size right_) {
    std::vector<Number> result;
    result.reserve(right_ - left_ + 1);
    Size left = left_;
    Size right = pivot_ + 1;
    while (left <= pivot_ && right <= right_) {
        if (vec[left] <= vec[right]) {
            result.push_back(vec[left]);
            ++left;
        } else {
            result.push_back(vec[right]);
            ++right;
        }
    }

    while (left <= pivot_) {
        result.push_back(vec[left]);
        ++left;
    }

    while (right <= right_) {
        result.push_back(vec[right]);
        ++right;
    }
    return result;
}

Size WrapperCountSumSegmentsLessK(const std::vector<Number>& vec, Number border, Size left,
                                  Size right, std::vector<Number>& segment_tree,
                                  TypeBranchTree type) {
    if (left == right) {
        segment_tree[left] = vec[left - 1];
        ChangeIndexSum(segment_tree, left, type);
        return 1 ? vec[left - 1] <= border : 0;
    }

    Size pivot = (right - left) / 2 + left;
    Size left_count =
        WrapperCountSumSegmentsLessK(vec, border, left, pivot, segment_tree, TypeBranchTree::LEFT);
    Size index_sum_left_part = segment_tree.front();
    Size right_count = WrapperCountSumSegmentsLessK(vec, border, pivot + 1, right, segment_tree,
                                                    TypeBranchTree::RIGHT);
    segment_tree.front() = index_sum_left_part;

    Size left_index = left;
    Size right_index = pivot + 1;
    Size middle_count = 0;
    Size index_sum_left = segment_tree.front();
    while (left_index <= pivot) {
        Number alpha = 0;
        if (left_index != index_sum_left) {
            alpha = segment_tree[index_sum_left] - segment_tree[left_index];
        } else {
            ++left_index;
            continue;
        }

        if (right_index - 1 != pivot && segment_tree[right_index - 1] + alpha <= border) {
            middle_count += right_index - pivot - 1;
        }

        while (right_index <= right && segment_tree[right_index] + alpha <= border) {
            ++right_index;
            ++middle_count;
        }

        ++left_index;
    }

    right_index = pivot + 1;
    while (right_index <= right &&
           segment_tree[right_index] + segment_tree[index_sum_left] <= border) {
        ++right_index;
        ++middle_count;
    }

    right_index = pivot + 1;
    while (right_index <= right) {
        segment_tree[right_index] += segment_tree[index_sum_left];
        ++right_index;
    }

    left_index = left;
    Number index_sum_right = segment_tree.back();
    Number sum_all_part = segment_tree[index_sum_right];

    std::vector<Number> sort = MergeVectorByOrder(segment_tree, left, pivot, right);
    for (Size index = left; index <= right; ++index) {
        if (sort[index - left] == sum_all_part) {
            ChangeIndexSum(segment_tree, index, type);
        }
        segment_tree[index] = sort[index - left];
    }

    return left_count + right_count + middle_count;
}

Size CountSumSegmentsLessK(const std::vector<Number>& vec, Number border) {
    std::vector<Number> segment_tree;
    Size vec_size = vec.size();
    segment_tree.resize(vec_size + 2);
    segment_tree.front() = 0;
    segment_tree.back() = 0;
    return WrapperCountSumSegmentsLessK(vec, border, 1, vec_size, segment_tree,
                                        TypeBranchTree::LEFT);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    Size count = 0;
    std::cin >> count;
    std::vector<Number> array;
    array.reserve(count);
    for (Size index = 0; index < count; ++index) {
        Number elem = 0;
        std::cin >> elem;
        array.push_back(elem);
    }
    Number left_border = 0, right_border = 0;
    std::cin >> left_border >> right_border;

    Size result_right = CountSumSegmentsLessK(array, right_border);
    Size result_left = CountSumSegmentsLessK(array, left_border - 1);

    Size result = result_right - result_left;

    std::cout << result;

    return 0;
}
