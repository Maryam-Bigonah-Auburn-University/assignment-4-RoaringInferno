[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/j-Psd8k7)
# Assignment_4


## Chapter 6
### Exercise 1 (15 points)

Implement a class named GasPump that will be used to model a pump at a gas station. A GasPump object should be able to perform the following tasks:

• Display the amount of gas dispensed

• Display the total amount charged for the amount of gas dispensed

• Set the cost per gallon on gas

• Display the cost per gallon of gas

• Reset the amount of gas dispensed and amount charged before each new usage

• Keep track of the amount of gas dispensed and the total charge

When implementing the GasPump class, you should assume that the gas pump dispenses

.10 gallons of gas per second. Write a test program in main() that prompts the user to enter the cost per gallon of gas and how many seconds they want to pump gas for. Then, display the number of gallons of gas pumped, the cost per gallon of gas, and the total cost of the gas.


### Exercise 2 (15 points)

Create a Temperature class that contains private member variables for degrees in Kelvin, Celsius, and Fahrenheit. Your class should also contain mutator and accessor functions for each of the variables. The mutator function for degrees in Kelvin should receive a double value and use that value to set degrees in Kelvin.
The mutator functions for degrees in Fahrenheit and degrees in Celsius should use the following equations for conversion:

Kelvin = Celsius + 273.15

Celsius = (5.0/9) * (Fahrenheit - 32)

In main(), test the implementation of your class. Prompt the user to enter a temperature in degrees Kelvin, and then use the Temperature class member functions to convert and display the value in degrees Celsius and degrees Fahrenheit.


## Chapter 7

### Exercise 3 (15 points)
Use a class named Player to store the 10 players. Be sure to include a constructor with this class that sets the name and score. Then use a vector of the Player class to store the ten players. Your program should support the following features:

• Add a new player and score (up to ten players).

• Print all player names and their scores to the screen.

• Allow the user to enter a player name and output that player’s score or a message if the player name has not been entered.

• Allow the user to enter a player name and remove the player from the list.

### Exercise 4 (15 points)

Define a class called Month that is an abstract data type for a month. Your class will have one member variable of type int to represent a month (1 for January, 2 for February, and so forth). Include all the following member functions:

• default constructor

• constructor to set month using first 3 letters as 3 arguments

• constructor to set month using int value: 1 for Jan etc.

• input function (from keyboard) that sets month from 1st 3 letters of month name

• input function (from keyboard) that sets month from int value: 1 for Jan etc.

• output function that outputs (to screen) month as 1st 3 letters in the name of the month (C-string?)

• output function that outputs (to screen) month as number, 1 for Jan etc.

• member function that returns the next month as a value of type Month.

int monthNo; // 1 for January, 2 for February etc.


Embed your class definition in a test program.
