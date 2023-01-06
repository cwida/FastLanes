#pragma once
#include "vectorwise/Operators.hpp"

class Query {
 protected:
   vectorwise::SharedStateManager shared;

 public:
   /// To be called by every worker thread to set up thread local resources
   void setup();
   /// To be called by every worker thread in order to execute query
   void run();
};
