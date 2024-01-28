//-----------------------------------------------------------------------------
// a1.c
//
// This program implements a calculator for a juice filling machine.
// Farmers produce different amounts of various juices, which can be filled into canisters.
// Depending on the user's input, the calculator determines the price for the filling.
//
//-----------------------------------------------------------------------------
//

#include "stdio.h"

//define constants for easy changing prices more easily,sizes later on
const double FLAT_RATE = 5.00;

const int ORANGE = 1;
const int APPLE = 2;

const double ORANGE_JUICE_PRICE = 0.20;
const double APPLE_JUICE_PRICE = 0.15;

const int SIZE_5 = 5;
const int SIZE_10 = 10;
const int SIZE_15 = 15;
const int SIZE_20 = 20;
const int SIZE_25 = 25;
const double COST_5 = 0.10;
const double COST_10 = 0.15;
const double COST_15 = 0.20;
const double  COST_20 = 0.20;
const double COST_25 = 0.25;
const int MIN_LITRES = 1;
const int MAX_LITRES = 1000;
#define INPUT_INVALID "Invalid input! Please choose a valid"



//function prototypes
void startMachine(void);

int userInputJuiceType(void);

int userInputLitres(void);

int userInputCanisterSize(int juice);

int calculateCanisterQuantity(int litres, int canister_size);

int costCalculation(int juice, int quantity, int canister_size);

double calculateCanisterCost(int canister_size, int quantity);

double calculateTotalPrice(double canister_cost, double juice_price);

int getStatusCode(void);

void printWelcomeMsg(void);

void printGoodbyeMsg(void);

void printErrMsg(char error[]);

//-----------------------------------------------------------------------------
///
/// Entry and Exit Point of the Program
/// Has little to no logic
///
/// @param void no values
///
/// @return 0 so that program exits correctly
//
int main(void)
{
  printWelcomeMsg();
  startMachine();
  printGoodbyeMsg();

  return 0;
}

//-----------------------------------------------------------------------------
///
/// Prints Goodbye Message
///
/// @param void no values
///
/// @return void no value
//
void printWelcomeMsg(void)
{
  printf("Welcome to the juice filling machine calculator!\n");
}

//-----------------------------------------------------------------------------
///
/// Prints Welcome Message
///
/// @param void no values
///
/// @return void no value
//
void printGoodbyeMsg(void)
{
  printf("\n"
         "The canisters will be filled as soon as we receive your payment.\n"
         "Thank you for using the juice filling machine calculator!\n");
}


//-----------------------------------------------------------------------------
///
/// Prints passed Error Message
///
/// @param char error[] string that contains the individual error Message
///
/// @return void no value
//
void printErrMsg(char error[])
{
  printf("%s %s\n", INPUT_INVALID, error);
}


//-----------------------------------------------------------------------------
///
/// Start of the filling machine
/// Calls all other functions and manages their return values
///
/// @param void no values
///
/// @return void no value gets returned to main function
//
void startMachine(void)
{
  int end;
  int juice_type;
  int litres;
  int canister_size;
  int quanity;

  do
  {
    juice_type = userInputJuiceType();
    litres = userInputLitres();
    canister_size = userInputCanisterSize(juice_type);
    quanity = calculateCanisterQuantity(litres, canister_size);
    end = costCalculation(juice_type, quanity, canister_size);
  } while (end == 1); //return of costCalculation Function restart or end program
}

//-----------------------------------------------------------------------------
///
/// Asks User to choose between different Juices
/// Reads user input via stdin
///
/// @param void no values
///
/// @return input juice gets returned
//
int userInputJuiceType(void){
  int input = 0;
  int result;
  int ch;

  do
  {
    printf("\n"
           "Which juice do you want to fill?\n"
           "%d. Orange juice\n"
           "%d. Apple juice\n"
           " > ", ORANGE, APPLE);

    fflush(stdout); //Clear stdout buffer
    result = scanf("%d", &input);
    while ((ch = getchar()) != '\n' && ch != EOF); //Clear stdin buffer

    if (result == 0 || (input != ORANGE && input != APPLE))
    {
      printErrMsg("juice.");
    }

  }while (input != ORANGE && input != APPLE);

  return input;
}

//-----------------------------------------------------------------------------
///
/// Asks User to choose the desired liters from 1 - 1000
/// Reads user input via stdin
///
/// @param void no values
///
/// @return input liters get returned
//
int userInputLitres(void)
{
  int input = 0;
  int result;
  int ch;

  do
  {
    printf("\n"
           "How many litres do you want to fill? (%d to %d)\n"
           " > ", MIN_LITRES, MAX_LITRES);

    fflush(stdout);
    result = scanf("%d", &input);
    while ((ch = getchar()) != '\n' && ch != EOF);

    if (result == 0 || (input < MIN_LITRES || input > MAX_LITRES))
    {
      printErrMsg("amount.");
    }

  } while (input < MIN_LITRES || input > MAX_LITRES);

  return input;
}

