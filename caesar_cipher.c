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

int main() {
   char message[] = "hello";
   int shift_value = 3;
   caesar_cipher(message, shift_value);
   printf("Encrypted message: %s\n", message);
   return 0;
}
