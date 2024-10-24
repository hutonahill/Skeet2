#pragma once
#include "visitor.h"

class FlyingObject
{
public:
   virtual void accept(Visitor& v) = 0;
};
