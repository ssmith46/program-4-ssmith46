/**
 * Project: Stock Simulator C++ Final Project
 * Author: Sullivan Smith
 * Date: November 26, 2024
 * 
 * File: Simulator.h
 * Purpose: Contains the declaration of the 'Simulator' class.
*/
#ifndef Simulator_H
#define Simulator_H

/*Forward declare class so it will compile.*/
class Simulator;

#include <string>
#include "Trader.h"
#include "Market.h"
#include <vector>
#include "CommandFactory.h"

using namespace std;

/**
 * Purpose:
 * - This class is the heart of the entire project. The simulator will be the way for
 *   a user to interact with the program. It will send user input to the CommandFactory,
 *   and will execute commands that are returned from it, in order to change the simulation
 *   in ways that make sense to user input.
 * - This class will be the one that prints information to the user, and collects input.
 * 
 * Data Members:
 * - Market market -> The Market that is used to manipulate all the stocks of the simulation.
 * - CommandFactory cf -> The CommandFactory used to create commands in the simulation.
 * - vector<Trader*> traders -> A vector containing all the available traders for the simulation.
 * - string simulatorName -> A name for the simulation of the currently running instance.
 * 
 * Member Functions:
 * - Simulator(Market m) -> A constructor for the Simulator class, used to instantiate a Simulator.
 * - void loginScreen() -> A method that will allow the user to login to the Simulator as
 *   a particular Trader. 
 * - void setSimulatorName(string name) -> Sets the name of the currently running simulation.
 * - string getSimulatorName() -> Returns the name of the currently runnning simulation.
 * 
 * Class Usage:
 * - This class is used to house a Stock Simulation command line interface experience. It
 *   houses all of the traders within the simulation, and has access to the Market where all the
 *   Stocks are housed, as well as the CommandFactory, in order to create and execute Commands.
*/
class Simulator {
    public:
        /**
         * The constructor used to instantiate a Simulator object.
         * 
         * @param m -> The market used for manipulating stocks during the simulation.
         */
        Simulator(Market *m);
        /**
         * A method used to set the CommandFactory of the Simulator. 
         * 
         * @param cf -> The command factory used for creating commands during the simulation.
         */
        void setCommandFactory(CommandFactory cf);
        /**
         * The method used to get a user logged in as a particular trader.
         */
        void loginScreen();
        /**
         * A method used to set the name of the simulation run.
         * 
         * @param name -> The name to set the simulation run to.
         */
        void setSimulatorName(string name);
        /**
         * A method used to retreive the name of the simulation run.
         * 
         * @return -> the name of the simulation run.
         */
        string getSimulatorName();
        /**
         * This function is used to get a line of input from the user, and convert
         * it into a command that can then be executed to do what they want. 
         * 
         * @return -> A command that can be used to change the simulation. 
         */
        Command getNextCommand();
    private:
        /*The market used to interact with Stocks during the simulation.*/
        Market *market;
        /*The command factory used to create commands based off of user input.*/
        CommandFactory cf;
        /*A vector that houses all of the potential traders for the simulation.*/
        vector<Trader*> traders;
        /*The name of the currently running simulation.*/
        string simulatorName;
};
#endif
