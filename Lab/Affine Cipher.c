#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to find the Greatest Common Divisor (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find the modular multiplicative inverse of 'a' modulo 26
// (Used exclusively for decryption)
int modInverse(int a) {
    a = a % 26;
    for (int x = 1; x < 26; x++) {
        if ((a * x) % 26 == 1) {
            return x;
        }
    }
    return -1; // Inverse doesn't exist
}

// Encryption function: C = (a * p + b) mod 26
void encryptAffine(char plaintext[], int a, int b, char ciphertext[]) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        char c = plaintext[i];
        if (isalpha(c)) {
            if (isupper(c)) {
                int p = c - 'A';
                ciphertext[i] = ((a * p + b) % 26) + 'A';
            } else {
                int p = c - 'a';
                ciphertext[i] = ((a * p + b) % 26) + 'a';
            }
        } else {
            ciphertext[i] = c; // Keep spaces and punctuation intact
        }
    }
    ciphertext[len] = '\0';
}

// Decryption function: P = a^-1 * (C - b) mod 26
void decryptAffine(char ciphertext[], int a, int b, char decryptedtext[]) {
    int len = strlen(ciphertext);
    int a_inv = modInverse(a);
    
    for (int i = 0; i < len; i++) {
        char c = ciphertext[i];
        if (isalpha(c)) {
            if (isupper(c)) {
                int C = c - 'A';
                // Add 26 to handle negative results before modulo in C
                int p = (a_inv * (C - b + 26)) % 26;
                decryptedtext[i] = p + 'A';
            } else {
                int C = c - 'a';
                int p = (a_inv * (C - b + 26)) % 26;
                decryptedtext[i] = p + 'a';
            }
        } else {
            decryptedtext[i] = c;
        }
    }
    decryptedtext[len] = '\0';
}

int main() {
    char plaintext[256];
    char ciphertext[256];
    char decryptedtext[256];
    int a, b;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline

    printf("Enter key component 'a': ");
    scanf("%d", &a);
    printf("Enter key component 'b': ");
    scanf("%d", &b);

    // CRITICAL VALIDATION STEP:
    // Check if 'a' is coprime to 26
    if (gcd(a, 26) != 1) {
        printf("\n[ERROR] Value a = %d is NOT allowed!\n", a);
        printf("Reason: gcd(%d, 26) = %d. 'a' must be coprime to 26 to allow decryption.\n", a, a, gcd(a, 26));
        printf("Try using values like: 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, or 25.\n");
        return 1; 
    }

    // Keep b within the 0-25 range logically
    b = (b % 26 + 26) % 26;

    // Process Cipher
    encryptAffine(plaintext, a, b, ciphertext);
    printf("\n--- Results ---\n");
    printf("Encrypted Text: %s\n", ciphertext);

    decryptAffine(ciphertext, a, b, decryptedtext);
    printf("Decrypted Text: %s\n", decryptedtext);

    return 0;
}
