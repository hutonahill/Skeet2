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

void ArrowListener::send(int up, int down, int left, int right)
{
   for (auto it = subscribers.begin(); it != subscribers.end(); it++)
   {
      (*it)->up = up;
      (*it)->down = down;
      (*it)->left = left;
      (*it)->right = right;
   }
}
