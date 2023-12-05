#include <cassert>
#include <cstddef>  // std::size_t
#include <cmath>    // std::floor
#include <fstream>  // file i/o
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

bool isSymbol(const std::vector<int>& v, std::size_t row, std::size_t col, std::size_t stride) {
    return (v[row + (col * stride)] == 2);
}

bool isAdjacent(const std::vector<int>& v, std::size_t start, std::size_t end, std::size_t stride, std::size_t cols) {
    assert(start <= end);

    std::size_t row_start = start % stride;
    std::size_t row_end = end % stride;
    std::size_t col = std::floor(start / stride);

    if (col == 0) {
        if (row_start == 0) {
            if (isSymbol(v, row_end + 1, 0, stride)) return true;
            for (std::size_t i{ row_start }; i < row_end + 2; ++i) {
                if (isSymbol(v, i, 1, stride))
                    return true;
            }
        }
        else if (row_end == stride - 1) {
            if (isSymbol(v, row_start - 1, col, stride)) return true;
            for (std::size_t i{ row_start - 1 }; i < row_end + 1; ++i) {
                if (isSymbol(v, i, col + 1, stride))
                    return true;
            }
        }
        else {
            if (isSymbol(v, row_end + 1, col, stride)) return true;
            if (isSymbol(v, row_start - 1, col, stride)) return true;
            for (std::size_t i{ row_start - 1 }; i < row_end + 2; ++i) {
                if (isSymbol(v, i, col + 1, stride))
                    return true;
            }
        }
    }
    else if (col == cols - 1) {
        if (row_start == 0) {
            if (isSymbol(v, row_end + 1, col, stride)) return true;
            for (std::size_t i{ row_start }; i < row_end + 2; ++i) {
                if (isSymbol(v, i, col - 1, stride))
                    return true;
            }
        }
        else if (row_end == stride - 1) {
            if (isSymbol(v, row_start - 1, col, stride)) return true;
            for (std::size_t i{ row_start - 1 }; i < row_end + 1; ++i) {
                if (isSymbol(v, i, col - 1, stride))
                    return true;
            }
        }
        else {
            if (isSymbol(v, row_end + 1, col, stride)) return true;
            if (isSymbol(v, row_start - 1, col, stride)) return true;
            for (std::size_t i{ row_start - 1 }; i < row_end + 2; ++i) {
                if (isSymbol(v, i, col - 1, stride))
                    return true;
            }
        }
    }
    else {
        if (row_start == 0) {
            if (isSymbol(v, row_end + 1, col, stride)) return true;
            for (std::size_t i{ row_start }; i < row_end + 2; ++i) {
                if (isSymbol(v, i, col - 1, stride))
                    return true;
            }
            for (std::size_t i{ row_start }; i < row_end + 2; ++i) {
                if (isSymbol(v, i, col + 1, stride))
                    return true;
            }
        }
        else if (row_end == stride - 1) {
            if (isSymbol(v, row_start - 1, col, stride)) return true;
            for (std::size_t i{ row_start - 1 }; i < row_end + 1; ++i) {
                if (isSymbol(v, i, col - 1, stride)) return true;
            }
            for (std::size_t i{ row_start - 1 }; i < row_end + 1; ++i) {
                if (isSymbol(v, i, col + 1, stride)) return true;
            }
        }
        else {
            if (isSymbol(v, row_end + 1, col, stride)) return true;
            if (isSymbol(v, row_start - 1, col, stride)) return true;
            for (std::size_t i{ row_start - 1 }; i < row_end + 2; ++i) {
                if (isSymbol(v, i, col - 1, stride)) return true;
            }
            for (std::size_t i{ row_start - 1 }; i < row_end + 2; ++i) {
                if (isSymbol(v, i, col + 1, stride)) return true;
            }
        }
    }

    return false;
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
        std::size_t cols{};

        while (std::getline(inf, s, '\n')) {
            stride = s.length();
            std::istringstream iss(s);
            std::copy(s.begin(), s.end(), std::back_inserter(charMap));
        }

        cols = charMap.size() / stride;

        std::vector<int> intMap{};
        for (char& c : charMap) {
            if (c == '.') intMap.emplace_back(0);
            else if (std::isdigit(c)) intMap.emplace_back(1);
            else intMap.emplace_back(2);
        }

        std::size_t size{ intMap.size() };
        for (std::size_t i{ 0 }; i < size; ++i) {
            std::size_t length{};
            while (intMap[i] == 1) {
                ++i; ++length;
            }

            std::size_t start{};
            std::size_t end{}; 
            if (length > 0) {
                start = i - length;
                end = i - 1;

                if (isAdjacent(intMap, start, end, stride, cols))
                    sum += std::stoi(std::string{ charMap.begin() + static_cast<long>(start), charMap.begin() + static_cast<long>(start + length) });

                length = 0;
            }
        }
    }
    
    std::cout << sum << '\n';
    
    return 0;
}