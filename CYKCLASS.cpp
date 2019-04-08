//
// Created by attilav on 3/10/19.
//
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstring>
#include "CYKCLASS.h"

using Vec3 = std::vector<std::vector<std::vector<std::string>>>;

void CYKCLASS::parseGrammar(std::string &inputFileName) {

    std::ifstream inputStream(inputFileName);
    std::string line, tempString, prod;

    getline(inputStream, line);
    startSymbol = line;


    getline(inputStream, line);
    std::istringstream iss(line);

    while (iss >> tempString) {
        nonTerminals.emplace_back(tempString);
    }

    getline(inputStream, line);
    std::istringstream iss2(line);

    while (iss2 >> tempString) {
        terminals.emplace_back(tempString);
    }

    while (getline(inputStream, line)) {
        std::istringstream iss3(line);
        iss3 >> prod;
        while (iss3 >> tempString) {
            grammar[prod].emplace_back(tempString);
        }
    }
    inputStream.close();
}

void CYKCLASS::test() {
    std::cout << "STARTSYMBOL" << std::endl << startSymbol << std::endl;

    std::cout << "NONTERMINALS" << std::endl;
    for (const auto &i:nonTerminals) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "TERMINALS" << std::endl;
    for (const auto &i:terminals) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "GRAMMAR" << std::endl;
    for (const auto &map:grammar) {
        std::cout << map.first << " ";
        for (const auto &i:map.second) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "RESULTTABLE" << std::endl;
    for (const auto &vec:resultTable) {
        for (const auto &i:vec) {
            for (const auto &ii:i) {
                std::cout << ii << ",";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

Vec3 CYKCLASS::createCYKTable() {
    long length = wordToFind.length();
    Vec3 cykTable;

    cykTable.clear();
    std::vector<std::string> kappa;
    std::string test = "-";
    kappa.push_back(test);


    cykTable.push_back(std::vector<std::vector<std::string>>());
    for (unsigned int ii = 0; ii < length; ii++) {
        cykTable[0].push_back(kappa);

    }


    for (unsigned int i = 1; i <= length; i++) {
        cykTable.push_back(std::vector<std::vector<std::string>>());
        for (unsigned int ii = 0; ii < length - i + 1; ii++) {
            cykTable[i].push_back(kappa);

        }

    }


    return cykTable;
}

Vec3 CYKCLASS::makeCYKTable(Vec3 &table) {

    for (int i = 0; i < wordToFind.length(); i++) {
        std::string tempString;
        tempString.push_back(wordToFind[i]);
        std::vector<std::string> tempVec;
        tempVec.push_back(tempString);
        table[0][i] = tempVec;
    }

    for (int i = 0; i < wordToFind.length(); i++) {
        std::string tempString;
        tempString.push_back(wordToFind[i]);

        table[1][i] = doProdVec(tempString);

    }
    if (wordToFind.size() == 1)
        return table;

    for (int i = 0; i < wordToFind.length(); i++) {
        std::vector<std::string> temp;
        if (i + 1 <= wordToFind.length())
            temp = doProdVec(table[1][i], table[1][i + 1]);
        if (!temp.empty())
            table[2][i] = temp;

    }

    if (wordToFind.size() == 2)
        return table;

    std::vector<std::string> temp;
    for (int i = 3; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            temp.clear();
            for (int compareFrom = 1; compareFrom < i; compareFrom++) {
                std::vector<std::string> temp2;
                temp2 = doProdVec(table[compareFrom][j], table[i - compareFrom][j + compareFrom]);
                temp.insert(temp.end(), temp2.begin(), temp2.end());


            }
            std::sort(temp.begin(), temp.end());
            temp.erase(std::unique(temp.begin(), temp.end()), temp.end());
            if (!temp.empty())
                table[i][j] = temp;

        }

    }
    return table;
}

std::vector<std::string>
CYKCLASS::doProdVec(const std::vector<std::string> &prodStringsA, const std::vector<std::string> &prodStringsB) {
    std::vector<std::string> resultVector;
    std::string tempString;


    for (const auto &j : prodStringsA) {
        for (const auto &ii : prodStringsB) {
            tempString = j + ii;

            for (const auto &map:grammar) {
                for (const auto &i:map.second) {
                    if (tempString == i) {

                        resultVector.push_back(map.first);
                    }
                }

            }
        }
    }


    return resultVector;
}


std::vector<std::string> CYKCLASS::doProdVec(const std::string &a) {
    std::vector<std::string> tempStrings;

    for (const auto &map:grammar) {
        for (const auto &i:map.second) {
            if (i == a)
                tempStrings.push_back(map.first);

        }

    }

    return tempStrings;

}

void CYKCLASS::doTheMath() {
    parseGrammar(inputStream);
    resultTable = createCYKTable();
    resultTable = makeCYKTable(resultTable);

}


const bool CYKCLASS::Contains(std::vector<std::string> &Vec, const std::string &Element) {
    return std::find(Vec.begin(), Vec.end(), Element) != Vec.end();
}

void CYKCLASS::viewCYKTable() {

    for (int i = static_cast<int>(resultTable.size() - 1); i >= 0; i--) {
        for (auto &j : resultTable[i]) {
            for (int k = 0; k < j.size(); ++k) {
                std::cout << j[k];
                if (j.size() > 1)
                    std::cout << ",";
            }

            std::cout << " ";
        }
        std::cout << std::endl;
    }
    if (isWord())
        std::cout << wordToFind << " szó levezethető a nyelvtanból" << std::endl;
    else
        std::cout << wordToFind << " szó nem vezethető le a nyelvtanból" << std::endl;
    std::cout << std::endl;

}

const bool CYKCLASS::isWord() {

    return Contains(resultTable[resultTable.size() - 1][0], startSymbol);

}
