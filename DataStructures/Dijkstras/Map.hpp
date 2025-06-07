#pragma once

#include <vector>
#include <string>
#include <iostream>

using namespace std;

template <typename X, typename Y>
class Map
{
public:
    X first;
    Y second;
    Map(X x, Y y) : first(x), second(y) {}
};