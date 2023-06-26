#include "common/algebra/Operators.hpp"
#include <ostream>

using namespace std;

namespace algebra {
Operator::Operator(string n) : name(n) {}

UnaryOperator::UnaryOperator(string n, unique_ptr<Operator>&& c)
    : Operator(n), child(move(c)) {
   child->parent = this;
}
BinaryOperator::BinaryOperator(string n, unique_ptr<Operator>&& l,
                               unique_ptr<Operator>&& r)
    : Operator(n), left(move(l)), right(move(r)) {
   left->parent = this;
   right->parent = this;
}

Scan::Scan(runtime::Relation& r) : Operator("scan"), rel(r) {}
Map::Map(std::unique_ptr<Operator> c) : UnaryOperator("map", move(c)) {}
Print::Print(std::unique_ptr<Operator> c, std::vector<std::string>&& att)
    : UnaryOperator("print", move(c)), attributes(move(att)) {}
HashJoin::HashJoin(std::unique_ptr<Operator>&& build,
                   std::unique_ptr<Operator>&& probe)
    : BinaryOperator("hashjoin", move(build), move(probe)) {}

void Operator::print(ostream& s) const { s << name; }
void UnaryOperator::print(ostream& s) const {
   s << name << " <- ";
   child->print(s);
}
void BinaryOperator::print(ostream& s) const {
   s << " " << name << " lhs:(";
   left->print(s);
   s << ") rhs:(";
   right->print(s);
   s << ")";
}
void HashJoin::print(ostream& s) const {
   s << " " << name << " build:(";
   left->print(s);
   s << ") probe:(";
   right->print(s);
   s << ")";
}
}
