#pragma once

#include <set>

using namespace std;


class Input;

class ArrowListener
{
public:

   void subscribe(Input* in);  
   void unsubscribe(Input* in);

   void send(int up, int down, int left, int right);

private:
   set<Input*> subscribers;
};
