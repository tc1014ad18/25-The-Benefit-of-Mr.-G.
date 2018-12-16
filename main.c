#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

// Macros that will help me limit my data structures
#define MAXROWS 400
#define MAXCOLS 200
#define NAME_LENGHT 70

// Enumerations to create catalogs.  The use of this enumerations will make my code
// more legible.
// Set of payment methods available in the system
enum PaymentMethod{Visa, MasterCard, AmericanExpress};
// Set of the Arena's zones
enum Zone{VIP, Platinum, Gold, Silver, Green, Yellow, Red, SkyBlue, NavyBlue, DeepBlue};

// I need to keep track of certain data for each seat: the name of its occupant, whether it
// is free or it is already occupied, the payment method used to buy its ticket and the price
// paid for that seat.  I create an array of the total number of rows (MAXROWS) by the total
// number of seats per row (MAXCOLS) to represent the arena.  I decided that the max length
// of the client's name would be NAME_LENGTH, defined above.
struct seat {
    char name[NAME_LENGHT];
    bool free;
    enum PaymentMethod paymentMethod;
    double price;
} arena[MAXROWS][MAXCOLS];

// This array will hold the seat prices for each of the arena zones
double zonePrice[10];

// Here comes the declaration of functions used in this program.
// LoadInformation will try to load into the arena array the data stored in a file
// from previous runs of the system.
void LoadInformation();
// This function initialises the arena array
void InitialiseArray();
// Displays the main menu in the standard output
void ShowMainMenu();
// Saves the arena array data to a file
void SaveData();
// Loads the seats prices in the zonePrice array
void LoadPrices();
// Method to sell tickets
void SellTickets();
// Displays in the standard output a list of the arena zones and their prices.
void ShowZonePrices();


bool ValidZoneOption(char option);

bool PickASeat(int zone);

// Main routine.  This routine initialises the array (for the first time or with
// previously recorded data) and shows the main menu within a loop, until the
// user decides to end the program.
int main() {
    // This variable will let me collect the option that the user chooses.
    char option;

    // Here I initialise my Data array with the contents of my
    // data file... if any.
    LoadInformation();

    // Within this loop, I show the user the main menu and let them choose among
    // its options.  Depending on the option, the program will go to a different
    // function in order to:
    //      Sell tickets to the client.
    //      Save the collected data so far to a file.
    //      Produce reports on sales and occupation.
    //      Exit the system, saving the collected data to a file.
    do {
        ShowMainMenu();
        fflush(stdin);
        option = (char) toupper(getchar());
        fflush(stdin);

        switch(option) {
            case 'A':
                SellTickets();
                break;
            case 'B':
                SaveData();
                printf("Your data has been saved. You can continue using the system.\n");
                break;
            case 'C':
                Reports();
                break;
            case 'D':
                SaveData();
                printf("Exiting program. See you later.\n");
                break;
            default:
                printf("Option not valid. Try again!\n");
        }

    } while(option != 'D');

    return 0;
}

// This function will help me sell tickets to clients. It will show the different
// arena's zones and their prices, allowing to choose one of them before collecting
// the rest of the data.  The client can also decide not to follow with the purchase
// and return to the main menu.
void SellTickets() {
    // I go into a loop to ask for the desired zone.  However, I gave the client the
    // option to exit this process without purchasing any tickets.
    char option;
    bool validZoneOption;
    do {
        // I show the Zone's menu with their prices
        ShowZonePrices();
        fflush(stdin);
        option = (char) toupper(getchar());
        fflush(stdin);
        validZoneOption = ValidZoneOption(option);

        // If the option is not a valid one, then I display an error message and ask
        // the user/client to try again
        if (!validZoneOption) {
            printf("\nInvalid option.  Please pick a valid option or press X to exit this module.\n\n");
        }
    } while (!validZoneOption);

    // If the option picked is not X (to exit the routine) then we proceed to collect
    // the rest of the data needed for the sale
    if (option != 'X') {
        // The zone's code is its ASCII value minus 48.
        int zone = option - 48;
        if(!PickASeat(zone)) {
            printf("Exiting without making the purchase.\n");
        }
    } else {
        printf("Exiting without making the purchase.\n");
    }
}

bool PickASeat(int zone) {

    return true;
}

bool ValidZoneOption(char option) {
    return ((option >= '0' && option <= '9') || option == 'X');
}

void ShowZonePrices() {
    printf("Arena zones:\n\n"
           "0. VIP\t\t$100.00\n"
           "1. Platinum\t$ 85.00\n"
           "2. Gold\t\t$ 70.00\n"
           "3. Silver\t$ 55.00\n"
           "4. Green\t\t$ 45.00\n"
           "5. Yellow\t$ 40.00\n"
           "6. Red\t\t$ 30.00\n"
           "7. Sky Blue\t$ 50.00\n"
           "8. Navy Blue\t$ 35.00\n"
           "9. Deep Blue\t$ 20.00\n"
           "X. Exit without buying tickets\n\n"
           "Pick your zone: ");
}

void SaveData() {
    FILE *file;

    file = fopen("./seats.dat", "wb");

    fwrite(arena, sizeof(arena), 1, file);
}

void ShowMainMenu() {
    printf("A. Sell a ticket.\n"
           "B. Save sells data.\n"
           "C. Reports.\n"
           "D. Exit.\n\n"
           "Option? ");
}

void LoadInformation() {
    FILE *file;

    file = fopen("./seats.dat", "rb");

    if (file == NULL) {
        // Here I do what I need to do when there is no file
        // to collect data.
        InitialiseArray();
    } else {
        // Here I collect data from file
        fread(arena, sizeof(arena), 1, file);
    }

    LoadPrices();
}

void LoadPrices() {
    zonePrice[VIP] = 100.0;
    zonePrice[Platinum] = 85.0;
    zonePrice[Gold] = 70.0;
    zonePrice[Silver] = 55.0;
    zonePrice[Green] = 45.0;
    zonePrice[Yellow] = 40.0;
    zonePrice[Red] = 30.0;
    zonePrice[SkyBlue] = 50.0;
    zonePrice[NavyBlue] = 35.0;
    zonePrice[DeepBlue] = 20.0;
}

void InitialiseArray() {
    for(int i = 0; i < MAXCOLS; i++) {
        for(int j = 0; j < MAXROWS; j++) {
            arena[j][i].free = true;
        }
    }
}