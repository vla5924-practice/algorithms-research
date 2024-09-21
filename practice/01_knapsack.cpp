#include <algorithm>
#include <cstdint>
#include <iostream>
#include <stack>
#include <vector>

using Number = std::uint_fast64_t;

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
            return Number();
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

struct TypeInfo {
    Number weight;
    Number cost;
    Number amount;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    Number num_types = 0;
    Number capacity = 0;
    std::cin >> num_types >> capacity;
    std::vector<TypeInfo> types(num_types);
    for (auto& type : types) {
        std::cin >> type.weight >> type.cost >> type.amount;
    }
    if (capacity == 0) {
        std::cout << 0;
        return 0;
    }
    std::vector<Number> prev(capacity + 1u);
    std::vector<Number> curr(capacity + 1u);
    for (Number cap = 0; cap <= capacity; ++cap) {
        const TypeInfo& type = types.front();
        prev[cap] = std::min(cap / type.weight, type.amount) * type.cost;
    }
    for (Number i_type = 1u; i_type < num_types; ++i_type) {
        const TypeInfo& type = types[i_type];
        Number window_size = type.amount + 1;
        for (Number weight = 0; weight < type.weight; ++weight) {
            Queue queue;
            Number num_step = capacity / type.weight + 1u;
            for (Number cap = weight; cap <= capacity; cap += type.weight) {
                if (queue.Size() >= window_size) {
                    queue.Pop();
                }
                Number delta = num_step * type.cost;
                queue.Push(prev[cap] + delta);
                curr[cap] = queue.Max() - delta;
                --num_step;
            }
        }
        prev.swap(curr);
    }
    std::cout << prev.back();
    return 0;
}
