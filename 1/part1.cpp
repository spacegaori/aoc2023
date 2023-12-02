#include <fstream>
#include <functional>
#include <iostream>
#include <string>

int main() {
    std::ifstream inf{ "input.txt" };

    if (!inf) {
        std::cerr << "Input file cannot be opened for reading.\n";

        return 1;
    }

    int sum { 0 };

    while (inf) {
        std::string strInput;
        inf >> strInput;

        if (strInput.empty())
            break;

        std::string strNum;
        strNum.push_back(*std::find_if(strInput.begin(), strInput.end(), [](char c){ return std::isdigit(c); }));
        strNum.push_back(*std::find_if(strInput.rbegin(), strInput.rend(), [](char c){ return std::isdigit(c); }));

        sum += std::stoi(strNum);
    }

    std::cout << sum << '\n';

    return 0;
}