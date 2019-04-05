//
// Created by attilav on 3/10/19.
//

#ifndef CYK_CYKCLASS_H
#define CYK_CYKCLASS_H

#include <vector>
#include <string>
#include <map>
#include <algorithm>

class CYKCLASS {
public:
    void test();

    CYKCLASS() {
        inputStream = "./default";
        wordToFind = "aabbaba";
        doTheMath();


    }

    CYKCLASS(std::string inputFileName, std::string word) {
        inputStream = inputFileName;
        wordToFind = word;
        doTheMath();


    }

private:
    std::string wordToFind;
    std::string inputStream;
    std::string startSymbol;
    std::vector<std::string> nonTerminals;
    std::vector<std::string> terminals;
    std::map<std::string, std::vector<std::string>> grammar;
    std::vector<std::vector<std::vector<std::string>>> resultTable;

    void parseGrammar(std::string &inputFileName);

    std::vector<std::vector<std::vector<std::string>>> createCYKTable();

    void makeCYKTable(std::vector<std::vector<std::vector<std::string>>> &table);

    std::vector<std::string> doProdVec(std::vector<std::string> prodStringsA, std::vector<std::string> prodStringsB);

    std::string doProd(std::string a);

    std::vector<std::string> doProdVec(std::string a);

    std::vector<std::string> doProdVec(std::vector<std::string> &a);


    void doTheMath();

    using Vec3 = std::vector<std::vector<std::vector<std::string>>>;

    void viewCYKTable(Vec3);

    const bool Contains(std::vector<std::string> &Vec, const std::string &Element);
};


#endif //CYK_CYKCLASS_H
