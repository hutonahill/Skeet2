#pragma once
#include "uiInteract.h"
#include "bullet.h"

class BulletMaker
{
public:
   virtual bool makeBullet(Bullet*& bullet, const UserInput& ui, int time, double angle) = 0;
};

class PelletMaker : public BulletMaker
{
public:
   bool makeBullet(Bullet*& bullet, const UserInput& ui, int time, double angle);
};

class MissleMaker : public BulletMaker
{
public:
   bool makeBullet(Bullet*& bullet, const UserInput& ui, int time, double angle);
};

class BombMaker : public BulletMaker
{
public:
   bool makeBullet(Bullet*& bullet, const UserInput& ui, int time, double angle);
};