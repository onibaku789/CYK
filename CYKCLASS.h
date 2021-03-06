//
// Created by attilav on 3/10/19.
//

#ifndef CYK_CYKCLASS_H
#define CYK_CYKCLASS_H

#include <utility>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using Vec3 = std::vector<std::vector<std::vector<std::string>>>;


class CYKCLASS {
public:
    void test();


    static CYKCLASS *getInstance();

    void setFileWord(std::string file, std::string word);

    void doTheMath();

private:

    static CYKCLASS *instance;

    CYKCLASS() = default;

    std::string wordToFind;
    std::string inputStream;
    std::string startSymbol;
    std::vector<std::string> nonTerminals;
    std::vector<std::string> terminals;
    std::map<std::string, std::vector<std::string>> grammar;
    std::vector<std::vector<std::vector<std::string>>> resultTable;


    void parseGrammar(std::string &inputFileName);

    std::vector<std::vector<std::vector<std::string>>> createCYKTable();

    Vec3 makeCYKTable(std::vector<std::vector<std::vector<std::string>>> &table);

    std::vector<std::string>
    doProdVec(const std::vector<std::string> &prodStringsA, const std::vector<std::string> &prodStringsB);


    std::vector<std::string> doProdVec(const std::string &a);

    void viewCYKTable();


    static const bool Contains(std::vector<std::string> &Vec, const std::string &Element);

    const bool isWord();
};


#endif //CYK_CYKCLASS_H
