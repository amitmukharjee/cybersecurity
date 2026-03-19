#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to reverse a string in place
void reverseString(char *str) {
    int len = strlen(str);
    int start = 0, end = len - 1;
    char temp;

    while (start < end) {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int main() {
    char message[256];

    printf("Enter a message (max 255 characters): ");
    if (fgets(message, sizeof(message), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    // Remove trailing newline if present
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';
    }

    // Encrypt (reverse)
    reverseString(message);
    printf("Encrypted message: %s\n", message);

    // Decrypt (reverse again)
    reverseString(message);
    printf("Decrypted message: %s\n", message);

    return 0;
}
