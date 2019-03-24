#include"pokemon.h"
using namespace std;

/*pokemon base class*/
//constructor level1 Exp0 
pokemon::pokemon()
{
    level = ini_level;
    exp = ini_exp;
}
//damage return 0-alive 2-dead
int pokemon::damage(int dmg)
{
    int p;
    p = rand();
    p = p % 100;

    if (calWinRate == no)
    {
        switch (kind)
        {
        case BULBASAUR:  cout << "bulbasaur"; break;
        case CHARMANDER: cout << "charmander"; break;
        case SQUIRTLE:	 cout << "Squirtle"; break;
        case PIKACHU:	 cout << "Pikachu"; break;
        case MANKEY:	 cout << "Mankey"; break;
        case SNORLAX:	 cout << "Snorlax"; break;
        case CROBAT:	 cout << "Crobat"; break;
        case SHUCKLE:	 cout << "Schuckle"; break;
        default:break;
        }
    }
    if (p < dodge)
    {
        dmg = 0;
        if (calWinRate == no)
            cout << "Evade ,";
    }
    else
    {
        if (calWinRate == no)
            cout << "受到了" << dmg << "点damage,";
    }

    //HP -damage
    HP -= dmg;
    //HP 
    if (HP <= 0)
    {
        if (calWinRate == no)
            cout << "死亡\n\n";
        HP = 0;
        //HP=0 return 1
        return yes;
    }
    else if (calWinRate == no)
    {
        cout << "HP: " << HP << "\n\n";
    }
    return no;
}

int pokemon::cal_exp(int opp_level)
{
    if (HP == 0)
    {
        if (calWinRate == no)
        {
            switch (kind)
            {
            case BULBASAUR:  cout << "bulbasaur"; break;
            case CHARMANDER: cout << "charmander"; break;
            case SQUIRTLE:	 cout << "Squirtle"; break;
            case PIKACHU:	 cout << "Pikachu"; break;
            case MANKEY:	 cout << "Mankey"; break;
            case SNORLAX:	 cout << "Snorlax"; break;
            case CROBAT:	 cout << "Crobat"; break;
            case SHUCKLE:	 cout << "Schuckle"; break;
            default:break;
            }
            cout << "+ " << opp_level*(opp_level + faiexp) << " Exp\n";
        }
        return opp_level*(opp_level + faiexp);
    }
    else
    {
        if (calWinRate == no)
        {
            switch (kind)
            {
            case BULBASAUR:  cout << "bulbasaur"; break;
            case CHARMANDER: cout << "charmander"; break;
            case SQUIRTLE:	 cout << "Squirtle"; break;
            case PIKACHU:	 cout << "Pikachu"; break;
            case MANKEY:	 cout << "Mankey"; break;
            case SNORLAX:	 cout << "Snorlax"; break;
            case CROBAT:	 cout << "Crobat"; break;
            case SHUCKLE:	 cout << "Schuckle"; break;
            default:break;
            }
            cout << "+ " << opp_level*(opp_level + sucexp) << " Exp\n";
        }
        return opp_level*(opp_level + sucexp);
    }
}

//get  pokemons attributes 
int pokemon::getAttr()
{
    return atk_attribute;
}
//get pokemons defence
int pokemon::getDef()
{
    return def;
}
//get pokemons speed 
int pokemon::getSpeed()
{
    return speed;
}
//ge pokemons level
int pokemon::getLevel()
{
    return level;
}
//get pokemons HP 
int pokemon::getTotalHp()
{
    return total_HP;
}
//get pokemons Exp
int pokemon::getExp()
{
    return exp;
}
//get pokemons attack 
int pokemon::getAtk()
{
    return atk;
}
//get pokemons Critical Hit
int pokemon::getCrit()
{
    return crit;
}
//get pokemons Evade rate
int pokemon::getDodge()
{
    return dodge;
}

