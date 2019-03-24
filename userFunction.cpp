#include"pokemon.h"

//global variable
char sendBuf[BUF_SIZE] = { '\0' };  //send buffer max_length: BUF_SIZE
char recvBuf[BUF_SIZE] = { '\0' };  //recerve buffer max_length: BUF_SIZE
int sendRequest = WAIT; //socket sending lock
int receiveInfo = WAIT; //socket receiving lock
int stop = no;			//stop flag
int calWinRate = no;     //calculating win rate flag

//user class constructor
user::user()
{
    //initialize user name and password
    for (int i = 0; i < maxLength; i++)
    {
        userName[i] = '\0';
        password[i] = '\0';
    }

    //initialize pokemon pointer
    for (int i = 0; i < 30; i++)
    {
        poke[i] = NULL;
    }
    //the number of pokemon=0
    pokemonNum = no;

    winNum = no; //win times=0
    playNum = no;//play times = 0

    //medal number=0
    for (int i = 0; i < 3; i++)
    {
        NumMedal[i] = no;
        LevelMedal[i] = no;
    }
}

//distructor
user::~user()
{

}

//user sign up
void user::signUp()
{
    char name[msgLength] = { '\0' };  //user name buffer
    char pword[msgLength] = { '\0' }; //password buffer
    int ok = no;  //matching flag

    while (!ok)
    {

        std::cout << "username: (1-14 digits contains numbers, letters and underscores):\n";
        while (!ok)
        {
            std::cin >> name;
            //is name correct
            ok = isCorrectName(name);
        }
        //send to server
        sendMessage(SIGNUP_NAME, name);

        //waiting for response
        while (receiveInfo == WAIT);

        //sign up unsuccessfull
        if (recvBuf[0] == FAILURE)
        {
            std::cout << "The username is already taken." << std::endl;
            ok = no;

            //clear buffer
            clearBuf();
        }
        //lock client
        receiveInfo = WAIT;
    }//ok

	 //clear buffer
    clearBuf();

    ok = no;
    //input password
    std::cout << "password: (6-14 digits password including numbers, letters and characters):\n";
    while (!ok)
    {
        std::cin >> pword;
        //is password correct
        ok = isCorrectPword(pword);
    }
    //send to server
    sendMessage(SIGNUP_PASSWORD, pword);

    //waiting for response
    while (receiveInfo == WAIT);

    //Automatically log in after registration and get three pokemon for the first time
    std::cout << "sign up successfully!\nFirst time log in and get:\n";
    for (int i = 0; i < 3; i++)
    {
        switch (recvBuf[i])
        {
        case BULBASAUR:  poke[i] = new bulbasaur;  std::cout << "bulbasaur "; break;
        case CHARMANDER: poke[i] = new charmander; std::cout << "charmander ";   break;
        case SQUIRTLE:   poke[i] = new squirtle;   std::cout << "squirtle ";   break;
        case PIKACHU:    poke[i] = new pikachu;    std::cout << "pikachu ";     break;
        case MANKEY:     poke[i] = new mankey;     std::cout << "mankey ";     break;
        case SNORLAX:    poke[i] = new snorlax;    std::cout << "snorlax "; break;
        case CROBAT:	 poke[i] = new crobat;     std::cout << "crobat ";   break;
        case SHUCKLE:	 poke[i] = new shuckle;    std::cout << "shuckle ";     break;

        default:break;
        }
    }
    std::cout << '\n';

    //update the user object and save user name and password
    for (int i = 0; i < maxLength; i++)
    {
        userName[i] = name[i];
        password[i] = pword[i];
    }
    //number of pokemon
    pokemonNum = 3;

    //clear buffer and locking
    clearBuf();
    receiveInfo = WAIT;
}

