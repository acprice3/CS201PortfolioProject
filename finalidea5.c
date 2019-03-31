/*
CS 201 Portfolio Project
Allison Price

*/

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>

struct Letter {
  char letter; // Letter value displayed in the board (uppercase)
  int number; // Defines which node in the graph it is
  bool visited;
};


struct TrieNode
{
    struct TrieNode *children[26]; // All of the next possible letters
    bool isEndOfWord;
};

// Converts from lowercase ASCII letter values to indices of 0-25 for use in the trie
int giveIndex(char c) {
    int a = c - 'a';
    return a;
}

/***************************************************************************************
*    Title: Trie | (Insert and Search)
*    Author: Venkateswara Rao Sanaka
*    Date Accessed: 3/ 5/ 2019
*    Availability: GeeksforGeeks
*    Link: https://www.geeksforgeeks.org/trie-insert-and-search/
*
***************************************************************************************/
// Returns a new node with all children set to NULL and isEndOfWord set to false
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (pNode)
    {
        int i;
        pNode->isEndOfWord = false;
        for (i = 0; i < 26; i++)
            pNode -> children[i] = NULL; // set all children to null
    }

    return pNode;
}


/*Storing the dictionary requires ignoring the null character and the newline that separate
the different words, this handles that*/
void insertDictionary(struct TrieNode *branch, char *str)
{

    struct TrieNode *newNode = branch;
    for(int a = 0; a < strlen(str) - 1; a ++) { // This for loop differentiates between insertDictionary and insertToWordList

      if(newNode -> children[giveIndex(str[a])] == NULL) {
        newNode -> children[giveIndex(str[a])] = getNode();
      }

      newNode = newNode -> children[giveIndex(str[a])];

    }

    newNode -> isEndOfWord = true;
  }


  /***************************************************************************************
  *    Title: Trie | (Insert and Search)
  *    Author: Venkateswara Rao Sanaka
  *    Date Accessed: 3/ 5/ 2019
  *    Availability: GeeksforGeeks
  *    Link: https://www.geeksforgeeks.org/trie-insert-and-search/
  *
  ***************************************************************************************/
/*Storing a word into the wordList trie doesn't require ignoring the null character
that needs to be ignored while storing the dictionary*/
  void insertToWordList(struct TrieNode *root, const char *key)
{

    struct TrieNode *pCrawl = root;

    for (int a = 0; a < strlen(key); a++)
    {
        if (!pCrawl->children[ giveIndex(key[a])])
            pCrawl->children[ giveIndex(key[a])] = getNode();

        pCrawl = pCrawl->children[giveIndex(key[a])];
    }

    pCrawl->isEndOfWord = true;
}

