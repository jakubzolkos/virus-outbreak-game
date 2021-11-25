#ifndef CLASSROOM_H
#define CLASSROOM_H
#include "Building.h"

class ClassRoom : public virtual Building
{
    enum ClassRoomStates
    {
        NOT_PASSED = 0,
        PASSED = 1
    };

    private:
        unsigned int num_assignments_remaining;
        unsigned int max_number_of_assignments;
        unsigned int antibody_cost_per_assignment;
        double dollar_cost_per_assignment;
        unsigned int credits_per_assignment;
    
    public:
        ClassRoom();
        virtual ~ClassRoom();
        ClassRoom(unsigned int max_assign, unsigned int antibody_cost, double dollar_cost, unsigned int crd_per_assign, int in_id, Point2D in_loc);
        double GetDollarCost(unsigned int unit_qty);
        unsigned int GetAntibodyCost(unsigned int unit_qty);
        unsigned int GetNumAssignmentsRemaining();
        bool IsAbleToLearn(unsigned int unit_qty, double budget, unsigned int antibodies);
        unsigned int TrainStudents(unsigned int assignment_units);
        virtual bool Update();
        bool Passed();
        void ShowStatus();
};

#endif