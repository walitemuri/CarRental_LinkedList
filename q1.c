/* Wali Temuri 1183379 */
#include <stdio.h>

struct AvailableRent
{
    long int mileage;
    char plate[160];
    struct AvailableRent *next;
};

struct Rented
{
    int expectedReturn;
    char plate[160];
    struct Rented *next;
};

struct Repairing
{
    char plate[160];
    struct Repairing *next;
};

// Add a new car to the available for rent list

// Add a returned car to the available-for-rent list

// Add a returned car to the repair list,

// Transfer a car from the repair list to the available-for-rent list,

// Rent the first available car,

// Print all the lists

// Quit

int main(void)
{

    int x;

    x = scanf("%d", &x);

    do
    {
        //Note to future -- Fix this 
        printf("1");
        printf("2");
        printf("3");
        printf("4");
        printf("5");
        printf("6");
        printf("7");

        switch (x)
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

    } while (x != 7);
}