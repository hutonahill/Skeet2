/***********************************************************************
 * Source File:
 *    Score
 * Author:
 *    Br. Helfrich
 * Summary:
 *    How well the player is doing
 ************************************************************************/

#include "score.h"
#include <sstream>
using namespace std;

/************************
 * SCORE GET TEXT
 * Get the status text
 ************************/
string Score::getText() const
{
    ostringstream sout;
    sout << "Score:  " << points;
    return sout.str();
}

/************************
 * HIT RATIO  GET TEXT
 * Get the status text
 ************************/
string HitRatio::getText() const
{
    ostringstream sout;
    sout << "Birds:   ";
    
    // compute the percentage when possible
    if (numMissed + numKilled)
        sout << (numKilled * 100 / (numMissed + numKilled)) << "%";
    else
        sout << "--";

    return sout.str();
}

/************************
 * HIT RATIO  ADJUST
 * Adjust the score for a bird hit (positive) or missed (negative)
 ************************/
void HitRatio::adjust(int value)
{
    if (value > 0)
        numKilled++;
    else if (value < 0)
        numMissed++;
}

/************************
 * NOTIFY
 * Calls all the colleagues
 ************************/
void Mediator :: notify(Message message)
{
   for (AbstractColleague* colleague: colleagues)
   {
      colleague->notify(message);
   }
}


/************************
 * ENROLL
 ************************/
void AbstractColleague:: enroll(Mediator* mediator) {
   this->mediator = mediator;
   mediator->enroll(this);
}
/************************
 * UNENROLL
 ************************/
void AbstractColleague:: unenroll(Mediator* mediator) {
   mediator->unenroll(this);
   this->mediator = nullptr;
}

/************************
* WENT OUT OF BOUNDS - BIRD
 ************************/
void BirdColleague::wentOutOfBounds()
{
   Message message;
   message.type = Message::BIRD_DIED;
   message.value = std::to_string(-pBird->getPoints());
   mediator->notify(message);
}

/************************
 * WAS SHOT - BIRD
 ************************/
void BirdColleague::wasShot()
{
   Message message;
   message.type = Message::BIRD_DIED;
   message.value = std::to_string(pBird->getPoints());
   mediator->notify(message);
}
/************************
 WENT OUT OF BOUNDS - BULLET
 ************************/
void BulletColleague::wentOutOfBounds()
{
   Message message;
   message.type = Message::OUTOFBOUNDS;
   message.value = std::to_string(-pBullet->getValue());
   mediator->notify(message);
}
/************************
 WAS FIRED - BULLET
 ************************/
void BulletColleague::wasFired()
{
   Message message;
   message.type = Message::BULLET_FIRED;
   message.value = std::to_string(pBullet->getValue());
   mediator->notify(message);
}
