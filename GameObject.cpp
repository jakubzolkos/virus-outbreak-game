#include "GameObject.h"
#include <iostream>
using namespace std;


GameObject::GameObject() : id_num(1), state(0), location(Point2D (0,0)) 
{
    cout << "GameObject default constructed" << endl;
}

GameObject::GameObject(char in_code) : display_code(in_code), id_num(1), state(0), location(Point2D (0,0))
{
    cout << "GameObject constructed" << endl;
}

GameObject::~GameObject() 
{
    cout << "GameObject destructed" << endl;
}

GameObject::GameObject(Point2D in_loc, int in_id, char in_code) 
: location(in_loc), id_num(in_id), display_code(in_code) 
{
    cout << "GameObject constructed" << endl;
}

Point2D GameObject::GetLocation()
{
    return location;
}

int GameObject::GetId()
{
    return id_num;
}

char GameObject::GetCode()
{
    return display_code;
}

char GameObject::GetState()
{
    return state;
}

void GameObject::ShowStatus()
{
    cout << display_code << id_num << " at " << location;
}

void GameObject::DrawSelf(char *ptr)
{
    if (!ShouldBeVisible())
    {
        *ptr = '.';
        *(ptr + 1) = ' ';
    }

    else
    {
        *ptr = display_code;
        *(ptr + 1) = id_num + '0';
    }
}