//print Pokemons info 
void pokemon::print()
{
    cout << "Type:";
    switch (kind)
    {
    case BULBASAUR:  cout << "bulbasaur\n"; break;
    case CHARMANDER: cout << "charmander\n"; break;
    case SQUIRTLE:	 cout << "Squirtle\n"; break;
    case PIKACHU:	 cout << "Pikachu\n"; break;
    case MANKEY:	 cout << "Mankey\n"; break;
    case SNORLAX:	 cout << "Snorlax\n"; break;
    case CROBAT:	 cout << "Crobat\n"; break;
    case SHUCKLE:	 cout << "Schuckle\n"; break;
    default:break;
    }
    cout << "level:" << level << endl;
    cout << "HP:" << HP << endl;
    cout << "Exp:" << exp << endl;
    cout << "atk:" << atk << endl;
    cout << "defense:" << def << endl;
    cout << "speed:" << speed << endl;
    cout << "Critical Hit Chance:" << crit << "%" << endl;
    cout << "dodge rate:" << dodge << "%" << endl;
    cout << "\n";
}
// pokemons recover 
void pokemon::recover()
{
    HP = total_HP;
}
//set pokemons level
void pokemon::setLevel(int l)
{
    level = l;
}
//destructor 
pokemon::~pokemon()
{}

//strength constructor 
/*strength type  pokemons : Mankey charmander
speed: 11
Critical Hit Chance: 30%
Evade Chance: 10%*/
strength::strength() :pokemon()
{
    speed = stren_speed;
    crit = ini_crit;
    dodge = ini_dodge;
}
//strength destructor 
strength::~strength()
{}

//strength upgrade 
/* Expexp=level*(level+upexp)  
strength pokemons increasing rate: 
attack and Critical Hit Chance: high rate
HP: middle rate
defence: middle rate
speed、Evade keep the same*/
void strength::promote(int add_exp)
{

    if (level < maxLevel)
    {
        exp += add_exp;
    }
    while (exp >= level*(level + upexp) && level < maxLevel)
    {
        exp = exp - level*(level + upexp);
        level++;
        atk = int(high_rate*atk);
        total_HP = int(mid_rate*total_HP);
        HP = total_HP;
        def = int(low_rate*def);
        crit = int(high_rate*crit);
        // pokemons  upgrade
        if (kind == MANKEY)
        {
            cout << "Congratulations! your Mankey has upgraded!\n";
        }
        else if (kind == CHARMANDER)
        {
            cout << "Congratulations! your charmander has upgraded!\n";
        }

        // pokemons evolves
        if (level == maxLevel)
        {
            
            if (kind == MANKEY)
            {
                cout << "congratulations! Your Mankey is full, evolving into the final form\n";
            }
            else if (kind == CHARMANDER)
            {
                cout << "congratulations!Your charmander is full, evolving into the final form\n";
            }
        }//end of if (level == maxLevel)
    }//end of while (exp >= level*(level + upexp) && level<maxLevel)
    if (level == maxLevel)
    {
        exp = ini_exp;
    }
}

void strength::promoteLevel()
{
    int i;
    for (i = 1; i < level; i++)
    {
        atk = int(high_rate*atk);
        total_HP = int(mid_rate*total_HP);
        def = int(low_rate*def);
        crit = int(high_rate*crit);
    }
    HP = total_HP;
}

//strength: Mankey constructor 
/*Mankey: 
attack : mankey_atk
HP : mankey_HP
defence: mankey_def
attack type: single attack 
attack attributes: fight  type */
mankey::mankey() :strength()
{
    atk = mankey_atk;
    total_HP = mankey_HP;
    HP = mankey_HP;
    def = mankey_def;
    kind = MANKEY;
    atk_kind = SINGLE;
    atk_attribute = FIGHT;
}

//Mankey destructor 
mankey::~mankey()
{}

