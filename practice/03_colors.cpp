#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <utility>

using Number = uint_fast64_t;
using Point = std::pair<Number, Number>;  // (x, y)

struct Rectangle {
    Point lower_left;
    Point upper_right;
    Number color;
    Number priority;
    bool is_delete = false;

    Number GetWidth() const {
        return upper_right.first - lower_left.first;
    }

    Number GetHeight() const {
        return upper_right.second - lower_left.second;
    }
};

enum Border { BEGIN, END };

struct PointInterval {
    Number coord;
    Border border;
    Number priority;
    Number color;
    bool is_garbage = false;
    PointInterval* pStart = nullptr;
};

void CalculateAreas(const std::vector<PointInterval*>& points, Number coef,
                    std::vector<Number>& areas) {
    Number count_points = points.size();
    std::vector<PointInterval*> heap;
    heap.reserve(count_points);
    Number prev_coord = points.front()->coord;
    heap.push_back(points.front());
    auto comp = [](const PointInterval* lhs, const PointInterval* rhs) {
        return lhs->priority < rhs->priority;
    };
    std::make_heap(heap.begin(), heap.end(), comp);

    for (size_t idx = 1; idx < count_points; ++idx) {
        auto current = points[idx];
        if (current->border == Border::BEGIN) {
            areas[heap.front()->color - 1] += coef * (current->coord - prev_coord);
            heap.push_back(current);
            std::push_heap(heap.begin(), heap.end(), comp);
            prev_coord = current->coord;
        } else if (current->border == Border::END) {
            current->pStart->is_garbage = true;
            areas[heap.front()->color - 1] += coef * (current->coord - prev_coord);
            prev_coord = current->coord;
            delete current;
        }
        while (!heap.empty() && heap.front()->is_garbage) {
            std::pop_heap(heap.begin(), heap.end(), comp);
            delete heap.back();
            heap.pop_back();
        }
    }
}

void AddWhiteSpace(std::vector<PointInterval*>& points, Number width) {
    PointInterval* start = new PointInterval();
    start->coord = 0;
    start->color = 1;
    start->priority = 0;
    start->border = Border::BEGIN;
    points.push_back(start);

    PointInterval* finish = new PointInterval();
    finish->coord = width;
    finish->color = 1;
    finish->priority = 0;
    finish->border = Border::END;
    finish->pStart = start;
    points.push_back(finish);
}

void AddInterval(std::vector<PointInterval*>& points, Rectangle rect) {
    PointInterval* start = new PointInterval();
    start->coord = rect.lower_left.first;
    start->color = rect.color;
    start->priority = rect.priority;
    start->border = Border::BEGIN;
    points.push_back(start);

    PointInterval* finish = new PointInterval();
    finish->coord = rect.lower_left.first + rect.GetWidth();
    finish->color = rect.color;
    finish->priority = rect.priority;
    finish->border = Border::END;
    finish->pStart = start;
    points.push_back(finish);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    Number width = 0;
    Number height = 0;
    Number count = 0;
    std::cin >> width >> height >> count;
    std::vector<Rectangle> rectangles;
    rectangles.reserve(count);
    Number max_color = 0;

    for (size_t idx = 0; idx < count; ++idx) {
        Number llx = 0, lly = 0, urx = 0, ury = 0, color = 0;
        std::cin >> llx >> lly >> urx >> ury >> color;
        Rectangle rectangle;
        rectangle.lower_left = std::make_pair(llx, lly);
        rectangle.upper_right = std::make_pair(urx, ury);
        rectangle.color = color;
        if (max_color <= rectangle.color) {
            max_color = rectangle.color;
        }
        rectangle.priority = idx + 1;
        rectangles.push_back(rectangle);
    }

    Number count_y = 2 * count;
    std::vector<Number> y_coord;
    y_coord.reserve(count_y);
    for (size_t idx = 0; idx < count; ++idx) {
        Number left_y = rectangles[idx].lower_left.second;
        y_coord.push_back(left_y);
        y_coord.push_back(left_y + rectangles[idx].GetHeight());
    }
    std::sort(y_coord.begin(), y_coord.end());

    std::vector<Number> areas(max_color, 0);
    areas.front() += y_coord.front() * width;
    for (size_t idx = 1; idx < count_y; ++idx) {
        std::vector<PointInterval*> points;
        AddWhiteSpace(points, width);
        for (const auto& rect : rectangles) {
            if (rect.lower_left.second <= y_coord[idx - 1] &&
                rect.lower_left.second + rect.GetHeight() >= y_coord[idx]) {
                AddInterval(points, rect);
            }
        }
        Number coef = y_coord[idx] - y_coord[idx - 1];
        std::sort(points.begin(), points.end(),
                  [](const PointInterval* lhs, const PointInterval* rhs) {
                      return lhs->coord < rhs->coord;
                  });
        CalculateAreas(points, coef, areas);
    }
    areas.front() += (height - y_coord.back()) * width;
    Number num = 1;
    for (const auto& area : areas) {
        if (area > 0) {
            std::cout << num << ' ' << area << std::endl;
        }
        ++num;
    }

    return 0;
}
