#include "../inc/sudokuManager.h"


SudokuManager::SudokuManager(int _level):level(_level){
    //firstly fill diagonals
    fillDiagonal();

    //then fill the rest
    fillRest();

    //mask random fields
    maskFields();
};

void SudokuManager::printFields(){
    //first print letters
    std::cout<<" ";
    for(int i = 0; i < firstRow.size(); ++i){
        //add space if smallField is reached
            if(i%smallField == 0)
                std::cout<< " |";
        std::cout << firstRow.at(i) << "|";
    }

    //print rest of the table
    for(int i = 0; i< rows; ++i){
        //add empty row if smallField is reached
        if(i%smallField == 0)
            std::cout<<std::endl;

        std::cout << i;
        
        for(int j = 0; j < columns; ++j){
            //add space if smallField is reached
            if(j%smallField == 0)
                std::cout<< " |";

            std::cout << gameFields.at(i).at(j) << "|";
        };
        std::cout << std::endl;
    };
};

void SudokuManager::maskFields(){
    int mask = 0;

    switch(level){
        case 1:
            mask = 3;
            break;
        case 2:
            mask = 4;
            break;
        case 3:
            mask = 5;
            break;
    }

std::set<std::pair<int, int>> maskedFields;
gameFields = fieldValues;

    for(int i = 0; i < rows; i = i + smallField){
        for(int j = 0; j < columns; j = j + smallField){
            do{
                std::pair<int, int> maskedField;
                std::pair<int, int> distribution(0,2);
                maskedField.first = generateNumber(distribution);
                maskedField.second = generateNumber(distribution);

                maskedFields.insert(maskedField);
            }
            while(maskedFields.size() < mask);

            for(auto pair:maskedFields){
                int row = std::get<0>(pair);
                int col = std::get<1>(pair);
                gameFields.at(row+i).at(col+j) = 0;
            }
            maskedFields.clear();
        }
    }
};

//methods to check if number is used in row, column or small field
bool SudokuManager::usedInRow(int rowNum, int x){
    std::array<int, 9> rowValues = fieldValues.at(rowNum);

    auto it = std::find(rowValues.begin(), rowValues.end(), x);
    
    if(it != rowValues.end())
        return true;
    else
        return false;
};
//for column
bool SudokuManager::usedInCol(int columnNum, int x){
    std::array<int, 9> colValues;
    
    for(int i = 0; i < 9; ++i){
        colValues.at(i) = fieldValues.at(i).at(columnNum);
    };

    auto it = std::find(colValues.begin(), colValues.end(), x);
    
    if(it != colValues.end())
        return true;
    else
        return false;     
};
//for small field 3x3
bool SudokuManager::usedInSField(int row0, int column0, int x){
    std::vector<int> values;

    for(int i = 0; i < smallField; ++i){
        for(int j = 0; j < smallField; ++j){
            if(fieldValues.at(row0+i).at(column0+j) == x)
                return true;
        };
    };
        return false;
};

bool SudokuManager::numberIsUsed(int row, int column, int x){
    return usedInRow(row, x) || usedInCol(column, x) || usedInSField(row-row%smallField, column-column%smallField, x);
};

void SudokuManager::addNumberToSmallField(int row, int col){
    for(int i = 0; i < smallField; ++i){
        for(int j = 0; j < smallField; ++j){
            if(fieldValues.at(row+i).at(col+j) == 0)
            {
                int num = generateNumber();

                while(numberIsUsed(row+i, col+j, num)){
                    num = generateNumber();
                    //printFields();
                    };
                fieldValues.at(row+i).at(col+j) = num;
            }
            else
                continue;
        }
    }
};

//methods for filling table
void SudokuManager::fillDiagonal(){
    for(int i=0; i<9; i=i+smallField){
        addNumberToSmallField(i,i);
    }
};

bool SudokuManager::fillRest(){
    int row = 0;
    int col = 0;

    //check if there is 0 anywhere
    if(!findZeroValue(row, col)){
        return true;
    }

    for(int i = 0; i < rows; ++i){
        int num = generateNumber();
        
        if(!numberIsUsed(row, col, num)){
            fieldValues.at(row).at(col) = num;

            if(fillRest())
                return true;

            fieldValues.at(row).at(col) = 0;
        }
    }
    return false;
};

bool SudokuManager::findZeroValue(int &row, int &col){
    for(row = 0; row<rows; ++row){
        for(col = 0; col<columns; ++col)
        {
            if(fieldValues.at(row).at(col) == 0)
                return true;
        }
    }
    return false;
};

int SudokuManager::generateNumber(std::pair<int, int> distribution){
    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()
                ).count() );

    std::mt19937 gen(seed);
    std::uniform_int_distribution<unsigned> distrib(std::get<0>(distribution), std::get<1>(distribution));

    return distrib(gen);
};

bool SudokuManager::setValue(int row, int col, int value){
    if(fieldValues.at(row).at(col) == value){
        gameFields.at(row).at(col) = value;
        std::cout << "Sucess!" << std::endl;
        
        return true;
    }
    else{
        std::cout << "Try again!" << std::endl;
        return false;
    }
};

bool SudokuManager::checkIsFinished(){
    if(fieldValues == gameFields)
        return true;
    else 
        return false;
}