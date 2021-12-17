#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>

#include "csvtable.h"

csvTable ReadCSV(std::string filePath, char delimiter){
    auto start = std::chrono::high_resolution_clock::now();

    std::fstream csvFile;
    csvFile.open(filePath, std::ios::in);

    if (!csvFile.is_open()){
        std::cout << "no such file" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::vector<std::string>> rows;
    std::vector<std::string> names;
    std::string line, word;

    std::getline(csvFile,line);

    std::stringstream lineStream(line);
    while (std::getline(lineStream, word, delimiter)) {
        names.push_back(word);
    }

    while (getline(csvFile,line)){
        std::vector<std::string> row;

        if (line.empty()){
            std::cout << "empty line" << std::endl;
            continue;
        }

        std::stringstream lineStream(line);
        while (std::getline(lineStream, word, delimiter)) {
            row.push_back(word);
        }

        rows.push_back(row);
    }
    csvFile.close();

    csvTable table = csvTable(names, rows);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "reading: " << duration.count() << " microseconds" << std::endl;

    return table;
}

void WriteCSV(csvTable table, std::string filePath, char delimiter){
    auto start = std::chrono::high_resolution_clock::now();

    std::fstream csvFile;
    csvFile.open(filePath, std::ios::out);

    if (!csvFile.is_open()){
        std::cout << "no such file" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::vector<std::string>> rows;
    std::vector<std::string> names;
    for(auto& column:table.getTable()){
        names.push_back(column.first);
        rows.push_back(column.second);
    }

    csvTable::Transpose(rows);
    for(auto& name:names){
        csvFile << name;
        if(&name != &names.back()){
            csvFile << delimiter;
        }
        else{
            csvFile << "\n";
        }
    }

    for(auto& row:rows){
        for(auto& word:row){
            csvFile << word;
            if(&word != &row.back()){
                csvFile << delimiter;
            }
            else{
                csvFile << "\n";
            }
        }
    }
    csvFile.close();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "writing: " << duration.count() << " microseconds" << std::endl;
}

int main(){
    csvTable table = ReadCSV("test.csv", ';');

    table.PrintTable();
    table.FormatDate("date", "%Y-%m-%d", "%B %G");

    table.Group({"Name", "date", "logged hours"});
    table.PrintTable();

    WriteCSV(table, "new.csv", ';');
    return 0;
}
