#include "Point2D.h"
#include "Vector2D.h"
#include "DoctorsOffice.h"
#include "ClassRoom.h"
#include "Student.h"
#include "Model.h"
#include "View.h"
#include "GameCommand.h"
#include "Input_Handling.h"
#include <sstream>
using namespace std;


int main()
{
    char code;
    int student_id, object_id;
    string line;

    srand(time(NULL));
    Model model;
    View v;
    Point2D location;

    cout << endl;
    
    model.ShowStatus();
    model.Display(v);

    do
    {
        cout << endl << "Enter command: ";
        line.clear();
        try 
        {
            getline(cin, line, '\n');
            istringstream iss(line);
            code = line[0];
            
        
            switch(code)
            {
                case 'q':
                    cout << endl << "Program terminated" << endl << endl;
                    return 0;
                
                case 'g':
                    DoGoCommand(model, v);
                    break;
                
                case 'r':
                    DoRunCommand(model, v);
                    break;
                
                case 'n':
                    iss >> code >> object_id >> location.x >> location.y;
                    cout << endl;
                    try
                    {
                        switch (code)
                        {
                            case 'd':
                                
                                break;
                        }
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }
                    
                    break;
                
                case 'm':
                {
                    iss >> code >> student_id >> location.x >> location.y;
                    cout << endl;
                    DoMoveCommand(model, student_id, location);
                    cout << endl;
                    v.Draw();
                    break;
                }

                case 'd':
                {
                    int office_id;
                    iss >> code >> student_id >> office_id;
                    cout << endl;
                    DoMoveToDoctorCommand(model, student_id, office_id);
                    cout << endl;
                    v.Draw();
                    break;
                }

                case 'c':
                {
                    int classroom_id;
                    iss >> code >> student_id >> classroom_id;
                    cout << endl;
                    DoMoveToClassCommand(model, student_id, classroom_id);
                    cout << endl;
                    v.Draw();
                    break;
                }

                case 's':
                    iss >> code >> student_id;
                    cout << endl;
                    DoStopCommand(model, student_id);
                    cout << endl;
                    v.Draw();
                    break;
                
                case 'v':
                {
                    int vaccine_amount;
                    iss >> code >> student_id >> vaccine_amount; 
                    cout << endl;
                    DoRecoverInOfficeCommand(model, student_id, vaccine_amount);
                    v.Draw();
                    break;
                }

                case 'a':
                {
                    int assignment_amount;
                    iss >> code >> student_id >> assignment_amount;
                    cout << endl;
                    DoLearningCommand(model, student_id, assignment_amount);
                    v.Draw();
                    break;
                }

                default:
                    cout << "Ivalid input. Please try again." << endl;
            } 
        }

        catch (Invalid_Input& except)
        {
            cout << "Invalid input - " << except.msg_ptr << endl;
        }

    } while (true);
    return 0;
}
    