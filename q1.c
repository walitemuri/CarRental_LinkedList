/* Wali Temuri 1183379 */
#include <stdio.h>
#include <stdbool.h>

typedef struct AvailableRent
{
    int mileage;
    char plate[160];
    struct AvailableRent *next;
}avRent;

typedef struct Rented
{
    int expectedReturn;
    char plate[160];
    int mileage;
    struct Rented *next;
}Rented;

typedef struct Repairing
{
    char plate[160];
    struct Repairing *next;
}Repair;

// Add a new car to the available for rent list (Least miles front of list)
avRent * createRentalCar()
{
    avRent *newCar = malloc(sizeof(avRent));

    printf("Enter plate: ");
    fgets(newCar -> plate , sizeof(newCar -> plate), stdin);

    printf("\nEnter mileage: ");
    scanf("%d", &(newCar -> mileage));

    newCar -> next = NULL;
}

//Add car to the list function (least miles first)
void addCarToRentedList (avRent ** carList , avRent * node)
{
    node -> next = NULL;

    if (*carList == NULL)
    {
        *carList = node;
        return;
    }

    avRent * temp = *carList;
    int key = node -> mileage;

    while(temp -> next != NULL && (temp -> next) -> mileage < key)
    {
        temp = temp -> next;
    }

    node -> next = temp -> next;
    temp -> next = node;

}
// Add a returned car to the available-for-rent list
void addReturnedCar (Rented ** carList, avRent ** rentList)
{
    char *plateInput;
    int mileage;
    bool isValid = false;

    printf("Enter plate: ");
    fgets(plateInput, 150, stdin);

    printf("\nEnter Mileage: ");
    scanf("%d" , &mileage);

    Rented * temp = *carList;

    
    //Fix Error: wrong linked list is transfered, need to make it available for rent not Rented
    while (temp != NULL)
    {
        if (plateInput == temp -> plate)
        {
            rmReturnedCar(temp);
            
            avRent * returnedCar = malloc(sizeof(avRent));

            strcpy(plateInput, returnedCar -> plate);
            returnedCar -> mileage = mileage;

            addCarToRentedList(rentList, returnedCar);
            
            isValid = true;
        }
    }

    if (!isValid)
    {
        printf("Invalid Input\n");
        return;
    }
}
// Add a returned car to the repair list,

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