#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstddef>
#include <string>
#include <string_view>
#include <sstream>
#include <vector>

int main() {
    std::ifstream inf{ "input.txt" };

    if (!inf) {
        std::cerr << "Input file cannot be opened for reading.\n";
        return 1;
    }

    while (inf) {
        std::string s;
        int sum{ 0 };

        while (std::getline(inf, s)) {
            std::istringstream iss(s);
            while (std::getline(iss, s, ':')) {
                int r{ 0 }; int g{ 0 }; int b{ 0 };
                while(std::getline(iss, s, ' ')) {
                    if (s.empty()) {
                        continue;
                    }

                    int value{};
                    if (std::ranges::all_of(s, [](char ch){ return std::isdigit(ch); })) {
                        value = std::stoi(s);
                    }

                    std::getline(iss, s, ' ');
                    if (s == "red," || s == "red;" || s == "red") {
                        r = std::max(value, r);
                    }
                    else if (s == "green," || s == "green;" || s == "green") {
                        g = std::max(value, g);
                    }
                    else if (s == "blue," || s == "blue;" || s == "blue") {
                        b = std::max(value, b);
                    }
                }
                sum += r*g*b;
            }
        }

        std::cout << sum << '\n';
    }

    return 0;
}