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

std::vector<std::vector<std::vector<std::string>>> CYKCLASS::createCYKTable() {
    long length = wordToFind.length();
    std::vector<std::vector<std::vector<std::string>>> cykTable;
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

void CYKCLASS::makeCYKTable(std::vector<std::vector<std::vector<std::string>>> &table) {

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


    for (int i = 0; i < wordToFind.length(); i++) {
        if (i + 1 <= wordToFind.length())
            table[2][i] = doProdVec(table[1][i], table[1][i + 1]);

    }


    std::vector<std::string> temp;
    for (int i = 3; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            temp.clear();
            for (int compareFrom = 1; compareFrom < i; compareFrom++) {
                std::vector<std::string> temp2;
                temp2 = doProdVec(table[compareFrom][j], table[i - compareFrom][j + compareFrom]);
                //NEM JÓ CSAK MŰKÖDIK EKSDE
                //TODO
                if (!Contains(temp2, "-"))
                    temp.insert(temp.end(), temp2.begin(), temp2.end());


            }

            table[i][j] = temp;
        }

    }

}

std::vector<std::string>
CYKCLASS::doProdVec(std::vector<std::string> prodStringsA, std::vector<std::string> prodStringsB) {
    std::vector<std::string> resultVector;
    std::string tempString;
    bool found = false;

    for (int j = 0; j < prodStringsA.size(); ++j) {
        for (int ii = 0; ii < prodStringsB.size(); ++ii) {
            tempString = prodStringsA[j] + prodStringsB[ii];

            for (auto map:grammar) {
                for (const auto &i:map.second) {
                    if (tempString == i) {
                        found = true;
                        //  std::cout << counter++ << ". TALÁLAT: " << tempString << " BEÍROM: " << map.first << std::endl;
                        resultVector.push_back(map.first);
                    }
                }

            }
        }
    }
    // std::cout << "kosz" << std::endl;

    if (!found)
        resultVector.push_back("-");


    return resultVector;
}


std::string CYKCLASS::doProd(std::string a) {


    for (auto map:grammar) {
        for (const auto &i:map.second) {
            if (i == a) {
                return map.first;
            }
        }
    }

    return "-";

}

std::vector<std::string> CYKCLASS::doProdVec(std::vector<std::string> &a) {
    std::vector<std::string> tempStrings;

    for (auto map:grammar) {
        for (const auto &i:map.second) {
            for (auto vec:a) {
                if (vec == i)
                    tempStrings.push_back(map.first);

            }
        }
    }

    return tempStrings;

}

std::vector<std::string> CYKCLASS::doProdVec(std::string a) {
    std::vector<std::string> tempStrings;

    for (auto map:grammar) {
        for (auto i:map.second) {
            if (i == a)
                tempStrings.push_back(map.first);

        }

    }

    return tempStrings;

}

void CYKCLASS::doTheMath() {
    parseGrammar(inputStream);
    resultTable = createCYKTable();
    makeCYKTable(resultTable);
}


const bool CYKCLASS::Contains(std::vector<std::string> &Vec, const std::string &Element) {
    if (std::find(Vec.begin(), Vec.end(), Element) != Vec.end())
        return true;

    return false;
}

void CYKCLASS::viewCYKTable(CYKCLASS::Vec3) {
    //TODO
}