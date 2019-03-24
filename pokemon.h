#pragma once
#pragma warning (disable : 4996)
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>  
#include <winsock.h>
#include <winbase.h>
#pragma comment (lib,"ws2_32.lib")


const int BUF_SIZE = 64;  //socketsend buffer size
const int maxLength = 14; //user name and password max length
const int msgLength = 63; //sending maximum length
const int SUCCESS = 1;    // request successfully
const int FAILURE = 0;    // fail
const int maxLevel = 15;  // maximum level

const int sucexp = 6; //win Exp 
const int faiexp = 3; //fail Exp coefficient
const int upexp = 7;  // upgrade Exp coefficient

const int atkdenomi = 308;  //attack calculate denominator
const int singlnumer = 350; //single attack pokemons attack coefficient
const int groupnumer = 200; //group attack pokemons attack coefficient

const int atkmod = 20; // pokemons attack range
const int atkrange = 10; // pokemons attack range

const int yes = 1; //yes
const int no = 0;  //no

//user request
const int SIGNUP = 1;			//user sign up
const int LOGIN = 2;			//user log in
const int LOGOUT = 3;			//log out
const int SEARCHONLINEUSER = 4; //query online user 
const int SEARCHPOKEMON = 5;    //query user's pokemons 
const int UPGRADE = 6;			//1v1 upgrading 
const int DUEL = 7;			    //1v1 duel
const int MEDAL = 8;			//medal
const int STOP = 0;			    //stop
const int DOUBLE_UPGRADE = 9;   //2v2 upgrading
const int SEARCHWINRATE = 10;   //query user's win rate

//socket sending lock
const int SEND = 1;
const int RECV = 1;
const int WAIT = 0;

//log in error message
const int PASSWORDERROR = 0; //user password incorrect
const int ONLINE = 1;        //user logged in
const int INEXISTENCE = 2;   //user name doesn't exist 

// server request
const int SIGNUP_NAME = 1;      //send signup user name
const int SIGNUP_PASSWORD = 2;  //send signup password
const int LOGIN_NAME = 3;       //send login user name
const int LOGIN_PASSWORD = 4;   //send login password
const int LOGOUT_REQ = 5;       //request log out 
const int SEARCHUSER_REQ = 6;   //request online user info
const int SEARCHPOKEMON_REQ = 7;//requestuser Pokemons info
const int UPDATE_REQ = 8;       //update local data 
const int SYNCHRONIZATION = 9;  //update server user date
const int WINRATE_REQ = 10;     //query user's win rate 
const int SYNCHROWINRATE = 11;  //update server win rate

//global variable 
extern char sendBuf[BUF_SIZE]; //send buffer
extern char recvBuf[BUF_SIZE]; //receive buffer
extern int sendRequest;		   // send lock 
extern int receiveInfo;		   //reveive lock 
extern int stop;			   //stop
extern int calWinRate;		   //calculating win rate flag

//KIND
const int BULBASAUR = 4;  //bulbasaur 
const int CHARMANDER = 2; //charmander
const int SQUIRTLE = 5;   //Squirtle
const int PIKACHU = 7;    //Pikachu
const int MANKEY = 1;     //Mankey  
const int SNORLAX = 3;    //Snorlax
const int CROBAT = 8;     //Crobat
const int SHUCKLE = 6;    //Schuckle

// pokemons attributes
const int ini_level = 1;     //initial level
const int ini_exp = 0;       //initial Exp
const int ini_crit = 30;     //Critical Hit Chance 
const int ini_dodge = 10;    //Evade Chance 
const double addition = 1.3; //attributes addition
const double crit_dmg = 1.5; //Critical Hit damage
const double recovery = 0.2; //bulbasaur recover


//strength type initial attributes
const int stren_speed = 11; //strength type  pokemons initial speed: 11
//Mankey
const int mankey_atk = 200; //Mankey initial attack : 200
const int mankey_HP = 750;  //Mankey initial HP: 750
const int mankey_def = 42;  //Mankey initial defence: 42
//charmander
const int charmander_atk = 160; //charmander initial attack : 160
const int charmander_HP = 1000; //charmander initial HP: 1000
const int charmander_def = 70;  //charmander initial defence: 70

//tank type initial attributes
const int tank_def = 100;  //tank pokemons initial defence: 100
const int tank_speed = 14; //tank pokemons initial speed: 14
const int tank_dodge = 5;  //tank pokemons initial Evade : 5%
//snorlax 
const int snorlax_atk = 100; //snorlax initial attack : 100
const int snorlax_HP = 1800; //snorlax initial HP: 1800
//bulbasaur
const int bulbasaur_atk = 105; //bulbasaur initial attack : 105
const int bulbasaur_HP = 1500; //bulbasaur initial HP: 1500

//defence type initial attributes
const int defence_dodge = 5; //defence pokemons initial Evade :5%
//Squirtle
const int squirtle_def = 260;  //Squirtle initial defence: 260
const int squirtle_speed = 13; //Squirtle initial speed: 13
const int squirtle_atk = 120;  //Squirtle initial attack : 120
const int squirtle_HP = 1000;  //Squirtle initial HP: 1000
//Schuckle
const int shuckle_def = 310;  //Schuckle initial defence: 310
const int shuckle_speed = 15; //Schuckle initial speed: 15
const int shuckle_atk = 90;   //Schuckle initial attack : 90
const int shuckle_HP = 1000;  //Schuckle initial HP: 1000

