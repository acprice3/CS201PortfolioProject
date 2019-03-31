# CS201PortfolioProject

INSTRUCTIONS:

This game follows traditional Boggle rules, so: 
- Words must be created using adjoining letters in any direction, this means they can be 
  diagonal, horizonal, or vertical, and in any direction
- The same dice (or letter) cannot be used multiple times in one word 
- Words must be 3 letters or longer, and no proper nouns or words containing special characters 
  or punctuation are allowed, as there are not dice containing the necessary punctuation or special
  characters to spell those words
- The player has 3 minutes to find all of the words possible on the board 
  
The game also follows a few rules based on my program itself: 
- The game allows words of up to 30 letters, based on the word "floccinaucinihilipilification" 
  which is 29 letters long and the longest non-technical word in the English language according to 
  the Oxford English Dictionary.
  
There a few steps to follow to start the game. After compilation (done through typing "make") the 
game is executed by typing "./boggle" in the command line. The game asks for 3 things: 

1.) The game mode. This is going to be either "s" or "t" for single player or two player. 
2.) The board size. This is going to be a single number. For instance, if a 5 is entered, a 5x5 board
    will be generated. Though you can choose to generate a board of any size, I recommend choosing 
    somewhere between 4x4 and 45x45. This is because, since the board is generated randomly, there is a 
    chance that the board could be unsolvable (as in, it could contain no words) if it is too small. While the
    game can reach much larger sizes than 45x45, at that point, the lines of letters will begin to overlap, 
    and since Boggle relies on being able to see which letters are adjacent, this makes the game much more 
    difficult to play. 
3.) The dictionary file. This should be stored locally and should contain words separated by a newline.
    My program will ignore any words containing capital letters or punctuation, so the words in the
    file should be entirely composed of lowercase letters. The list that I used can be found at this
    link: https://users.cs.duke.edu/~ola/ap/linuxwords. If you decide to use this file, just store it 
    into a .txt file and enter the title, for example "words.txt" when the game asks for the dictionary 
    file. Otherwise, any dictionary file will work so long as it matches the format (separated by a newline, 
    with all non-proper nouns composed entirely of lowercase letters and no punctuation or special characters)

The game will then display the board and an instruction to start your timer. This can be done on a phone or simply 
through the clock on your computer. The game will then recursively search through the board to find all possible words. 
As the words are found, they are stored into a trie called wordList. Once the computer has found all of the words in 
the board, the game will display the line "Enter Word (one by one):." You should wait for this to show up before 
attempting to enter any words, as the computer will not yet have compiled a list of all possible words. As stated in 
the instruction, the words are expected to be entered one-by-one and using all lowercase letters. If the user happens 
to enter a word with a non-legal character, the game will display a warning that words should be lowercase. The user 
is not allowed to repeat words, since as they are entered they are stored in a separate trie. If written in legal 
characters, the word is checked against the wordList trie. The point value of the word depends on the word length. 
The Boggle rules for point assignment are as follows: 

3 and 4 letters: 1 point
5 letters: 2 points
6 letters: 3 points
7 letters: 5 points 
8 letters and up: 11 points 

After 3 minutes, the round should be over. The user can end the round by typing "endround" in the "Enter Word" space. 
At this point, the computer will display a list of all words possible in the board. In single player, the computer will then
display the users current high score, and the user will have the option to enter "y" or "n" to play another round or not. 
In two player mode this will generate another random board and then give an instruction to start the tier for the second 
player. Once the second player types "endround" the computer will display who won that round, along with a current game count, 
and the users will have the option to enter "y" or "n" to play another round or not. 


