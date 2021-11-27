#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H
#include "Model.h"
#include "Input_Handling.h"

void DoMoveCommand(Model &model, int student_id, Point2D p1);
void DoMoveToDoctorCommand(Model &model, int student_id, int office_id);
void DoMoveToClassCommand(Model &model, int student_id, int class_id);
void DoStopCommand(Model &model, int student_id);
void DoLearningCommand(Model &model, int student_it, unsigned int assignments);
void DoRecoverInOfficeCommand(Model &model, int student_id, unsigned int vaccine_needs);
void DoGoCommand(Model &model, View &view);
void DoRunCommand(Model &model, View &view);
void NewCommand(Model &model, char code, int id, Point2D location);

#endif