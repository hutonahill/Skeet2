#include "Storage.h"

Storage::IteratorElement Storage::beginElement()
{
   return IteratorElement(*(Element.begin()));
}

Storage::IteratorElement Storage::endElement()
{
   return IteratorElement(*(Element.end()));
}

Storage::IteratorBird Storage::beginBird()
{
   return IteratorBird(*(Element.begin()));
}

Storage::IteratorBird Storage::endBird()
{
   return IteratorBird(*(Element.end()));
}

Storage::IteratorBullet Storage::beginBullet()
{
   return IteratorBullet(*(Element.begin()));
}

Storage::IteratorBullet Storage::endBullet()
{
   return IteratorBullet(*(Element.end()));
}

void Storage::add(ElementStorage* element)
{
   Element.push_back(element);
}

void Storage::remove(ElementStorage* it)
{
   Element.remove(it);
}

void Storage::reset()
{
   *this = Storage();
}

Storage::IteratorElement Storage::IteratorElement::operator++()
{
   it++;
   return *this;
}

ElementStorage* Storage::IteratorElement::operator*()
{
   return it;
}

Storage::IteratorBird::IteratorBird(ElementStorage* it)
{
   it++;

   while (!(it.isBird()) && it != nullptr)
   {
      it++;
   }
}

Storage::IteratorBird Storage::IteratorBird::operator++()
{
   it++;

   while (!(it.isBird()) && it != nullptr)
   {
      it++;
   }

   return *this;
}

ElementStorage* Storage::IteratorBird::operator*()
{
   return it;
}

Storage::IteratorBullet::IteratorBullet(ElementStorage* it)
{
   while (!(it.isBullet()) && it != nullptr)
   {
      it++;
   }
}

Storage::IteratorBullet Storage::IteratorBullet::operator++()
{
   it++;

   while (!(it.isBullet()) && it != nullptr)
   {
      it++;
   }

   return *this;
}

ElementStorage* Storage::IteratorBullet::operator*()
{
   return it;
}
