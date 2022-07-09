//
// Created by Florian Kamps on 07/07/2022.
//

#include "../inc/Parser.hpp"
#include "../inc/VirtualMachine.hpp"

int main(int ac, char **av) {
    Parser parser(av[1]);
    VirtualMachine vm;
    try {
        ac < 2 ? parser.parse() : parser.parsefrmfile();
    } catch (ParserException &e) {
        std::cerr << "ParserException: " << e.what() << std::endl;
    }
    try {
        vm.run(parser.getInstructions());
    } catch (VMException &e) {
        std::cerr << "VMException: " << e.what() << std::endl;
        exit(84);
    }
}