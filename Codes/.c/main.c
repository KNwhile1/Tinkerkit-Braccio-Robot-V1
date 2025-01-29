// =====================================================================================================================
// Name: Tinkerkit_Braccio_Robot_V1
// Description: This program allows control of a Braccio robotic arm through serial communication.
// Target: Arduino Uno
// Compiler: PYcharm
// Usage: Control the Braccio robot using Python
// Restriction(s): None.
// History: 7/05/2024 | E. Zoukou / C. Courtemanche / K. Niamba / Creation;
//          1/28/2025 | K. Niamba / Modification ---> Documentation translation (FR to ENG);
// =====================================================================================================================

// =====================================================================================================================
// Inclusion of files
// =====================================================================================================================
#include <windows.h>                                  // Serial communication with the Win32 API
#include <stdio.h>
#include <conio.h>
#include "serialcom.h"                                // Import of serial_Write() and serial_Read() functions
#include <time.h>                                     // Import of the << time.h >> library

FILE * fp;                                            // The file << fp >> is a pointer

// =====================================================================================================================
// Main program #1
// =====================================================================================================================
int main() {
    fp = fopen("Journalisation.txt", "at+");          // Opening the file << Journalisation.txt >> for reading/writing
    if (fp == NULL) {
        printf("Unable to open the file\n");
    }

    int h, min, s, jour, mois, an;                    // Variables for the date
    time_t now;                                       // The current time of the computer

    time(&now);                                       // Current time of the computer (function)

// --------------------------------------------------
// Block for converting to << local time >> format
// --------------------------------------------------
    struct tm *local = localtime(&now);               // The structure for the date
    h = local->tm_hour;                               // The hour
    min = local->tm_min;                              // The minutes
    s = local->tm_sec;                                // The seconds
    jour = local->tm_mday;                            // The day
    mois = local->tm_mon + 1;                         // The month
    an = local->tm_year + 1900;                       // The year

    char *versArduino = calloc(7, sizeof(char));      // Memory allocation

    int M[6];                                         // Declaration of six servo motors as << M1, M2, M3, M4, M5, and M6 >> which are then put in an array
    int V;                                            // Declaration of speed as << V >>

// --------------------------------------------------
// Block for the << >>> MAIN MENU <<< >>
// --------------------------------------------------
    while(1) {
        char option[] = {0};                          // To change the case

        printf("\n");                                 // Main menu
        printf("\n");
        printf("\n>>> MAIN MENU <<<\n"
               "\n (P) Positions M1-M6"
               "\n (V) Speed: step in ms 10-30 ms"
               "\n (E) Save position"
               "\n (L) Start object pickup"
               "\n (S) EXIT"
               "\n Enter your choice:");

        scanf("%s", option);                          // Taking the user's choice into account

        switch(option[0]){

// ---------------------------------------------------
// Block for case << P >>
// --------------------------------------------------
            case 'P':                                 // Managing the arm's positions
                for(int i = 0; i < 6; i++) {
                    printf("Enter the position of servo motor M%i: ", i + 1);
                    scanf("%d", &M[i]);
                }
                for (int x = 0; x < 6; x++){
                    fprintf(fp, "M%i: %d\n", x + 1, M[x]);
                }
                break;

// --------------------------------------------------
// Block for case << V >>
// --------------------------------------------------
            case 'V':                                 // Managing speed
                do {
                    printf("Enter the speed between 10 and 30 ms: ");
                    scanf("%d", &V);
                } while(V < 10 || V > 30);            // Limiting the speed
                fprintf(fp, "V: %d\n", V);
                break;

// --------------------------------------------------
// Block for case << E >>
// --------------------------------------------------
            case 'E':                                 // Saving (Logging)
                fprintf(fp, " \tTime: %02d:%02d:%02d\t Date: %02d/%d/%d\n\n\n", h, min, s, jour, mois, an);
                fclose(fp);
                break;

// --------------------------------------------------
// Block for case << L >>
// --------------------------------------------------
            case 'L':                                 // Starting the entered positions
                sprintf(versArduino, " %d:%d:%d:%d:%d:%d:%d", V, M[0], M[1], M[2], M[3], M[4], M[5]);
                serial_Write(versArduino);
                break;

// --------------------------------------------------
// Block for case << S >>
// --------------------------------------------------
            case 'S':                                 // Exiting the program
                return 0;

// --------------------------------------------------
// Block for error message
// --------------------------------------------------
            default:                                  // Asking the user again for their option
                printf("\nINVALID CHOICE\n");
                break;
        }
    }
}