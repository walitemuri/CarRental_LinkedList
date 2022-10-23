/* Wali Temuri 1183379 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
Data Structure: Linked List
Purpose: List for cars that are available for rent
Stores: Mileage, Car Plate, Address of next node
*/
typedef struct AvailableRent
{
    int mileage;
    char plate [150];
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
    char plate[150];
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
    char * plate;
    int mileage;
    struct Repairing *next;
}Repair;

avRent * createRentalCar();
void addCarToAvRentList (avRent ** carList , avRent * node);
void addReturnedCarToAv (Rented ** carList, avRent ** rentList);
void rmReturnedCar (Rented ** rented, char * plate);
void addReturnedCarToRep (Rented ** currRentedList , Repair ** repairList);
bool checkValidReturnPlate (Rented * currRentedList, char * plate);
void addNodeToRepairList (Repair ** repairList, Repair * node);
void transferRepairedCar (Repair ** repairList, avRent ** avRentList);
int rmRepairedCar (char * plateInput, Repair ** repairList);
bool checkValidRepairedPlate (char *plateInput, Repair * repairList, int * carIndex);
void deleteHeadAv (avRent ** avRentList);
void addCarToRentList (Rented ** rentList, avRent ** avRentList);
bool isEarlier (int expR1 , int expR2);
void addNodeToRentList (Rented ** rentList, Rented * node);
int getYear(int n);
int getMonth(int n);
int getDay(int n);

void saveRepairListToFile (Repair * repairList);
void saveAvRentListToFile (avRent * avList);
void saveRentedListToFile (Rented * rentList);

void loadAv (avRent ** avRentList);
void loadRented (Rented ** avRentList);
void loadRepair (Repair ** avRentList);

int main(void)
{
    int userInput;
    char str_i[20];

    avRent * avPtr = NULL;
    avRent * avHead = NULL;

 //   Rented * rentPtr = NULL;
    Rented * rentHead = NULL;

   // Repair * repairPtr = NULL;
    Repair * repairHead = NULL;

    //loadAv(&avHead);
    //loadRented(&rentHead);
    //loadRepair(&repairHead);
    

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

        fgets(str_i, 20, stdin);
        userInput = strtol(str_i, NULL, 0);

        if (userInput == 1)
        {
            if (avHead == NULL)
               {
                   avHead = createRentalCar(avHead);
               }
               else
               {
                   avPtr = createRentalCar(avPtr);
                   addCarToAvRentList(&avHead, avPtr);
               }
        }

        switch (userInput)
        {
            case 2:
                addReturnedCarToAv(&rentHead, &avHead);
                break;
            case 3:
                addReturnedCarToRep(&rentHead, &repairHead);
                break;
            case 4:
                transferRepairedCar(&repairHead, &avHead);
                break;
            case 5:
                addCarToRentList(&rentHead, &avHead);
                break;
            case 6:
            printf("%s", avHead->plate);
                break;
            case 7:
                saveAvRentListToFile(avHead);
                saveRentedListToFile(rentHead);
                saveRepairListToFile(repairHead);
                break;
            default:
                break;
        }
                
    } while(userInput != 7); 
}

