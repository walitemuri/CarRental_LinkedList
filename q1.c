/* Wali Temuri 1183379 */

#include <stdio.h>
#include <stdbool.h>

/*
Data Structure: Linked List
Purpose: List for cars that are available for rent
Stores: Mileage, Car Plate, Address of next node
*/
typedef struct AvailableRent
{
    int mileage;
    char plate[160];
    struct AvailableRent *next;
}avRent;

/*
Data Structure: Linked List
Purpose: List for cars that are currently rented
Stores: Mileage, Car Plate, Expected Return (yymmdd), Address of next node
*/
typedef struct Rented
{
    int expectedReturn;
    char plate[160];
    int mileage;
    struct Rented *next;
}Rented;

/*
Data Structure: Linked List
Purpose: List for cars that are currently under repair
Stores: Car Plate, Address of next node
*/
typedef struct Repairing
{
    char plate[160];
    int mileage;
    struct Repairing *next;
}Repair;

/*
Function: Creates a new rental car node for available rent list
Input: void
Output: avRent *
*/
avRent * createRentalCar()
{
    //Allocating memory for new node
    avRent *newCar = malloc(sizeof(avRent));

    //Gathering Inputs
    printf("Enter plate: ");
    fgets(newCar -> plate , sizeof(newCar -> plate), stdin);

    printf("\nEnter mileage: ");
    scanf("%d", &(newCar -> mileage));

    newCar -> next = NULL;

    return newCar;
}

/*
Function: Adds a rental car to the Available to rent linked list given node
Input: avRent ** carList, avRent * node
Output: void
*/
void addCarToAvRentList (avRent ** carList , avRent * node)
{
    node -> next = NULL;

    //Check for Empty List
    if (*carList == NULL)
    {
        *carList = node;
        return;
    }

    //Declaring key to allow sorting to occur 
    avRent * temp = *carList;
    int key = node -> mileage;

    //Inserting node in its proper order (ascending)
    while(temp -> next != NULL && (temp -> next) -> mileage < key)
    {
        temp = temp -> next;
    }

    node -> next = temp -> next;
    temp -> next = node;

}

/*
Function: Adds a returned car to the Available to rent list
Input: Rented ** carList, avRent ** rentList
Output: void
*/
void addReturnedCarToAv (Rented ** carList, avRent ** rentList)
{
    char *plateInput = (char*)malloc(sizeof(char) * 50);
    int mileage;
    bool isValid = false;

    //Gathering Inputs
    printf("Enter plate: ");
    fgets(plateInput, 150, stdin);

    printf("\nEnter Mileage: ");
    scanf("%d" , &mileage);

    Rented * temp = *carList;

    //Checks for matching plates in input on the rented list
    while (temp != NULL)
    {
        if (strcmp(plateInput, temp -> plate) == 0)
        {
            rmReturnedCar(*carList, plateInput);
            
            avRent * returnedCar = malloc(sizeof(avRent));

            strcpy(plateInput, returnedCar -> plate);
            returnedCar -> mileage = mileage;

            addCarToAvRentList(rentList, returnedCar);
            
            isValid = true;
            free(plateInput);
        }
    }

    if (!isValid)
    {
        printf("Invalid Input\n");
        return;
    }
}

/*
Function: Removes rented car from linked list when it is returend
Input: Rented ** rented, char * plate
Output: void
*/
void rmReturnedCar (Rented ** rented, char * plate)
{
    Rented *temp = *rented;
    int numCars = 0;
    int target = 0;

    while(temp != NULL)
    {
        numCars++;
        temp = temp -> next;
    }

    temp = *rented;


    if (numCars == 1)
    {
        (*rented) = (*rented) -> next;
        free(temp);
        return;
    }
    else
    {
        while (temp != NULL)
        {
            target++;

            if (strcmp(temp -> plate, plate) == 0)
            {
                break;
            }

            temp = temp -> next;

        }

        temp = *rented;

        //Increment to the node before the targetted node
        for (int i = 0; i < target - 1; i++)
        {
            temp = temp -> next;
        }

        Rented * delete = temp -> next;
        temp -> next = temp -> next -> next;
        delete -> next = NULL;
        free(delete);
        free(temp);
    }
}

// Add a returned car to the repair list,
void addReturnedCarToRep (Rented ** currRentedList , Repair ** repairList)
{
    char * plateInput = malloc(sizeof(char)* 50);
    int mileage;

     //Gathering Inputs
    printf("Enter plate: ");
    fgets(plateInput, 150, stdin);

    printf("\nEnter Mileage: ");
    scanf("%d" , &mileage);

    Rented * temp = *currRentedList;

    if (checkValidReturnPlate(temp, plateInput))
    {
        rmReturnedCar(*currRentedList, plateInput);

        Repair * newNode = malloc(sizeof(Repair));

        newNode -> mileage = mileage;

        strcpy(newNode->plate , plateInput);

        addNodeToRepairList(temp, newNode);
    }
    else
    {
        printf("Invalid Input\n");
    }
}

bool checkValidReturnPlate (Rented * currRentedList, char * plate)
{
    Rented * temp = currRentedList;

    while (temp != NULL)
    {
        if (strcmp(plate, temp -> plate) == 0)
        {
            return true;
        }

        temp = temp -> next;
    }

    return false;
}

void addNodeToRepairList (Repair ** repairList, Repair * node)
{
    node -> next = NULL;

    if (*repairList == NULL)
    {
        *repairList = node;
    }

    Repair * temp = *repairList;

    while(temp->next == NULL)
    {
        temp = temp -> next;
    }

    temp->next = node;
}

// Transfer a car from the repair list to the available-for-rent list,

// Rent the first available car,

// Print all the lists

// Quit

int main(void)
{
    int userInput;
    avRent * avPtr = NULL;
    avRent * avHead = NULL;

    do
    {
        // Print Menu
        printf("1 - Add a new car to the available for rent list\n");
        printf("2 - Add a returned car to the available-for-rent list\n");
        printf("3 - Add a returned car to the repair list\n");
        printf("4 - Transfer a car from the repair list to the available-for-rent list\n");
        printf("5 - Rent the first available car\n");
        printf("6 - Print all the lists\n");
        printf("7 - Quit\n");

        userInput = scanf("%d", &userInput);

        switch (userInput)
        {
        case 1:
            printf("");
            break;
        case 2:
            printf("");
            break;
        case 3:
            printf("");
            break;
        case 4:
            printf("");
            break;
        case 5:
            printf("");
            break;
        case 6:
            printf("");
            break;
        case 7:
            printf("");
            break;
        default:
            break;
        }

    } while (userInput != 7);
}