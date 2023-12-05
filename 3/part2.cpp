#include <cassert>
#include <cstddef>  // std::size_t
#include <fstream>  // file i/o
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int calculateGearRatio(const std::vector<char>& v, std::size_t index, std::size_t stride) {
    std::string s{};
    int gearRatio{ 0 };

    std::size_t i{};
    if (std::isdigit(v[index - stride - 1])) {
        i = index - stride - 1;
        while(std::isdigit(v[i])) {
            --i;
        }
        ++i;
        while(std::isdigit(v[i])) {
            s += v[i];
            ++i;
        }
        gearRatio += std::stoi(s);
        s.clear();
        if (v[index - stride] == '.' && std::isdigit(v[index - stride + 1])) {
            i = index - stride + 1;
            while(std::isdigit(v[i])) {
                s += v[i];
                ++i;
            }

            gearRatio *= std::stoi(s);
            return gearRatio;
        }
    }
    else if (std::isdigit(v[index - stride])) {
        i = index - stride;
        while(std::isdigit(v[i])) {
            s += v[i];
            ++i;
        }
        gearRatio += std::stoi(s);
        s.clear();
    }
    else if (std::isdigit(v[index - stride + 1])) {
        i = index - stride + 1;
        while(std::isdigit(v[i])) {
            s += v[i];
            ++i;
        }
        gearRatio += std::stoi(s);
        s.clear();
    }


    if (std::isdigit(v[index - 1])) {
        i = index - 1;
        while (std::isdigit(v[i])) --i;
        ++i;
        while (std::isdigit(v[i])) {
            s += v[i];
            ++i;
        }

        if (gearRatio) {
            gearRatio *= std::stoi(s);
            return gearRatio;
        }
        else {
            gearRatio += std::stoi(s);
            s.clear();
        }
    }

    if (std::isdigit(v[index + 1])) {
        i = index + 1;
        while (std::isdigit(v[i])) {
            s += v[i];
            ++i;
        }

        if (gearRatio) {
            gearRatio *= std::stoi(s);
            return gearRatio;
        }
        else {
            gearRatio += std::stoi(s);
            s.clear();
        }
    }

    if (std::isdigit(v[index + stride - 1])) {
        i = index + stride - 1;
        while(std::isdigit(v[i])) {
            --i;
        }
        ++i;
        while(std::isdigit(v[i])) {
            s += v[i];
            ++i;
        }
        if (gearRatio) {
            gearRatio *= std::stoi(s);
            return gearRatio;
        }
        else {
            gearRatio += std::stoi(s);
            s.clear();
        }
        
        if (v[index + stride] == '.' && std::isdigit(v[index + stride + 1])) {
            i = index + stride + 1;
            while(std::isdigit(v[i])) {
                s += v[i];
                ++i;
            }

            gearRatio *= std::stoi(s);
            return gearRatio;
        }
    }
    else if (std::isdigit(v[index + stride])) {
        i = index + stride;
        while(std::isdigit(v[i])) {
            s += v[i];
            ++i;
        }
        if (gearRatio) {
            gearRatio *= std::stoi(s);
            return gearRatio;
        }
        else {
            gearRatio += std::stoi(s);
            s.clear();
        }
    }
    else if (std::isdigit(v[index + stride + 1])) {
        i = index + stride + 1;
        while(std::isdigit(v[i])) {
            s += v[i];
            ++i;
        }
        if (gearRatio) {
            gearRatio *= std::stoi(s);
            return gearRatio;
        }
        else {
            gearRatio += std::stoi(s);
            s.clear();
        }
    }

    return 0;
}

int main() {
    std::ifstream inf{ "input.txt" };

    if (!inf) {
        std::cerr << "Input file cannot be opened for reading.\n";
        return 1;
    }

    int sum{ 0 };

    while (inf) {
        std::vector<char> charMap{};
        std::string s{};
        std::size_t stride{};
        while (std::getline(inf, s, '\n')) {
            stride = s.length();
            std::istringstream iss(s);
            std::copy(s.begin(), s.end(), std::back_inserter(charMap));
        }

        std::size_t size{ charMap.size() };

        for (std::size_t i{ 0 }; i < size; ++i) {
            if (charMap[i] == '*') {
                sum += calculateGearRatio(charMap, i, stride);
            }
        }
    }

    std::clog << sum << '\n';        

    return 0;
}