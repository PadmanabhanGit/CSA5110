#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to find the coordinates of a character in the 5x5 matrix
void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; // Treat 'J' as 'I'
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to generate the 5x5 Playfair key matrix
void generateMatrix(char key[], char matrix[SIZE][SIZE]) {
    int map[26] = {0};
    int len = strlen(key);
    int r = 0, c = 0;

    // 'J' is mapped onto 'I'
    map['J' - 'A'] = 1; 

    // Insert unique characters of the keyword into the matrix
    for (int i = 0; i < len; i++) {
        char ch = toupper(key[i]);
        if (isalpha(ch) && map[ch - 'A'] == 0) {
            matrix[r][c] = ch;
            map[ch - 'A'] = 1;
            c++;
            if (c == SIZE) {
                c = 0;
                r++;
            }
        }
    }

    // Fill the remaining cells with the rest of the alphabet
    for (int i = 0; i < 26; i++) {
        if (map[i] == 0) {
            matrix[r][c] = (char)(i + 'A');
            c++;
            if (c == SIZE) {
                c = 0;
                r++;
            }
        }
    }
}

// Function to format the plaintext into clean digraphs
int prepareText(char text[], char prepared[]) {
    int len = strlen(text);
    int count = 0;

    for (int i = 0; i < len; i++) {
        char ch = toupper(text[i]);
        if (isalpha(ch)) {
            if (ch == 'J') ch = 'I';
            
            // If the next character matches the current one in a pair, insert filler 'X'
            if (count % 2 != 0 && prepared[count - 1] == ch) {
                prepared[count++] = 'X';
            }
            prepared[count++] = ch;
        }
    }

    // If the final text has an odd length, pad it with 'X'
    if (count % 2 != 0) {
        prepared[count++] = 'X';
    }
    prepared[count] = '\0';
    return count;
}

// Function to encrypt the text using Playfair rules
void encryptPlayfair(char matrix[SIZE][SIZE], char text[], char ciphertext[]) {
    int len = strlen(text);
    int r1, c1, r2, c2;

    for (int i = 0; i < len; i += 2) {
        findPosition(matrix, text[i], &r1, &c1);
        findPosition(matrix, text[i+1], &r2, &c2);

        // Rule 1: Same Row -> Shift Right (with wraparound)
        if (r1 == r2) {
            ciphertext[i]   = matrix[r1][(c1 + 1) % SIZE];
            ciphertext[i+1] = matrix[r2][(c2 + 1) % SIZE];
        }
        // Rule 2: Same Column -> Shift Down (with wraparound)
        else if (c1 == c2) {
            ciphertext[i]   = matrix[(r1 + 1) % SIZE][c1];
            ciphertext[i+1] = matrix[(r2 + 1) % SIZE][c2];
        }
        // Rule 3: Different Row and Column -> Form a Rectangle
        else {
            ciphertext[i]   = matrix[r1][c2];
            ciphertext[i+1] = matrix[r2][c1];
        }
    }
    ciphertext[len] = '\0';
}

int main() {
    char key[100];
    char plaintext[200];
    char preparedText[400];
    char ciphertext[400];
    char matrix[SIZE][SIZE];

    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline

    // 1. Generate 5x5 Key Matrix
    generateMatrix(key, matrix);

    // Display the Key Matrix
    printf("\nGenerated 5x5 Key Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    // 2. Prepare Plaintext into pairs
    prepareText(plaintext, preparedText);
    printf("\nPrepared Text (Digraphs): %s\n", preparedText);

    // 3. Encrypt Plaintext
    encryptPlayfair(matrix, preparedText, ciphertext);
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    return 0;
}
