#ifndef INPUT_HANDLING_H
#define INPUT_HANDLING_H
#include <string>
using namespace std;

class Invalid_Input
{
    public:
        string msg_ptr;
        Invalid_Input(string in_ptr) : msg_ptr(in_ptr) {}
    
    private:
        Invalid_Input();
};

#endif