# CS201PortfolioProject

INSTRUCTIONS:

This game follows traditional Boggle rules allowing horizontal, vertical, and diagonal 
moves. The game only accepts words with  minimum length of 3 and doesn't accept proper nouns or any 
words containing irregular characters or punctuation marks. This game allows words with a maximum
of 30 letters. 

After execution, the game asks the user to choose game between two game modes: single 
player or two player by entering either a "t" or an "s". The game then asks for the board size. 
The size should be entered as one number, for instance, if a 5 is entered, a 5x5 board will be 
printed. Then the game asks for the name of the dictionary file, which is expected to be a 
text file with each word separated by a new line. When reading in and storing the dictionary, 
the code ignores words with capital letters, assuming them to be proper nouns, and ignores 
punctuation or words that contain special characters. 

The game then recursively searches for all words in the board. As it finds the words,
it stores them into a different trie called wordList. After finding all words, the board 
displays an instruction for the user to start a timer and enter words but the clock on the computer
works fine as well. Per official Boggle rules, the timer/ clock should count to 3 minutes and then
the round should be over. The words found are expected to be entered one-by-one. These words are
then checked against the wordList trie to ensure that they exist on the board and an appropriate 
point value is assigned based on the length of the word in accordance with official Boggle rules.
The user is not allowed to repeat words, as they are also stored in a separate trie called 
userWords. To end the round, the user types "endround." In single-player mode this allows the 
user to choose whether or not to play again by entering either "y" or "n." In two-player mode 
this causes a new board to generate for the second players turn. 