int mankey::attack(int attri, int opp_def)
{
    //damage
    int atk_n = 0;

    int p = rand() % 100;

    if (calWinRate == no)
    {
        cout << "Mankey";
    }

    //Critical Hit  
    if (p <= crit)
    {
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);
        if (calWinRate == no)
        {
            cout << "Critical Hit \n";
        }
    }
    else
    {
        atk_n = atk * singlnumer / (atkdenomi + opp_def);
        if (calWinRate == no)
        {
            cout << "attack \n";
        }
    }
    if (attri == NORMAL)
    {
        atk_n = int(addition*atk_n);
    }
    else if (attri == FLY || attri == BUG)
    {
        atk_n = int(atk_n / addition);
    }

    p = rand() % atkmod - atkrange;
    atk_n += p;

    //return damage
    return atk_n;
}


//strength: charmander constructor 
/*charmander: 
attack : charmander_atk
HP : charmander_HP
defence: charmander_def
attack type: group attack 
attack attributes: fire  type */
charmander::charmander() :strength()
{
    atk = charmander_atk;
    total_HP = charmander_HP;
    HP = charmander_HP;
    def = charmander_def;
    kind = CHARMANDER;
    atk_kind = GROUP;
    atk_attribute = FIRE;
}
//charmanderdestructor 
charmander::~charmander()
{}
//charmanderattack method 
int charmander::attack(int attri, int opp_def)
{
    //damage
    int atk_n = 0;

    int p = rand() % 100;

    if (calWinRate == no)
        cout << "charmander";

    //Critical Hit  
    if (p <= crit)
    {
        atk_n = int(atk * groupnumer / (atkdenomi + opp_def)*crit_dmg);
        if (calWinRate == no)
        {
            cout << "Critical Hit \n";
        }
    }
    else
    {
        atk_n = atk * groupnumer / (atkdenomi + opp_def);
        if (calWinRate == no)
        {
            cout << "attack \n";
        }
    }
    if (attri == GRASS)
    {
        atk_n = int(addition*atk_n);
    }
    else if (attri == WATER)
    {
        atk_n = int(atk_n / addition);
    }

    p = rand() % atkmod - atkrange;
    atk_n += p;
    return atk_n;
}

//tank type pokemon constructor 
/*tank type  pokemons : Snorlax bulbasaur
defence: tank_def
speed: tank_speed
Critical Hit Chance: 30%
Evade Chance: 5%*/
tank::tank() :pokemon()
{
    def = tank_def;
    speed = tank_speed;
    crit = ini_crit;
    dodge = tank_dodge;
}

//destructor 
tank::~tank()
{}

void tank::promote(int add_exp)
{
    if (level < maxLevel)
    {
        exp += add_exp;
    }
    while (exp >= level*(level + upexp) && level<maxLevel)
    {
        exp = int(exp - level*(level + upexp));
        level++;
        atk = int(low_rate*atk);
        total_HP = int(high_rate*total_HP);
        HP = total_HP;
        def = int(mid_rate*def);
        crit = int(low_rate*crit);
        if (kind == SNORLAX)
        {
            cout << "Congratulations! your Snorlax has upgraded!\n";
        }
        else if (kind == BULBASAUR)
        {
            cout << "Congratulations! your bulbasaur has upgraded!\n";
        }
        if (level == maxLevel)
        {
            if (kind == SNORLAX)
            {
                cout << "Congratulations! Your Snorlax is full, evolving into the final form!\n";
            }
            else if (kind == BULBASAUR)
            {
                cout << "Congratulations! Your bulbasaur is full, evolving into the final form!\n";
            }
        }
    }//end of while (exp >= level*(level + upexp) && level<maxLevel)

    if (level == maxLevel)
    {
        exp = ini_exp;
    }
}

void tank::promoteLevel()
{
    int i;
    for (i = 1; i < level; i++)
    {
        atk = int(low_rate*atk);
        total_HP = int(high_rate*total_HP);
        def = int(mid_rate*def);
        crit = int(low_rate*crit);
    }
    HP = total_HP;
}

