#include <iostream>
#include <vector>

using namespace std;
class cards_rank
{
    public:

        int rank_trio(const int& num1, const int& num2, const int& num3);
        int rank_straight_run(const int& num1, const int& num2, const int& num3);
        int rank_color(unsigned const& num1_color, unsigned const int& num2, unsigned const int& num3);
        int rank_pair(unsigned const int& num1, unsigned const int& num2, unsigned const int& num3);
        int rank_high_card(unsigned const int& num1, unsigned const int& num2, unsigned const int& num3);
        int weighttage_of_cards(array<pair<int,int>, 3>& card);  //This is just for debugging;


};