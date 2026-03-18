#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/bio.h>

#define RSA_KEY_BITS 2048
#define MAX_BUFFER_SIZE 8192

// gcc Generating_Asymmetric_Key.c -lcrypto
void print_openssl_error() {
   char err_buf[256];
   unsigned long err = ERR_get_error();
   ERR_error_string_n(err, err_buf, sizeof(err_buf));
   fprintf(stderr, "OpenSSL error: %s\n", err_buf);
}

void secure_memzero(void *buf, size_t len) {
   volatile unsigned char *p = (volatile unsigned char *)buf;
   while (len--) *p++ = 0;
}

void print_bio_contents(const char *filename, const char *label) {
   BIO *bio = BIO_new_file(filename, "r");
   if (!bio) {
      fprintf(stderr, "Failed to open %s for reading\n", filename);
      return;
   }

   char *buffer = malloc(MAX_BUFFER_SIZE);
   if (!buffer) {
      fprintf(stderr, "Failed to allocate memory\n");
      BIO_free(bio);
      return;
   }

   memset(buffer, 0, MAX_BUFFER_SIZE);
   int read_size = BIO_read(bio, buffer, MAX_BUFFER_SIZE - 1);
   if (read_size > 0) {
      buffer[read_size] = '\0';
      printf("%s:\n%s\n", label, buffer);
   }

   if (strstr(filename, "private")) {
      secure_memzero(buffer, MAX_BUFFER_SIZE);
   }

   free(buffer);
   BIO_free(bio);
}

int generate_asymmetric_keypair() {
   EVP_PKEY *pkey = NULL;
   EVP_PKEY_CTX *ctx = NULL;
   BIO *priv_bio = NULL;
   BIO *pub_bio = NULL;
   int ret = -1;

   // Initialize OpenSSL
   OpenSSL_add_all_algorithms();
   ERR_load_crypto_strings();

   // Create context and generate key
   ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
   if (!ctx) {
      fprintf(stderr, "Failed to create key context\n");
      print_openssl_error();
      goto cleanup;
   }

   if (EVP_PKEY_keygen_init(ctx) <= 0) {
      fprintf(stderr, "Failed to initialize key generation\n");
      print_openssl_error();
      goto cleanup;
   }

   if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, RSA_KEY_BITS) <= 0) {
      fprintf(stderr, "Failed to set key size\n");
      print_openssl_error();
      goto cleanup;
   }

   if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
      fprintf(stderr, "Failed to generate key\n");
      print_openssl_error();
      goto cleanup;
   }

   // Write private key using BIO
   priv_bio = BIO_new_file("private_key.pem", "w");
   if (!priv_bio) {
      fprintf(stderr, "Failed to create private key BIO\n");
      print_openssl_error();
      goto cleanup;
   }

   if (!PEM_write_bio_PrivateKey(priv_bio, pkey, NULL, NULL, 0, NULL, NULL)) {
      fprintf(stderr, "Failed to write private key\n");
      print_openssl_error();
      goto cleanup;
   }

   // Write public key using BIO
   pub_bio = BIO_new_file("public_key.pem", "w");
   if (!pub_bio) {
      fprintf(stderr, "Failed to create public key BIO\n");
      print_openssl_error();
      goto cleanup;
   }

   if (!PEM_write_bio_PUBKEY(pub_bio, pkey)) {
      fprintf(stderr, "Failed to write public key\n");
      print_openssl_error();
      goto cleanup;
   }

   // Close BIOs before reading
   BIO_free(priv_bio);
   BIO_free(pub_bio);
   priv_bio = pub_bio = NULL;

   // Print the keys
   print_bio_contents("private_key.pem", "Private Key");
   print_bio_contents("public_key.pem", "Public Key");

   ret = 0;  // Success

cleanup:
   // Clean up resources
   if (priv_bio) BIO_free(priv_bio);
   if (pub_bio) BIO_free(pub_bio);
   EVP_PKEY_free(pkey);
   EVP_PKEY_CTX_free(ctx);
   EVP_cleanup();
   ERR_free_strings();

   return ret;
}

int main() {
   if (generate_asymmetric_keypair() != 0) {
      fprintf(stderr, "Key generation failed\n");
      return 1;
   }
   return 0;
}
