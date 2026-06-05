#include "VERYLONG.h"
#include <iostream>

int main()
{
    using namespace chapter13::verylong;
    
    std::cout << "Test 1: simple addition (123 + 456)" << std::endl;
    verylong v1("123"); // Internally "123" if bug exists, should be "321"
    verylong v2("456"); // Internally "456"
    verylong vsum = v1 + v2;
    std::cout << "Sum (should be 579): ";
    vsum.putvl();
    std::cout << std::endl;

    std::cout << "Test 2: simple multiplication (10 * 10)" << std::endl;
    verylong v3("10");
    verylong v4("10");
    verylong vprod = v3 * v4;
    std::cout << "Prod (should be 100): ";
    vprod.putvl();
    std::cout << std::endl;

    std::cout << "Test 3: the user's case (997 * 8329)" << std::endl;
    verylong v5("997");
    verylong v6("8329");
    verylong vres = v5 * v6;
    std::cout << "Result (should be 8304013): ";
    vres.putvl();
    std::cout << std::endl;

    return 0;
}
