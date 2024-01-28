//-----------------------------------------------------------------------------
// a1.c
//
// <Explanation of the program ...>
// <... May have multiple lines.>
//
// Author: 12309681
//-----------------------------------------------------------------------------
//

#include <stdio.h>
#include <string.h>

void startMachine(void);
int userInputJuice(void);
int userInputLitres(void);
int userInputCanisterSize(int juice);
int userInputCanisterQuantity(int litres, int canister_size);
void costCalculation(int quantity, int litres, int juice, int canister_size);

int main(void)
{
  printf("Welcome to the juice filling machine calculator!\n");
  startMachine();
  return 0;
}
void startMachine(void)
{
  int juice;
  int litres;
  int canister_size;
  int quantity;

  juice = userInputJuice();
  litres = userInputLitres();
  canister_size = userInputCanisterSize(juice);
  quantity = userInputCanisterQuantity(litres, canister_size);
  costCalculation(quantity, litres - litres % canister_size, juice, canister_size);
}

int userInputJuice(void)
{
  int juice = 0;

  printf("\n"
         "Which juice do you want to fill?\n"
         "1. Orange juice\n"
         "2. Apple juice\n"
         " > ");
  do {
    scanf("%d", &juice);
    if(juice == 1 || juice == 2)
    {
      break;
    }
    else
    {
      printf("Invalid input! Please choose a valid juice.\n");
      while(getchar() != '\n');
    }
  } while (juice == 0);
  return juice;
}

int userInputLitres(void)
{
  int litres = 0;
  do {
    printf("\nHow many litres do you want to fill? (1 to 1000)\n > ");
    scanf("%d", &litres);

    if(litres >= 1 && litres <= 1000)
    {
      break;
    }
    else
    {
      printf("Invalid input! Please choose a valid amount.\n");
      litres = 0;
    }
  } while (litres == 0);
  return litres;
}
 int userInputCanisterSize(int juice)
 {
  int size_in_litres;
  if(juice == 1)
  {
    printf("\n"
           "Which size of canister would you like to use for your orange juice?\n"
           "- 5 litres\n"
           "- 10 litres\n"
           "- 20 litres\n"
           " > ");
  }
  else if (juice == 2)
  {
    printf("\n"
           "Which size of canister would you like to use for your apple juice?\n"
           "- 5 litres\n"
           "- 15 litres\n"
           "- 25 litres\n"
           " > ");
  }

   do
   {
     scanf("%d", &size_in_litres);

     switch (size_in_litres)
     {
       case 5:
         break;
       case 10:
         break;
       case 15:
         break;
       case 20:
         break;
       case 25:
         break;
       default:
         size_in_litres = 0,
         printf("Invalid input! Please choose a valid canister size.\n");
     }

  } while (size_in_litres == 0);
   return size_in_litres;
 }

int userInputCanisterQuantity(int litres, int canister_size)
{
  int quantity = litres / canister_size;

  printf("\nIt is possible to fill %d canisters with the size of %d litres.\n",
         quantity, canister_size);

  printf("This results in %d left-over litres.\n", litres % canister_size);
  return quantity;
}

void costCalculation(int quantity, int litres, int juice, int canister_size)
{
  float canister_cost;
  float juice_cost;
  char juice_type[13] = "orange juice";
  float flat_rate = 5;
  int user_input = 0;

  if(juice == 2)
  {
    strcpy(juice_type, "apple juice");
  }

  switch (canister_size)
  {
    case 5:
      canister_cost = 0.10;
      break;
    case 10:
      canister_cost = 0.15;
      break;
    case 15:
      canister_cost = 0.20;
      break;
    case 20:
      canister_cost = 0.20;
      break;
    case 25:
      canister_cost = 0.25;
      break;
  }

  canister_cost *= quantity;

  switch (juice)
  {
    case 1:
      juice_cost = 0.20;
      break;
    case 2:
      juice_cost = 0.15;
      break;
  }

  juice_cost *= litres;

  float total_cost = flat_rate + canister_cost + juice_cost;

  printf("\n"
         "The filling costs are:\n"
         "----------------------------------------------\n"
         "- %d litres of %s: %.2f €\n"
         "- %d canisters: %.2f €\n"
         "- Flat rate for using the machine: 5.00 €\n"
         "----------------------------------------------\n"
         "This results in a total cost of %.2f €.\n",
         litres, juice_type, juice_cost, quantity, canister_cost, total_cost);

  printf("\n"
         "Are you sure you want to fill the canisters?\n"
         "1. Yes\n"
         "2. No\n"
         " > ");

  do
  {
    scanf("%d", &user_input);
    if(user_input == 1)
    {
      printf("\n"
             "The canisters will be filled as soon as we receive your payment.\n"
             "Thank you for using the juice filling machine calculator!\n");
      break;
    }
    else if (user_input == 2)
    {
      startMachine();
    }
    else
    {
      user_input = 0;
    }
  } while (user_input == 0);
}
