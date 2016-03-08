#ifndef BUDDYFIT_H
#define BUDDYFIT_H
#include <string>
#include "Area.h"
#include "Fitter.h"
using namespace std;


class BuddyFit : public Area
{
	public:
		BuddyFit(string name, int base, int size);
		~BuddyFit();
		Area *alloc(int wanted);
		void  free(Area *);
	protected:
	private:
		void split();
		string name;
		/// Pointer to the left buddy in the tree
		BuddyFit *buddyFitLeft;
		/// Pointer to the right buddy in the tree
		BuddyFit *buddyFitRight;
		/// boolean that defines if all the memory is used from this buddy on
		bool used;
};

#endif // BUDDYFIT_H
