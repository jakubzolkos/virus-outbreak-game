#include <iostream>
#include <string>
#include "Building.h"


Building::Building() : GameObject('B') 
{
    cout << "Building default constructed" << endl;
}

Building::~Building() 
{
    cout << "Building destructed" << endl;
}

Building::Building(char in_code, int in_id, Point2D in_loc) : GameObject(in_loc, in_id, in_code) 
{
    cout << "Building constructed" << endl;
}

void Building::AddOneStudent()
{
    student_count++;
}

void Building::RemoveOneStudent()
{
    student_count--;
}

void Building::ShowStatus()
{
    string verb, ending;
    cout << display_code << id_num << " located at " << location << endl;
    
    if (student_count == 1)
    {
        verb = "is";
        ending = "";
    }
    else
    {
        verb = "are";
        ending = "s";
    }

    cout << "\t" << student_count << " student" << ending << " " << verb << " in this building." << endl;
}

bool Building::ShouldBeVisible()
{
    return true;
}