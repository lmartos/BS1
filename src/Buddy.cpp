#include "Buddy.h"
#include <iostream>
using namespace std;
Buddy::Buddy()
: Allocator(false, "buddy"),memoryControl(nullptr)
{
}

Buddy::~Buddy()
{
	delete memoryControl;
}

void Buddy::setSize(int size) {
	Allocator::setSize(size);
	memoryControl = new BuddyFit("main", 0, size);
}

Area* Buddy::alloc(int wanted) {


	require(wanted > 0);		// has to be "something",
	require(wanted <= size);

	Area* area = 0;

    cout << "boss wants some memory!" << endl;
	area = memoryControl->alloc(wanted);


	if (area == nullptr) {
        cout << "unable to obtain memory" << endl;
		return nullptr;
	} else {
		updateStats(wanted, area->getSize());
		return area;
	}

}

void  Buddy::free(Area * area) {
    try{
	if (memoryControl->free(area))
		mergers++;
    }catch(...){
        cout << "Oops something went wrong..." << endl;
        return;
    }
}

void Buddy::updateStats(int wanted, int allocated) {
	efficiencyInPercentages = efficiencyInPercentages * timesMemoryWasAllocated;

	timesMemoryWasAllocated++;

	efficiencyInPercentages = (efficiencyInPercentages += (wanted / allocated) * 100) / timesMemoryWasAllocated;
}

void  Buddy::report(){
	cout << type << " : " << " gemiddeld verlies in percentages: " << efficiencyInPercentages << endl;
	cout << " times memory was allocated: "
			<< timesMemoryWasAllocated << " times subtree is merged : " << mergers << endl;
}
