#ifndef ECS_HPP
#define ECS_HPP

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::shared_ptr;

// components placeholders
class CTransform;
class CName;
class CShape;
class CBBox;

/* ---------------------------------- debug --------------------------------- */
static inline void debug(const string &msg) {
    #if defined (__DEBUG__)
    cerr << "[DEBUG]: " << msg << endl;
    #endif // __DEBUG__
}

#endif //  ECS_HPP