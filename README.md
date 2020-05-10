# 2020-pd2-sokoban

2020-pd2-sokoban is an assignment for 2020's Program Design course in NCKU.
This particular instance is inspired by the popular Japanese game Sokoban, with a few thematic changes in the gameplay but other wise unchanged in the general rules.
In Sokoban, the player pushes boxes onto storage points.
In my version, the player bushes big stones onto marks.

## Video link


https://www.youtube.com/watch?v=1e-kAJEDCY8


## How to play

Main Menu:

	Player will be prompted with a window.

	On the right, there are four buttons to manipulate with.
	"Start Game" starts a new game.
	"Level _" indicate the level you will be in when you start a new game.
	When the focus is on "Level _", use arrow keys left or right to change levels or click it by mouse.
	"LoadSavedGame" loads the game status previously saved by a player. If there is none, player stays in the main menu.
	"Quit" will exit the game.
	
	There is a kunai(ninja knife) on the left to indicate which button you are currently focused on.
	In addition to that, the focused button will also appear a little bigger.
	To move focus to a button and choose you can either:
	Use the arrow key up and down to move the focus, and press Enter to choose.
	Or hover the cursor/mouse over that button to move focus to it and click to choose.

	On the left, there stands the character you will be using to play the game.
	Hover the cursor over that character and "Game Intro" will appear in a speech bubble.

Gameplay:

	In the gameplay menu, you will be presented with a maze-like map.
	In th map, player is encircled by units of walls, between the walls, there are stones waiting to be pushes and marks waiting to be matched.
	The marks are a symbol of a leaf, and on each stone there is the same symbol.
	When unmatched, the symbol on the stone is yellow, but turns red when it's moved onto a mark.
	Player can be manipulated by the arrow keys to push stones around.
	
	On top of the map is the status bar. There you can see:
	Step count.
	Level.
	Special keys to manipulate the game with, including:
		Esc to escape to main menu.
		S to save game.
		R to restart the same game (same map).
		N to start a new game, with a different map.
		Z to undo the previous step.
	Current Status: what the player is doing, warnings, and winning prompts.

	When level 1 is cleared, we are on to level two. When level 2 is cleared, we go back to the main menu.


## Features
 
	Can save game status (step count, map status, level, etc.) and load it later in the future.
	Can show step count.
	Shows main menu.

## Bonus

	Background music.
	Winning sound effect.
	Walls collapse when winning, so that player is not trapped anymore.
	Character walks out after winning.
	Can start a new game (different map, rather than restarting the same map).
	Shows the number of stones matched and how many more to match.
	Shows movement types. (Status bar line 4)

	

