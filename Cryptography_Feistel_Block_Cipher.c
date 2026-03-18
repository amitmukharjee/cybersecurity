#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void random_key(int p, char *key) {
   for (int i = 0; i < p; i++) {
      key[i] = '0' + (rand() % 2);
   }
   key[p] = '\0';
}

void exor_func(char *a, char *b, char *result, int len) {
   for (int i = 0; i < len; i++) {
      result[i] = (a[i] == b[i]) ? '0' : '1';
   }
   result[len] = '\0';
}

int convert_bin_to_dec(char *binary) {
   int decimal = 0;
   for (int i = 0; binary[i] != '\0'; i++) {
      decimal = decimal * 2 + (binary[i] - '0');
   }
   return decimal;
}

int main() {
   char plaintext[] = "Hello Everyone";
   printf("Plain Text is: %s\n", plaintext);

   int len = strlen(plaintext);
   char plaintext_Bin[8 * len + 1];
   for (int i = 0; i < len; i++) {
      for (int j = 7; j >= 0; j--) {
         plaintext_Bin[8 * i + (7 - j)] = (plaintext[i] >> j) & 1 ? '1' : '0';
      }
   }
   plaintext_Bin[8 * len] = '\0';

   int n = len * 8 / 2;
   char L1[n + 1], R1[n + 1];
   strncpy(L1, plaintext_Bin, n);
   strncpy(R1, plaintext_Bin + n, n);
   L1[n] = '\0';
   R1[n] = '\0';

   int m = strlen(R1);
   char K1[m + 1], K2[m + 1];
   random_key(m, K1);
   random_key(m, K2);

   char f1[m + 1], R2[m + 1];
   exor_func(R1, K1, f1, m);
   exor_func(f1, L1, R2, m);
   char L2[m + 1];
   strncpy(L2, R1, m);
   L2[m] = '\0';

   char f2[m + 1], R3[m + 1];
   exor_func(R2, K2, f2, m);
   exor_func(f2, L2, R3, m);
   char L3[m + 1];
   strncpy(L3, R2, m);
   L3[m] = '\0';

   char bin_data[2 * m + 1];
   snprintf(bin_data, sizeof(bin_data), "%s%s", L3, R3);

   char str_data[8 * m + 1];
   int j = 0;
   for (int i = 0; i < 2 * m; i += 7) {
      char temp_data[8];
      strncpy(temp_data, bin_data + i, 7);
      temp_data[7] = '\0';
      int decimal_data = convert_bin_to_dec(temp_data);
      str_data[j++] = (char)decimal_data;
   }
   str_data[j] = '\0';

   printf("Cipher Text: %s\n", str_data);

   char L4[m + 1], R4[m + 1];
   strncpy(L4, L3, m);
   strncpy(R4, R3, m);

   char f3[m + 1], L5[m + 1];
   exor_func(L4, K2, f3, m);
   exor_func(R4, f3, L5, m);
   char R5[m + 1];
   strncpy(R5, L4, m);
   R5[m] = '\0';

   char f4[m + 1], L6[m + 1];
   exor_func(L5, K1, f4, m);
   exor_func(R5, f4, L6, m);
   char R6[m + 1];
   strncpy(R6, L5, m);
   R6[m] = '\0';

   char plaintext1[2 * m + 1];
   snprintf(plaintext1, sizeof(plaintext1), "%s%s", L6, R6);

   int num = strtol(plaintext1, NULL, 2);
   printf("Decrypted Plain Text is: %x\n", num);
   return 0;
}
