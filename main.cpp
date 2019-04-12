
#include "CYKCLASS.h"
#include <iostream>

int main(int argc, char *argv[]) {
    CYKCLASS *CYK = CYKCLASS::getInstance();
    if (argc > 1) {
        if (argc < 2)
            std::cout << "Usage: ./a.out <grammarfile> <word>" << std::endl;
        else {
            std::string file, word;
            file = argv[1];
            word = argv[2];
            CYK->setFileWord(file, word);
            CYK->doTheMath();
        }

    }


    CYK->setFileWord("./pet_rules", "fxey((P(x)iQ(y))dR(z))");

    CYK->doTheMath();

    CYK->setFileWord("./default", "aabbaaaaaaaba");

    CYK->doTheMath();

    CYK->setFileWord("./default", "aabbaba");

    CYK->doTheMath();

    return 0;
}
