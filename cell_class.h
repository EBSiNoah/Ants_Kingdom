
using namespace std;
	
class Cell
{
	public:
		int property;//*0==empty, 1==queen, 2==male, 3==worker, 4==food*/
		int life;//*queen=5~10years, male=180, worker=360*/
		int hunger;//*5 days, 10 days*/
		int health;//*100=queen, 20=male, 50=worker, 10<food<100*/
		bool rest;
		bool move;
		Cell();//*initialize, means delete or clear*/
		Cell(int property_value);
};
