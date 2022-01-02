#include "game.hpp"
#include "cards_rank.hpp"
#include "functions.hpp"

int Game::RandomGenState()
{
    int num = (rand() % 20);
    return num;   
}

int Game::LengthOfPlayer(Player* &head)
{
    if(head == NULL)
        return 0;
    int counter = 0;
    Player* node = head;
    do
    {
        node=node->next;
        counter++;
    }while(node !=head);

    return counter;
}

void Game::DeleteAtHead(Player* &head)
{
     //Only one node
    if(head->next == head)
    {
        Player* node = head;
        free(node);
        head = NULL;
        return;
    }
    if(head != NULL)
    {
        Player* n = head;
        while(n->next != head)
        {
            n = n->next;
        }
        Player* temp = head;
        n->next = head->next;
        head = head->next;
        delete temp;
    }
}

void Game::DeleteNode(Player* &head, int value)
{
    if(head->player_num == value && head->next == head)
        return;
    if(head->player_num == value)
    {
       DeleteAtHead(head);
       return;
    }

    Player* node = head;
    while (node->next->player_num != value)
    {
        node = node->next;
    }
    Player* temp = node->next;
    node->next = node->next->next;
    delete temp;

}

void Game::DeletePackedPlayer(Player* &head)
{
     if(packed_player.empty())
        return;
    else
    {
        for(int i=0; i<packed_player.size(); i++)
        {
            DeleteNode(head, packed_player[i]);
        }
        packed_player.clear();
        return;
    }
}
bool IsCardExists(vector<pair<int,int> >& cards, pair<int,int>& cur_card)
{
    //This functions will return true if card exists
    /*v1
   auto itr = find(cards.begin(), cards.end(), cur_card);
   if((itr-cards.begin())!= cards.size())
       return true;
   else
    return false;
    */
    if(cards.empty())
        return false;
    
    for(int i=0; i < cards.size(); i++)
    {
        if(cards[i].first == cur_card.first && cards[i].second == cur_card.second)
            return true;
    }
    return false;
}

array<pair<int,int>, 3> Game::CardsGenerator()
{
    int counter = 0;
    array<pair<int,int> , 3> card_pair;
    while(counter!= 3)
    {
        int color = (rand() % 4);
        int card = (rand() % 13);
        pair<int,int> p = make_pair(color,card);
        if(!IsCardExists(card_vector, p))
            {
                card_vector.push_back(p); 
                card_pair[counter] = p;
                counter++;
            }    
    }
       return card_pair; 
}

int Game::CardsWeight(Player* &node)
{
    cards_rank c;
    array<pair<int,int> , 3> card = node->cards;
    int num = c.weighttage_of_cards(card); 
    return num;
}

Player* Game::Init()
{
      //Initialization of cards and players.
    Player* head = new Player;
    Player* second = new Player;
    Player* third = new Player;
    Player* fourth = new Player;
    Player* fifth = new Player;

    head->player_num = 1;
    head->isrequest = false;
    head->cards = CardsGenerator();   
    head->cards_weightage = CardsWeight(head);
    head->balance = 10000;
    head->next = second;

    second->player_num = 2;
    second->isrequest = false;
    second->cards = CardsGenerator();  
    second->cards_weightage = CardsWeight(second);
    second->balance = 10000;
    second->next = third;

    third->player_num = 3;
    third->isrequest = false;
    third->cards = CardsGenerator(); 
    third->cards_weightage = CardsWeight(third); 
    third->balance = 10000;
    third->next = fourth;

    fourth->player_num = 4;
    fourth->isrequest = false;
    fourth->cards = CardsGenerator();  
    fourth->cards_weightage = CardsWeight(fourth);
    fourth->balance = 10000;
    fourth->next = fifth;

    fifth->player_num = 5;
    fifth->isrequest = false;
    fifth->cards = CardsGenerator();  
    fifth->cards_weightage = CardsWeight(fifth);
    fifth->balance = 10000;
    fifth->next = head;

    return head;
}

Player* Game::GetLastPlayer(Player* &head)
{
    Player* node = head;
    do
    {
        node = node->next;   
    } while (node->next != head);
    
    return node;
}

