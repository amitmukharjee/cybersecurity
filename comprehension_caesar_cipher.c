#include <stdio.h>
#include <string.h>

void caesar_cipher(char *text, int shift) {
   int length = strlen(text);
   for (int i = 0; i < length; i++) {
      if ('A' <= text[i] && text[i] <= 'Z') {
         text[i] = (char)((((text[i] - 65) + shift) % 26) + 65);
      } else if ('a' <= text[i] && text[i] <= 'z') {
         text[i] = (char)((((text[i] - 97) + shift) % 26) + 97);
      }
   }
}

int main() {
   char message[] = "hello everyone";
   int shift_value = 3;
   caesar_cipher(message, shift_value);
   printf("Encrypted message: %s\n", message);
   return 0;
}
