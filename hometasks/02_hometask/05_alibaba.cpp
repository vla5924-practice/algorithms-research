#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

constexpr size_t kMaxInt = std::numeric_limits<size_t>::max();

struct Coin {
    size_t time;
    size_t coord;
};

void InitWalkArray(std::vector<std::vector<size_t>> &arr) {
    for (size_t pos = 0; pos < arr.size(); ++pos) {
        arr[pos].assign(arr.size(), kMaxInt);
        arr[pos][pos] = 0;
    }
}

void FillPositionInWalkArray(std::vector<std::vector<size_t>> &left,
                             std::vector<std::vector<size_t>> &right, bool is_update_left,
                             bool is_cum_left, std::vector<Coin> &coins, size_t from, size_t to,
                             size_t time_coord, size_t distance_left, size_t distance_right,
                             size_t left_ptr, size_t right_ptr) {
    size_t dist = 0;
    if (coins[distance_left].coord > coins[distance_right].coord) {
        dist = coins[distance_left].coord - coins[distance_right].coord;
    } else {
        dist = coins[distance_right].coord - coins[distance_left].coord;
    }

    size_t cum_dist = 0;
    if (is_cum_left) {
        if (left[from][to] == kMaxInt) {
            return;
        }
        cum_dist = left[from][to] + dist;
    } else {
        if (right[from][to] == kMaxInt) {
            return;
        }
        cum_dist = right[from][to] + dist;
    }

    if (cum_dist <= coins[time_coord].time) {
        if (is_update_left) {
            left[left_ptr][right_ptr] = std::min(left[left_ptr][right_ptr], cum_dist);
        } else {
            right[left_ptr][right_ptr] = std::min(right[left_ptr][right_ptr], cum_dist);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);

    size_t number_of_coins = 0;
    std::cin >> number_of_coins;

    std::vector<Coin> coins(number_of_coins);
    for (size_t pos = 0; pos < number_of_coins; ++pos) {
        std::cin >> coins[pos].coord >> coins[pos].time;
    }

    std::sort(coins.begin(), coins.end(),
              [](const Coin &first_coin, const Coin &second_coin) -> bool {
                  return first_coin.coord < second_coin.coord;
              });
    std::vector<std::vector<size_t>> left(number_of_coins);
    std::vector<std::vector<size_t>> right(number_of_coins);

    InitWalkArray(left);
    InitWalkArray(right);

    for (size_t seg_len = 1; seg_len < number_of_coins; ++seg_len) {
        for (size_t seg_beg = 0; seg_beg + seg_len < number_of_coins; ++seg_beg) {
            FillPositionInWalkArray(left, right, true, true, coins, seg_beg + 1, seg_beg + seg_len,
                                    seg_beg, seg_beg, seg_beg + 1, seg_beg, seg_beg + seg_len);
            FillPositionInWalkArray(left, right, true, false, coins, seg_beg + 1, seg_beg + seg_len,
                                    seg_beg, seg_beg, seg_beg + seg_len, seg_beg,
                                    seg_beg + seg_len);
            FillPositionInWalkArray(right, right, false, false, coins, seg_beg,
                                    seg_beg + seg_len - 1, seg_beg + seg_len, seg_beg + seg_len - 1,
                                    seg_beg + seg_len, seg_beg, seg_beg + seg_len);
            FillPositionInWalkArray(left, right, false, true, coins, seg_beg, seg_beg + seg_len - 1,
                                    seg_beg + seg_len, seg_beg, seg_beg + seg_len, seg_beg,
                                    seg_beg + seg_len);
        }
    }

    if (std::min(left[0][left.size() - 1], right[0][right.size() - 1]) != kMaxInt) {
        std::cout << std::min(left[0][left.size() - 1], right[0][right.size() - 1]) << std::endl;
    } else {
        std::cout << "No solution" << std::endl;
    }

    return 0;
}
