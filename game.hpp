#include <iostream>
#include <vector>
#include <array>

using namespace std;

struct Player
{
    int player_num;
    bool isrequest;
    array<pair<int,int> ,3> cards;
    int cards_weightage;
    int balance;
    Player* next;
};

class Game
{
    public:
    void Window(Player* &head);
    Player* Init();
    void Display(Player* &head, int bid);

    //LinkedList
    int LengthOfPlayer(Player* &head);
    void DeleteAtHead(Player* &head);
    void DeleteNode(Player* &head, int value);
    void DeletePackedPlayer(Player* &head);
    Player* GetLastPlayer(Player* &head);

    //Cards-Related Funcitons
    bool ShowAccept();
    int RandomGenState();
    int CardsWeight(Player* &node);  //Node means:- it can be anynode
    array<pair<int,int>,3> CardsGenerator();
    bool IsPackedPlayerExists(int player_num);

    private:
    vector<int> packed_player;
    vector<pair<int,int> > card_vector;
   

};
