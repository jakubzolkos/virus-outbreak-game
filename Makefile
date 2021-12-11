CC = g++ -g

OBJS = main.o Building.o Point2D.o Vector2D.o GameObject.o GameCommand.o DoctorsOffice.o Model.o Student.o ClassRoom.o View.o Pharmacy.o Bus.o Virus.o

default: PA4

PA4: $(OBJS)
	$(CC) -o PA4 $(OBJS) 

Vector2D.o: Vector2D.cpp Vector2D.h
	$(CC) -c Vector2D.cpp -o Vector2D.o 
	
Point2D.o: Point2D.cpp Point2D.h Vector2D.h
	$(CC) -c Point2D.cpp -o Point2D.o 

Building.o: Building.cpp Building.h
	$(CC) -c Building.cpp -o Building.o

GameObject.o: GameObject.cpp GameObject.h Point2D.h Vector2D.h
	$(CC) -c GameObject.cpp -o GameObject.o 

Bus.o: Bus.cpp Bus.h GameObject.h Point2D.h Vector2D.h Building.h
	$(CC) -c Bus.cpp -o Bus.o

DoctorsOffice.o: DoctorsOffice.cpp DoctorsOffice.h GameObject.h Point2D.h
	$(CC) -c DoctorsOffice.cpp -o DoctorsOffice.o

Model.o: Model.cpp Model.h GameObject.h Student.h ClassRoom.h DoctorsOffice.h View.h Virus.h Pharmacy.h 
	$(CC) -c Model.cpp -o Model.o 

Pharmacy.o: Pharmacy.cpp Pharmacy.h GameObject.h
	$(CC) -c Pharmacy.cpp -o Pharmacy.o

ClassRoom.o: ClassRoom.cpp ClassRoom.h GameObject.h Point2D.h
	$(CC) -c ClassRoom.cpp -o ClassRoom.o

View.o: View.cpp View.h GameObject.h Point2D.h
	$(CC) -c View.cpp -o View.o 

Virus.o: Virus.cpp Virus.h Student.h View.h
	$(CC) -c Virus.cpp -o Virus.o

Student.o: Student.cpp Student.h GameObject.h Point2D.h Vector2D.h DoctorsOffice.h ClassRoom.h Virus.h Pharmacy.h
	$(CC) -c Student.cpp -o Student.o

GameCommand.o: GameCommand.cpp GameCommand.h Model.h Input_Handling.h
	$(CC) -c GameCommand.cpp -o GameCommand.o

main.o: main.cpp Building.h Point2D.h Vector2D.h GameCommand.h DoctorsOffice.h Model.h Student.h ClassRoom.h GameObject.h View.h Virus.h Pharmacy.h Bus.h Input_Handling.h
	$(CC) -c main.cpp -o main.o
	
clean: 
	rm $(OBJS) PA4 *.out