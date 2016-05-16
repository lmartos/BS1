#ifndef BUDDYFIT_H
#define BUDDYFIT_H
#include <string>
#include <stack>
#include "../Area.h"
#include "../Fitter.h"
using namespace std;


class BuddyFit : public Area
{
	public:
	    BuddyFit(string name, int base, int size);
		BuddyFit(string name, int base, int size, BuddyFit* parent);
		virtual ~BuddyFit();
		Area *alloc(int wanted);
		bool  free(Area *);
		bool  isUsed();
		void  setUsed(bool used);
		string getName();
		bool updateParent();
		BuddyFit* findMemory(string path);
		BuddyFit* getBuddyFitLeft();
		BuddyFit* getBuddyFitRight();
	protected:
	private:
		void divide();
		string name;

		BuddyFit *parent;
		/// Pointer to the left buddy in the tree
		BuddyFit *buddyFitLeft;
		/// Pointer to the right buddy in the tree
		BuddyFit *buddyFitRight;
		/// boolean that defines if all the memory is used from this buddy on
		bool used;

};

#endif // BUDDYFIT_H