/*
Function: Creates a new rental car node for available rent list
Input: void
Output: avRent *
*/
avRent * createRentalCar()
{
    //Allocating memory for new node
    avRent *newCar = malloc(sizeof(avRent));
    int mileage = 0;

    //Gathering Inputs
    printf("Enter plate: ");
    scanf("%s" , newCar->plate);
    newCar -> plate[strcspn(newCar -> plate, "\n")] = 0;

    printf("\nEnter mileage: ");
    scanf(" %d", &mileage);

    newCar->mileage = mileage;

    newCar -> next = NULL;

    return newCar;
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
    plateInput[strcspn(plateInput, "\n")] = 0;


    printf("\nEnter Mileage: ");
    scanf(" %d" , &mileage);

    Rented * temp = *carList;

    //Checks for matching plates in input on the rented list
    while (temp != NULL)
    {
        if (strcmp(plateInput, temp -> plate) == 0)
        {
            rmReturnedCar(&(*carList), plateInput);
            
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
    plateInput[strcspn(plateInput, "\n")] = 0;
    
    printf("\nEnter Mileage: ");
    scanf(" %d" , &mileage);

    Rented * temp = *currRentedList;

    if (checkValidReturnPlate(temp, plateInput))
    {
        rmReturnedCar(&(*currRentedList), plateInput);

        Repair * newNode = malloc(sizeof(Repair));

        newNode -> mileage = mileage;

        strcpy(newNode->plate , plateInput);

        addNodeToRepairList(&(*repairList), newNode);
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
void transferRepairedCar (Repair ** repairList, avRent ** avRentList)
{
    char* plateInput = malloc(sizeof(char) * 50);

    printf("Enter plate: ");
    fgets(plateInput, 150, stdin);

    plateInput[strcspn(plateInput, "\n")] = 0;


    printf("\n");

    int carMileage = rmRepairedCar(plateInput, &(*repairList));

    if (carMileage != -1)
    {
        avRent * newNode = malloc(sizeof(avRent));

        newNode->mileage = carMileage;
        strcpy(newNode->plate, plateInput);
        newNode->next  = NULL;

        addCarToAvRentList(&(*avRentList), newNode);
        return;
    }
    else
    {
        printf("Error\n");
        return;
    }

}

//rm node from repair list 
int rmRepairedCar (char * plateInput, Repair ** repairList)
{
    Repair * temp = *repairList;
    int carCount = 0;
    int carIndex;

    while (temp != NULL)
    {
        carCount++;
        temp = temp -> next;
    }

    temp = *repairList;

    if (carCount == 0)
    {
        printf("There are currently no Cars in repair.\n");
    }
    else if (carCount == 1)
    {
        if (checkValidRepairedPlate(plateInput, temp, &carIndex))
        {
            return temp->mileage;
            (*repairList) = (*repairList) -> next;
            free(temp);
        }
        else
        {
            printf("Invalid Input\n");
        }
    }
    else
    {
        bool validInput = checkValidRepairedPlate(plateInput, temp, &carIndex);

        if(validInput && carIndex == 1)
        {
            (*repairList) = (*repairList)->next;
            free(temp);
        }
        else if(validInput)
        {
            for (int i = 1; i < carIndex - 1; i++)
            {
                temp = temp->next;
            }

            Repair * delete = temp->next;
            temp->next = temp->next->next;
            delete->next = NULL;
            int miles = delete->mileage;
            free(delete);
            return miles;
        }
        else
        {
            printf("Invalid Input\n");
            return -1;
        }
    }

    return -1;

}

bool checkValidRepairedPlate (char *plateInput, Repair * repairList, int * carIndex)
{
    Repair * temp = repairList; 
    *carIndex = 0;

    while (temp != NULL)
    {
        ++(*carIndex);
        if (strcmp (temp->plate, plateInput) == 0)
        {
            return true;
        }

        temp = temp->next;
    }

    return false;
}

void deleteHeadAv (avRent ** avRentList)
{
    if (*avRentList == NULL)
    {
        return;
    }

    (*avRentList) = (*avRentList)->next;
    
}

void addCarToRentList (Rented ** rentList, avRent ** avRentList)
{
    int expectReturn;
    Rented * node = malloc(sizeof(Rented));
    node->next = NULL;
    printf("Enter Expected Return Date (yymmdd): ");
    scanf(" %d", &expectReturn);

    avRent * avList = *avRentList;

    node->mileage = avList->mileage;
    strcpy(node->plate , avList->plate);
    node->expectedReturn = expectReturn;

    deleteHeadAv(avRentList);

    if (*rentList == NULL) 
    {
        *rentList = node;    
    }

    Rented * temp = *rentList;

    while(temp -> next != NULL && isEarlier((temp -> next) -> expectedReturn, node->expectedReturn))
    {
        temp = temp -> next;
    }

    node -> next = temp-> next;
    temp->next = node;

}

bool isEarlier (int expR1 , int expR2) 
{
    int y1 = getYear(expR1);
    int m1 = getMonth(expR1);
    int d1 = getDay(expR1);

    int y2 = getYear(expR2);
    int m2 = getMonth(expR2);
    int d2 = getDay(expR2);

    if (y1 > y2)
    {
        return false;
    }
    else if (y1 == y2)
    {
        if (m1 > m2)
        {
            return false;
        }
        else if (m1 == m2)
        {
            if (d1 > d2)
            {
                return false;
            }
            else if (d1 == d2)
            {
                return true;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }

    return true;
}

int getYear(int n)
{
    return n/10000;
}

int getMonth(int n)
{
    int placeH = n / 100;
    return placeH % 100;
}

int getDay(int n) 
{
    return n % 10000;
}
// Print all the lists

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

void saveRepairListToFile (Repair * repairList)
{
    FILE * fptr;

    fptr = fopen("repairList.txt", "w+");

    if (fptr == NULL)
    {
        printf("Error opening file\n");
    }

    Repair * temp = repairList;

    while(temp != NULL)
    {
        if(temp->next == NULL)
        {
            fprintf(fptr, "%s, %d",temp->plate, temp->mileage);
        }
        else
        {
            fprintf(fptr, "%s, %d\n", temp->plate, temp->mileage);
        }

        temp = temp->next;
    }
}

void saveAvRentListToFile (avRent * avList)
{
    FILE * fptr;

    fptr = fopen("avRent.txt", "w+");

    if (fptr == NULL)
    {
        printf("Error opening file\n");
    }

    avRent * temp = avList;

    while(temp != NULL)
    {
        if(temp->next == NULL)
        {
            fprintf(fptr, "%s, %d",temp->plate, temp->mileage);
        }
        else
        {
            fprintf(fptr, "%s, %d\n", temp->plate, temp->mileage);
        }

        temp = temp->next;
    }
}

void saveRentedListToFile (Rented * rentList)
{
    FILE * fptr;

    fptr = fopen("rentedList.txt", "w+");

    if (fptr == NULL)
    {
        printf("Error opening file\n");
    }

    Rented * temp = rentList;

    while(temp != NULL)
    {
        if(temp->next == NULL)
        {
            fprintf(fptr, "%s, %d, %d",temp->plate, temp->mileage, temp->expectedReturn);
        }
        else
        {
            fprintf(fptr, "%s, %d, %d\n", temp->plate, temp->mileage, temp->expectedReturn);
        }

        temp = temp->next;
    }

    fclose(fptr);
}

void loadAv (avRent ** avRentList)
{
    char *token;
    FILE * fptr;

    fptr = fopen("avRent.txt", "r");

    if (fptr == NULL)
    {
        printf("Error loading from file\n");
    }

    char line[200];

    while (fgets(line, 200, fptr) != NULL)
    {
        avRent * newNode = malloc(sizeof(avRent));
        token = strtok(line, ",");

        strcpy(newNode->plate , token);
        token = strtok(NULL, "\n");

        newNode->mileage = atoi(token);

        newNode->next = NULL;

        addCarToAvRentList(avRentList, newNode);
    }

    fclose(fptr);

}

void loadRented (Rented ** rentList)
{
    char *token;
    FILE * fptr;

    fptr = fopen("rentedList.txt", "r");

    if (fptr == NULL)
    {
        printf("Error loading from file\n");
    }

    char line[200];

    while (fgets(line, 200, fptr) != NULL)
    {
        Rented * newNode = malloc(sizeof(Rented));
        token = strtok(line, ",");

        strcpy(newNode->plate , token);
        token = strtok(NULL, ",");

        newNode->mileage = atoi(token);

        token = strtok(NULL, "\n");

        newNode->expectedReturn = atoi(token);

        newNode->next = NULL;

        addNodeToRentList(rentList, newNode);
    }

    fclose(fptr);
}

void addNodeToRentList (Rented ** rentList, Rented * node)
{
    node->next = NULL;

    if (*rentList == NULL)
    {
        *rentList = node;
    }

    Rented * temp = *rentList;

    while(temp -> next != NULL && isEarlier((temp -> next) -> expectedReturn, node->expectedReturn))
    {
        temp = temp -> next;
    }

    node -> next = temp-> next;
    temp->next = node;

}

void loadRepair (Repair ** repairList)
{
    char *token;
    FILE * fptr;

    fptr = fopen("repairList.txt", "r");

    if (fptr == NULL)
    {
        printf("Error loading from file\n");
    }

    char line[200];

    while (fgets(line, 200, fptr) != NULL)
    {
        Repair * newNode = malloc(sizeof(Repair));
        token = strtok(line, ",");

        strcpy(newNode->plate , token);
        token = strtok(NULL, "\n");

        newNode->mileage = atoi(token);

        newNode->next = NULL;

        addNodeToRepairList(repairList,  newNode);
    }

    fclose(fptr);
}
