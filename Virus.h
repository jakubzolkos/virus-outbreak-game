#ifndef VIRUS_H
#define VIRUS_H
#include "Student.h"
#include "View.h"
using namespace std;

class Virus : public GameObject
{
    enum VirusStates
    {
        IN_ENVIRONMENT = 0,
        DEAD = 1,
        IN_STUDENT = 2
    };
    
    protected:
        double virulence = 5;
        double infection_treshold = 2;
        double resistance = 2;
        bool variant = false;
        double energy = 10;
        bool is_in_student = false;
        string name;
        Student *current_student = NULL;
    
    public:
        Virus(string name, int id, Point2D in_loc);
        Virus(string name, double virulence, double resistance, double energy, bool variant, int id, Point2D in_loc);
        virtual ~Virus();
        void infect(Student *s);
        void destroy_self();
        bool get_variant();
        double get_virulence();
        double get_resistance();
        double get_energy();
        bool get_in_student();
        string get_name();
        virtual bool Update();
        void ShowStatus();
        bool IsAlive();
        bool ShouldBeVisible();
        bool UpdateLocation();
};

#endif