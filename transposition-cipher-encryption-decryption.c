#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// transposition-cipher-encryption-decryption.c
// encryption and decryption algorithm for transposition cipher.
// Function to remove spaces and convert to uppercase
void preprocessText(char *text) {
    int i, j = 0;
    for (i = 0; text[i] != '\0'; i++) {
        if (!isspace((unsigned char)text[i])) {
            text[j++] = toupper((unsigned char)text[i]);
        }
    }
    text[j] = '\0';
}

// Function to encrypt using Columnar Transposition Cipher
void encrypt(char *plaintext, int key, char *ciphertext) {
    int len = strlen(plaintext);
    int rows = (len + key - 1) / key; // Ceiling division
    int index = 0;

    // Fill matrix row-wise
    char matrix[rows][key];
    memset(matrix, 'X', sizeof(matrix)); // Fill with 'X' as padding

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < key; c++) {
            if (index < len) {
                matrix[r][c] = plaintext[index++];
            }
        }
    }

    // Read column-wise to get ciphertext
    index = 0;
    for (int c = 0; c < key; c++) {
        for (int r = 0; r < rows; r++) {
            ciphertext[index++] = matrix[r][c];
        }
    }
    ciphertext[index] = '\0';
}

// Function to decrypt using Columnar Transposition Cipher
void decrypt(char *ciphertext, int key, char *plaintext) {
    int len = strlen(ciphertext);
    int rows = (len + key - 1) / key;
    int index = 0;

    // Fill matrix column-wise
    char matrix[rows][key];
    memset(matrix, 'X', sizeof(matrix));

    for (int c = 0; c < key; c++) {
        for (int r = 0; r < rows; r++) {
            if (index < len) {
                matrix[r][c] = ciphertext[index++];
            }
        }
    }

    // Read row-wise to get plaintext
    index = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < key; c++) {
            plaintext[index++] = matrix[r][c];
        }
    }
    plaintext[index] = '\0';
}

int main() {
    char plaintext[256], ciphertext[256], decrypted[256];
    int key;

    printf("Enter plaintext: ");
    if (!fgets(plaintext, sizeof(plaintext), stdin)) {
        printf("Error reading input.\n");
        return 1;
    }
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline

    preprocessText(plaintext);

    printf("Enter key (number of columns): ");
    if (scanf("%d", &key) != 1 || key <= 0) {
        printf("Invalid key. Must be a positive integer.\n");
        return 1;
    }

    encrypt(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    decrypt(ciphertext, key, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
