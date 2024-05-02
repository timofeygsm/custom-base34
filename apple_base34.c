#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

const char custom_table[] = "0123456789ABCDEFGHJKLMNPQRSTUVWXYZ"; // Custom character table for BASE34


// Function to convert a character to its corresponding integer value
int charToInt(char c) {
    for (int i = 0; i < 34; i++) {
        if (custom_table[i] == c) {
            return i;
        }
    }
    return -1; // Return -1 in case of an error
}


// Function to convert a number from base from_base to decimal
unsigned long long fromB34ToDec(char *num) {
    unsigned long long result = 0;
    int len = strlen(num);
    for (int i = 0; i < len; i++) {
        result = result * 34 + charToInt(num[i]);
    }
    return result;
}


// Function to convert a number from decimal to BASE34
void fromDecimalToBase(unsigned long long num) {
    char result[100];
    int i = 0;
    while (num > 0) {
        result[i++] = custom_table[num % 34];
        num /= 34;
    }
    // print the result in reverse order
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", result[j]);
    }
}


int main() {
    char inputB34[35];
    char snPart1[8], snPart2[6], snPart3[8];
    bool exit_requested = false;

    while (!exit_requested) {
        printf("Enter LIDAR SN (or type 'exit'): ");
        scanf("%34s", inputB34);

        if (strcmp(inputB34, "exit") == 0) {
            exit_requested = true;
            continue;
        }

        strncpy(snPart1, inputB34, 6);
        snPart1[6] = '\0';
        strncpy(snPart2, inputB34 + 6, 5);
        snPart2[5] = '\0';
        strncpy(snPart3, inputB34 + 11, 6);
        snPart3[6] = '\0';
        // Convert the number from base 34 to decimal
        uint64_t hexNum1 = fromB34ToDec(snPart1);
        uint64_t hexNum2 = fromB34ToDec(snPart2);
        uint64_t hexNum3 = fromB34ToDec(snPart3);
        printf("Number in HEX: %08"PRIX64"%06"PRIX64"%08"PRIX64"\n", hexNum1,hexNum2,hexNum3);

        char inputHEX[100];
        int b34Num1, b34Num2, b34Num3; // First variable containing 4 bytes. Second variable containing 3 bytes. Third variable containing 4 bytes

        // Request input string
        printf("Enter LIDAR SN in HEX (or type 'exit'): ");
        scanf("%s", inputHEX);

        if (strcmp(inputHEX, "exit") == 0) {
            exit_requested = true;
            continue;
        }

        // Copy the corresponding parts into variables
        sscanf(inputHEX, "%8x%6x%8x", &b34Num1, &b34Num2, &b34Num3);

        // Output the results in BASE34 format
        printf("Number in BASE34: ");
        fromDecimalToBase(b34Num1);
        fromDecimalToBase(b34Num2);
        fromDecimalToBase(b34Num3);
        printf("\n");

    }

    return 0;
}


// HNQ2322C1R31CCD10  2F D8 F3 B0 30 02 59 03 B1 68 16  HNQ232 2C1R3 1CCD10    2FD8F3B030025903B16816