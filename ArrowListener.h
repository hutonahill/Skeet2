#pragma once

#include <set>

using namespace std;


class Input;

class ArrowListener
{
public:

   ArrowListener* subscribe(Input& in);  
   void unsubscribe(Input& in);

private:
   set<Input*> subscribers;
};
