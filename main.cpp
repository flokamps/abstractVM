//
// Created by Florian Kamps on 07/07/2022.
//

#include "inc/Parser.hpp"

int main(int ac, char **av) {
    Parser parser(av[1]);
    parser.parsefrmfile();
}