//user log in
void user::logIn()
{
    char name[msgLength] = { '\0' };  //username buffer
    char pword[msgLength] = { '\0' }; //password buffer

    int ok = no; //matching flag

    std::cout << "username:\n";
    while (!ok)
    {
        std::cin >> name;
		//is name correct
        ok = isCorrectName(name);
    }
	//send to server
    sendMessage(LOGIN_NAME, name);
	//waiting for response
    while (receiveInfo == WAIT);

	//clear buffer and locking
    receiveInfo = WAIT;
    clearBuf();

    ok = no;
    std::cout << "password:\n";
    while (!ok)
    {
        std::cin >> pword;
		//is password correct
        ok = isCorrectPword(pword);
    }
	//send to server
    sendMessage(LOGIN_PASSWORD, pword);

	//waiting for response
    while (receiveInfo == WAIT);

    //log in unsuccessfully
    if (FAILURE == recvBuf[0])
    {
        //username doesn't exist
        if (INEXISTENCE == recvBuf[1])
        {
            std::cout << "username doesn't exist" << std::endl;
        }
        //password incorrect
        if (PASSWORDERROR == recvBuf[1])
        {
            std::cout << "password incorrect" << std::endl;
        }
        //You are logged in
        else if (ONLINE == recvBuf[1])
        {
            std::cout << "You are logged in" << std::endl;
        }
    }
    //log in successfully
    else
    {
        std::cout << "log in successfully!\n";
		//update the user object and save user name and password
        for (int i = 0; i < maxLength; i++)
        {
            userName[i] = name[i];
            password[i] = pword[i];
        }

        //loading pokemons data from server
        std::cout << "loading¡­¡­\n";

		//clear buffer and locking
        receiveInfo = WAIT;
        clearBuf();

        /*****update win rate*****/
        //send win rate request
        sendMessage(WINRATE_REQ, name);

		//waiting for response
        while (receiveInfo == WAIT);

        char winRateInfo[msgLength] = { '\0' };

        int winN = no, sumN = no, useless = no;
        
        strncpy(winRateInfo, recvBuf + 1, msgLength);

        
        readInfo(winRateInfo, winN, sumN, useless);

       
        winNum = winN;
        playNum = sumN;

        //clear buffer and locking
        receiveInfo = WAIT;
        clearBuf();

        /*****synchronize *****/
        //user request
        char in[msgLength] = { '\0' };
        in[0] = yes;

        int pokeNum = no; //The number of pokemons
        char elfInfo[msgLength] = { '\0' }; //Pokemons info

                                            //request loading pokemons
        sendMessage(UPDATE_REQ, in);

        //waiting for response
        while (receiveInfo == WAIT);

        //response to the server
        in[0] = no;

        
        while (recvBuf[0])
        {
            int eKind, eExp, eLevel;
            strncpy(elfInfo, recvBuf + 1, msgLength);
            readInfo(elfInfo, eKind, eLevel, eExp);

            switch (eKind)
            {
            case BULBASAUR:  poke[pokeNum] = new bulbasaur;  break;
            case CHARMANDER: poke[pokeNum] = new charmander; break;
            case SQUIRTLE:   poke[pokeNum] = new squirtle;   break;
            case PIKACHU:    poke[pokeNum] = new pikachu;    break;
            case MANKEY:     poke[pokeNum] = new mankey;     break;
            case SNORLAX:    poke[pokeNum] = new snorlax;    break;
            case CROBAT:	 poke[pokeNum] = new crobat;     break;
            case SHUCKLE:	 poke[pokeNum] = new shuckle;    break;
            default:break;
            }
            //update Pokemons info
            poke[pokeNum]->exp = eExp;
            poke[pokeNum]->level = eLevel;
            // pokemons upgrade
            poke[pokeNum]->promoteLevel();
            //The number of pokemons increment
            pokeNum++;

            //clear buffer and locking
            receiveInfo = WAIT;
            clearBuf();

            //send request
            sendMessage(UPDATE_REQ, in);

            //waiting
            while (receiveInfo == WAIT);
        }
        //update The number of pokemons
        pokemonNum = pokeNum;
    }//log in successfully

     //clear buffer and locking
    receiveInfo = WAIT;
    clearBuf();
}

//log out
void user::logOut()
{
    char name[msgLength] = { '\0' }; //username buffer

                                     //get username from the user object
    for (int i = 0; i < maxLength; i++)
    {
        name[i] = userName[i];
    }

    //sending logout request
    sendMessage(LOGOUT_REQ, name);

    //waiting for response
    while (receiveInfo == WAIT);

    // log out unsuccessfully
    if (!recvBuf[0])
    {
        //did not log in
        if (recvBuf[1])
        {
            std::cout << "user didn't log in£¡\n" << std::endl;
        }
        // doesn't exist user 
        else
        {
            std::cout << "user didn't sign up£¡\n" << std::endl;
        }
    }
    // log out successfully
    else
    {
        //clear buffer and locking
        receiveInfo = WAIT;
        clearBuf();

        synchron();

        std::cout << " log out successfully" << std::endl;
    }
    //clear buffer and locking
    receiveInfo = WAIT;
    clearBuf();

    for (int i = 0; i < pokemonNum; i++)
    {
        poke[i] = NULL;
    }
    pokemonNum = 0;

    for (int i = 0; i < 3; i++)
    {
        NumMedal[i] = no;
        LevelMedal[i] = no;
    }
}