//Snorlax constructor 
/*Snorlax: 
attack : snorlax_atk
HP : snorlax_HP
attack type: single attack 
attack attributes: normal  type */
snorlax::snorlax() :tank()
{
    atk = snorlax_atk;
    HP = snorlax_HP;
    total_HP = HP;
    kind = SNORLAX;
    atk_kind = SINGLE;
    atk_attribute = NORMAL;
}
//Snorlax destructor 
snorlax::~snorlax()
{}
int snorlax::attack(int attri, int opp_def)
{
    //damage
    int atk_n;

    int p = rand() % 100;

    if (calWinRate == no)
    {
        cout << "Snorlax";
    }

    //Critical Hit 
    if (p <= crit)
    {
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);
        if (calWinRate == no)
        {
            cout << "Critical Hit \n";
        }
    }
    //normal attack 
    else
    {
        atk_n = atk * singlnumer / (atkdenomi + opp_def);
        if (calWinRate == no)
        {
            cout << "attack \n";
        }
    }

    p = rand() % atkmod - atkrange;
    atk_n += p;

    //return damage
    return atk_n;
}

//bulbasaurconstructor 
/*bulbasaur: 
attack : bulbasaur_atk
HP : bulbasaur_HP
attack type: single attack  attack 时 recoverattack 的20%
attack attributes: grass */
bulbasaur::bulbasaur() :tank()
{
    atk = bulbasaur_atk;
    HP = bulbasaur_HP;
    total_HP = HP;
    kind = BULBASAUR;
    atk_kind = SINGLE;
    atk_attribute = GRASS;
}

//destructor 
bulbasaur::~bulbasaur()
{}

int bulbasaur::attack(int attri, int opp_def)
{
    //damage
    int atk_n;

    int p = rand() % 100;

    if (calWinRate == no)
    {
        cout << "bulbasaur";
    }

    //Critical Hit  
    if (p <= crit)
    {
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);
        if (calWinRate == no)
        {
            cout << "Critical Hit \n";
        }
    }
    //normal attack 
    else
    {
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def));
        if (calWinRate == no)
            cout << "attack \n";
    }

    if (attri == WATER)
    {
        atk_n = int(addition*atk_n);
    }
    else if (attri == FIRE)
    {
        atk_n = int(atk_n / addition);
    }

    p = rand() % atkmod - atkrange;
    atk_n += p;

    HP += int(atk_n*recovery);
    int rec;
    rec = int(atk_n*recovery);
    if (calWinRate == no)
    {
        cout << "bulbasaur + " << rec << " HP\n";
    }

    if (HP>total_HP)
    {
        HP = total_HP;
    }
    //return damage
    return atk_n;
}

//defence type  pokemons  constructor 
/*defence type  pokemons : Squirtle Schuckle
Critical Hit Chance: 30%
Evade Chance: 5%*/
defence::defence()
{
    crit = ini_crit;
    dodge = defence_dodge;
}

//destructor 
defence::~defence()
{}

void defence::promote(int add_exp)
{
    if (level < maxLevel)
    {
        exp += add_exp;
    }
    while (exp >= level*(level + upexp) && level<maxLevel)
    {
        exp = exp - level*(level + upexp);
        level++;
        atk = int(low_rate*atk);
        total_HP = int(mid_rate*total_HP);
        HP = total_HP;
        def = int(high_rate*def);
        crit = int(low_rate*crit);
        dodge = int(high_rate*dodge);
        // pokemons  upgrade 提示
        if (kind == SQUIRTLE)
        {
            cout << "Congratulations! your Squirtle has upgraded!\n";
        }
        else if (kind == SHUCKLE)
        {
            cout << "Congratulations! your Schuckle has upgraded!\n";
        }
        if (level == maxLevel)
        {
            if (kind == SQUIRTLE)
            {
                cout << "Congratulations! Your Squirtle is full, evolving into the final form!\n";
            }
            else if (kind == SHUCKLE)
            {
                cout << "Congratulations! Your Schuckle is full!\n";
            }
        }
    }//end of while (exp >= level*(level + upexp) && level<maxLevel)

    if (level == maxLevel)
    {
        exp = ini_exp;
    }
}

