#ifndef BOTS_H_INCLUDED
#define BOTS_H_INCLUDED

#define n 64
#define m 64

#define TS 10


typedef enum land_type_s{
    GRSS = 1,
    RUIN,
    WALL
}land;

typedef struct position{
    int x;
    int y;
}position;


typedef enum guntype{MELEE, ART, FLAMER, PROJ}guntype;

typedef enum model{TANK, CHARGER, SEEKER, TROOPER}model;

typedef enum direction{NODIR = 0, N = 1, NE, E, SE, S, SW, W, NW}direction;

enum faction{RED, BLUE};

class Weapon{
private:
    guntype type;
    double damage; //average
    double radius; //maximal
    int burst; //number of successive strikes
    double accuracy; //the chance of miss = accuracy*log2(distance)
    double pierce; //the percentage of damage guaranteed to pas the armor and chance to deliver additional damage
    //is not affected by distance for artillery and always 1 for flamethrower
    double splash; //the amount of damage distributer over the nearby points
    double apPerStrike;
    double apPerBurst;
public:
    Weapon(guntype type,
        double damage,
        double radius,
        int burst,
        double accuracy,
        double pierce,
        double splash,
        double apPerStrike,
        double apPerBurst){
            this->type = type;
            this->damage = damage;
            this->radius = radius;
            this->burst = burst;
            this->accuracy = accuracy;
            this->pierce = pierce;
            this->splash = splash;
            this->apPerStrike = apPerStrike;
            this->apPerBurst = apPerBurst;
        }
};

class battle_robot{
    private:
        int destroyed;
        int maxAp;
        int currAp;
        int hp;
        int maxhp;
        int armor;
        Weapon *gun1;
        Weapon *gun2;
        model rm;
        direction dir;
        position pos;
        int tm;
    public:
        battle_robot(){
            destroyed = 0;
            rm = TROOPER;
            maxAp = 112;
            currAp = 112;
            armor = 12;
            maxhp = 125;
            hp = 125;
            this->gun1 = NULL;
            this->gun2 = NULL;
            dir = S;
            pos.x = 0;
            pos.y = 0;
        }
        battle_robot(Weapon *gun1, Weapon *gun2){
            destroyed = 0;
            rm = TROOPER;
            maxAp = 112;
            currAp = 112;
            armor = 12;
            maxhp = 125;
            hp = 125;
            this->gun1 = gun1;
            this->gun2 = gun2;
            dir = S;
            pos.x = 0;
            pos.y = 0;
        }
        battle_robot(model rm, Weapon *gun1, Weapon *gun2){
            destroyed = 0;
            this->rm = rm;
            this->gun1 = gun1;
            this->gun2 = gun2;
            switch(rm){
            case TANK: //slow but brutal, heavy fire support at any distance
                maxAp = 88;
                armor = 20;
                maxhp = 150;
            break;
            case CHARGER: //fast but unused to long distances
                maxAp = 120;
                armor = 6;
                maxhp = 140;
            break;
            case SEEKER: //performs best at long distances
                maxAp = 104;
                armor = 16;
                maxhp = 100;
            break;
            case TROOPER: //useful in any case
            default:
                maxAp = 112;
                armor = 12;
                maxhp = 125;
            break;
            }
            hp = maxhp;
            currAp = maxAp;
            dir = S;
            pos.x = 0;
            pos.y = 0;
        }
};

#endif // BOTS_H_INCLUDED