//query online user 
void user::searchOnlineUser()
{
    // send info  1: query request   0: received response and send request
    char in[msgLength] = { '\0' };
    in[0] = yes;

    //the number of online user 
    int userNum = no;
    //online username
    char onlineUser[maxLength] = { '\0' };

    //send request
    sendMessage(SEARCHUSER_REQ, in);

    //waiting for response
    while (receiveInfo == WAIT);
    in[0] = no;

    std::cout << "online user :\n";
    //print query
    while (recvBuf[0])
    {
        strncpy(onlineUser, recvBuf + 1, maxLength);
        std::cout << onlineUser << std::endl;
        //online user number  increment
        userNum++;

        //clear buffer and locking
        receiveInfo = WAIT;
        clearBuf();

        sendMessage(SEARCHUSER_REQ, in);

        while (receiveInfo == WAIT);
    }
    //clear buffer and locking
    receiveInfo = WAIT;

    //print the result
    std::cout << "\nThe number of online users is" << userNum << "\n";
    clearBuf();
}

//query user's pokemon
void user::searchPokemon()
{
    char userNameBuf[msgLength] = { '\0' };

    std::cout << "username: \n" << std::endl;
    std::cin >> userNameBuf;

    // send request
    sendMessage(SEARCHPOKEMON_REQ, userNameBuf);

    //waiting for response
    while (receiveInfo == WAIT);

    //failure
    if (recvBuf[0] == FAILURE)
    {
        std::cout << "the user doesn't exist £¡\n";
        clearBuf();
    }
    //success
    else
    {
        //print the result
        std::cout << "The user has: \n";
        for (int i = 1; recvBuf[i] != '\0'; i++)
        {
            switch (recvBuf[i])
            {
            case BULBASAUR:  std::cout << "bulbasaur "; break;
            case CHARMANDER: std::cout << "charmander "; break;
            case SQUIRTLE:	 std::cout << "Squirtle "; break;
            case PIKACHU:	 std::cout << "Pikachu "; break;
            case MANKEY:	 std::cout << "Mankey "; break;
            case SNORLAX:	 std::cout << "Snorlax "; break;
            case CROBAT:	 std::cout << "Crobat "; break;
            case SHUCKLE:	 std::cout << "Schuckle "; break;
            default:break;
            }
        }
        std::cout << '\n';
    }
    //clear buffer and locking
    receiveInfo = WAIT;
    clearBuf();
}

//query user's win rate 
void user::searchWinRate()
{
    char userNameBuf[msgLength] = { '\0' };

    std::cout << "user name: \n" << std::endl;
    std::cin >> userNameBuf;

    // send request
    sendMessage(WINRATE_REQ, userNameBuf);

    //waiting for response
    while (receiveInfo == WAIT);

    
    if (recvBuf[0] == FAILURE)
    {
        std::cout << "the user doesn't exist.\n";
        clearBuf();
    }
    
    else
    {
        char winRateInfo[msgLength] = { '\0' };
        //print the result
        std::cout << "the user's win rate is: ";

        int winN, sumN, useless;
        strncpy(winRateInfo, recvBuf + 1, msgLength);
        readInfo(winRateInfo, winN, sumN, useless);

        if (sumN == no)
        {
            std::cout << "0\n";
        }
        else
        {
            double winr = (double)(winN) / sumN;
            std::cout << winr << "\n";
        }
    }
    //clear buffer and locking
    receiveInfo = WAIT;
    clearBuf();
}

// pokemons  competitorA and competitorB are user's pokemon and competitor's pokemons 
int user::fighting(pokemon* competitorA, pokemon* competitorB)
{
    int win = no;   //win flag
    int time = no;  //timer
    int death = no; // pokemons dead flag
                   //pokemons' speed£¬attack attributes and defence
    int sp1 = 0, sp2 = 0, attr1 = 0, attr2 = 0, def1 = 0, def2 = 0;

    //get  pokemons's speed£¬attack attributes and defence
    sp1 = competitorA->getSpeed();
    sp2 = competitorB->getSpeed();
    attr1 = competitorA->getAttr();
    attr2 = competitorB->getAttr();
    def1 = competitorA->getDef();
    def2 = competitorB->getDef();

    
    while (!death)
    {
        
        time++;
        //pokemons A
        if (time%sp1 == 0)
        {
            death = competitorB->damage(competitorA->attack(attr2, def2));
            // pokemons B dead
            if (death == yes)
            {
                win = yes;
                break;
            }
        }
        //pokemons B
        if (time%sp2 == 0)
        {
            death = competitorA->damage(competitorB->attack(attr1, def1));
        }
    }
    //calculate Exp
    competitorA->promote(competitorA->cal_exp(competitorB->level));
    competitorB->promote(competitorB->cal_exp(competitorA->level));
    //print Pokemons info
    competitorA->print();
    competitorB->print();
    
    time = 0;
    //return result
    return win;
}

