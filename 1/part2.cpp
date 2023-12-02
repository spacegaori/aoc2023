#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>

int main() {
    constexpr std::array<std::string_view, 9> strDigits{ "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

    std::ifstream inf{ "input.txt" };

    if (!inf) {
        std::cerr << "Input file cannot be opened for reading.\n";

        return 1;
    }

    int sum{ 0 };

    while (inf) {
        std::string strInput;
        inf >> strInput;

        if (strInput.empty())
            break;

        auto iterL{ std::find_if(strInput.begin(), strInput.end(), [](char c){ return std::isdigit(c); }) };
        int digIndexL{ static_cast<int>(std::distance(strInput.begin(), iterL)) };

        const int lastIndex{ static_cast<int>(strInput.length() - 1) };
        auto iterR{ std::find_if(strInput.rbegin(), strInput.rend(), [](char c){ return std::isdigit(c); }) };
        int digIndexR{ static_cast<int>(lastIndex - std::distance(strInput.rbegin(), iterR)) };
        
        int minIndexL{ -1 };
        int minL{ -1 };

        int maxIndexR{ -1 };
        int maxR{ -1 };

        for (std::string::size_type i{ 0 }; i < 9; ++i) {
            auto strIndexL{ (strInput.find(strDigits[i])) };

            if (std::string::npos != strIndexL) {
                if (minIndexL == -1) {
                    minIndexL = strIndexL;
                    minL = i + 1;
                }
                else if (minIndexL > static_cast<int>(strIndexL)) {
                    minIndexL = strIndexL;
                    minL = i + 1;
                }
            }

            auto strIndexR{ strInput.rfind(strDigits[i]) };

            if (std::string::npos != strIndexR) {
                if (maxIndexR == -1) {
                    maxIndexR = strIndexR;
                    maxR = i + 1;
                }
                else if (maxIndexR < static_cast<int>(strIndexR)) {
                    maxIndexR = strIndexR;
                    maxR = i + 1;
                }
            }
        }

        int l{ -1 };
        if (minIndexL == -1) {
            l = *iterL - '0';
        }
        else{
            if (minIndexL < digIndexL) {
                l = minL;
            }
            else {
                l = *iterL - '0';
            }
        }

        int r{ -1 };
        if (maxIndexR == -1) {
            r = *iterR - '0';
        }
        else {
            if (maxIndexR > digIndexR) {
                r = maxR;
            }
            else {
                r = *iterR - '0';
            }
        }

        sum += (l * 10) + r;
    }
    std::cout << sum << '\n';

    return 0;
}