/***************************************************************************************
*    Title: Trie | (Insert and Search)
*    Author: Venkateswara Rao Sanaka
*    Date Accessed: 3/ 5/ 2019
*    Availability: GeeksforGeeks
*    Link: https://www.geeksforgeeks.org/trie-insert-and-search/
*
***************************************************************************************/
bool search(struct TrieNode *root, char *key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < strlen(key); i++)
    {
        if (!pCrawl->children[giveIndex(key[i]))
            return false;

        pCrawl = pCrawl->children[giveIndex(key[i])];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

/***************************************************************************************
*    Title: Trie | (Display Content)
*    Author: Yash Singla
*    Date Accessed: 3/ 5/ 2019
*    Availability: GeeksforGeeks
*    Link: https://www.geeksforgeeks.org/trie-display-content/
*
***************************************************************************************/
void display(struct TrieNode* root, char str[], int level)
{
    // If node is leaf node, it indicates end
    // of string, so a null character is added
    // and string is displayed
    if (root->isEndOfWord != false)
    {
        str[level] = '\0';
        printf("%s\n", str);

    }

    int i;
    for (i = 0; i < 26; i++)
    {
        // if NON NULL child is found
        // add parent key to str and
        // call the display function recursively
        // for child node
        if (root -> children[i])
        {
            str[level] = i + 'a';
            display(root -> children[i], str, level + 1);
        }
    }
}

/*Returns the lowercase value of the letter so long as it is currently an uppercase letter */
char lower(char a) {
{
    if ((a >= 65) && (a <= 90))
        a = a + 32;
    return a;
  }
}

/*Makes sure that a string only contains integers and no character*/
bool isNumber(char *str) {
   for (int i = 0; i < strlen(str); i ++) {
     if (isdigit(str[i]) == false) {
       return false;
     }
   }

   return true;
}

/*Returns true if the string contains only lowercase alphabetical characters and false otherwise */
bool onlyLowerAlpha(char *str) {

   for (int i= 123; i <= 255; i ++) { // Checks for non-alphabetical characters
     if (strchr(str, i) != NULL) {    // and accented letters and disregards them
       return false;
     }
   }

   for (int i = 33; i <= 96; i ++) { // More checks for non-alphabetical characters,
     if (strchr(str, i) != NULL) {   // numbers, punctuation, and capital letters
       return false;
     }
   }

   return true;

}

/*Checks for a path in a trie rather than a whole word
(doesn't check for isEndOfWord)*/
bool existInTrie(struct TrieNode *root, char *word) {

  struct TrieNode *ptr = root;
  for (int a = 0; a < strlen(word); a++) {
    if ((giveIndex(word[a]) < 0) || (giveIndex(word[a]) > 26)) { // If the index is invalid
       return false;
    }

    if(ptr -> children[giveIndex(word[a])] == NULL) { //
      return false;
    }

    ptr = ptr -> children[giveIndex(word[a])];
  }

  return (ptr);
}

/*Checks whether or not those coordinates in the 2D array have been checked already
and if they exist within the bounds of the board*/
bool withinBounds(int i, int j, int boardSize, struct Letter **array) {

   if ((i >= boardSize) || (j >= boardSize) ) { // If either i or j is greater than the boardsize (not on the board)
     return false;
   }

   else if(array[i][j].visited == true) {// If that point in the 2D array has been visited
     return false;
   }

   else if ((i < 0) || (j < 0)) { // If either i or j is less than 0 (not on the board)
     return false;
   }

   else {
     return true; // Return true if none of the other reasons cause the function to return false
   }
}

/*Returns the lowercase letter at the given vertex in the game board*/
char charInBoard (int vertex, int boardSize, struct Letter **array) {

   char charInBoard;
   for (int i = 0; i < boardSize; i ++) {
      for (int j = 0; j < boardSize; j ++ ) {
         if (vertex == array[i][j].number) {
            charInBoard = lower(array[i][j].letter);
        }
      }
    }

   return charInBoard;
}

/*When a word is found in the wordSearch function, this stores it into the wordList trie if it is not already
present in the trie and if it is longer than 2 letters (per official Boggle rules)*/
void foundWord(int i, int j, int letterIndex, int boardSize, char *word, struct Letter **array, struct TrieNode *wordList) {

  if ((!search(wordList, word)) && (strlen(word) > 2)) { // If it's longer than 2 letters and isn't already stored
    insertToWordList(wordList, word);
  }
}

/*Function to recursively check all 8 directions around each letter to find all possible paths on the board */
void wordSearch(int i, int j, int letterIndex, int boardSize, char *word, struct Letter **array, struct TrieNode *root, struct TrieNode *wordList) {

  word[letterIndex] = lower(array[i][j].letter);
  array[i][j].visited = true;

/* If this is a word in the dictionary then call foundWord */
  if (search(root, word)) {
     foundWord(i, j, letterIndex, boardSize, word, array, wordList);

  }

/* Stop pursuing this path if it doesn't exist in the trie */
  if ((letterIndex > 0) && (existInTrie(root, word) == false)) {
    array[i][j].visited = false;
    word[letterIndex] = '\0'; // Backtrack
    letterIndex--;
    return;

  }

  if(withinBounds(i + 1, j, boardSize, array)) { // Checks down
    wordSearch(i + 1, j, letterIndex + 1, boardSize, word, array, root, wordList);
  }

  if(withinBounds(i - 1, j, boardSize, array)) { // Checks up
    wordSearch(i - 1, j, letterIndex + 1, boardSize, word, array, root, wordList);
  }

  if(withinBounds(i, j + 1, boardSize, array)) { // Checks right
    wordSearch(i, j + 1, letterIndex + 1, boardSize, word, array, root, wordList);
  }

  if(withinBounds(i, j - 1, boardSize, array)) { // Checks left
    wordSearch(i, j - 1, letterIndex + 1, boardSize, word, array, root, wordList);
  }

  if(withinBounds(i + 1, j + 1, boardSize, array)) { // Checks down and to the right
    wordSearch(i + 1, j + 1, letterIndex + 1, boardSize, word, array, root, wordList);
  }

  if(withinBounds(i + 1, j - 1, boardSize, array)) { // Checks down and to the left
    wordSearch(i + 1, j - 1, letterIndex + 1, boardSize, word, array, root, wordList);
  }

  if(withinBounds( i - 1, j + 1, boardSize, array)) { // Checks up and to the right
    wordSearch(i - 1, j + 1, letterIndex + 1, boardSize, word, array, root, wordList);
  }
  if(withinBounds(i - 1, j - 1, boardSize, array)) { // Checks up and to the left
    wordSearch(i - 1, j - 1, letterIndex + 1, boardSize, word, array, root, wordList);
  }

  array[i][j].visited = false; // Backtracking through to find all paths
  word[letterIndex] = '\0'; // Reset this point in the path
  letterIndex--;

}

/*Returns the score with the updated added points from each new word.
The point values are based on Boggle rules*/
int calcScore(char *str, int currScore) {

    int size = strlen(str);

    if (size >= 8) {
      return currScore += 11;
    }
    else if (size == 7) {
      return currScore += 5;
    }
    else if (size == 6) {
      return currScore += 3;
    }
    else if (size == 5) {
      return currScore += 2;
    }
    else if ((size == 4) || (size == 3)) {
      return currScore += 1;
    }

return currScore;
}

/* This function contains the game logic and allows multiple games to be played with the game storing a
high score between games for single player and a count of wins and losses per player for two player*/
int gamePlay(int bsize, char *dictionaryFile, char *diceArray[17]) {

   int numDice = bsize * bsize;
   int a = numDice - 1;

   struct Letter *boggle[bsize];
   for (int i = 0; i < bsize; i ++) {  // Dynamically allocating space for the board
     boggle[i] = (struct Letter*)malloc(bsize * sizeof(struct Letter));
   }

   srand(time(0));
   int k = 0;
   for (int i = 0; i < bsize; i++) {
      for (int j = 0; j < bsize; j++) {
         int whichDice = (rand() % 15); // Chooses 1-16 dice
         int diceSide = (rand() % 6 ); // Chooses 1-6 sides of dice

         if (a % bsize != 0) {
            printf("%c  ", diceArray[whichDice][diceSide]);// Prints the board

            boggle[i][j].letter = diceArray[whichDice][diceSide]; // Stores the board
            boggle[i][j].visited = false;
            boggle[i][j].number = k;
            k++;
          }

         else {
            printf("%c \n", diceArray[whichDice][diceSide]); // Prints the board

            boggle[i][j].letter = diceArray[whichDice][diceSide]; // Stores the board
            boggle[i][j].visited = false;
            boggle[i][j].number = k;
            k++;

          }
        }

       printf("\n\n");
    }

   FILE *dictionary;
   char str[128];
   int insertedWords = 0;

   dictionary = fopen(dictionaryFile, "r");

   struct TrieNode *root = getNode(); // Creates the root to the trie that will hold the dictionary
   while (fgets(str, 128 , dictionary)) {

      if ((strlen(str) > 2) && (onlyLowerAlpha(str) == true)) { // Ensures that the word is longer than two
         str[strlen(str) - 1] = '\0';                           // letters and only composed of lowercase letters
         insertDictionary(root, str);
         insertedWords++; // The number of words that are stored in the dictionary trie
      }
    }

   fclose(dictionary);
   int level = 0;
   int letterIndex;
   char letters[31]; // Variable used in displaying the wordList trie
   int score = 0;
   char word[31];
   char word2[31];

   struct TrieNode *wordList = getNode(); // Make a new trie holding the words found in the board
   struct TrieNode *userWords = getNode(); // Make a third trie to hold the words entered by the user

   for (int i = 0; i < bsize; i ++) {
      for (int j = 0; j < bsize; j ++) {

         for (int x = 0; x < bsize; x++) {  // Set visited to false before every iteration of the scan function
            for (int y = 0; y < bsize; y++) {
                boggle[x][y].visited = false;
               }
            }

         for (int z = 0; z < 31; z ++) {
            word2[z] = '\0';
           }

         letterIndex = 0;
         wordSearch(i, j, letterIndex, bsize, word2, boggle, root, wordList);

      }
    }

   while(1) {

      printf("\nEnter Word (one by one): ");
      scanf("%30s", word);

      if (!onlyLowerAlpha(word)) {
        printf("Not a valid word! Make sure you're only using lowercase letters\n");
      }

      else if(strcmp(word, "endround") == 0) { // Exit round if user inputs "endround"
          break;
       }

      else if ((strlen(word) > numDice) || strlen(word) < 3 || strlen(word) > 30) {  // If the word has more letters than there are dice on the board
         printf("Not a valid word length!\n ");                                      // or is shorter than 3 letters, or is longer than the maximum
       }                                                                             //  word length

       else {

      bool there = search(wordList, word);

      if (there == true) {                               // If the word exists in the dictionary
         bool alreadyFound = search(userWords, word);    // check to see if it has already been found
         if (alreadyFound == true ) {                    // if it has, don't give more points for it
           printf("That word has already been found!\n");
         }

         else {                                           // If it hasn't already been found, then store it into the userWords
           insertToWordList(userWords, word);             // trie and update the score
           score = calcScore(word, score);
           printf("Nice! Your current score is %d\n", score);
        }
     }

      else {
         printf("That word doesn't exist\n");
      }
    }
  }

   printf("\n\nThe computer found the following words: \n");
   display(wordList, letters, level); // Displays the list of all words in the board

//Free all allocated memory
   free(root);
   free(wordList);
   free(userWords);

   for (int i = 0; i < bsize; i ++) {
     free(boggle[i]);
   }

   return score;

}

int main(void) {

  printf("\n\nBB BB           OOOO            GGG                GGG           LL            EEEEEEEE         \n");
  printf("BB    BB      OO    OO        GG   GG            GG   GG         LL            EE               \n");
  printf("BB     BB    OO      OO      GG     GG          GG     GG        LL            EE               \n");
  printf("BB    BB    OO        OO    GG                 GG                LL            EE               \n");
  printf("BB BB       OO        OO    GG                 GG                LL            EEEEEE           \n");
  printf("BB   BB     OO        OO    GG      GGGGGG     GG      GGGGGG    LL            EE               \n");
  printf("BB     BB   OO        OO    GG        GG       GG        GG      LL            EE               \n");
  printf("BB      BB   OO      OO      GG      GG         GG      GG       LL            EE               \n");
  printf("BB     BB     OO    OO        GG    GG           GG    GG        LL            EE               \n");
  printf("BB BBBB         OOOO            GGGG               GGGG          LLLLLLLLLLL   EEEEEEEE         \n");


  char die0[6] = {'R', 'I', 'F', 'O', 'B', 'X'}; // General Boggle dice
  char die1[6] = {'I', 'F', 'E', 'H', 'E', 'Y'};
  char die2[6] = {'D', 'E', 'N', 'O', 'W', 'S'};
  char die3[6] = {'U', 'T', 'O', 'K', 'N', 'D'};
  char die4[6] = {'H', 'M', 'S', 'R', 'A', 'O'};
  char die5[6] = {'L', 'U', 'P', 'E', 'T', 'S'};
  char die6[6] = {'A', 'C', 'I', 'T', 'O', 'A'};
  char die7[6] = {'Y', 'L', 'G', 'K', 'U', 'E'};
  char die8[6] = {'Q', 'B', 'M', 'J', 'O', 'A'};
  char die9[6] = {'E', 'H', 'I', 'S', 'P', 'N'};
  char die10[6] = {'V', 'E', 'T', 'I', 'G', 'N'};
  char die11[6] = {'B', 'A', 'L', 'I', 'Y', 'T'};
  char die12[6] = {'E', 'Z', 'A', 'V', 'N', 'D'};
  char die13[6] = {'R', 'A', 'L', 'E', 'S', 'C'};
  char die14[6] = {'U', 'W', 'I', 'L', 'R', 'G'};
  char die15[6] = {'P', 'A', 'C', 'E', 'M', 'D'};

  char *diceArray[17];

  diceArray[0] = die0;
  diceArray[1] = die1;
  diceArray[2] = die2;
  diceArray[3] = die3;
  diceArray[4] = die4;
  diceArray[5] = die5;
  diceArray[6] = die6;
  diceArray[7] = die7;
  diceArray[8] = die8;
  diceArray[9] = die9;
  diceArray[10] = die10;
  diceArray[11] = die11;
  diceArray[12] = die12;
  diceArray[13] = die13;
  diceArray[14] = die14;
  diceArray[15] = die15;

   int bsize = 0;
   char gameMode = '\0';
   char gMode[20];
   char size[20];
   char dictionaryFile[50];
   FILE *dictionary;

   printf("\n\nChoose Game Mode: \nS - Single Player \nT - Two Player \n");
   scanf("%s", gMode);

   while (strlen(gMode) >= 2) { // Makes sure the user only enters one letter
     printf("Only enter one letter! Try again: \n");
     scanf("%s", gMode);
   }

   gameMode = gMode[0]; // Converting gMode to a character
   while (gameMode != 'S' && gameMode != 's' && gameMode != 'T' && gameMode != 't') { // If not "s" or "t" ask for input again
     printf("Not a valid game mode! Try again here: ");
     scanf(" %c", &gameMode);
   }

   printf("\nBoard Size (in form NxN)? Enter a side length: ");
   scanf("%s", size);

   while (!isNumber(size)) { // Makes sure that the user enters a number for board size
     printf("Not a valid board size! Try again: "); // Asks for input again if the board size entered contains anything
     scanf("%s", size);                             // besides numbers
   }

   bsize = atoi(size);                             // Converts to an integer

   printf("\nWhat is the name of the dictionary file?\n");
   scanf("%s", dictionaryFile);

   dictionary = fopen(dictionaryFile, "r");
   while (dictionary == NULL) { // Ensures that the dictionary file entered isn't NULL
      printf("Error! Can't find that dictionary file! Enter a different one: \n");
      scanf("%s", dictionaryFile);
      dictionary = fopen(dictionaryFile, "r");
    }

  fclose(dictionary);

   // This if statement is for the single player mode
   if ((gameMode == 'S') || (gameMode == 's')) {

      int pscore = 0;
      int highScore = 0;
      char again[20];
      char playAgain = '\0';

      while(playAgain != 'n' && playAgain != 'N') { // As long as the user doesn't say no to playing again,
                                            // The game continues running
         printf("Start your timer now!\n\n");
         pscore = gamePlay(bsize, dictionaryFile ,diceArray);

         if (pscore > highScore) { // Updates high score
            highScore = pscore;
         }

          printf("Current High Score is: %d\n", highScore);

          printf("\nPlay again? Enter 'y' or 'n': ");
          scanf("%s", again);

          while (strlen(again) >= 2) { // Make sure the user enters only one character
            printf("Only enter one letter! Try again: ");
            scanf("%s", again);
          }

          playAgain = again[0]; // Convert to character
          while (playAgain != 'y' && playAgain != 'Y' && playAgain != 'n' && playAgain != 'N') {
            printf("Not a valid answer! Try again: ");
            scanf(" %c", &playAgain);
          }
      }
   }


   //This is the two player option
   else  {
      int p1score, p2score;
      int p1games = 0;
      int p2games = 0;
      char again[20];
      char playAgain = '\0';

      while(playAgain != 'n' && playAgain != 'N') {
         printf("Player 1 goes first! Start the timer now!\n\n");
         p1score = gamePlay(bsize, dictionaryFile ,diceArray);

         printf("\n\nPlayer 2's Turn! The timer starts now!\n\n");
         p2score = gamePlay(bsize, dictionaryFile ,diceArray);

         if (p1score > p2score) {  // Keeps track of game count
            printf("Player 1 Wins!\n");
            p1games++;
         }

         else if(p2score > p1score) {
            printf("Player 2 Wins!\n");
            p2games++;
       }

         else {
           printf("It's a tie!\n\n");
           p1games++;
           p2games++;
      }

   printf("\nPLAYER 1: %d games won and PLAYER 2: %d games won\n", p1games, p2games);
   printf("\n\nPlay again? Enter 'y' or 'n': ");
   scanf("%s", again);

   while (strlen(again) >= 2) { // If the user enters more than one character, ask for the input again
     printf("Only enter one letter! Try again: ");
     scanf("%s", again);
   }

   playAgain = again[0]; // Convert it to a character
   while (playAgain != 'y' && playAgain != 'Y' && playAgain != 'n' && playAgain != 'N') { // If the one character
     printf("Not a valid answer! Try again: ");                                           // isn't "y" or "n" then ask for it again
     scanf(" %c", &playAgain);
    }
  }
}

  return 0;

}
