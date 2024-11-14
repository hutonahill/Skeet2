#pragma once

#include "Interface.h"
#include "SkeetLogic.h"

class InterfaceLogicFactory
{
public:
   static Interface* create(Interface* i, SkeetLogic* sl)
   {
      i->setSkeetLogic(sl);
      sl->setInterface(i);

      return i;
   }

};