bool Game::IsPackedPlayerExists(int player_num)  // prevent packed player from normal user's actions like bid, show and packed
{
    for(int i=0; i < packed_player.size(); i++)
    {
        if(packed_player[i] == player_num)
            return true;
    }
    return false;
}
void Game::Display(Player* &head,  int bid)
{
    array<string, 13>p_card = {"2", "3", "4", "5", "6", "7","8", "9","10", "J", "Q", "K", "A"}; 
    array<string, 4> p_color = {"♠️", "♥️","♣️", "♦️"};
    functions fun;
    fun.clear_screen();
    Player* node = head;
    Player* ptr = GetLastPlayer(head);
    do 
    {
        if(node->player_num != 5)
        {

            if(node->isrequest)
            { 
                    if(ptr->player_num != 5)
                    {
                        cout << "Player"<< node->player_num << " has accpeted the request"<<"\n";
                        if(ptr->cards_weightage > node->cards_weightage)
                        {
                            cout << "Player"<< node->player_num << " has Lost the Show and Packed\n";
                            packed_player.push_back(node->player_num);    
                        }
                        else
                        {
                            cout << "Player"<< node->player_num<< " has won the show\n";
                            packed_player.push_back(ptr->player_num);
                        }      
                    }
                    else
                    {
                        cout << "Player"<<node->player_num <<" Cards:- " << p_color[node->cards[0].first] <<" "<<p_card[node->cards[0].second] << "  "
                            << p_color[node->cards[1].first] << " " << p_card[node->cards[1].second]<< "  "
                            << p_color[node->cards[2].first] << " " << p_card[node->cards[2].second] << "\n";

                        if(ptr->cards_weightage > node->cards_weightage)
                        {
                            cout << "Player"<< node->player_num << " has Lost the Show and Packed\n";
                            packed_player.push_back(node->player_num);    
                        }
                        else
                        {
                            cout << "Player"<< node->player_num<< " has won the show\n";
                            packed_player.push_back(ptr->player_num);
                        }      
                    }
                node->isrequest = false;
            }


            int rand_num = RandomGenState();
            if(rand_num == 1)   // player will be packed
            {
                if(!IsPackedPlayerExists(node->player_num))
                {
                cout <<"Player"<<node->player_num << ":- " << "Packed\n";
                packed_player.push_back(node->player_num);
                }
            } 
            else if(rand_num == 18)  // Player will request the show 
            {
                if(!IsPackedPlayerExists(node->player_num))  //Check if user who is already packed is trying to reuest a show
                {
                   cout << "Player"<< node->player_num << " has requested the show\n";
                   node->next->isrequest = true;
                }
              
            } 
            else
            {
                if(!IsPackedPlayerExists(node->player_num))
                {
                    if(node->balance >= bid)
                    {
                        node->balance = node->balance - bid;
                        cout << "Player" << node->player_num << ":- " << "Bid:- " << bid << " Placed\n";
                    }
                    else
                    {
                        cout << "Player" << node->player_num << ":- Packed\n";
                        packed_player.push_back(node->player_num);   
                    }
                }
            }
        }
        else
        {
            if(node->isrequest)
            {
                cout << "\n\a You Got Show Request:-\n";
                cout << "Player"<<ptr->player_num <<" Cards:- " << p_color[ptr->cards[0].first] <<" "<<p_card[ptr->cards[0].second] << "  "
                            << p_color[ptr->cards[1].first] << " " << p_card[ptr->cards[1].second]<< "  "
                            << p_color[ptr->cards[2].first] << " " << p_card[ptr->cards[2].second] << "\n";
                
                cout << "Your Cards" << p_color[node->cards[0].first] <<" "<<p_card[node->cards[0].second] << "  "
                            << p_color[node->cards[1].first] << " " << p_card[node->cards[1].second]<< "  "
                            << p_color[node->cards[2].first] << " " << p_card[node->cards[2].second] << "\n";
                
                if(ptr->cards_weightage > node->cards_weightage)
                {
                    cout << "You:- Lost the Show and Packed\n";
                    packed_player.push_back(5);
                }
                else
                {
                    cout << "You:- Won the Show\n";
                    packed_player.push_back(ptr->player_num);
                }
                cout << "Press Enter to Continue..\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cin.get();
                node->isrequest = false;
            }
            else
            {
                bool cond = true;
                int choice;
                do
                {
                    if(!IsPackedPlayerExists(node->player_num))
                    {
                        cout << "\n\n\aYour Cards:- " << p_color[node->cards[0].first] <<" "<<p_card[node->cards[0].second] << "  "
                            << p_color[node->cards[1].first] << " " << p_card[node->cards[1].second]<< "  "
                            << p_color[node->cards[2].first] << " " << p_card[node->cards[2].second] << "\n";
                        cout << "(1)-> Place a bid\n"; //<<"("<<bid <<")"<<"\n";
                        cout << "(2)-> Pack\n";
                        cout << "(3)-> Request the Show\n"; //<<"("<<2*bid<<")"<<"\n";
                        cin >> choice;
                        if(cin.fail())
                        {
                            cin.clear();
                            cerr << "Please Enter the valid Input\n";
                        }
                        else
                        {
                            if(choice == 1)   //Place a bid
                            {
                                    cout << "You:- "<< bid << " Bid Placed\n";
                                    cond = false;
                            }
                            else if(choice == 2)
                            {
                                cout << "You:- Packed\n"; 
                                packed_player.push_back(5);
                                cond = false;
                            }
                            else if(choice == 3)
                            {
                                    cout << "You:- have requested the show\n";
                                    node->next->isrequest = true;
                                    cond = false;
                            }
                            else
                                cout << "Please Enter the correct input\n";
                        }
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    }
                    else
                        cond = false;
                  
                }while(cond);
            }
        }   
        node = node->next;
        ptr = ptr->next;
        fun.sleepcp(500);

    }  while(node != head);
}
void Game::Window(Player* &head)
{
    functions fun;
    Player* node = head;
    int bid = 100;
    do
    {
       Display(node, bid);
       bid += 100;
       DeletePackedPlayer(node);
       fun.sleepcp(500);
       
    }while(LengthOfPlayer(node) != 1);

    cout <<"\n-------------------------------\n";
    if(node->player_num == 5)
        cout << "You:- Won \n";
    else
        cout << "Player" << node->player_num << ":- Won\n";
    delete node;
}
