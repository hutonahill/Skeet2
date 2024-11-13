#include "ArrowListener.h"
#include "ElementLogic.h"

void ArrowListener::subscribe(Input* in)
{
   subscribers.insert(in);
}




void ArrowListener::unsubscribe(Input* in)
{
   if (subscribers.find(in) != subscribers.end())
   {
      subscribers.erase(in);
   }
}
