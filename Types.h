#pragma once
#include<boost/multiprecision/cpp_int.hpp>
#include<memory>

#define MON_NUM 2
class Formula;
class Frame;
struct Pol;
using integer = boost::multiprecision::cpp_int;
using rational = boost::multiprecision::cpp_rational;
struct Unks;
struct Mon;
struct Node;
struct Pol;
using pUnks = std::shared_ptr<Unks>;
using pMon = std::shared_ptr<Mon>;
using pNode = std::shared_ptr<Node>;
using pPol = std::shared_ptr<Pol>;
enum OPERATOR { NONE = 0, ADD = 1, SUB, MUL, DIV, POW, SIN, COS, TAN, ASIN, ACOS, ATAN };