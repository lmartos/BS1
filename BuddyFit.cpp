#include "BuddyFit.h"


BuddyFit::BuddyFit(string name, int base, int size)
:Area(base, size), buddyFitLeft(nullptr), buddyFitRight(nullptr), used(false), name(name)
{

}

BuddyFit::~BuddyFit()
{
  delete buddyFitLeft;
  delete buddyFitRight;
}

Area* BuddyFit::alloc(int wanted)
{
	if(wanted <= size/2){
		BuddyFit::split();
		if(!buddyFitLeft->used){
			return buddyFitLeft::alloc(wanted);
		}else if(!BuddyFitRight->used){
			return buddyFitRight:alloc(wanted);
		}
	}
	this->used = true;
	return memory;

}

void BuddyFit::free(Area *area)
{
	if(area->getBase() == memory->getBase() && buddyFitLeft == nullptr && buddyFitRight == nullptr){
		used = false;
	}else if(area->getBase() >= (base + size/2)){
		buddyFitLeft::free(area);
	}else{
		buddyFitRight::free(area);
	}
	if(buddyFitLeft != used && buddyFitRight != used){
		memory->join(buddyFitLeft->memory);
		delete buddyFitLeft;
		delete buddyFitRight;
		used = false;
	}
}

 void BuddyFit::report()
{

}

void BuddyFit::split()
{
	if((!buddyFitLeft == nullptr) && (!buddyFitRight == nullptr)){
	Area *childMemoryLeft = this->split(size/2);
	Area *childMemoryRight = this;
	buddyFitLeft = new BuddyFit(name + "L", childMemoryLeft->getBase(), childMemoryLeft->getSize());
	buddyFitRight = new BuddyFit(name + "R", childMemoryRight->getBase(), childMemoryRight->getSize());
	}
}
