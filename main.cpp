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
#include <vector>
#include <cstring>
using namespace std;

// Function for tokenizing a string based on a specified delimeter
void tokenize(string const &str, const char* delim, vector<string> &out) 
{ 
    char *token = strtok(const_cast<char*>(str.c_str()), delim); 
    while (token != NULL) 
    { 
        out.push_back(string(token)); 
        token = strtok(NULL, delim); 
    } 
} 


int main()
{
    srand(time(NULL));

    Model model;
    View v;
    Point2D location;
    string line;

    cout << endl;
    model.ShowStatus();
    model.Display(v);

    do
    {
        cout << endl << "Enter command: ";
        line.clear();
        try 
        {
            // Get a command string and tokenize it with space delimeter
            getline(cin, line, '\n');
            vector<string> params;
            tokenize(line, " ", params); 

            // If the length of the command code is greater than 1, throw exception
            if (params[0].length() > 1)
                throw Invalid_Input("Invalid command code");


            switch(params[0][0])
            {
                case 'q':
                    if (params.size() != 1)
                        throw Invalid_Input("Expected no parameters");

                    cout << endl << "Program terminated" << endl << endl;
                    return 0;
                
                case 'g':
                    if (params.size() != 1)
                        throw Invalid_Input("Expected no parameters");

                    DoGoCommand(model, v);
                    break;
                
                case 'r':
                    if (params.size() != 1)
                        throw Invalid_Input("Expected no parameters");

                    DoRunCommand(model, v);
                    break;
                
                case 'n':
                {
                    cout << endl;
                    if (params.size() != 5)
                        throw Invalid_Input("Expected a char, an integer and xy-coordinate parameters");

                    NewCommand(model, params[1][0], stoi(params[2]), Point2D(stod(params[3]), stod(params[4])));
                    cout << endl;
                    v.Draw();
                    break;
                }

                case 'm':
                {
                    cout << endl;
                    if (params.size() != 4)
                        throw Invalid_Input("Expected an integer and xy-coordinate parameters");

                    DoMoveCommand(model, stoi(params[1]), Point2D(stod(params[2]), stod(params[3])));
                    cout << endl;
                    v.Draw();
                    break;
                }

                case 'd':
                {
                    cout << endl;
                    if (params.size() != 3)
                        throw Invalid_Input("Expected two integer parameters");

                    DoMoveToDoctorCommand(model, stoi(params[1]), stoi(params[2]));
                    cout << endl;
                    v.Draw();
                    break;
                }

                case 'c':
                {
                    cout << endl;
                    if (params.size() != 3)
                        throw Invalid_Input("Expected two integer parameters");

                    DoMoveToClassCommand(model, stoi(params[1]), stoi(params[2]));
                    cout << endl;
                    v.Draw();
                    break;
                }

                case 'h':
                {
                    cout << endl;
                    if (params.size() != 3)
                        throw Invalid_Input("Expected two integer parameters");

                    DoMoveToPharmacyCommand(model, stoi(params[1]), stoi(params[2]));
                    cout << endl;
                    v.Draw();
                    break;
                }

                case 's':
                    cout << endl;
                    if (params.size() != 2)
                        throw Invalid_Input("Expected one integer parameter");

                    DoStopCommand(model, stoi(params[1]));
                    cout << endl;
                    v.Draw();
                    break;
                
                case 'v':
                {
                    cout << endl;
                    if (params.size() != 3)
                        throw Invalid_Input("Expected two integer parameters");

                    DoRecoverInOfficeCommand(model, stoi(params[1]), stoi(params[2]));
                    v.Draw();
                    break;
                }

                case 'a':
                {
                    cout << endl;
                    if (params.size() != 3)
                        throw Invalid_Input("Expected two integer parameters");

                    DoLearningCommand(model, stoi(params[1]), stoi(params[2]));
                    v.Draw();
                    break;
                }

                case 'p':
                {
                    cout << endl;
                    if (params.size() != 4)
                        throw Invalid_Input("Expected two integer parameters and one char parameter");

                    DoPurchaseItemsCommand(model, stoi(params[1]), params[2][0], stoi(params[3]));
                    v.Draw();
                    break;
                }

                default:
                    throw Invalid_Input("Ivalid input. Please try again.");
            } 
        }

        catch (Invalid_Input &except)
        {
            cout << "Invalid input - " << except.msg_ptr << endl;
        }

        catch (invalid_argument &ia)
        {
            cout << "Invalid input - invalid argument types" << endl;
        }


    } while (true);
    return 0;
}
    