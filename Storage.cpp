#include "Storage.h"

Storage::Storage()
{
}

Storage::IteratorElement Storage::begin()
{
   return IteratorElement();
}

Storage::IteratorElement Storage::end()
{
   return IteratorElement();
}

Storage::IteratorBird Storage::beginBird()
{
   return IteratorBird();
}

Storage::IteratorBird Storage::endBird()
{
   return IteratorBird();
}

Storage::IteratorBullet Storage::beginBullet()
{
   return IteratorBullet();
}

Storage::IteratorBullet Storage::endBullet()
{
   return IteratorBullet();
}

void Storage::add(ElementStorage* element)
{
}

void Storage::remove(ElementStorage* it)
{
}

void Storage::reset()
{
}

Storage::IteratorElement Storage::IteratorElement::operator++()
{
   return IteratorElement();
}

ElementStorage* Storage::IteratorElement::operator*()
{
   return nullptr;
}

Storage::IteratorBird Storage::IteratorBird::operator++()
{
   return IteratorBird();
}

ElementStorage* Storage::IteratorBird::operator*()
{
   return nullptr;
}

Storage::IteratorBullet Storage::IteratorBullet::operator++()
{
   return IteratorBullet();
}

ElementStorage* Storage::IteratorBullet::operator*()
{
   return nullptr;
}