// upgrade
void user::upgrade()
{
    int upgradePoke;

    if (pokemonNum > 0)
    {
        std::cout << "Please select one of your Pokemons\n";
        //print Pokemons info
        for (int i = 0; i < pokemonNum; i++)
        {
            std::cout << i << ":\n";
            poke[i]->print();
        }

        std::cin >> upgradePoke;
    }
    //user doesn't have pokemons 
    else
    {
        //1-8 random int
        std::cout << "you don't have any pokemon. Randomly generate a pokemon to you\n";
        int p = rand() % 8 + 1;

        switch (p)
        {
        case BULBASAUR:  poke[0] = new bulbasaur;  std::cout << "bulbasaur "; break;
        case CHARMANDER: poke[0] = new charmander; std::cout << "charmander ";   break;
        case SQUIRTLE:   poke[0] = new squirtle;   std::cout << "Squirtle ";   break;
        case PIKACHU:    poke[0] = new pikachu;    std::cout << "Pikachu ";    break;
        case MANKEY:     poke[0] = new mankey;     std::cout << "Mankey ";     break;
        case SNORLAX:    poke[0] = new snorlax;    std::cout << "Snorlax ";   break;
        case CROBAT:	 poke[0] = new crobat;     std::cout << "Crobat "; break;
        case SHUCKLE:	 poke[0] = new shuckle;    std::cout << "Schuckle "; break;
        default:break;
        }
        upgradePoke = 0;
        std::cout << "\n";
        //print Pokemons info
        poke[0]->print();
    }

    std::cout << "Please select a pokemon from the list as your competitor.\n";
    std::cout << "strength type :  1-Mankey     2-charmander\n";
    std::cout << "tank type :      3-Snorlax    4-bulbasaur\n";
    std::cout << "defence type :   5-Squirtle   6-Schuckle\n";
    std::cout << "speed type :     7-Pikachu    8-Crobat\n";

    int comp = 0; //pokemons type
    std::cin >> comp;

    //create pokemons 
    pokemon *competitor = NULL;

    switch (comp)
    {
    case BULBASAUR:  competitor = new bulbasaur;  break;
    case CHARMANDER: competitor = new charmander; break;
    case SQUIRTLE:   competitor = new squirtle;   break;
    case PIKACHU:    competitor = new pikachu;    break;
    case MANKEY:     competitor = new mankey;     break;
    case SNORLAX:    competitor = new snorlax;    break;
    case CROBAT:	 competitor = new crobat;     break;
    case SHUCKLE:	 competitor = new shuckle;    break;
    default:break;
    }

    int opp_level; //pokemons level
    std::cout << "Please input pokemon's level£¨1-15£©\n";
    std::cin >> opp_level;

    //update Pokemons info
    competitor->level = opp_level;
    competitor->promoteLevel();
    //print Pokemons info
    competitor->print();

    //calculate win rate 
    int k = poke[upgradePoke]->kind;
    int l = poke[upgradePoke]->level;
    CalWinRate(competitor, k, l);

    //end flag
    int end = no;

    while (!end)
    {
        playNum++;

        int w = fighting(poke[upgradePoke], competitor);

        if (w == yes)
        {
            winNum++;
        }

        std::cout << "Do you want to stop£¿1-yes£¬0-no\n";
        std::cin >> end;

        //pokemons recover
        poke[upgradePoke]->recover();
        competitor->recover();
    }
    //release  pokemons
    delete competitor;
}

