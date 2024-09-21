#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <utility>

using Number = std::uint64_t;
using Player = std::pair<Number, Number>;  // index, feature

bool CompareFeature(const Player &lhs, const Player &rhs) {
    return lhs.second < rhs.second;
}

int main() {
    size_t length;
    std::cin >> length;

    std::vector<Player> players;
    players.resize(length);
    for (size_t idx = 0; idx < length; ++idx) {
        Number feature = 0;
        std::cin >> feature;
        players[idx] = std::make_pair(idx, feature);
    }
    if (length == 1) {
        std::cout << players.front().second << std::endl;
        std::cout << length << std::endl;
        return 0;
    }

    std::sort(players.begin(), players.end(), CompareFeature);

    Number maximal_effectivness = 0;
    Number sum = 0;
    Number worst = 0;
    Number best = 0;
    size_t begin = 0;
    size_t end = 1;

    for (size_t idx = 0; idx < length; ++idx) {
        best = players[worst + 1].second + players[worst].second;
        if (players[idx].second <= best) {
            sum += players[idx].second;
        } else {
            if (sum > maximal_effectivness) {
                maximal_effectivness = sum;
                begin = worst;
                end = idx;
            }
            sum -= players[worst].second;
            --idx;
            ++worst;
        }
    }

    if (sum > maximal_effectivness) {
        maximal_effectivness = sum;
        begin = worst;
        end = length;
    }

    std::vector<Player> team;
    team.reserve(end - begin + 1);
    for (size_t idx = begin; idx < end; ++idx) {
        team.push_back(players[idx]);
    }
    std::sort(team.begin(), team.end());

    std::cout << maximal_effectivness << std::endl;
    for (const auto &elem : team) {
        std::cout << elem.first + 1 << " ";
    }
    return 0;
}
