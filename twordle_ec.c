//Author: Joseph Garcia Cruz
//Duplicate Letter Extra Credit
#include <stdio.h>
#define FILE_NAME "word.txt"
#define SIZE 100
#define WORD_LEN 5
#define MAX_GUESSES 6

void initializeSymbols(char symbols[]);
void calculateLetterMatches(char guessWords[], char symbols[], char solution[], int solutionUsed[]);
void placementCheck(char guessWords[], char solution[], int solutionUsed[]);
void lowerCase(char guessWords[]);
int lengthCheck(char guessWords[]);
int symbolCheck(char guessWords[]);
int solutionChecker(char guessWords[]);
void previousAttempts(char guessWords[][WORD_LEN + 1], int i);
int finalCheck(char guessWords[][WORD_LEN + 1], char solution[], int i); 
void getSolution(char solution[]);
void getGuess(char guessWords[][WORD_LEN + 1], int i); 
void validateGuess(char guessWords[]);

int main(){
    char solution[WORD_LEN + 1]; 
    char guessWords[MAX_GUESSES * 2][WORD_LEN + 1];

    getSolution(solution);

    int i = 0;
    for( i = 0; i < MAX_GUESSES * 2; i+=2){
        int solutionUsed[WORD_LEN] = {0}; 

        getGuess(guessWords, i); 
        validateGuess(guessWords[i]);
        lowerCase(guessWords[i]); 
        placementCheck(guessWords[i], solution, solutionUsed);
        initializeSymbols(guessWords[i + 1]);
        calculateLetterMatches(guessWords[i], guessWords[i + 1], solution, solutionUsed);
        
        if(finalCheck(guessWords, solution, i) == 1){ 
            return 0;
        }
        previousAttempts(guessWords, i);
    }
    return 0;
}

void validateGuess(char guessWords[]) {
    int isInvalid = 1;
    while (isInvalid) {
        int badLen = lengthCheck(guessWords); 
        int badSym = symbolCheck(guessWords);

        if (badLen == 0 && badSym == 0) {
            isInvalid = 0;
        } else {
            printf("\nPlease try again: ");
            scanf("%s", guessWords);
        }
    }
}

void getGuess(char guessWords[][WORD_LEN + 1], int i){
    if(i < (MAX_GUESSES * 2) - 3){
        printf("GUESS %d! Enter your guess: ", (i + 2) / 2);
        scanf("%s", guessWords[i]);
        printf("=================================\n");
    }
    else{
        printf("FINAL GUESS : ");
        scanf("%s", guessWords[i]);
        printf("=================================\n");
    }
}

void getSolution(char solution[]){
    FILE *fp;
    fp = fopen(FILE_NAME, "r");
    if(fp == NULL){
        printf("Cannot open file\n");
        return;
    }
    fscanf(fp, " %s", solution);
    fclose(fp);
}

int finalCheck(char guessWords[][WORD_LEN + 1], char solution[], int i){ 
    if((solutionChecker(guessWords[i]) == 1) && (i < (MAX_GUESSES * 2) - 3) && (i != 0)){
        printf("\t\t%s", solution);
        printf("\n\tYou won in %d guesses!\n\t\tGOATED!\n", (i + 2) / 2);
        return 1;
    }
    else if((solutionChecker(guessWords[i]) == 1) && (i > (MAX_GUESSES * 2) - 3)){
        printf("\t\t%s", solution);
        printf("\n\tYou won in 6 guesses!\n");
        return 1;
    }
    else if((solutionChecker(guessWords[i]) == 1) && (i == 0)){
        printf("\t\t%s", solution);
        printf("\n\tYou won in 1 guess!\n\t\tGOATED!\n");
        return 1;
    }
    else if((solutionChecker(guessWords[i]) == 0) && (i > (MAX_GUESSES * 2) - 3)){
        previousAttempts(guessWords, i); 
        printf("You lost, better luck next time!\n");
        return 1;
    }
    return 0;
}

void previousAttempts(char guessWords[][WORD_LEN + 1], int i){
    for(int j = 0; j <= i; j+=2){
        printf("%s\n", guessWords[j]);
        printf("%s\n", guessWords[j + 1]);
    }
}

int symbolCheck(char guessWords[]){
    int foundError = 0;
    for(int j = 0; guessWords[j] != '\0'; j++){
        if(!((guessWords[j] >= 'A' && guessWords[j] <= 'Z') || (guessWords[j] >= 'a' && guessWords[j] <= 'z'))){
            printf("Your guess must contain only letters.");
            foundError = 1;
            break;
        }
    }
    return foundError;
}

int lengthCheck(char guessWords[]){ 
    int size = 0;
    for(int j = 0; guessWords[j] != '\0'; j++){ 
        size++;
    }
    if(size != WORD_LEN){
        printf("Your guess must be 5 letters long. "); 
        return 1;
    }
    return 0;
}

void lowerCase(char guessWords[]){
    for(int j = 0; j < WORD_LEN; j ++){
        if(guessWords[j] >= 'A' && guessWords[j] <= 'Z'){
                guessWords[j] += 32; 
        }
    }
}

void placementCheck(char guessWords[], char solution[], int solutionUsed[]){
    for(int i = 0; i < WORD_LEN; i++){
        if(guessWords[i] == solution[i]){
            guessWords[i] -= 32;
            solutionUsed[i] = 1; 
        }
    }
}

void initializeSymbols(char symbols[]) {
    for (int x = 0; x < WORD_LEN; x++) {
        symbols[x] = ' ';
    }
    symbols[WORD_LEN] = '\0';
}

void calculateLetterMatches(char guessWords[], char symbols[], char solution[], int solutionUsed[]) {
    for (int x = 0; x < WORD_LEN; x++) {
            for (int j = 0; j < WORD_LEN; j++) {
                if (guessWords[x] == solution[j] && solutionUsed[j] == 0) {
                    symbols[x] = '^';
                    solutionUsed[j] = 1; 
                    break; 
                }
            }
    }
}

int solutionChecker(char guessWords[]){
    for(int i = 0; i < WORD_LEN; i++){
        if(guessWords[i] < 'A' || guessWords[i] > 'Z'){
            return 0;
        }
    }
    return 1;
}
