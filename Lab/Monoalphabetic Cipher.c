#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 256

void encrypt(char* plaintext, const char* key, char* ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];
        
        if (isupper(ch)) {
            // Map 'A'-'Z' to the key index (0-25) and keep uppercase
            ciphertext[i] = toupper(key[ch - 'A']);
        } else if (islower(ch)) {
            ciphertext[i] = tolower(key[ch - 'a']);
        } else {
            ciphertext[i] = ch;
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; // Null-terminate the string
}

void decrypt(char* ciphertext, const char* key, char* decryptedtext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        
        if (isalpha(ch)) {
            char target = tolower(ch);
            int index = -1;
            
            
            for (int j = 0; j < 26; j++) {
                if (tolower(key[j]) == target) {
                    index = j;
                    break;
                }
            }
            
            
            if (index != -1) {
                if (isupper(ch)) {
                    decryptedtext[i] = 'A' + index;
                } else {
                    decryptedtext[i] = 'a' + index;
                }
            }
        } else {
            
            decryptedtext[i] = ch;
        }
    }
    decryptedtext[strlen(ciphertext)] = '\0'; 
}

int main() {
    char plaintext[MAX_SIZE];
    char ciphertext[MAX_SIZE];
    char decryptedtext[MAX_SIZE];
    
    char key[27]; 

    printf("Enter a 26-letter substitution key (e.g., QWERTYUIOPASDFGHJKLZXCVBNM): ");
    scanf("%26s", key);
    
    while (getchar() != '\n'); 

    printf("Enter the message to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    
    plaintext[strcspn(plaintext, "\n")] = '\0';

    encrypt(plaintext, key, ciphertext);
    printf("\n--- Results ---\n");
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, key, decryptedtext);
    printf("Decrypted Plaintext:  %s\n", decryptedtext);

    return 0;
}
