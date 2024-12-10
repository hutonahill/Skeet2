/***********************************************************************
 * Header File:
 *    Abstract Draw : Entities that can be drawn
 * Author:
 *    Taemour and Jessica
 * Summary:
 *    Stuff that moves across the screen to be drawn
 ************************************************************************/


#pragma once
#include "bullet.h"
#include "bird.h"


class DrawUI
{
public:

/************************************************************************
 * DRAW Disk
 * Draw a filled circule at [center] with size [radius]
 *************************************************************************/
   void drawDisk( Position& center, double radius,
      double red, double green, double blue);
   void drawStandard(double radius, Position& pt) ;
};