<link href="http://kevinburke.bitbucket.org/markdowncss/markdown.css" rel="stylesheet"></link>

pmuj Design Document
====================
pmuj is a new game written in C, designed to be a fun experience.

Overview
---------------------
A game where vertical movement is crucial.
Jumping in particular is encouraged.

High Level Design
---------------------
Presents the high-level design of the system.

###sys
This is the system-specific layer and it will have different directives based on whether it is linux or windows-specific.

###logic
The logic layer defines the "game" itself. All of the game's features such as physics and gameplay are stored here.

###view
This handles all of the rendering of the game and takes input from the user.


Alternative Design (in C)
--------------------

	Physics* physics = physics_new();
	physics_init(physics);
	GameLogic* gamelogic = gamelogic_new();
	gamelogic_init(gamelogic);
	GameView* gameview = gameview_new();
	view_init(gameview);
	
	while(true) {
		physics_mainloop(physics); //Move our guys along, if there is nothing then this does nothing.
		GameState* gamestate = get_game_state(physics); //Retrieves physics object positions
		gamelogic_mainloop(gamelogic, gamestate); //Acts on current positions of physical objects
		gameview_mainloop(gameview, gamestate); //Shows the current state of the game, also handles user input, etc.
	}
