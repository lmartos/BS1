#ifndef BUDDYFIT_H
#define BUDDYFIT_H


class BuddyFit : public Fitter
{
	public:
		BuddyFit();
		~BuddyFit();
		public Area *alloc(int wanted);
		public void  free(Area *);
		public void  report();
	protected:
	private:
		/// Pointer to the left buddy in the tree
		BuddyFit *buddyFitLeft;
		/// Pointer to the right buddy in the tree
		BuddyFit *buddyFitRight;
		/// boolean that defines if all the memory is used from this buddy on
		bool used;
};

#endif // BUDDYFIT_H
