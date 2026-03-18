#include <stdio.h>
#include <string.h>

void pad(unsigned char* text, int* text_len, int block_size) {
   int padding_length = block_size - (*text_len % block_size);
   for (int i = 0; i < padding_length; i++) {
      text[*text_len + i] = padding_length;
   }
   *text_len += padding_length;
}

void unpad(unsigned char* text, int* text_len) {
   int padding_length = text[*text_len - 1];
   *text_len -= padding_length;
}

void xor_bytes(unsigned char* byte1, unsigned char* byte2, unsigned char* result, int block_size) {
   for (int i = 0; i < block_size; i++) {
      result[i] = byte1[i] ^ byte2[i];
   }
}

void encrypt_ecb(unsigned char* key, unsigned char* plaintext, int plaintext_len, unsigned char* ciphertext, int block_size) {
   unsigned char block[block_size];
   int num_blocks = (plaintext_len + block_size - 1) / block_size;
   int padded_len = plaintext_len;

   pad(plaintext, &padded_len, block_size);

   for (int i = 0; i < num_blocks; i++) {
      memcpy(block, plaintext + i * block_size, block_size);
      xor_bytes(block, key, ciphertext + i * block_size, block_size);
   }
}

void decrypt_ecb(unsigned char* key, unsigned char* ciphertext, int ciphertext_len, unsigned char* plaintext, int block_size) {
   unsigned char block[block_size];
   int num_blocks = ciphertext_len / block_size;

   for (int i = 0; i < num_blocks; i++) {
      memcpy(block, ciphertext + i * block_size, block_size);
      xor_bytes(block, key, plaintext + i * block_size, block_size);
   }

   int plaintext_len = ciphertext_len;
   unpad(plaintext, &plaintext_len);
}

int main() {
   unsigned char key[] = "ABCDEFGHIJKLMNOP"; // 16 bytes key for AES-128
   unsigned char plaintext[] = "Hello, Tutorialspoint!";
   int block_size = 16;

   unsigned char ciphertext[256];
   unsigned char decrypted_plaintext[256];

   encrypt_ecb(key, plaintext, strlen((char*)plaintext), ciphertext, block_size);
   printf("Ciphertext: ");
   for (int i = 0; i < strlen((char*)plaintext) + block_size; i++) {
      printf("%02X", ciphertext[i]);
   }
   printf("\n");

   decrypt_ecb(key, ciphertext, strlen((char*)plaintext) + block_size, decrypted_plaintext, block_size);
   printf("Decrypted plaintext: %s\n", decrypted_plaintext);

   return 0;
}
