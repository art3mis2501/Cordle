#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/*
    in order to make a wordle i'll need to make a char[] to house
    the WORD, and ig thats easier than using a string maybe cuz i
    can iterate through the array to check each letter.
    This should be easy (i hopes lol :p)
*/


int pickWord(char word[]){
    FILE *file = fopen("words.txt", "r");
    if (!file) return 1;

    int count = 0;
    char buffer[6];

    // 1. Count total lines
    while (fgets(buffer, sizeof(buffer), file)) {
        count++;
    }

    if (count > 0) {
        // 2. Pick a random index
        srand(time(NULL));
        int target = rand() % count;

        // 3. Go back to start and find that line
        rewind(file);
        for (int i = 0; i <= target; i++) {
            fgets(buffer, sizeof(buffer), file);
        }
    }

    fclose(file);

    for(int i=0; i<6; i++){
        word[i] = buffer[i];
    }

    return 0;
}

int main(){
    char word[6];
    char guess[6];
    char result[6] = "_____";
    bool run = true;
    bool game = false;
    bool help = false;
    bool victory = false;

    
    while(run == true){

        // PICKING RANDOM WORD
        pickWord(word);
    
        int select;
        printf("---------------------------------------------------\n");
        printf("  _____   ____     ____     ____     _       _____       \n");
        printf(" //     //    \\\\  ||   \\\\  ||   \\\\  ||      ||    |\n");
        printf("||     ||      || ||___//  ||    || ||      |_____       \n");
        printf("||     ||      || ||   \\\\  ||    || ||      ||         \n");
        printf(" \\\\____ \\\\____//  ||    \\\\ ||___//  |_____| |_____|\n\n");
        printf("---------------------------------------------------\n");
        printf("~A Wordle clone by art3mis2501~\n\n");
        printf("---------------------------------------------------\n");
        printf("> 0...........................................START\n");
        printf("> 1....................................HELP / ABOUT\n");
        printf("> 2............................................QUIT\n");
        printf("> Select a number: ");

        scanf("%d", &select);
        
        switch(select){
            case 0:
                // START GAME
                game = true;
                system("clear");
                break;
            case 1:
                 // HELP||ABOUT SESSION
                help = true;
                system("clear");
                break;
            case 2:
                // QUIT GAME
                run = false;
                system("clear");
                break;
        }
        
        // HELP||ABOUT SESSION
        while(help == true){
            printf("---------------------------------------------------\n\n");
            printf("||   ||  ____   _      ____  \n");
            printf("||___|| ||   | ||     ||   \\ \n");
            printf("| ___ | |____  ||     ||___/ \n");
            printf("||   || ||     ||     ||     \n");
            printf("||   || |____| |____| ||     \n\n");
            printf("---------------------------------------------------\n\n");
            
            printf("> A random word will be selected and you must try to guess it.\n");
            printf("> The word will slowly be revealed as you guess\n");
            printf("> A # symbol indicates a correct letter in the wrong place\n");
            
            printf("---------------------------------------------------\n\n");
            printf("  _____    ___     _____    _     _   ______ \n");
            printf(" //   \\\\  || \\\\   //   \\\\  ||     || |  ||  |   \n");
            printf("||_____|| ||_//  ||     || ||     ||    ||   \n");
            printf("| _____ | ||  \\\\ ||     || ||     ||    ||    \n");
            printf("||     || |___//  \\\\___//   \\\\___//     ||     \n");
            printf("---------------------------------------------------\n\n");
            
            printf("> CORDLE is a clone of Wordle I made for learning C\n");
            printf("> This is just a silly little project, theres probably\n");
            printf("> better ways to make it but this is my first try :p\n\n");
            printf("> https://github.com/art3mis2501\n> :3\n\n");

            
            int c = 1;
            while(c != 0){
                printf("> Insert 0 to return to the title screen: ");
                scanf("%d", &c);
            }
            system("clear");
            help = false;
            break;
        }
        // GAME LOOP
        while(game == true){
            printf("---------------------------------------------------\n");
            //printf("%s", word); // UNCOMMENT THIS TO DEBUG THE WORD
            printf("Your guess: ");
            scanf("%s", guess);

            // WAIT FOR INPUT
            if(strlen(guess) < 4 || strlen(guess) >= 6){
                for(int i=0; i<5; i++){
                    guess[i] = '_';
                }
                
                printf("---------------------------------------------------\n");
                printf("Input a FIVE letter word!!!\n");
                printf("---------------------------------------------------\n");
                
            }

            // COMPARE INPUT AND WORD
            for(int i=0; i<5; i++){
                // WIN CONDITION
                if(strcmp(word, guess) == 0){
                    victory = true;
                    break;
                }

                // right letter wrong place
                if(strchr(word, guess[i])){
                    result[i] = '#';
                }
                // right letter right place
                if(word[i] == guess[i]){
                    result[i] = guess[i];
                }
            }
            printf("%s\n", result);

            // IF WIN GO TO VICTORY SCREEN
            // IF NOT, GO BACK TO INPUT
            // VICTORY SCREEN
            while(victory == true){
                system("clear");

                printf("---------------------------------------------------\n\n");
                printf("||      // || ||\\  ||  \n");
                printf("|| /|| //  || ||\\\\ || \n");
                printf("||//||//   || || \\\\|| \n");
                printf("| / | /    || ||  \\\\| \n\n");
                
                printf("> The word was %s!\n\n", word);

                printf("> 0........................................PLAY AGAIN\n");
                printf("> 1.............................................TITLE\n");
                printf("> 2..............................................QUIT\n");
                printf("> Select a number: ");

                scanf("%d", &select);

                switch(select){
                    case 0:
                    // PICKING RANDOM WORD
                    pickWord(word);
                    
                    printf("---------------------------------------------------\n");
                        victory = false;
                        for(int i=0; i<5; i++){
                            result[i] = '_';
                        }
                        system("clear");
                        break;
                    case 1:
                    printf("---------------------------------------------------\n");
                        victory = false;
                        game = false;
                        for(int i=0; i<5; i++){
                            result[i] = '_';
                        }
                        system("clear");
                        break;
                    case 2:
                    printf("---------------------------------------------------\n");
                        printf("Thanks for playing!\n");
                        printf("---------------------------------------------------\n");
                        victory = false;
                        game = false;
                        run = false;
                        system("clear");
                        break;
                }
                
            }
        }
    }
    
    return 0;
}