// duel 
void user::duel()
{
    //pokemons 
    int upgradePoke;

    if (pokemonNum > 0)
    {
        std::cout << "Please select one of your Pokemons \n";
        for (int i = 0; i < pokemonNum; i++)
        {
            std::cout << i << ":\n";
            poke[i]->print();
        }
        std::cin >> upgradePoke;
    }
    else
    {
        std::cout << "you don't have any pokemon. Randomly generate a pokemon to you\n";
        int p = rand() % 8 + 1;
        switch (p)
        {
        case BULBASAUR:  poke[0] = new bulbasaur;  std::cout << "bulbasaur "; break;
        case CHARMANDER: poke[0] = new charmander; std::cout << "charmander ";   break;
        case SQUIRTLE:   poke[0] = new squirtle;   std::cout << "squirtle ";   break;
        case PIKACHU:    poke[0] = new pikachu;    std::cout << "pikachu ";   break;
        case MANKEY:     poke[0] = new mankey;     std::cout << "mankey ";     break;
        case SNORLAX:    poke[0] = new snorlax;    std::cout << "snorlax ";   break;
        case CROBAT:	 poke[0] = new crobat;     std::cout << "crobat "; break;
        case SHUCKLE:	 poke[0] = new shuckle;    std::cout << "shuckle "; break;
        default:break;
        }
        std::cout << "\n";
        upgradePoke = 0;
        //print Pokemons info
        poke[0]->print();
    }
    std::cout << "Please select a pokemon from the list as your competitor.\n";
    std::cout << "strength type :  1-Mankey     2-charmander\n";
    std::cout << "tank type :      3-Snorlax    4-bulbasaur\n";
    std::cout << "defence type :   5-Squirtle   6-Schuckle\n";
    std::cout << "speed type :     7-Pikachu    8-Crobat\n";

    int comp = 0;
    std::cin >> comp;

    //create pokemons 
    pokemon *competitor = NULL;

    switch (comp)
    {
    case BULBASAUR:  competitor = new bulbasaur;
        poke[pokemonNum] = new bulbasaur; break;
    case CHARMANDER: competitor = new charmander;
        poke[pokemonNum] = new charmander; break;
    case SQUIRTLE:   competitor = new squirtle;
        poke[pokemonNum] = new squirtle;   break;
    case PIKACHU:    competitor = new pikachu;
        poke[pokemonNum] = new pikachu;    break;
    case MANKEY:     competitor = new mankey;
        poke[pokemonNum] = new mankey;     break;
    case SNORLAX:    competitor = new snorlax;
        poke[pokemonNum] = new snorlax;    break;
    case CROBAT:	 competitor = new crobat;
        poke[pokemonNum] = new crobat;     break;
    case SHUCKLE:	 competitor = new shuckle;
        poke[pokemonNum] = new shuckle;    break;
    default:break;
    }
    // pokemons level
    int opp_level;
    std::cout << "Please input pokemon's level£¨1-15£©\n";
    std::cin >> opp_level;

    //update Pokemons info print 
    competitor->level = opp_level;
    competitor->promoteLevel();
    competitor->print();

    //calculate  win rate 
    int k = poke[upgradePoke]->kind;
    int l = poke[upgradePoke]->level;
    CalWinRate(competitor, k, l);

    int win = fighting(poke[upgradePoke], competitor);

    if (win == SUCCESS && pokemonNum < 30)
    {
        playNum++;
        winNum++;

        // pokemons recover
        poke[upgradePoke]->recover();

        std::cout << "Win! Getting a pokemons \n";
        //print
        competitor->print();

        //user got a pokemon
        poke[pokemonNum]->level = competitor->level;
        poke[pokemonNum]->exp = competitor->exp;
        poke[pokemonNum]->promoteLevel();

        //The number of pokemons increment
        pokemonNum++;
        std::cout << "Congratulations! You have " << pokemonNum << " pokemons \n";
    }

    else if (win == FAILURE)
    {
        playNum++;

        //release pokemon
        delete poke[pokemonNum];

        int give;

      
        if (pokemonNum <= 3)
        {
            std::cout << "Please select a pokemon from your list and you will lose the pokemon\n";
            for (int i = 0; i < pokemonNum; i++)
            {
                std::cout << i << ":\n";
                poke[i]->print();
            }
            std::cin >> give;
        }
        else
        {
            std::cout << "Three randomly selected from your pokemons, please select one to send out!\n";
            int p[3] = { 0,0,0 };  
            p[0] = rand() % pokemonNum;
            p[1] = rand() % pokemonNum;

            while (p[1] == p[0])
            {
                p[1] = rand() % pokemonNum;
            }
            p[2] = rand() % pokemonNum;
            while (p[2] == p[0] || p[2] == p[1])
            {
                p[2] = rand() % pokemonNum;
            }
            for (int i = 0; i < 3; i++)
            {
                std::cout << p[i] << ":\n";
                poke[p[i]]->print();
            }

            std::cin >> give;
        }
        delete poke[give];

        for (int i = give; i < pokemonNum; i++)
        {
            poke[i] = poke[i + 1];
        }

        pokemonNum--;
        std::cout << "You lost a pokemons, now you have "<< pokemonNum <<" pokemons \n";
    }
    else
    {
        std::cout << "The number of pokemons reached upper limit\n";
    }
    delete competitor;
}

