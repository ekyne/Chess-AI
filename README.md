# <p style="text-align: center;">Chess AI (Under Construction)</p>
![ChessBoard](https://drive.google.com/uc?export=view&id=1elM9pOUX_ILduRzbG0oNMdm1V3eBQIhi)

This is a chess project written in C++, which includes the SDL2 library for the purpose of demonstrating the computational complexity and capabilities an artitifical intelligence can achieve when using compiled programming languages.

The end goal for the AI is to evaluate all possible states of the chess board by using sophisticated depth-first-search algorithms, more specifically the minimax algorithm accompanied with alpha-beta pruning.
## SDL2 Library Setup
This program has only been tested on Unix/Linux-based systems, but compatability for Windows-based systems will be worked on in future updates. For now, the usage of Unix/Linux commands on Windows, as well as any dependencies required by both operating systems, can be obtained by following the links below:

[MinGW-w64 - for Linux](https://www.mingw-w64.org/downloads/)

[MinGW-w64 - for 32 and 64 bit Windows](https://sourceforge.net/projects/mingw-w64/)

[SDL version 2.0.20 (stable)](https://www.libsdl.org/download-2.0.php)

[SDL2_image](https://www.libsdl.org/projects/SDL_image/)

After downloading the SDL2 and SDL2_image libraries, follow the installation instructions below:

[SDL2 Installation Guide](https://wiki.libsdl.org/Installation)

[SDL2_image Documentation](https://libsdl.org/projects/SDL_image/docs/index.html)

To compile and run the program, navigate to the folder and type in the following commands:
```
make
./run
``` 
## Artificial Intelligence
![MiniMax](https://drive.google.com/uc?exportv=view&id=1vNiWAedsmBtJ8iHvTsb6ACzSxPvHkRCq)

As stated above, the artificial intelligence evaluates the different states of the chess board to calculate the best move to play. 

### Minimax Algorithm
Minimax is an excellent algorithm to apply to any kind of match-based game for an AI because for each possible move the AI can make, the least costly move for the AI from the user's perspective can be calculated on the next future state of the search algorithm as well. Gauging the best move to play with the least to lose is what causes the AI to become a "smarter" player.

More on Minimax Algorithm:
[MiniMax - Chessprogramming Wiki](https://www.chessprogramming.org/Minimax)
### Alpha-beta Pruning
![AlphaBeta](https://drive.google.com/uc?exportv=view&id=1QyirinekIbSXeoOnu4ZmDiQ0vfX_3wK7)

The Minimax algorithm is great at computing the best potential moves which an AI can play. However, the several layers of chess board states to evaluate can come at a great computational cost. Many computations may be uneccessary, as some board evaluations may not recover from negative results.

Alpha-beta pruning becomes useful to implement into the Minimax algorithm because the method prunes future states of the board that have worse possible values for the AI from the player's perspective than the least values to be gained from the AI's.

More on Alpha-beta Pruning: 
[Alpha-Beta - Chessprogramming Wiki](https://www.chessprogramming.org/Alpha-Beta)
