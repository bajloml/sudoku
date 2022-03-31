#include "inc/sudokuManager.h"

int main(int argc, char const *argv[])
{
    //read value from console
    int level = 1;
    if(argc < 2 ){
        level = 1;
    }
    else{
        level = atoi(argv[1]);
    }
    std::cout << "Difficulty level is: " << level << std::endl;

    SudokuManager sm(level);
    sm.printFields();

    int row = 0, column = 0, value = 0;

    while(!sm.checkIsFinished()){
        std::cout << "set field value in format 'row column value' " << std::endl;

        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        ss >> row >> column >> value;

        sm.setValue(row, column, value);
        sm.printFields();
    }

    std::cout << "Congratulations!!!" << std::endl;

    return 0;
}