//speed type initial attributes
const int quick_atk = 110; //speed pokemons initial attack : 110
const int quick_HP = 700;  //speed pokemons initial HP: 700
const int quick_def = 60;  //speed pokemons initial defence: 60
//Pikachu
const int pikachu_speed = 7; //Pikachuinitial speed: 7
//Crobat
const int crobat_speed = 8; //Crobatinitial speed: 8

// pokemons attack attributes
const int WATER = 1;    //water
const int FIRE = 2;		//fire 
const int GRASS = 3;	//grass 
const int ELECTRIC = 4; //electric 
const int FIGHT = 5;	//fight 
const int NORMAL = 6;	//normal 
const int BUG = 7;		//bug 
const int FLY = 8;		//fly 

//ATK_KIND
const int SINGLE = 1;  //single attack 
const int GROUP = 2;   //group attack 
const int TANK = 3;	   //T

// upgrade attributes rate
const double high_rate = 1.07; //high rate
const double mid_rate = 1.04;  //mid rate
const double low_rate = 1.01;  //low rate

//user class declare
class user;

// pokemons class
class pokemon
{
public:
    pokemon();						//constructor
    ~pokemon();						//destructor
    friend class user;			    //frined
    virtual void promote(int) {};   //upgrade 
    virtual void promoteLevel() {}; //pokemons level
    virtual int attack(int, int) { return 0; }; //virtual method  pokemons attack
    int damage(int);	//damage
    int cal_exp(int);	//calculate Exp
    int getAttr();		//get attack attributes
    int getDef();		//get defence
    int getSpeed();		//get speed
    int getLevel();		//get level
    int getTotalHp();	//get HP
    int getExp();		//get Exp
    int getAtk();		//get attack
    int getCrit();		//get Critical Hit Chance
    int getDodge();		//get Evade Chance
    void setLevel(int);	//set pokemons level
    void print();		//print Pokemons info
    void recover();		// pokemons recover

protected:
    int kind;      //type 
    int atk_attribute; //attributes
    int level;     //level
    int total_HP;  //total HP
    int HP;		   //HP 
    int exp;	   //Exp 
    int def;       //defence 
    int atk;	   //attack 
    int atk_kind;  //attack type 
    int speed;     //speed
    int crit;	   //Critical Hit Chance£¨Critical Hit =150% * attack£© 
    int dodge;	   //Evade Chance
};

/*strength type pokemon*/
class strength :public pokemon
{
public:
    strength();
    ~strength();
    void promote(int);
    void promoteLevel();
};

/*strength type 1:single sttack Mankey*/
class mankey :public strength
{
public:
    mankey();
    ~mankey();
    int attack(int, int); //attack method
};

/*strength type 2:group attack charmander*/
class charmander :public strength
{
public:
    charmander();
    ~charmander();
    int attack(int, int); //attack method
};

/*tank pokemon*/
class tank :public pokemon
{
public:
    tank();
    ~tank();
    void promote(int);
    void promoteLevel();
};

/*¸ßHP1:T Snorlax*/
class snorlax :public tank
{
public:
    snorlax();
    ~snorlax();
    int attack(int, int); //attack method
};

/*¸ßHP2: recover bulbasaur*/
class bulbasaur :public tank
{
public:
    bulbasaur();
    ~bulbasaur();
    int attack(int, int); //attack method
};

/*defence type pokemon*/
class defence :public pokemon
{
public:
    defence();
    ~defence();
    void promote(int);
    void promoteLevel();
};

/*defence1: Squirtle*/
class squirtle :public defence
{
public:
    squirtle();
    ~squirtle();
    int attack(int, int); //attack method
};

/*defence2: Schuckle*/
class shuckle :public defence
{
public:
    shuckle();
    ~shuckle();
    int attack(int, int); //attack method
};


/*speed type pokemon*/
class quick :public pokemon
{
public:
    quick();
    ~quick();
    void promote(int);
    void promoteLevel();
};

/*speed1:Pikachu*/
class pikachu :public quick
{
public:
    pikachu();
    ~pikachu();
    int attack(int, int); //attack method
};

/*speed2:Crobat*/
class crobat :public quick
{
public:
    crobat();
    ~crobat();
    int attack(int, int); //attack method
};

//user class 
class user
{
public:
    user();
    ~user();
    void signUp();  //user sign up 
    void logIn();   //user log in 
    void logOut();	//log out 
    void searchOnlineUser();	//query online user  
    void searchPokemon();		//query user's pokemons  
    void searchWinRate();       //query user's win rate 
    void upgrade();				// upgrade
    void duel();				// duel 
    void medal();				//user medal	
    void upgrade2v2();			//2v2 upgrade
    void terminate();			//stop 
private:
    char userName[maxLength];	//user name
    char password[maxLength];	//password
    pokemon *poke[30];			//user pokemons 
    int pokemonNum;				//pokemons number 
    int NumMedal[3];			//pokemons number medal
    int LevelMedal[3];			//full level pokemons medals
    void synchron();			//server synchronize
    int winNum;					//win
    int playNum;				//
    int fighting(pokemon*, pokemon*); // fighting
};


int client();						        //user socket
void clearBuf();							//clear buffer
void sendMessage(char, char*);				//generate send info
int isCorrectPword(char *);					//is password correct
int isCorrectName(char *);					//is user name correct
void readInfo(char*, int&, int&, int&);		//get Pokemons info
void CalWinRate(pokemon *, int, int);		//calculate  win rate 
double simuFight(pokemon*, pokemon*);		//simulating fight
void toString(char*, int, int, int);		//generate send info
void toChar(int, char*, int&);