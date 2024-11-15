#include "Storage.h"

Storage::IteratorElement Storage::IteratorElement::emptyObject = new Storage::IteratorElement();

Storage::IteratorElement Storage::beginElement() const {
   if (Element == nullptr || Element->empty()) {
      return endElement();
   }

   std::list<ElementStorage*>::iterator start = Element->begin();
   
   return IteratorElement(start); 
}

Storage::IteratorElement Storage::endElement() const {
   if (Element == nullptr || Element->empty()) {
      
      return IteratorElement::emptyObject;
   }
   return IteratorElement(Element->end());
}



Storage::IteratorBird Storage::beginBird() const {
   if (Element == nullptr || Element->empty()) {
      return endBird();
   }
   
   
   return IteratorBird(Element);
}

Storage::IteratorBird Storage::endBird() const {
   if (Element == nullptr || Element->empty()) {
      static const IteratorBird staticEnd;
      return staticEnd;
   }
   return IteratorBird(Element).end();
}

Storage::IteratorBullet Storage::beginBullet() const {
   if(Element == nullptr || Element->empty()) {
      return endBullet();
   }
   
   return IteratorBullet(Element);
}

Storage::IteratorBullet Storage::endBullet() const {
   if(Element == nullptr || Element->empty()) {
      static const IteratorBullet staticEnd;
      return staticEnd;
   }
   return IteratorBullet(Element).end();
}

void Storage::addElement(ElementStorage* element)
{
   if (element->isBird)
   {
      numBirds++;
   }

   Element->push_back(element);
}

void Storage::remove(ElementStorage* element)
{
   if (element->isBird)
   {
      numBirds--;
   }
   Element->remove(element);
}

std::list<ElementStorage*>::iterator Storage::erase(const std::list<ElementStorage*>::iterator& it) {
   if((*it)->isBird) {
      numBirds--;
   }
   return Element->erase(it);
}

void Storage::reset()
{
   *this = Storage();
}

Storage::IteratorElement& Storage::IteratorElement::operator++()
{
   ++it;
   return *this;
}

ElementStorage* Storage::IteratorElement::operator*() const {
   return *it;
}

Storage::IteratorBird::IteratorBird(std::list<ElementStorage*>* elementInput)
{
   element = elementInput;
   it = element->begin();
   ++it;

   while ((it != element->end()) && (!(*it)->isBird))
   {
      ++it;
   }
}

Storage::IteratorBird& Storage::IteratorBird::operator++()
{
   ++it;

   while (it != element->end() && !(*it)->isBird)
   {
      ++it;
   }

   return *this;
}

ElementStorage* Storage::IteratorBird::operator*() const {
   return *it;
}

Storage::IteratorBullet::IteratorBullet(std::list<ElementStorage*>* elementInput)
{
   element = elementInput;

   it = element->begin();

   ++it;
   
   while (it != element->end() && !(*it)->isBullet)
   {
      ++it;
   }
}

Storage::IteratorBullet& Storage::IteratorBullet::operator++()
{
   ++it;

   while (it != element->end() && !(*it)->isBullet)
   {
      ++it;
   }

   return *this;
}

ElementStorage* Storage::IteratorBullet::operator*() const {
   return *it;
}
