//
// Created by attilav on 3/10/19.
//

#ifndef CYK_CYKCLASS_H
#define CYK_CYKCLASS_H

#include <vector>
#include <string>

#include <map>
class CYKCLASS {
public:
    void test();
    CYKCLASS(){
        inputStream = "./default";
        wordToFind = "aabbaba";
        parseGrammar(inputStream);
        resultTable = createCYKTable();
        makeCYKTable(resultTable);


    }
    CYKCLASS(std::string  inputFileName, std::string  word){
        inputStream = inputFileName;
        wordToFind = word;
        parseGrammar(inputStream);

    }

private:
    std::string wordToFind;
    std::string inputStream;
    std::string startSymbol;
    std::vector<std::string> nonTerminals;
    std::vector<std::string> terminals;
    std::map<std::string,std::vector<std::string>> grammar;
    std::vector<std::vector<std::string>> resultTable;
    void parseGrammar(std::string & inputFileName);
    std::vector<std::vector<std::string>>   createCYKTable();
    void makeCYKTable( std::vector<std::vector<std::string>>  & table);
    std::vector<std::string> doProd(std::string a, std::string b);
};


#endif //CYK_CYKCLASS_H
