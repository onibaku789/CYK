//
// Created by attilav on 3/10/19.
//
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstring>
#include "CYKCLASS.h"

void CYKCLASS::parseGrammar(std::string & inputFileName) {
    std::ifstream inputStream(inputFileName);
    std::string line,tempString,prod;

    getline(inputStream,line);
    startSymbol = line;

    getline(inputStream,line);
    std::istringstream iss (line);

    while(iss >> tempString){
        nonTerminals.emplace_back(tempString);
    }

    getline(inputStream,line);
    std::istringstream iss2 (line);

    while(iss2 >> tempString){
        terminals.emplace_back(tempString);
    }

    while(getline(inputStream,line)) {
        std::istringstream iss3(line);
        iss3 >> prod;
        while (iss3 >> tempString) {
            grammar[prod].emplace_back(tempString);
        }
    }
}
void CYKCLASS::test() {
    std::cout << "STARTSYMBOL" <<std::endl << startSymbol<<std::endl;

    std::cout << "NONTERMINALS" << std::endl;
    for(const auto & i:nonTerminals){
        std::cout << i << " " ;
    }
    std::cout<< std::endl;
    std::cout << "TERMINALS" <<  std::endl;
    for(const auto & i:terminals){
        std::cout << i << " " ;
    }
    std::cout<< std::endl;
    std::cout << "GRAMMAR" <<  std::endl;
    for(const auto & map:grammar) {
        std::cout << map.first << " ";
        for (const auto & i:map.second) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "RESULTTABLE" << std::endl;
    for(const auto & vec:resultTable){
        for(const auto & i:vec){
            for(const auto & ii:i){
            std::cout << ii<< ",";
            }
        std::cout << " ";
        }
        std::cout << std::endl;
    }
}

 std::vector<std::vector<std::vector<std::string>>>  CYKCLASS::createCYKTable (){
    long length =  wordToFind.length();
     std::vector<std::vector<std::vector<std::string>>> cykTable ;
     cykTable.clear();




     for(unsigned long i = 0; i < length+1 ;i++){
         cykTable.push_back(std::vector<std::vector<std::string>>(length));
         for(unsigned long ii = 0; ii < length-i+1; ii++){
                cykTable[i].push_back(std::vector<std::string>(grammar.size()));
             cykTable[i].resize(wordToFind.length()-i+1);
             cykTable[i][ii].resize(grammar.size());
         }


     }





    return cykTable;
}

void CYKCLASS::makeCYKTable( std::vector<std::vector<std::vector<std::string>>> & table){

for(int i = 0; i <wordToFind.length(); i++ ) {
    char tomb[2];
    wordToFind.copy(tomb, 1, i);
    std::string tempString(tomb);
    std::cout << tempString << std::endl;
    std::vector<std::string> temp(grammar.size());
    temp = doProdVec(tempString);
    table[0][i] =  temp;
}
    table[0].resize(wordToFind.length());

for(int i = 0 ; i<wordToFind.length();i++){
    if(i+1 <= wordToFind.length())
    table[1][i] = doProdVec(table[0][i],table[0][i+1]);

}
table[1].resize(wordToFind.length()-1);



   for(int i = 2; i < wordToFind.length()-1; i++){
        for (int j = 0; j < wordToFind.length()-i  ; j++) {
            for(int compareFrom = 0; compareFrom < i; compareFrom++) {
               //std::cout << "downwards" << table[compareFrom][j] << std::endl;
               //std::cout << table[i-compareFrom][j+compareFrom]<<std::endl;
              // std::cout << "downwards: " << downwards << " diagonal: " << diagonals;
                   // std::cout << "prodstirng" << table[compareFrom][j]+table[i-compareFrom][j+compareFrom] << std::endl;

                   table[i][j] = doProdVec(table[compareFrom][j],table[i-compareFrom-1][j+compareFrom]);

            }


        }

    }
}
std::vector<std::string> CYKCLASS::doProdVec(std::vector<std::string> prodStringsA, std::vector<std::string>prodStringsB){
    std::vector<std::string> resultVector(grammar.size());
    std::string tempString;
    bool found = false;

    for (int j = 0; j < prodStringsA.size() ; ++j) {
        for(int ii = 0 ; ii < prodStringsB.size(); ++ii){
            tempString = prodStringsA[j]+prodStringsB[ii];

            for (auto map:grammar) {
                for (const auto &i:map.second) {
                   if (tempString == i) {
                       found = true;
                        std::cout << tempString << std::endl;
                       resultVector.push_back(map.first);
                   }
                }

            }
        }
    }
    std::cout << "kosz" << std::endl;

        if(!found)
            resultVector.push_back("-");


    return  resultVector;
}



std::string CYKCLASS::doProd(std::string a){


    for( auto  map:grammar){
        for( const auto & i:map.second){
            if(a == i){
                return map.first;
            }
        }
    }

    return  "-";

}

std::vector<std::string> CYKCLASS::doProdVec(std::vector<std::string> & a){
    std::vector<std::string> tempStrings;

    for( auto  map:grammar){
        for( const auto & i:map.second){
            for(auto vec:a){
                if(vec == i)
                tempStrings.push_back(map.first);
            }
        }
    }

    return  tempStrings;

}
std::vector<std::string> CYKCLASS::doProdVec(std::string a){
    std::vector<std::string> tempStrings;

    for( auto  map:grammar){
        for( const auto & i:map.second){
                if(a == i)
                    tempStrings.push_back(map.first);
            }

    }

    return  tempStrings;

}
void  CYKCLASS::doTheMath() {
    parseGrammar(inputStream);
    resultTable = createCYKTable();
    makeCYKTable(resultTable);
}


