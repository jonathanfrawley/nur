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
