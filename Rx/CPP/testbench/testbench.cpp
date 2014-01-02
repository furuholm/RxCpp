// // Copyright (c) Microsoft Open Technologies, Inc. All rights reserved. See License.txt in the project root for license information.

// // testbench.cpp : Defines the entry point for the console application.
// //

#include "cpprx/rx.hpp"

int main(int argc, char const *argv[])
{
    /* code */
    // rxcpp::Return(42, 0);

    rxcpp::just(43)
    	.select([](int value){return value + 1;})
    	.subscribe([](int value) {std::cout << "got value: " << value << std::endl;});
    return 0;
}
