#include"pokemon.h"

int main()
{
    DWORD ThreadID2 = 0;
    HANDLE hClient = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)client, NULL, 0, &ThreadID2);

    int request = -1;

    user user1;

    srand((int)time(NULL));

    while (request != STOP)
    {
        //print menu
        std::cout << "\nWelcome to pokemons game£¡" << std::endl;
        std::cout << "Please input: " << std::endl;
        std::cout << "1-sign up" << std::endl;
        std::cout << "2-log in" << std::endl;
        std::cout << "3-log out " << std::endl;
        std::cout << "4-query online users " << std::endl;
        std::cout << "5-query user's pokemons" << std::endl;
        std::cout << "6-upgrade" << std::endl;
        std::cout << "7-duel" << std::endl;
        std::cout << "8-medals" << std::endl;
        std::cout << "9-2v2 upgrade" << std::endl;
        std::cout << "10-query user's win rate" << std::endl;
        std::cout << "0-exit\n" << std::endl;

        //input request
        std::cin >> request;

        switch (request)
        {
        case SIGNUP:           user1.signUp();           break;//user sign up
        case LOGIN:            user1.logIn();            break;//user log in
        case LOGOUT:           user1.logOut();           break;//log out
        case SEARCHONLINEUSER: user1.searchOnlineUser(); break;//query online user 
        case SEARCHPOKEMON:    user1.searchPokemon();    break;//query user's pokemons 
        case STOP:             user1.terminate();        break;//stop
        case UPGRADE:		   user1.upgrade();			 break;// upgrade 
        case DUEL:			   user1.duel();			 break;// duel 
        case MEDAL:			   user1.medal();			 break;//medal
        case DOUBLE_UPGRADE:   user1.upgrade2v2();       break;//2v2 upgrade
        case SEARCHWINRATE:	   user1.searchWinRate();    break;//query user's win rate 
        default:break;
        }
    }
    return 0;
}


void sendMessage(char type, char *message)
{
    sendBuf[0] = type;
    strncpy(sendBuf + 1, message, msgLength);

    //send lock 
    sendRequest = SEND;
}


int isCorrectName(char *name)
{
    for (int i = 0; i < maxLength; i++)
    {
        
        if (name[i] == '\0' && i>0)
        {
            
            return SUCCESS;
        }

       
        if (!((name[i] >= '0' && name[i] <= '9')
            || (name[i] >= 'a' && name[i] <= 'z')
            || (name[i] >= 'A' && name[i] <= 'Z')
            || (name[i] == '_')))
        {
            std::cout << "user name should only contain letters, numbers and underlines" << std::endl;
            return FAILURE;
        }
    }
    return FAILURE;
}

int isCorrectPword(char *word)
{
    for (int i = 0; i < maxLength; i++)
    {
        if (word[i] == '\0' && i <= 5)
        {
            std::cout << "password should have 6-14 digits" << std::endl;
            return FAILURE;
        }

        else if (word[i] == '\0' && i > 5)
        {
            return SUCCESS;
        }

        if (!(word[i] >= 33 && word[i] <= 126))
        {
            std::cout << "password should contains letters, numbers and characters" << std::endl;
            return FAILURE;
        }
    }
    return FAILURE;
}

void clearBuf()
{
    for (int i = 0; i < BUF_SIZE; i++)
    {
        sendBuf[i] = '\0';
        recvBuf[i] = '\0';
    }
}

void readInfo(char* info, int& kind, int& level, int& exp)
{
    int i;

    kind = atoi(info);
    for (i = 0; info[i] != ','; i++);
    i++;

    level = atoi(info + i);
    for (; info[i] != ','; i++);

    exp = atoi(info + i + 1);
}

void CalWinRate(pokemon *A, int kind, int level)
{
    std::cout << "Do you want to calculate win rate£¿1-yes 0-no\n";
    std::cin >> calWinRate;

    if (calWinRate == no)
    {
        return;
    }
    //user  pokemons 
    pokemon *pokea = NULL;

    switch (kind)
    {
    case BULBASAUR:  pokea = new bulbasaur;  break;
    case CHARMANDER: pokea = new charmander; break;
    case SQUIRTLE:   pokea = new squirtle;   break;
    case PIKACHU:    pokea = new pikachu;    break;
    case MANKEY:     pokea = new mankey;     break;
    case SNORLAX:    pokea = new snorlax;    break;
    case CROBAT:	 pokea = new crobat;     break;
    case SHUCKLE:	 pokea = new shuckle;    break;
    default:break;
    }

    pokea->setLevel(level);
    pokea->promoteLevel();
    std::cout << "The win rate of your pokemon is: ";

    double winRate = simuFight(pokea, A);
    std::cout << winRate << "\n";

    delete pokea;
    calWinRate = 0;
}

double simuFight(pokemon* competitorA, pokemon* competitorB)
{
    int time = 0;  //timer
    int end = 0;   //end flag
    int death = 0; // pokemons 
    int win = 0;   

    int sp1 = 0, sp2 = 0, attr1 = 0, attr2 = 0, def1 = 0, def2 = 0;
    double winRate = 0; // win rate 

                     
    sp1 = competitorA->getSpeed();
    sp2 = competitorB->getSpeed();
    attr1 = competitorA->getAttr();
    attr2 = competitorB->getAttr();
    def1 = competitorA->getDef();
    def2 = competitorB->getDef();

    
    for (int i = 0; i < 1000; i++)
    {
        while (!death)
        {
            time++;
            if (time%sp1 == 0)
            {
                death = competitorB->damage(competitorA->attack(attr2, def2));
                if (death == 1)
                {
                    win++;
                    break;
                }
            }
            if (time%sp2 == 0)
            {
                death = competitorA->damage(competitorB->attack(attr1, def1));
            }
        }

        time = 0;
        death = 0;
        competitorA->recover();
        competitorB->recover();
    }//1000

     //return  win rate 
    winRate = double(win / 1000.0);
    return winRate;
}

void toString(char*a, int k, int l, int e)
{
    int count = 0;

    toChar(k, a, count);

    toChar(l, a, count);

    toChar(e, a, count);
}

void toChar(int a, char*b, int& c)
{
    char x[10] = { '\0' };
    for (int i = 0; i < 10; i++)
    {
        x[i] = '\0';
    }
    itoa(a, x, 10);

    strncpy(b + c, x, strlen(x));
    c = c + strlen(x);

    b[c] = ',';
    c++;
}