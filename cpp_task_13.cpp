#include <iostream>
#include <fstream>
#include <sstream>

bool getMatrixFromFile(const std::string &filename, std::vector<std::vector<int>> &a) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Cannot open " << filename << std::endl;
        return false;
    }

    a.clear();
    std::string line;
    while (std::getline(file, line) and not line.empty()) {
        std::vector<int> row;
        std::stringstream ss(line);
        int val;
        while (ss >> val) {
            row.push_back(val);
        }
        a.push_back(row);
    }

    int size = 0;
    for (int i = 0; i < a.size(); i++) {

        if (i == 0) {
            size = a[i].size();

        } else {
            if (size != a[i].size()) {
                a.clear();
                std::cout << "Incorrectly specified matrix: " << filename << std::endl;
                return false;
            }
        }

    }

    file.close();
    return true;
}

void multiMatrix(const std::vector<std::vector<int>> &a, const std::vector<std::vector<int>> &b,
                 std::vector<std::vector<int>> &matrix) {
    for (int i = 0; i < a.size(); ++i) {
        matrix.push_back({0});
        for (int j = 0; j < b[0].size() - 1; ++j)
            matrix[i].push_back(0);
    }

    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b[0].size(); j++) {
            int s = 0;
            for (int k = 0; k < b.size(); k++)
                s += (a[i][k] * b[k][j]);
            matrix[i][j] = s;
        }
}

std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<int>> &matrix) {
    for (auto &x: matrix) {
        for (auto i: x)
            out << i << " ";
        out << "\n";
    }
    return out;
}

int main() {
    bool w1, w2;
    std::vector<std::vector<int>> mA;
    std::vector<std::vector<int>> mB;
    std::vector<std::vector<int>> mC;

    w1 = getMatrixFromFile("macierz1.txt", mA);
    w2 = getMatrixFromFile("macierz2.txt", mB);

    if (!w1 || !w2)
        return -1;

    if (mA[0].size() != mB.size()) {
        std::cout
                << "Incorrectly specified matrices:\nthe number of elements in a row \nof matrix A must be equal to the number\nof rows of matrix B\n\n";
        return -1;
    }

    multiMatrix(mA, mB, mC);


    std::cout << "A:\n" << mA << std::endl;
    std::cout << "B:\n" << mB << std::endl;
    std::cout << "AXB:\n" << mC << std::endl;

    std::ofstream outFile("wynik.txt");
    if (!outFile.is_open()) {
        std::cout << "Cannot open wynik.txt" << std::endl;
        return -1;
    }
    outFile << mC;
}



