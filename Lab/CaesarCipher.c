#include<stdio.h>

#include<ctype.h>

void encrypt(char text[], int key) {
    key = key % 26;
    if (key < 0) {
        key += 26;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        
        if (isupper(ch)) {
            text[i] = (ch - 'A' + key) % 26 + 'A';
        }
        else if (islower(ch)) {
            text[i] = (ch - 'a' + key) % 26 + 'a';
        }
    }
}

void decrypt(char text[], int key) {
  
    encrypt(text, -key);
}

int main() {
    char text[500];
    int key, choice;

    printf("--- Caesar Cipher Program ---\n");
    printf("1. Encrypt text\n");
    printf("2. Decrypt text\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);

    // Consume trailing newline character from buffer
    while (getchar() != '\n');

    printf("Enter message: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter shift key (integer): ");
    scanf("%d", &key);

    if (choice == 1) {
        encrypt(text, key);
        printf("Encrypted message: %s", text);
    } else if (choice == 2) {
        decrypt(text, key);
        printf("Decrypted message: %s", text);
    } else {
        printf("Error: Invalid choice.\n");
    }

    return 0;
}

