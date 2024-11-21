#pragma once


class abstractDraw
{
public:
   virtual void draw() = 0;

};

class birdDraw : public abstractDraw
{
public:
   virtual void draw() = 0;
};

class bulletDraw : public abstractDraw
{
public:
   virtual void draw() = 0;
};


/***********
BIRD DRAW
***********/
class standardDraw : public birdDraw
{
public:
   virtual void draw() = 0;
};

class sinkerDraw : public birdDraw
{
public:
   virtual void draw() = 0;
};

class floaterDraw : public birdDraw
{
public:
   virtual void draw() = 0;
}; 

class crazyDraw : public birdDraw
{
public:
   virtual void draw() = 0;
}; 

/***********
BULLET DRAW
***********/
class pelletDraw : public bulletDraw
{
public:
   virtual void draw() = 0;
};

class missileDraw : public bulletDraw
{
public:
   virtual void draw() = 0;
}; 

class bombDraw : public bulletDraw
{
public:
   virtual void draw() = 0;
}; 

class shrapnelDraw : public bulletDraw
{
public:
   virtual void draw() = 0;
};