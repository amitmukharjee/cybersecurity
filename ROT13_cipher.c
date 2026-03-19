#include <stdio.h>
#include <ctype.h>  // for isalpha, isupper, islower
#include <string.h> // for strlen

/**
 * Applies ROT13 encryption/decryption to the given string in-place.
 * 
 * @param text - The string to be transformed (must be null-terminated).
 * @return 0 on success, -1 if input is invalid.
 */
int rot13Func(char *text) {
    if (text == NULL) {
        return -1; // Invalid input
    }

    for (size_t i = 0; text[i] != '\0'; i++) {
        char c = text[i];

        if (isupper((unsigned char)c)) {
            // Rotate within 'A'..'Z'
            text[i] = (char)(((c - 'A' + 13) % 26) + 'A');
        } 
        else if (islower((unsigned char)c)) {
            // Rotate within 'a'..'z'
            text[i] = (char)(((c - 'a' + 13) % 26) + 'a');
        }
        // Non-alphabetic characters remain unchanged
    }
    return 0;
}

// Example usage
int main() {
    char message[] = "Hello, World!";

    if (rot13Func(message) == 0) {
        printf("ROT13 Encoded: %s\n", message);
    } else {
        printf("Error: Invalid input.\n");
    }

    // Decode back (ROT13 is symmetric)
    rot13Func(message);
    printf("Decoded: %s\n", message);

    return 0;
}
