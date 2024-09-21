#include <algorithm>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

using Number = std::uint32_t;

Number Gcd(Number num, Number denom) {
    Number rem;
    if (num < denom) {
        std::swap(num, denom);
    }
    while ((rem = num % denom)) {
        num = denom;
        denom = rem;
    }
    return denom;
}

struct Triangle {
    Number first, second, third;
    Triangle(Number afirst, Number asecond, Number athird)
        : first(afirst), second(asecond), third(athird) {
        if (first > second) {
            std::swap(first, second);
        }
        if (second > third) {
            std::swap(second, third);
        }
        if (first > second) {
            std::swap(first, second);
        }
        Number gcd = Gcd(first, Gcd(second, third));
        first /= gcd;
        second /= gcd;
        third /= gcd;
    }

    bool operator==(const Triangle &other) const {
        return (first == other.first) && (second == other.second) && (third == other.third);
    }

    bool operator<(const Triangle &other) const {
        if (first != other.first) {
            return first < other.first;
        }
        if (second != other.second) {
            return second < other.second;
        }
        return third < other.third;
    }
};

struct SmartDeque {
    std::vector<Triangle> first;
    std::vector<Triangle> second;
    SmartDeque(size_t max) {
        first.reserve(max);
        second.reserve(max);
    }
    size_t Size() const {
        return first.size() + second.size();
    }
    void Insert(const Triangle &triangle) {
        auto size = Size();
        if (size == 0) {
            second.push_back(triangle);
            return;
        }
        if (size == 1) {
            first.push_back(triangle);
        }
        
    }
};

int main() {
    Number count;
    std::cin >> count;
    std::vector<Triangle> triangles;
    triangles.reserve(count);
    Number classes = 0;
    for (Number idx = 0; idx < count; ++idx) {
        Number first, second, third;
        std::cin >> first >> second >> third;
        Triangle triangle(first, second, third);
        auto has = std::find(triangles.begin(), triangles.end(), triangle);
        if (has == triangles.end()) {
            triangles.push_back(triangle);
            ++classes;
        }
    }
    std::cout << classes;
    return 0;
}

/*
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_set>

using Number = std::uint32_t;

struct Triangle {
    Number first;
    Number second;
    Number third;
};

Number Gcd(Number num, Number denom) {
    Number rem;
    if (num < denom) {
        std::swap(num, denom);
    }
    while ((rem = num % denom)) {
        num = denom;
        denom = rem;
    }
    return denom;
}

struct Chisla {
    Number first_num;
    Number first_denom;
    Number second_num;
    Number second_denom;

    explicit Chisla(const Triangle &triangle)
        : first_num(triangle.first),
          first_denom(triangle.second),
          second_num(triangle.second),
          second_denom(triangle.third) {
        Number denom_one = Gcd(first_num, first_denom);
        Number denom_two = Gcd(second_num, second_denom);
        first_num /= denom_one;
        first_denom /= denom_one;
        second_num /= denom_two;
        second_denom /= denom_two;
    }

    bool operator==(const Chisla &other) const {
        return first_num == other.first_num && first_denom == other.first_denom &&
               second_num == other.second_num && second_denom == other.second_denom;
    }
};

void Sort(Triangle &triangle) {
    if (triangle.first > triangle.second) {
        std::swap(triangle.first, triangle.second);
    }
    if (triangle.second > triangle.third) {
        std::swap(triangle.second, triangle.third);
    }
    if (triangle.first > triangle.second) {
        std::swap(triangle.first, triangle.second);
    }
}

int main() {
    Number count;
    std::cin >> count;
    Triangle triangle;
    std::vector<Chisla> factors;
    factors.reserve(count);
    Number classes = 0;
    for (Number idx = 0; idx < count; ++idx) {
        std::cin >> triangle.first >> triangle.second >> triangle.third;
        Sort(triangle);
        Chisla needle(triangle);
        auto has = std::find(factors.begin(), factors.end(), needle);
        if (has == factors.end()) {
            factors.push_back(needle);
            ++classes;
        }
    }
    std::cout << classes;
    return 0;
}
*/
