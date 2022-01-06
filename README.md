# Virus Outbreak Terminal Game
Welcome to the game!

## About The Game
The objective of the game is to complete all assignments in the classrooms located around the map before all students lose their antibodies. 


## Newest Changes

### Pharmacy

The pharmacy class introduces a new object to the game that serves as a in-game store. At a pharmacy, a student can buy three consumable items:

- hand sanitizers: reduces the probability of next virus infection by 60%
- mask: reduces the probability of next virus infectino by 100%
- medicine pack: helps with virus recovery by increasing base immunity to the contracted virus by 2.0

### Bus Stop

Bus Stops is another new class in the game that introduces means of fast travel, which is especially convenient when a student is low on antibodies and won't make it to the doctor in time. For a fee, the student can instantly travel to any other bus stop on the map, which are by default located close to classrooms and doctor's offices.

### Map Changes

Because two new static building objects have been introduced to the game, I decided to increase the size of the map to a square of 30x30. Addtionally, I increased the base student antibodies and money to 100 and 30 respectively. Locations of all the objects have been changed to be spread more evenly around the map. Viruses move based on random angle from 0 to 2pi and radius 3 (however, they can't move out of display). 

### Virus Infections

In addition to the loss of antibodies that the student experience every turn, the game now features a virus class which can increase that effect based on the virus' virulence. If the student finds themselves in the proximity of 5 units around a virus and doesn't have any protection items, they will become infected with a virus. The student will lose additional antibodies each turn equal to the formula: ceil(0.3 * virulence). However, with each passing turn, the student builds up immunity to the virus according to the formula: 1/virus_resistance. When the student's immunity reaches the virus' virulence, the virus is eradicated from the game. However, if the student runs out of antibodies while having a virus, the student is eliminated and the virus escapes to the environment again, while gaining energy equal to the difference between the virulence and the hosts immunity. When the virus doesn't have a host, it loses energy every turn according to the formula: -1/pow(virus_resistance, 3). 

