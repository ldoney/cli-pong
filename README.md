# Intro
This is a command line interface pong game written in C!

# Software
This project was built with ncurses, and is a cli-only pong game which requires 2 players. A fun way to play this online is to use `tmux` to interface two people in the same console.

# Build instructions
As this repository has a makefile, the only thing you need to do is type: `make` to build the project. The executable should be in the build directory labeled `pong`

Alternatively, you can type `make install` to install the program to your system, then type `pong` to start the game! (You may need to run this as sudo)

# Removing the game
Typing `make clean` will remove the project
