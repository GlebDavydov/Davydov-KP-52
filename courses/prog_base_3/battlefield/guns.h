#ifndef GUNS_H_INCLUDED
#define GUNS_H_INCLUDED

typedef enum guntype{MELEE, ART, FLAMER, PROJ}guntype;

#define lucky1 0.2 //influences the chance of armor piercing
#define lucky2 0.33 //influences the damage

class Weapon{
    public:
    guntype type;
    float damage; //average
    float radius; //maximal
    int burst; //number of successive strikes
    float accuracy; //the chance of miss = accuracy*log2(distance)
    float pierce; //the percentage of damage guaranteed to pas the armor and chance to deliver additional damage
    //is not affected by distance for artillery and always 1 for flamethrower
    float splash; //the amount of damage distributer over the nearby points
    float apPerStrike;
    float apPerBurst;
    Weapon(guntype type,
        float damage,
        float radius,
        int burst,
        float accuracy,
        float pierce,
        float splash,
        float apPerStrike,
        float apPerBurst){
            this->type = type;
            this->radius = radius;
            this->burst = burst;
            this->accuracy = accuracy;
            this->pierce = pierce;
            this->splash = splash;
            this->apPerStrike = apPerStrike;
            this->apPerBurst = apPerBurst;
        }
};


#endif // GUNS_H_INCLUDED
