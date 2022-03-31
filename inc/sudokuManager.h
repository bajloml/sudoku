#include <iostream>
#include <string>
#include <array>
#include <set>
#include <tuple>
#include <ctime>
#include <cstdlib>
#include <random>
#include <chrono>
#include <algorithm>
#include <sstream>

class SudokuManager{
    private:
        const int rows = 9; 
        const int columns = 9;
        const int smallField = 3;

        std::array<char, 9> firstRow = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
        std::array<std::array<int, 9>, 9> fieldValues = {0};
        std::array<std::array<int, 9>, 9> gameFields = {0};

        //game level
        int level;

    public:
        SudokuManager(int _level = 2);

        ~SudokuManager() = default;

        void printFields();
        void maskFields();

        //methods to check if number is used in row, column or small field
        bool usedInRow(int rowNum, int x);
        //for column
        bool usedInCol(int columnNum, int x);
        //for small field 3x3
        bool usedInSField(int row0, int column0, int x);

        //methods for filling table
        void fillDiagonal();
        bool fillRest();

        //helper functions
        bool numberIsUsed(int row, int column, int x);
        void addNumberToSmallField(int row, int col);
        bool findZeroValue(int &row, int &col);
        int generateNumber(std::pair<int, int> distribution = std::pair<int, int>(1,9));
        bool setValue(int row, int col, int value);
        bool checkIsFinished();
};