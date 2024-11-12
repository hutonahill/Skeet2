#pragma once

#include <set>

using namespace std;


class Input;

class ArrowListener
{
public:

   void subscribe(Input* in);  
   void unsubscribe(Input* in);

private:
   set<Input*> subscribers;
};
