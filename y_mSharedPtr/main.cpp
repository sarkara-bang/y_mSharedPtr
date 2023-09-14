#include <iostream>
#include <string>
#include "y_Shared_Ptr.h"
#pragma once

using namespace std;

int main() {
    string s = "hello world!";
    CySharedPtr<string> p(&s);
    std::cout << *p << std::endl;
    return 0;
}
