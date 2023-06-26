#pragma once
#include <string>
#include <memory>
#include "common/runtime/Database.hpp"


namespace algebra {

   class Operator{
   public:
      const std::string name;
      Operator(std::string name);
      virtual void print(std::ostream& s) const;
      Operator* parent;
      virtual ~Operator() = default;
   };

   class UnaryOperator: public Operator{
   public:
      std::unique_ptr<Operator> child;
      UnaryOperator(std::string n, std::unique_ptr<Operator>&& c);
      void print(std::ostream& s)const override;
   };

   class BinaryOperator: public Operator{
   public:
      std::unique_ptr<Operator> left;
      std::unique_ptr<Operator> right;
      BinaryOperator(std::string n, std::unique_ptr<Operator>&& l, std::unique_ptr<Operator>&& r);
      void print(std::ostream& s)const override;
   };

   class Scan : public Operator{
   public:
      runtime::Relation& rel;
      Scan(runtime::Relation& r);
   };
   class Map : public UnaryOperator{
   public:
      Map(std::unique_ptr<Operator> c);
   };
   struct Print : public UnaryOperator{
     // fully qualified attributes, e.g. "relname.attr"
     std::vector<std::string> attributes;
     Print(std::unique_ptr<Operator> c, std::vector<std::string>&& attributes);
   };
   class HashJoin : public BinaryOperator{
   public:
      HashJoin(std::unique_ptr<Operator>&& build, std::unique_ptr<Operator>&& probe);
      void print(std::ostream& s)const override;
   };

}
