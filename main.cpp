
#include "CYKCLASS.h"
#include <iostream>

int main(int argc, char *argv[]) {

    if (argc > 1) {
        if (argc < 2)
            std::cout << "Usage: ./a.out <grammarfile> <word>" << std::endl;
        std::string file, word;
        file = argv[1];
        word = argv[2];
        CYKCLASS CYK2(file, word);
        CYK2.viewCYKTable();


    }


    CYKCLASS CYK3("/home/attilav/Programozas/Fordito/CYK/pet_rules", "fxey((P(x)iQ(y))dR(z))");

    CYK3.viewCYKTable();

    CYKCLASS CYK4("/home/attilav/Programozas/Fordito/CYK/default", "aabbaaaaaaaba");

    CYK4.viewCYKTable();

    CYKCLASS asd;
    asd.viewCYKTable();

    return 0;
}
