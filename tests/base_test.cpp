//
// Created by Florian Kamps on 11/07/2022.
//

#include <criterion/criterion.h>
#include "../inc/VirtualMachine.hpp"

Test(base_test, test_base) {
    cr_assert_eq(1, 1);
}