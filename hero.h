#ifndef HERO_H
#define HERO_H

#include <QString>

class Hero
{
public:
    Hero();

    int id;
    QString name;
    int age;

    int race_id;
    int class_id;
    int perk1_id;
    int perk2_id;
    int perk3_id;

    int strength;
    int agility;
    int dexterity;
    int intelligence;

    bool update;

private:




};

#endif // HERO_H