void user::upgrade2v2()
{
    int uPoke[2];
    if (pokemonNum > 2)
    {
        for (int i = 0; i < pokemonNum; i++)
        {
            std::cout << i << ":\n";
            poke[i]->print();
        }
        std::cout << "Please select two pokemons from your list to duel \n";
        std::cin >> uPoke[0];
        std::cin >> uPoke[1];
    }
    else if (pokemonNum == 2)
    {
        std::cout << "your pokemons are: \n";
        for (int i = 0; i <= 1; i++)
        {
            poke[i]->print();
        }
    }
    else if (pokemonNum == 1)
    {
        std::cout << "your pokemon is: \n";
        poke[0]->print();

        std::cout << "Randomly generate a pokemon : \n";
        int p = rand() % 8 + 1;

        switch (p)
        {
        case BULBASAUR:  poke[1] = new bulbasaur;  break;
        case CHARMANDER: poke[1] = new charmander; break;
        case SQUIRTLE:   poke[1] = new squirtle;   break;
        case PIKACHU:    poke[1] = new pikachu;    break;
        case MANKEY:     poke[1] = new mankey;     break;
        case SNORLAX:    poke[1] = new snorlax;    break;
        case CROBAT:	 poke[1] = new crobat;     break;
        case SHUCKLE:	 poke[1] = new shuckle;    break;
        default:break;
        }
        //user  pokemons 
        uPoke[0] = 0;
        uPoke[1] = 1;

        //print Pokemons info
        poke[1]->print();
    }
    else
    {
        std::cout << "You don't have pokemon. Randomly grnerate two for you.\n";

        for (int i = 0; i <= 1; i++)
        {
            int p = rand() % 8 + 1;
            switch (p)
            {
            case BULBASAUR:  poke[i] = new bulbasaur;  break;
            case CHARMANDER: poke[i] = new charmander; break;
            case SQUIRTLE:   poke[i] = new squirtle;   break;
            case PIKACHU:    poke[i] = new pikachu;    break;
            case MANKEY:     poke[i] = new mankey;     break;
            case SNORLAX:    poke[i] = new snorlax;    break;
            case CROBAT:	 poke[i] = new crobat;     break;
            case SHUCKLE:	 poke[i] = new shuckle;    break;
            default:break;
            }
            poke[i]->print();
        }
        uPoke[0] = 0;
        uPoke[1] = 1;
    }
    std::cout << "Please select two pokemons from the list \n";
    std::cout << "strength type :  1-Mankey     2-charmander\n";
    std::cout << "tank type :      3-Snorlax    4-bulbasaur\n";
    std::cout << "defence type :   5-Squirtle   6-Schuckle\n";
    std::cout << "speed type :     7-Pikachu    8-crobat\n";

    int comp[2];
    std::cin >> comp[0];
    std::cin >> comp[1];

    pokemon *competitor[2];
    for (int i = 0; i <= 1; i++)
    {
        switch (comp[i])
        {
        case BULBASAUR:  competitor[i] = new bulbasaur;  std::cout << "bulbasaur "; break;
        case CHARMANDER: competitor[i] = new charmander; std::cout << "charmander ";   break;
        case SQUIRTLE:   competitor[i] = new squirtle;   std::cout << "Squirtle ";   break;
        case PIKACHU:    competitor[i] = new pikachu;    std::cout << "Pikachu ";   break;
        case MANKEY:     competitor[i] = new mankey;     std::cout << "Mankey ";     break;
        case SNORLAX:    competitor[i] = new snorlax;    std::cout << "Snorlax ";   break;
        case CROBAT:	 competitor[i] = new crobat;     std::cout << "Crobat "; break;
        case SHUCKLE:	 competitor[i] = new shuckle;    std::cout << "Schuckle "; break;
        default:break;
        }

        int opp_level;
        std::cout << "\nPlease input the first pokemons's level(1-15)\n";
        std::cin >> opp_level;

        competitor[i]->level = opp_level + 1;
        competitor[i]->promoteLevel();
        competitor[i]->print();
    }

    int win = 0; 
    int lose = 0;
    int time = 0;
    int death[4] = { 0,0,0,0 };
    int sp[4], attr[4], def[4];// pokemons attributes

    sp[0] = competitor[0]->getSpeed();
    sp[1] = competitor[1]->getSpeed();
    sp[2] = poke[uPoke[0]]->getSpeed();
    sp[3] = poke[uPoke[1]]->getSpeed();
    attr[0] = competitor[0]->getAttr();
    attr[1] = competitor[1]->getAttr();
    attr[2] = poke[uPoke[0]]->getAttr();
    attr[3] = poke[uPoke[1]]->getAttr();
    def[0] = competitor[0]->getDef();
    def[1] = competitor[1]->getDef();
    def[2] = poke[uPoke[0]]->getDef();
    def[3] = poke[uPoke[1]]->getDef();

    while (win != 2 && lose != 2)
    {
        time++;

        if (time%sp[2] == 0 && death[2] == no)
        {
            int at = -1;

            if (death[0] == yes)
            {
                at = 2;
            }
            else if (death[1] == yes)
            {
                at = 1;
            }

			else if (poke[uPoke[0]]->atk_kind != 2)
            {
                std::cout << "Please select No.1 pokemon's target pokemon: (1 or 2):\n";
                std::cin >> at;
            }
            if (at == -1)
            {
                death[0] = competitor[0]->damage(poke[uPoke[0]]->attack(attr[0], def[0]));
                death[1] = competitor[1]->damage(poke[uPoke[0]]->attack(attr[1], def[1]));
                if (death[0] == yes)
                {
                    win++;
                }
                if (death[1] == yes)
                {
                    win++;
                }
            }
            else
            {
                death[at - 1] = competitor[at - 1]->damage(poke[uPoke[0]]->attack(attr[at - 1], def[at - 1]));
                if (death[at - 1] == yes)
                {
                    win++;
                }
            }
            if (win == 2)
            {
                break;
            }
        }

        if (time%sp[3] == 0 && death[3] == no)
        {
            int at = -1;//attack

            if (death[0] == yes)
            {
                at = 2;
            }
            else if (death[1] == yes)
            {
                at = 1;
            }
            else if (poke[uPoke[1]]->atk_kind != 2)
            {
                std::cout << "Please select No.2 pokemon's target pokemon: (1 or 2):\n";
                std::cin >> at;
            }
            if (at == -1)
            {
                death[0] = competitor[0]->damage(poke[uPoke[1]]->attack(attr[0], def[0]));
                death[1] = competitor[1]->damage(poke[uPoke[1]]->attack(attr[1], def[1]));
                if (death[0] == yes)
                {
                    win++;
                }
                if (death[1] == yes)
                {
                    win++;
                }
            }
            else
            {
                death[at - 1] = competitor[at - 1]->damage(poke[uPoke[1]]->attack(attr[at - 1], def[at - 1]));
                if (death[at - 1] == yes)
                {
                    win++;
                }
            }
            if (win == 2)
            {
                break;
            }
        }
        if (time%sp[0] == 0 && death[0] == 0)
        {
            int at = -1;
            if (death[2] == yes)
            {
                at = 1;
            }
            else if (death[3] == yes)
            {
                at = 0;
            }
            else if (competitor[0]->atk_kind != 2)
            {
                at = rand() % 2;
            }

            if (at == -1)
            {
                death[2] = poke[uPoke[0]]->damage(competitor[0]->attack(attr[2], def[2]));
                death[3] = poke[uPoke[1]]->damage(competitor[0]->attack(attr[3], def[3]));
                if (death[2] == yes)
                {
                    lose++;
                }
                if (death[3] == yes)
                {
                    lose++;
                }
            }
            else
            {
                death[at + 2] = poke[uPoke[at]]->damage(competitor[0]->attack(attr[at + 2], def[at + 2]));
                if (death[at + 2] == yes)
                {
                    lose++;
                }
            }
            if (lose == 2)
            {
                break;
            }
        }
        if (time%sp[1] == 0 && death[1] == yes)
        {
            int at = -1;
            if (death[2] == yes)
            {
                at = 1;
            }
            else if (death[3] == yes)
            {
                at = 0;
            }
            else if (competitor[1]->atk_kind != 2)
            {
                at = rand() % 2;
            }
            if (at == -1)
            {
                death[2] = poke[uPoke[0]]->damage(competitor[1]->attack(attr[2], def[2]));
                death[3] = poke[uPoke[1]]->damage(competitor[1]->attack(attr[3], def[3]));
                if (death[2] == yes)
                {
                    lose++;
                }
                if (death[3] == yes)
                {
                    lose++;
                }
            }
            else
            {
                death[at + 2] = poke[uPoke[at]]->damage(competitor[1]->attack(attr[at + 2], def[at + 2]));
                if (death[at + 2] == yes)
                {
                    lose++;
                }
            }
            if (lose == 2)
            {
                break;
            }
        }//end if (time%sp[1] == 0)
    }//end while (win != 2 && lose != 2)

    if (win == 2)
    {
        playNum++;
        winNum++;
        std::cout << "congratulations!\n\n";
    }
    else
    {
        playNum++;
        std::cout << "Sorry!\n\n";
    }

    //calculate experience
    poke[uPoke[0]]->
        promote(poke[uPoke[0]]->
            cal_exp((competitor[0]->level + competitor[1]->level) / 2));
    poke[uPoke[1]]->
        promote(poke[uPoke[1]]->
            cal_exp((competitor[0]->level + competitor[1]->level) / 2));

    //recover
    poke[uPoke[0]]->recover();
    poke[uPoke[1]]->recover();
    //print pokemon info
    poke[uPoke[0]]->print();
    poke[uPoke[1]]->print();

    //release
    delete competitor[0];
    delete competitor[1];
}

