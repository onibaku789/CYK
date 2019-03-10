//
// Created by attilav on 3/10/19.
//
#include <sstream>
#include <iostream>
#include <fstream>
#include "CYKCLASS.h"

void CYKCLASS::parseGrammar(std::string inputFileName) {
    std::ifstream inputStream(inputFileName);
    std::string line,tempString,prod;
    getline(inputStream,line);
    startSymbole =line;
    getline(inputStream,line);
    std::istringstream iss (line);
    while(iss >> tempString){
        nonTerminals.push_back(tempString);
    }
    getline(inputStream,line);
    std::istringstream iss2 (line);
    while(iss2 >> tempString){
        terminals.push_back(tempString);
    }
    while(getline(inputStream,line)) {
        std::istringstream iss3(line);
        iss3 >> prod;
        while (iss3 >> tempString) {
            grammar[prod].push_back(tempString);
        }
    }
}
void CYKCLASS::test() {
    std::cout << "STARTSYMBOLE" <<std::endl << startSymbole<<std::endl;

    std::cout << "NONTERMINALS" << std::endl;
    for(auto i:nonTerminals){
        std::cout << i << " " ;
    }
    std::cout<< std::endl;
    std::cout << "TERMINALS" <<  std::endl;
    for(auto i:terminals){
        std::cout << i << " " ;
    }
    std::cout<< std::endl;
    std::cout << "GRAMMAR" <<  std::endl;
    for(auto map:grammar) {
        std::cout << map.first << " ";
        for (auto i:map.second) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

}

 std::vector<std::vector<std::string>>  CYKCLASS::createCYKTable (){
    long length =  wordToFind.length();
     std::vector<std::vector<std::string>> cykTable ;
     cykTable.clear();
     for(int i = 0; i < length + 1;i++){
         cykTable.push_back(std::vector<std::string>(wordToFind.length()));
     }

    return cykTable;
}

void CYKCLASS::makeCYKTable( std::vector<std::vector<std::string>> & table){

    for(int i = 0; i < table[wordToFind.length()].size(); i++ ){
        table[wordToFind.length()-1][i].push_back(wordToFind[i]);
       // std::cout << table[wordToFind.length()-1][i] << " "  << wordToFind[i] << std::endl;
    }

}
