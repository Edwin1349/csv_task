#include "csvtable.h"

csvTable::csvTable(){}

csvTable::csvTable(std::vector<std::string> names, std::vector<std::vector<std::string>> rows){
    Transpose(rows);
    for(int i = 0; i < rows.size(); i++){
        this->table[names[i]] = rows[i];
    }

}

std::vector<std::string>& csvTable::GetColumn(std::string columnName){
    try{
        return this->table.at(columnName);
    }
    catch (...) {
        std::cerr << "wrong column name" << std::endl;
        exit(EXIT_FAILURE);
    }
}
std::map<std::string, std::vector<std::string>>& csvTable::getTable(){
    return this->table;
}

void csvTable::FormatDate(const char* columnName, const char* fromFormat, const char* toFormat){
    tm tm;
    for(auto& value:GetColumn(columnName)){
        time_t t;
        setlocale(LC_ALL,"/QSYS.LIB/EN_US.LOCALE");
        if(!strptime(value.c_str(), fromFormat,&tm)){
            std::cerr << "wrong date format" << std::endl;
            exit(EXIT_FAILURE);
        }
        std::stringstream dateStream;
        dateStream << std::put_time(&tm, toFormat);
        value = dateStream.str();
    }
}

void csvTable::PrintTable(){
    for(auto& column:this->table){
        std::cout << column.first << "\n";
        for(auto& value: column.second){
            std::cout << value << "\\";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void csvTable::AddSame(std::vector<std::string>& a, std::vector<std::string>& b){
    for(int i = 1; i < a.size(); i++){
        try{
            std::stoi(a[i]);
            a[i] = std::to_string(std::stoi(a[i]) + std::stoi(b[i]));
        }
        catch ( ... ){
            continue;
        }
    }
}

bool csvTable::SameGroup(std::vector<std::string>& a, std::vector<std::string>& b){
    bool isGroup = true;
    for(int i = 0; i < a.size(); i++){
        if(a[i] != b[i]){
            if(i > 0){
                try{
                    std::stoi(a[i]);
                }
                catch ( ... ){
                    isGroup = false;
                    continue;
                }
            }
            else{
                isGroup = false;
            }
        }
    }
    return isGroup;
}

std::map<std::string, std::vector<std::string>>& csvTable::Group(std::vector<std::string> columnsNames){
    std::vector<std::vector<std::string>> rows;
    for(auto& columnName: columnsNames){
        rows.push_back(GetColumn(columnName));
    }

    Transpose(rows);
    for(int i = 0; i < rows.size() - 1; i++){
        for(int j = i + 1; j < rows.size(); j++){
            if(SameGroup(rows[i], rows[j])){
                AddSame(rows[i], rows[j]);
                rows.erase(rows.begin() + j);
                j--;
            }
        }
    }

    this->table.clear();

    Transpose(rows);
    for(int i = 0; i < rows.size(); i++){
        this->table[columnsNames[rows.size() - i - 1]] = rows[rows.size() - i - 1];
    }

    return this->table;
}

void csvTable::Transpose(std::vector<std::vector<std::string>>& matrix){
    if (matrix.size() == 0){
        return;
    }

    std::vector<std::vector<std::string>> trans_vec(matrix[0].size(), std::vector<std::string>());

    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix[i].size(); j++){
            if (trans_vec[j].size() != matrix.size()){
                trans_vec[j].resize(matrix.size());
            }
            trans_vec[j][i] = matrix[i][j];
        }
    }
    matrix = trans_vec;
}





