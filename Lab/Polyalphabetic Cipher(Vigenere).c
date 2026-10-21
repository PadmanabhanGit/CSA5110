#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LIMIT 256

// Function to encrypt the plaintext
void encryptVigenere(char plaintext[], char key[], char ciphertext[]) {
    int ptLen = strlen(plaintext);
    int keyLen = strlen(key);
    int i, j = 0;

    for (i = 0; i < ptLen; i++) {
        char c = plaintext[i];

        if (isalpha(c)) {
            // Determine shift amount from the current key character (case-insensitive)
            int shift = toupper(key[j % keyLen]) - 'A';
            j++; // Only advance key index for alphabetic characters

            if (isupper(c)) {
                ciphertext[i] = ((c - 'A' + shift) % 26) + 'A';
            } else {
                ciphertext[i] = ((c - 'a' + shift) % 26) + 'a';
            }
        } else {
            // Copy spaces, numbers, and punctuation as they are
            ciphertext[i] = c;
        }
    }
    ciphertext[ptLen] = '\0'; // Null-terminate the string
}

// Function to decrypt the ciphertext
void decryptVigenere(char ciphertext[], char key[], char decryptedtext[]) {
    int ctLen = strlen(ciphertext);
    int keyLen = strlen(key);
    int i, j = 0;

    for (i = 0; i < ctLen; i++) {
        char c = ciphertext[i];

        if (isalpha(c)) {
            // Determine shift amount from the current key character
            int shift = toupper(key[j % keyLen]) - 'A';
            j++; 

            if (isupper(c)) {
                // Adding 26 before modulo ensures the result is never negative in C
                decryptedtext[i] = ((c - 'A' - shift + 26) % 26) + 'A';
            } else {
                decryptedtext[i] = ((c - 'a' - shift + 26) % 26) + 'a';
            }
        } else {
            decryptedtext[i] = c;
        }
    }
    decryptedtext[ctLen] = '\0';
}

int main() {
    char plaintext[MAX_LIMIT];
    char key[MAX_LIMIT];
    char ciphertext[MAX_LIMIT];
    char decryptedtext[MAX_LIMIT];

    printf("Enter the plain text: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    // Remove trailing newline character from fgets
    plaintext[strcspn(plaintext, "\n")] = '\0';

    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    // Validate that the key only contains alphabetic characters
    for(int i = 0; key[i] != '\0'; i++) {
        if(!isalpha(key[i])) {
            printf("Error: Keyword must contain letters only.\n");
            return 1;
        }
    }

    // Perform Encryption
    encryptVigenere(plaintext, key, ciphertext);
    printf("\n--- Results ---\n");
    printf("Encrypted Cipher Text: %s\n", ciphertext);

    // Perform Decryption
    decryptVigenere(ciphertext, key, decryptedtext);
    printf("Decrypted Plain Text:  %s\n", decryptedtext);

    return 0;
}
