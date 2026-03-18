#include <stdio.h>
#include <string.h>
#include <stdint.h>

void aes_encrypt(uint8_t *data, uint8_t *key, uint8_t *encrypted_data, size_t data_len) {
   uint8_t aes_key[16];
   for (int i = 0; i < 16; i++) {
      aes_key[i] = key[i % strlen((char *)key)];
   }

   for (size_t i = 0; i < data_len; i++) {
      encrypted_data[i] = data[i] ^ aes_key[i % 16];
   }
}

void rsa_encrypt(uint8_t *data, uint8_t *public_key, uint8_t *encrypted_data, size_t data_len) {
   for (size_t i = 0; i < data_len; i++) {
      encrypted_data[i] = data[i] ^ public_key[i % strlen((char *)public_key)];
   }
}

void double_encrypt(uint8_t *data, size_t data_len, uint8_t *aes_key, uint8_t *rsa_public_key, uint8_t *result) {
   uint8_t aes_encrypted_data[data_len];
   aes_encrypt(data, aes_key, aes_encrypted_data, data_len);

   rsa_encrypt(aes_encrypted_data, rsa_public_key, result, data_len);
}

int main() {
   uint8_t data[] = "This is a secret message.";
   size_t data_len = strlen((char *)data);

   uint8_t aes_key[] = "AES_Key";
   uint8_t rsa_public_key[] = "RSA_Public_Key";
   uint8_t encrypted_data[data_len];

   double_encrypt(data, data_len, aes_key, rsa_public_key, encrypted_data);

   printf("Sample Data: %s\n", data);
   printf("Double Encrypted Data: ");
   for (size_t i = 0; i < data_len; i++) {
      printf("%02x", encrypted_data[i]);
   }
   printf("\n");

   return 0;
}
