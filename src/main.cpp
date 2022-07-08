//
// Created by Florian Kamps on 07/07/2022.
//

#include "../inc/Parser.hpp"
#include "../inc/VirtualMachine.hpp"

int main(int ac, char **av) {
    Parser parser(av[1]);
    VirtualMachine vm;
    parser.parsefrmfile();
    vm.run(parser.getInstructions());
}