#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_symmetric_key(int key_length, unsigned char *key) {
   // Generate a random key with the specified length
   for (int i = 0; i < key_length; i++) {
      key[i] = rand() % 256;
   }
}

int main() {
   // Seed the random number generator
   srand(time(NULL));

   // Create a symmetric key with a length of 32 bytes (256 bits)
   unsigned char key[32];
   generate_symmetric_key(32, key);

   // Display the key in hexadecimal format
   printf("Symmetric Key: ");
   for (int i = 0; i < 32; i++) {
      printf("%02x", key[i]);
   }
   printf("\n");

   return 0;
}