//the number of medals
void user::medal()
{
    if (pokemonNum >= 8)
    {
        NumMedal[0] = yes;
        std::cout << "The number of your full level pokemons is larger than 8£¬get a high level medal\n";
    }
    if (pokemonNum >= 6)
    {
        NumMedal[1] = yes;
        std::cout << "The number of your full level pokemons is larger than 6£¬get a mid level medal£¡\n";
    }
    if (pokemonNum >= 4)
    {
        NumMedal[2] = yes;
        std::cout << "The number of your full level pokemons is larger than 4£¬get a low level medal£¡\n";
    }

    int fullLevelNum = no;
    for (int i = 0; i < pokemonNum; i++)
    {
        if (poke[i]->level == maxLevel)
        {
            fullLevelNum++;
        }
    }
    if (fullLevelNum >= 5)
    {
        LevelMedal[0] = yes;
        std::cout << "The number of your full level pokemons is larger than 5£¬get a high level medal£¡\n";
    }
    if (fullLevelNum >= 3)
    {
        LevelMedal[1] = 1;
        std::cout << "The number of your full level pokemons is larger than 3£¬get a mid level medal£¡\n";
    }
    //The number of full level pokemons is larger than 1£¬get low level medal
    if (fullLevelNum >= 1)
    {
        LevelMedal[2] = yes;
        std::cout << "The number of your full level pokemons is larger than 1£¬get a low level medal£¡\n";
    }
}