void defence::promoteLevel()
{
    int i;
    for (i = 1; i < level; i++)
    {
        atk = int(mid_rate * atk);
        HP = int(mid_rate * HP);
        def = int(mid_rate * def);
        crit = int(low_rate * crit);
        dodge = int(high_rate * dodge);
    }
    total_HP = HP;
}

//Squirtle constructor 
/*Squirtle: 
attack : squirtle_atk
HP : squirtle_HP
defence: squirtle_def
speed: squirtle_speed
attack type: single attack 
attack attributes: water*/
squirtle::squirtle() :defence()
{
    atk = squirtle_atk;
    HP = squirtle_HP;
    total_HP = HP;
    def = squirtle_def;
    speed = squirtle_speed;
    kind = SQUIRTLE;
    atk_kind = SINGLE;
    atk_attribute = WATER;
}

squirtle::~squirtle()
{}

int squirtle::attack(int attri, int opp_def)
{
    //damage
    int atk_n;
    int p = rand() % 100;

    if (calWinRate == no)
    {
        cout << "Squirtle";
    }

    //Critical Hit  
    if (p <= crit)
    {
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);

        if (calWinRate == no)
        {
            cout << "Critical Hit \n";
        }
    }
    //normal attack 
    else
    {
        atk_n = atk * singlnumer / (atkdenomi + opp_def);
        if (calWinRate == no)
        {
            cout << "attack \n";
        }
    }

    if (attri == FIRE)
    {
        atk_n = int(addition*atk_n);
    }
    else if (attri == GRASS || attri == ELECTRIC)
    {
        atk_n = int(atk_n / addition);
    }

    p = rand() % atkmod - atkrange;
    atk_n += p;

    return atk_n;
}

//Schuckle constructor 
/*Schuckle 
attack : shuckle_atk
HP : shuckle_HP
defence: shuckle_def
speed: shuckle_speed
attack type: single attack 
attack attributes: bug */
shuckle::shuckle() :defence()
{
    atk = shuckle_atk;
    HP = shuckle_HP;
    total_HP = HP;
    def = shuckle_def;
    speed = shuckle_speed;
    kind = SHUCKLE;
    atk_kind = SINGLE;
    atk_attribute = BUG;
}

//Schuckledestructor 
shuckle::~shuckle()
{}

int shuckle::attack(int attri, int opp_def)
{
    //damage
    int atk_n;

    int p = rand() % 100;

    if (!calWinRate)
    {
        cout << "Schuckle";
    }

    //Critical Hit 
    if (p <= crit)
    {
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);

        if (calWinRate == no)
        {
            cout << "Critical Hit \n";
        }
    }
    //normal attack 
    else
    {
        atk_n = atk * singlnumer / (atkdenomi + opp_def);

        if (calWinRate == no)
        {
            cout << "attack \n";
        }
    }
    if (attri == GRASS)
    {
        atk_n = int(addition*atk_n);
    }
    else if (attri == FIRE || attri == FLY || attri == FIGHT)
    {
        atk_n = int(atk_n / addition);
    }

    p = rand() % atkmod - atkrange;
    atk_n += p;

    //return damage
    return atk_n;
}

//speed type  
/*speed type  pokemons : Pikachu Crobat
attack : quick_atk
HP: quick_HP
defence: quick_def
Critical Hit Chance: 30%
Evade Chance: 10%*/
quick::quick() :pokemon()
{
    atk = quick_atk;
    HP = quick_HP;
    total_HP = HP;
    def = quick_def;
    crit = ini_crit;
    dodge = ini_dodge;
}

