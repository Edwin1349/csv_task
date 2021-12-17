#ifndef CSVTABLE_H
#define CSVTABLE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <iostream>

class csvTable{
public:
    csvTable();

    csvTable(std::vector<std::string> names, std::vector<std::vector<std::string>> rows);

    std::vector<std::string>& GetColumn(std::string columnName);

    std::map<std::string, std::vector<std::string>>& getTable();

    void FormatDate(const char* columnName, const char* fromFormat, const char* toFormat);

    void PrintTable();

    std::map<std::string, std::vector<std::string>>& Group(std::vector<std::string> columnsNames);//groupBy first element

    static void Transpose(std::vector<std::vector<std::string>> &matrix);//transposes rows into columns
private:
    void AddSame(std::vector<std::string>& a, std::vector<std::string>& b);//sum nums in group

    bool SameGroup(std::vector<std::string>& a, std::vector<std::string>& b);//check if same group

    std::map<std::string, std::vector<std::string>> table {};
};


#endif
