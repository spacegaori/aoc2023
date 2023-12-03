#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstddef>
#include <string>
#include <string_view>
#include <sstream>
#include <vector>

bool isPossible(int red, int green, int blue) {
    if (red > 12 || green > 13 || blue > 14) return false;
    return true;
}

int main() {
    std::ifstream inf{ "input.txt" };

    if (!inf) {
        std::cerr << "Input file cannot be opened for reading.\n";
        return 1;
    }

    while (inf) {
        std::string s;
        int game_index{ 1 };
        int sum{ 0 };

        while (std::getline(inf, s)) {
            std::istringstream iss(s);
            while (std::getline(iss, s, ':')) {
                bool valid{ true };
                int r{ 0 }; int g{ 0 }; int b{ 0 };
                while(std::getline(iss, s, ' ')) {
                    if (s.empty()) continue;

                    int value{};
                    if (std::ranges::all_of(s, [](char ch){ return std::isdigit(ch); }))
                        value = std::stoi(s);

                    std::getline(iss, s, ' ');
                    if (s == "red;" || s == "red") {
                        r += value;
                        if (!isPossible(r, g, b))
                            valid = false;
                        r = 0; g = 0; b = 0;
                    }
                    else if (s == "green;" || s == "green") {
                        g += value;
                        if (!isPossible(r, g, b))
                            valid = false;
                        r = 0; g = 0; b = 0;
                    }
                    else if (s == "blue;" || s == "blue") {
                        b += value;
                        if (!isPossible(r, g, b))
                            valid = false;
                        r = 0; g = 0; b = 0;
                    }
                    else if (s == "red,") r += value;
                    else if (s == "green,") g += value;
                    else if (s == "blue,") b += value;
                }
                if (valid) sum += game_index;
                valid = true;
            }
            ++game_index;
        }
        std::cout << sum << '\n';
    }

    return 0;
}