quick::~quick()
{}

void quick::promote(int add_exp)
{
    if (level < maxLevel)
    {
        exp += add_exp;
    }
    while (exp >= level*(level + upexp) && level<maxLevel)
    {
        exp = (int)exp - level*(level + upexp);
        level++;
        atk = int(mid_rate*atk);
        total_HP = int(low_rate*total_HP);
        HP = total_HP;
        def = int(low_rate*def);
        crit = int(high_rate*crit);
        dodge = int(high_rate*dodge);

        if (kind == PIKACHU)
        {
            cout << "Congratulations! your Pikachu has upgraded!\n";
        }
        else if (kind == CROBAT)
        {
            cout << "Congratulations! your Crobat has upgraded! \n";
        }
        if (level == maxLevel)
        {
            if (kind == PIKACHU)
            {
                cout << "Congratulations! Your Pikachu is full, evolving into the final form!\n";
            }
            else if (kind == CROBAT)
            {
                cout << "Congratulations! Your Crobat is full, evolving into the final form!\n";
            }
        }
    }//end of while (exp >= level*(level + upexp) && level<maxLevel)

    if (level == maxLevel)
    {
        exp = ini_exp;
    }
}

void quick::promoteLevel()
{
    int i;
    for (i = 1; i < level; i++)
    {
        atk = int(mid_rate*atk);
        HP = int(low_rate*HP);
        def = int(low_rate*def);
        crit = int(high_rate*crit);
        dodge = int(high_rate*dodge);
    }
    total_HP = HP;
}

//Pikachuconstructor 
/*Pikachu: 
speed: 7
attack type: single attack 
attack attributes: electric */
pikachu::pikachu() :quick()
{
    speed = pikachu_speed;
    kind = PIKACHU;
    atk_kind = SINGLE;
    atk_attribute = ELECTRIC;
}
pikachu::~pikachu()
{}
int pikachu::attack(int attri, int opp_def)
{
    //damage
    int atk_n;

    int p = rand() % 100;

    if (calWinRate == no)
    {
        cout << "Pikachu";
    }

    //Critical Hit 
    if (p <= crit)
    {
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);

        if (calWinRate == no)
        {
            cout << "Critical Hit \n";
        }
    }
    //normal attack 
    else
    {
        atk_n = atk * singlnumer / (atkdenomi + opp_def);

        if (calWinRate == no)
        {
            cout << "attack \n";
        }
    }
    if (attri == WATER)
    {
        atk_n = int(addition*atk_n);
    }

    p = rand() % atkmod - atkrange;
    atk_n += p;

    //return damage
    return atk_n;
}

//Crobatconstructor 
/*Crobat: 
speed: 8
attack type: single attack 
attack attributes: fly type */
crobat::crobat() :quick()
{
    speed = crobat_speed;
    kind = CROBAT;
    atk_kind = SINGLE;
    atk_attribute = FLY;
}

crobat::~crobat()
{}

int crobat::attack(int attri, int opp_def)
{
    //damage
    int atk_n;

    int p = rand() % 100;

    if (calWinRate == no)
    {
        cout << "Crobat";
    }

    //Critical Hit 
    if (p <= crit)
    {
        atk_n = int(atk * singlnumer / (atkdenomi + opp_def)*crit_dmg);

        if (calWinRate == no)
        {
            cout << "Critical Hit \n";
        }
    }
    //normal attack 
    else
    {
        atk_n = atk * singlnumer / (atkdenomi + opp_def);

        if (calWinRate == no)
        {
            cout << "attack \n";
        }
    }
    if (attri == BUG || attri == FIGHT || attri == GRASS)
    {
        atk_n = int(addition*atk_n);
    }

    p = rand() % atkmod - atkrange;
    atk_n += p;

    //return damage
    return atk_n;
}
