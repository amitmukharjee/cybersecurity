#include <stdio.h>
#include <string.h>

#define ALPHABET "abcdefghijklmnopqrstuvwxyz"

void caesar_cipher(char *text, int shift) {
   int length = strlen(text);
   for (int i = 0; i < length; i++) {
      if (text[i] >= 'a' && text[i] <= 'z') {
         text[i] = ALPHABET[(strchr(ALPHABET, text[i]) - ALPHABET + shift) % 26];
      }
   }
}

void caesar_decipher(char *text, int shift) {
   // Decryption is the reverse of encryption, so we apply a negative shift
   caesar_cipher(text, -shift);
}

int main() {
   char encrypted_msg[] = "khoor";  // Example encrypted message
   int shift_value = 3;
   caesar_decipher(encrypted_msg, shift_value);
   printf("Decrypted message: %s\n", encrypted_msg);  // Fixed the string termination
   return 0;
}
