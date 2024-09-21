#include <algorithm>
#include <cstdint>
#include <iostream>
#include <stack>
#include <vector>

using Number = std::int_fast64_t;
using Size = std::uint_fast64_t;

struct Pair {
    Number value;
    Number max;
};

class Stack {
public:
    Stack() = default;
    Stack(Stack&&) = default;
    Stack(const Stack&) = delete;
    ~Stack() = default;

    Stack& operator=(Stack&&) = default;
    Stack& operator=(const Stack&) = delete;

    bool Empty() const {
        return backend_.empty();
    }

    void Push(const Number& value) {
        if (Empty()) {
            backend_.push({value, value});
        } else {
            backend_.push({value, std::max(value, backend_.top().max)});
        }
    }

    void Pop() {
        backend_.pop();
    }

    Number Top() const {
        return backend_.top().value;
    }

    Number Max() const {
        if (Empty()) {
            return INT_FAST64_MIN;
        }
        return backend_.top().max;
    }

    Number Size() const {
        return backend_.size();
    }

private:
    std::stack<Pair> backend_;
};

class Queue {
public:
    Queue() = default;
    Queue(Queue&&) = default;
    Queue(const Queue&) = delete;
    ~Queue() = default;

    Queue& operator=(Queue&&) = default;
    Queue& operator=(const Queue&) = delete;

    void Push(const Number& value) {
        s1_.Push(value);
    }

    void Pop() {
        Shuffle();
        s2_.Pop();
    }

    Number Top() {
        Shuffle();
        return s2_.Top();
    }

    Number Max() const {
        return std::max(s1_.Max(), s2_.Max());
    }

    Number Size() const {
        return s1_.Size() + s2_.Size();
    }

private:
    void Shuffle() {
        if (s2_.Empty()) {
            while (!s1_.Empty()) {
                s2_.Push(s1_.Top());
                s1_.Pop();
            }
        }
    }

    Stack s1_;
    Stack s2_;
};

int main() {
    std::ios_base::sync_with_stdio(false);

    Size size_array = 0;
    std::cin >> size_array;
    std::vector<Number> array;
    array.reserve(size_array);
    Size index = 0;
    for (; index < size_array; ++index) {
        Number number = 0;
        std::cin >> number;
        array.push_back(number);
    }

    Queue queue;
    queue.Push(array.front());
    Size count_requests;
    std::cin >> count_requests;
    std::vector<Number> result;
    result.reserve(count_requests);
    index = 0;
    for (Size request = 0; request < count_requests; ++request) {
        char req = ' ';
        std::cin >> req;
        if (req == 'R') {
            queue.Push(array[++index]);
        } else if (req == 'L') {
            queue.Pop();
        }
        result.push_back(queue.Max());
    }

    for (const auto& element : result) {
        std::cout << element << ' ';
    }

    return 0;
}