//terminate
void user::terminate()
{
    char name[msgLength] = { '\0' }; //user name»º³åÇø

                                     //´Óuser classget user name
    for (int i = 0; i < maxLength; i++)
    {
        name[i] = userName[i];
    }
    // send  log out request and user name
    sendMessage(LOGOUT_REQ, name);

    //waiting for response
    while (receiveInfo == WAIT);

    //user logged in
    if (recvBuf[0])
    {
        //clear buffer and locking
        receiveInfo = WAIT;
        clearBuf();
		
		//synchronize info
        synchron();
        std::cout << " log out successfully" << std::endl;
    }
    //clear buffer and locking
    receiveInfo = WAIT;
    clearBuf();


    stop = yes;
}

//synchronize user's win rate and Pokemons info  
void user::synchron()
{
    //update win rate 
    char chWinRate[msgLength] = { '\0' }; // send info

                                          //generate win rate 
    toString(chWinRate, winNum, playNum, 0);

    //send request
    sendMessage(SYNCHROWINRATE, chWinRate);

    //waiting for response
    while (receiveInfo == WAIT);

    //clear buffer and locking
    receiveInfo = WAIT;
    clearBuf();

    for (int i = 0; i < pokemonNum; i++)
    {
        char toStr[msgLength] = { '\0' }; // send info
                                          //generate send info
        toString(toStr, poke[i]->kind, poke[i]->level, poke[i]->exp);

        //send request
        sendMessage(SYNCHRONIZATION, toStr);

        //waiting for response
        while (receiveInfo == WAIT);

        //clear buffer and locking
        receiveInfo = WAIT;
        clearBuf();
    }

    //release user's pokemons
    for (int i = 0; i < pokemonNum; i++)
    {
        delete poke[i];
    }
}
