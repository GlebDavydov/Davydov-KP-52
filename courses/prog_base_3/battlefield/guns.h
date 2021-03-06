#ifndef GUNS_H_INCLUDED
#define GUNS_H_INCLUDED

typedef enum guntype{MELEE, ART, FLAMER, PROJ}guntype;

#define lucky1 0.2 //influences the chance of armor piercing
#define lucky2 0.33 //influences the damage

class Weapon{
    public:
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


#endif // GUNS_H_INCLUDED