//-----------------------------------------------------------------------------
///
/// Asks User to choose between different canister sizes
/// Checks which juice got chosen prior to adapt the canister sizes
/// Reads user input via stdin
///
/// @param juice prior chosen
///
/// @return input canister size gets returned
//
int userInputCanisterSize(int juice)
{
  int input = 0;
  int result;
  int ch;

  if (juice == ORANGE)
  {
    do
    {
      printf("\n"
             "Which size of canister would you like to use for your orange juice?\n"
             "- %d litres\n"
             "- %d litres\n"
             "- %d litres\n"
             " > ", SIZE_5, SIZE_10, SIZE_20);

      fflush(stdout);
      result = scanf("%d", &input);
      while ((ch = getchar()) != '\n' && ch != EOF);

      if (result == 0 || (input != SIZE_5 && input != SIZE_10 && input != SIZE_20))
      {
        printErrMsg("canister size.");
      }

    } while (input != SIZE_5 && input != SIZE_10 && input != SIZE_20);
  }
  else
  {
    do
    {
      if (juice == APPLE)
      {
        printf("\n"
               "Which size of canister would you like to use for your apple juice?\n"
               "- %d litres\n"
               "- %d litres\n"
               "- %d litres\n"
               " > ", SIZE_5, SIZE_15, SIZE_25);
        fflush(stdout);
      }

      result = scanf("%d", &input);
      while ((ch = getchar()) != '\n' && ch != EOF);

      if (result == 0 || (input != SIZE_5 && input != SIZE_15 && input != SIZE_25))
      {
        printErrMsg("canister size.");
      }

    } while (input != SIZE_5 && input != SIZE_15 && input != SIZE_25);
  }

  return input;
}

//-----------------------------------------------------------------------------
///
/// Calculates how much canisters can be filled.
/// Calculates also the left-over liters.
///
/// @param liter desired liters chosen prior
/// @param canister_size chosen prior
///
/// @return quantity amount of canisters that can be filled
//
int calculateCanisterQuantity(int litres, int canister_size)
{
  int quantity = litres / canister_size;

  printf("\n"
         "It is possible to fill %d canisters with the size of %d litres."
         "\n", quantity, canister_size);
  printf("This results in %d left-over litres.\n", litres % canister_size);

  return quantity;
}

//-----------------------------------------------------------------------------
///
/// Calls function to calculate end price
/// Prints these prices
///
/// @param juice chosen prior
/// @param quantity chosen prior
/// @param canister_size chosen prior
///
/// @return confirmation to end program or to start over again
//
int costCalculation(int juice, int quantity, int canister_size)
{
  double juice_price;
  double canister_cost;
  double total_cost;

  canister_cost = calculateCanisterCost(canister_size, quantity);


  printf("\n"
         "The filling costs are:\n"
         "----------------------------------------------\n");
  if(juice == 1)
  {
    juice_price = quantity * canister_size * ORANGE_JUICE_PRICE;
    printf("- %d litres of orange juice: %.2lf €\n", quantity * canister_size, juice_price);
  }
  else
  {
    juice_price = quantity * canister_size * APPLE_JUICE_PRICE;
    printf("- %d litres of apple juice: %.2lf €\n", quantity * canister_size, juice_price);
  }

  total_cost = calculateTotalPrice(canister_cost, juice_price);

  printf("- %d canisters: %.2lf €\n"
         "- Flat rate for using the machine: %.2lf €\n"
         "----------------------------------------------\n"
         "This results in a total cost of %.2lf €.\n",
         quantity, canister_cost, FLAT_RATE, total_cost);

  return getStatusCode();
}

//-----------------------------------------------------------------------------
///
/// Asks User whether he want to complete the transaction or start over again
///
/// @param void no values
///
/// @return status_code
//
int getStatusCode(void)
{
  int input;
  int result;
  int ch;

  do{
    printf("\n"
           "Are you sure you want to fill the canisters?\n"
           "1. Yes\n"
           "2. No\n"
           " > ");

    fflush(stdout);
    result = scanf("%d", &input);
    while ((ch = getchar()) != '\n' && ch != EOF);

    if(result == 0 || (input != 1 && input != 2))
    {
      printErrMsg("option.");
    }
    else if (input == 1)
    {
      return 0; //End Program
    }
    else if (input == 2)
    {
      return 1; //Start over again
    }
  } while (input != 1 && input != 2);

  return 0;
}

//-----------------------------------------------------------------------------
///
/// Calculates the total price
///
/// @param canister_size chosen prior
/// @param juice_price calculated prior
///
/// @return total_price
//
double calculateTotalPrice(double canister_cost, double juice_price)
{
  return canister_cost + juice_price + FLAT_RATE;
}

//-----------------------------------------------------------------------------
///
/// Calculates the cost per canister
///
/// @param canister_size chosen prior
/// @param quantity calculated prior
///
/// @return cost per canister
//
double calculateCanisterCost(int canister_size, int quantity)
{
  switch (canister_size)
  {
    case 5:
      return quantity * COST_5;
    case 10:
      return quantity * COST_10;
    case 15: //consolidate these cases as same output
    case 20:
      return quantity * COST_15;
    case 25:
      return quantity * COST_25;
    default:
      return 0;
  }
}
