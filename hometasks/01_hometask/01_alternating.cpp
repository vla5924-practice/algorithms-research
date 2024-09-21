#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

using Number = std::int32_t;

enum class Ordering { Up, Down, Equal };

Ordering CheckOrdering(Number curr, Number next) {
    if (curr > next) {
        return Ordering::Down;
    } else if (curr < next) {
        return Ordering::Up;
    }
    return Ordering::Equal;
}

int main() {
    unsigned count;
    std::cin >> count;
    if (count == 1u) {
        Number curr;
        std::cin >> curr;
        std::cout << curr;
        return 0;
    }

    Number curr = 0;
    Number next = 0;
    std::cin >> curr;

    std::vector<Number> sequence;
    sequence.reserve(count);
    sequence.push_back(curr);
    unsigned index = 1u;
    do {
        std::cin >> next;
        ++index;
    } while (curr == next && index < count);
    Ordering current_ordering = CheckOrdering(curr, next);
    std::queue<Number> first;
    if (curr != next) {
        first.push(next);
    }
    curr = next;
    Ordering last_ordering = current_ordering;
    std::queue<Number> second;
    while (index < count) {
        std::cin >> next;
        ++index;
        if (curr == next) {
            continue;
        }
        current_ordering = CheckOrdering(curr, next);
        if (current_ordering == last_ordering) {
            first.push(next);
        } else {
            second.push(next);
            curr = next;
            last_ordering = current_ordering;
            break;
        }
        curr = next;
    }

    while (index < count) {

        while (index < count) {
            std::cin >> next;
            ++index;
            if (curr == next) {
                if (index >= count && last_ordering == current_ordering) {
                    last_ordering = last_ordering == Ordering::Up ? Ordering::Down : Ordering::Up;
                }
                continue;
            }
            current_ordering = CheckOrdering(curr, next);
            if (current_ordering == last_ordering) {
                second.push(next);
            } else {
                last_ordering = current_ordering;
                break;
            }
            curr = next;
            if (index >= count && last_ordering == current_ordering) {
                last_ordering = last_ordering == Ordering::Up ? Ordering::Down : Ordering::Up;
            }
        }

        if (last_ordering == Ordering::Down) {
            while (!first.empty() &&
                   (first.front() >= second.back() || sequence.back() <= first.front())) {
                first.pop();
            }
        } else if (last_ordering == Ordering::Up) {
            while (!first.empty() &&
                   (first.front() <= second.back() || sequence.back() >= first.front())) {
                first.pop();
            }
        }

        if (!first.empty()) {
            sequence.push_back(first.front());
        }

        first = std::move(second);
        second = std::queue<Number>();
        second.push(next);
        if (index < count) {
            last_ordering = current_ordering;
        }
        curr = next;
    }

    if (index >= count && last_ordering == current_ordering) {
        last_ordering = last_ordering == Ordering::Up ? Ordering::Down : Ordering::Up;
    }

    if (!first.empty() && !second.empty() && first.back() == second.front()) {
        second.pop();
    }

    if (sequence.size() != 1 && second.empty()) {
        if (last_ordering == Ordering::Up) {
            while (!first.empty() && sequence.back() <= first.front()) {
                first.pop();
            }
        } else if (last_ordering == Ordering::Down) {
            while (!first.empty() && sequence.back() >= first.front()) {
                first.pop();
            }
        }
    } else if (!second.empty()) {
        if (last_ordering == Ordering::Down) {
            while (!first.empty() &&
                   (first.front() >= second.back() || sequence.back() <= first.front())) {
                first.pop();
            }
        } else if (last_ordering == Ordering::Up) {
            while (!first.empty() &&
                   (first.front() <= second.back() || sequence.back() >= first.front())) {
                first.pop();
            }
        }
    }

    if (!first.empty()) {
        sequence.push_back(first.front());
    }

    if (!second.empty()) {
        sequence.push_back(second.front());
    }

    for (auto& elem : sequence) {
        std::cout << elem << ' ';
    }
    return 0;
}
