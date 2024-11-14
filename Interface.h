#pragma once

#include "ArrowListener.h"
#include "SkeetLogic.h"
#include "storage.h"
#include "uiInteract.h"


class Interface 
{
public:

   Interface() 
   {
      al = new ArrowListener();
      sl = nullptr;
   };

   void setSkeetLogic(SkeetLogic* sl) { this->sl = sl; }
   ArrowListener* getArrowListener() const { return al; }

   SkeetLogic*    getSkeetLogic() const { return sl; }

   void advance() const { sl->Advance(); }

   void drawLevel() const;

   void drawStatus() const;

   bool isPlaying() const;

   void interact(const UserInput& ui);

   void drawGun() const;

   void drawBackground2(double redBack, double greenBack, double blueBack) const;

   void drawTimer(double percent,
                  double redFore, double greenFore, double blueFore,
                  double redBack, double greenBack, double blueBack) const;

private:
   int getLevel() const { return sl->getTime()->level(); }
   Time* getTime() const { return sl->getTime(); }
   ArrowListener* al;
   SkeetLogic* sl;
};

