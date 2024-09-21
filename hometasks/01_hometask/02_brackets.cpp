#include <iostream>
#include <stack>
#include <string>

int main() {
    std::string sequence;
    std::getline(std::cin, sequence);
    std::stack<std::string::value_type> brackets;
    size_t count = 0;
    for (auto bracket : sequence) {
        if (bracket == '(' || bracket == '[' || bracket == '{') {
            brackets.push(bracket);
        } else {
            if (brackets.empty()) {
                break;
            }
            auto last_bracket = brackets.top();
            if ((bracket == ')' && last_bracket != '(') ||
                (bracket == ']' && last_bracket != '[') ||
                (bracket == '}' && last_bracket != '{')) {
                break;
            } else {
                brackets.pop();
            }
        }
        ++count;
    }
    if (count == sequence.size() && brackets.empty()) {
        std::cout << "CORRECT";
    } else {
        std::cout << count;
    }
    return 0;
}
