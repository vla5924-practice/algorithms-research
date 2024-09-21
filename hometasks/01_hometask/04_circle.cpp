#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

void Input(std::vector<std::vector<int>>& input, int amount) {
    for (int i = 0; i < amount; ++i) {
        int x_coord, y_coord;
        std::cin >> x_coord >> y_coord;

        input.push_back(std::vector<int>{x_coord, y_coord});
    }
}

struct point {
    double x_coord;
    std::string border;
};

bool SortPoint(const point& a_point, const point& b_point) {
    const double EPS = 1e-9;
    if (fabs(a_point.x_coord - b_point.x_coord) < EPS) {
        return a_point.border == "left";
    }
    return (a_point.x_coord < b_point.x_coord);
}

double Solve(const std::vector<std::vector<int>>& dots, const int k_required) {
    double left = 0;
    double right = 1500;

    while (left < right - 10e-8) {
        double radius = (left + right) / 2;
        std::vector<point> intervals;

        for (size_t index = 0; index < dots.size(); ++index) {
            const int x_coord = dots[index][0];
            const int y_coord = dots[index][1];

            const double bias = radius * radius - y_coord * y_coord;
            if (bias < 0) {
                continue;
            }
            const double x_left = x_coord - sqrt(bias);
            const double x_right = x_coord + sqrt(bias);

            intervals.push_back({x_left, "left"});
            intervals.push_back({x_right, "right"});
        }

        std::sort(intervals.begin(), intervals.end(), SortPoint);
        int max_inner_dots = 0;
        int inner_dots = 0;
        for (size_t index = 0; index < intervals.size(); ++index) {
            const std::string border = intervals[index].border;
            if (border == "left") {
                inner_dots++;

                if (inner_dots >= max_inner_dots) {
                    max_inner_dots = inner_dots;
                }
            } else if (border == "right") {
                inner_dots--;
            }
        }

        if (max_inner_dots < k_required) {
            left = radius;
        } else {
            right = radius;
        }
    }

    return (left + right) / 2;
}

int main() {

    int amount;
    int k_required;
    std::cin >> amount;
    std::cin >> k_required;

    std::vector<std::vector<int>> dots;

    Input(dots, amount);

    double result = Solve(dots, k_required);
    std::cout << std::fixed << std::setprecision(6) << result;

    return 0;
}
