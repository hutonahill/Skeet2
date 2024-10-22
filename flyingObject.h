#pragma once
#include "visitor.h"

class FlyingObject
{
   virtual void accept(Visitor& v) = 0;
};
