#include <stdio.h>
#include <string.h>

void caesar_decipher(char *text, int shift) {
   int length = strlen(text);
   for (int i = 0; i < length; i++) {
      if ('A' <= text[i] && text[i] <= 'Z') {
         text[i] = (char)((((text[i] - 65) - shift + 26) % 26) + 65);  // Adding 26 to avoid negative values
      } else if ('a' <= text[i] && text[i] <= 'z') {
         text[i] = (char)((((text[i] - 97) - shift + 26) % 26) + 97);  // Adding 26 to avoid negative values
      }
   }
}

int main() {
   char encrypted_msg[] = "khoor hyhubrqh";  // Example encrypted message
   int shift_value = 3;
   caesar_decipher(encrypted_msg, shift_value);
   printf("Decrypted message: %s\n", encrypted_msg);
   return 0;
}
