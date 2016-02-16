#include "BuddyFit.h"

BuddyFit::BuddyFit()
: buddyFitLeft(nullptr), buddyFitRight(nullptr), used(false)
{
	//ctor
}

BuddyFit::~BuddyFit()
{
  delete buddyFitLeft;
  delete buddyFitRight;
}

BuddyFit::alloc(int wanted)
{

}

BuddyFit::free(Area *area)
{

}

BuddyFit::report()
{

}
