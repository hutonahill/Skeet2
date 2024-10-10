/**********************
 * BIRD DECORATOR
 * Everything that can be shot
 **********************/

#include "bird.h"

class Bird;

class BirdDecorator
{
   
public:
    virtual void apply(Bird* self) = 0;

};

