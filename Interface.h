#pragma once

#include "ArrowListener.h"
#include "SkeetLogic.h"
#include "storage.h"
#include "gun.h"
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
   ArrowListener* getArrowListener() { return al; }

   SkeetLogic*    getSkeetLogic()    { return sl; }

   void advance() { sl->Advance(); }

   void drawLevel() const;

   void drawStatus() const;

   bool isPlaying() const { return getTime().isPlaying(); }

   void interact(const UserInput& ui);

   void drawGun() const;

   void drawStatus() const;

   void drawBackground(double redBack, double greenBack, double blueBack) const;

   void drawTimer(double percent,
                  double redFore, double greenFore, double blueFore,
                  double redBack, double greenBack, double blueBack) const;

private:
   int getLevel() const { return sl->getTime().level(); }
   Time getTime() const { return sl->getTime(); }
   ArrowListener* al;
   SkeetLogic* sl;
};

