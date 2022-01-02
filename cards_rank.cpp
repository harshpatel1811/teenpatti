#include "cards_rank.hpp"
#include <array>

using namespace std;


int cards_rank::rank_trio(const int &num1, const int &num2, const int &num3)
{
    if ((num1 == num2) && (num2 == num3) && (num1 == num3))
        return 300;

    else
        return 0;
}

int cards_rank::rank_straight_run(const int &num1, const int &num2, const int &num3)
{
    array<int, 3> t_arr = {num1, num2, num3};
    sort(t_arr.begin(), t_arr.end());

    if ((t_arr[1] == t_arr[0] + 1) && (t_arr[2] == t_arr[1] + 1))
    {
        return 150;
    }
    else
        return 0;
}

int cards_rank::rank_color(unsigned const int &num1_color, unsigned const int &num2_color, unsigned const int &num3_color)
{
    if ((num1_color == num2_color) && (num2_color == num3_color) && (num1_color == num3_color))
    {
        return 100;
    }
    else
        return 0;
}

int cards_rank::rank_pair(unsigned const int &num1, unsigned const int &num2, unsigned const int &num3)
{
    if (num1 == num2)
        return 50;

    else if (num1 == num3)
        return 50;

    else if (num2 == num3)
        return 50;

    else
        return 0;
}

int cards_rank::rank_high_card(unsigned const int &num1, unsigned const int &num2, unsigned const int &num3)
{
    if (num1 == 0)
        return 1 + (num2 + 1) + (num3 + 1);

    else if (num2 == 0)
        return 1 + (num1 + 1) + (num3 + 1);

    else if (num3 == 0)
        return 1 + (num1 + 1) + (num2 + 1);

    else
        return (num1 + 1) + (num2 + 1) + (num3 + 1);
}


int cards_rank::weighttage_of_cards(array<pair<int,int> , 3>& c)   
{
    int num1,num2,num3,num4,num5;

       num1 = rank_trio(c[0].second, c[1].second, c[2].second);
       num2 = rank_straight_run(c[0].second, c[1].second, c[2].second);
       num3 = rank_color(c[0].first, c[1].first, c[2].first);
       num4 = rank_pair(c[0].second, c[1].second, c[2].second);
       num5 = rank_high_card(c[0].second, c[1].second, c[2].second);

   return num1+num2+num3+num4+num5;
}