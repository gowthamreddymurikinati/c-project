#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define FIRST_CLASS_ROWS 12
#define PREMIUM_ECONOMY_ROWS 12
#define ECONOMY_ROWS 52
#define ROWS (FIRST_CLASS_ROWS + PREMIUM_ECONOMY_ROWS + ECONOMY_ROWS)
#define SEATS_PER_ROW 4

bool seats[ROWS][SEATS_PER_ROW] = {{false}};
int pnr[ROWS][SEATS_PER_ROW] = {{0}};
int pnrCounter = 1;

const int firstClassPrice = 5000;
const int premiumEconomyPrice = 3500;
const int economyPrice = 2000;
const int windowSeatExtra = 500;
const int aisleSeatExtra = 300;

// Function to sign in
void signIn() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Sign-in successful!\n\n");
}

// Function to select flight route
void selectRoute() {
    int routeChoice;
    printf("Select your flight route:\n");
    printf("1. Delhi -> Mumbai\n2. Bangalore -> Kolkata\n3. Chennai -> Hyderabad\n4. Ahmedabad -> Pune\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &routeChoice);
    printf("Route selected successfully.\n");
}

// Function to book a seat
void bookSeat() {
    int seat, basePrice, totalPrice = 0;
    int rowStart, rowEnd;
    printf("Select class: \n1. First Class (Rows 1-12)\n2. Premium Economy (Rows 13-24)\n3. Economy (Rows 25-76)\n");
    printf("Enter your choice (1-3): ");
    int classChoice;
    scanf("%d", &classChoice);

    if (classChoice == 1) {
        rowStart = 1;
        rowEnd = FIRST_CLASS_ROWS;
        basePrice = firstClassPrice;
        printf("First Class selected. Available seats: 1, 4, 5, 8, 9, 12\n");
    } else if (classChoice == 2) {
        rowStart = FIRST_CLASS_ROWS + 1;
        rowEnd = FIRST_CLASS_ROWS + PREMIUM_ECONOMY_ROWS;
        basePrice = premiumEconomyPrice;
        printf("Premium Economy selected. Available seats: 1, 4, 5, 8, 9, 12\n");
    } else if (classChoice == 3) {
        rowStart = FIRST_CLASS_ROWS + PREMIUM_ECONOMY_ROWS + 1;
        rowEnd = ROWS;
        basePrice = economyPrice;
        printf("Economy Class selected. Available seats: 1, 4, 5, 8, 9, 12\n");
    } else {
        printf("Invalid class choice. Try again.\n");
        return;
    }

    printf("Enter seat number (1-%d): ", SEATS_PER_ROW);
    scanf("%d", &seat);

    if (seat < 1 || seat > SEATS_PER_ROW) {
        printf("Invalid seat number. Try again.\n");
        return;
    }

    // Check if the seat is already booked
    if (seats[rowStart - 1][seat - 1]) {
        printf("Seat already booked. Please choose another seat.\n");
        return;
    }

    totalPrice = basePrice;
    printf("Seat booked! Row: %d, Seat: %d\n", rowStart, seat);

    // Assign PNR: row * 2 * seat number
    int pnrNumber = rowStart * 2 * seat;
    seats[rowStart - 1][seat - 1] = true;
    pnr[rowStart - 1][seat - 1] = pnrNumber;

    printf("PNR: %d\n", pnrNumber);
    printf("Total Price: ₹%d\n", totalPrice);
}

// Function to check PNR
void checkPNR() {
    int pnrNumber, found = 0;
    printf("Enter your PNR number to check booking status: ");
    scanf("%d", &pnrNumber);

    for (int row = 0; row < ROWS; row++) {
        for (int seat = 0; seat < SEATS_PER_ROW; seat++) {
            if (pnr[row][seat] == pnrNumber) {
                printf("PNR found! Row: %d, Seat: %d\n", row + 1, seat + 1);
                found = 1;
                break;
            }
        }
        if (found) break;
    }

    if (!found) {
        printf("No booking found for the given PNR.\n");
    }
}

void cancelBooking() {
    int row, seat;
    printf("Enter row number: ");
    scanf("%d", &row);
    printf("Enter seat number: ");
    scanf("%d", &seat);

    if (!seats[row - 1][seat - 1]) {
        printf("No booking found.\n");
    } else {
        seats[row - 1][seat - 1] = false;
        pnr[row - 1][seat - 1] = 0;
        printf("Booking canceled.\n");
    }
}

void rescheduleBooking() {
    int row, seat, newRow, newSeat;
    printf("Enter row number to reschedule from: ");
    scanf("%d", &row);
    printf("Enter seat number to reschedule from: ");
    scanf("%d", &seat);

    if (!seats[row - 1][seat - 1]) {
        printf("No booking found.\n");
        return;
    }

    printf("Enter new row number: ");
    scanf("%d", &newRow);
    printf("Enter new seat number: ");
    scanf("%d", &newSeat);

    if (seats[newRow - 1][newSeat - 1]) {
        printf("New seat already booked. Try another.\n");
        return;
    }

    seats[row - 1][seat - 1] = false;
    pnr[row - 1][seat - 1] = 0;
    seats[newRow - 1][newSeat - 1] = true;
    int newPnr = newRow * 2 * newSeat;
    pnr[newRow - 1][newSeat - 1] = newPnr;
    printf("Rescheduled! New Row: %d, Seat: %d (PNR: %d)\n", newRow, newSeat, newPnr);
}

void menu() {
    int choice;
    while (1) {
        printf("\n==============================================\n");
        printf("\t\tADVANCED FLIGHT BOOKING SYSTEM\n");
        printf("==============================================\n");
        printf("1>> BOOK A TICKET\n2>> CHECK PNR\n3>> CANCEL BOOKING\n4>> RESCHEDULE\n5>> EXIT\n");
        printf("Choose your service: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookSeat(); break;
            case 2: checkPNR(); break;
            case 3: cancelBooking(); break;
            case 4: rescheduleBooking(); break;
            case 5: printf("Thank you for using FLYDOM!\n"); return;
            default: printf("Invalid choice! Try again.\n");
        }
    }
}

int main() {
    printf("\t\t=================================================\n");
    printf("\t\t|                                               |\n");
    printf("\t\t|        -----------------------------          |\n");
    printf("\t\t|                   FLYDOM...                   |\n");
    printf("\t\t|        -----------------------------          |\n");
    printf("\t\t|              BROUGHT TO YOU BY                |\n");
    printf("\t\t|                 CSM-C                         |\n");
    printf("\t\t=================================================\n\n");
    
    printf("Press any key to continue...\n");
    
    signIn();
    selectRoute();
    menu();
    
    return 0;
}