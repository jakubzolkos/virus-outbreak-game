#ifndef BUILDING_H
#define BUILDING_H
#include "GameObject.h"

class Building : public GameObject
{
    private:
        unsigned int student_count = 0;
    
    public:
        Building();
        virtual ~Building();
        Building(char in_code, int in_id, Point2D in_loc);
        void AddOneStudent();
        void RemoveOneStudent();
        void ShowStatus();
        bool ShouldBeVisible();        
};

#endif