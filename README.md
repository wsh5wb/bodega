Game design engine

Two running options:

* With sanitizer: `make sanitizer`

* Without sanitizer: `make`

Once compiled, use `make run` to run game

Note, you may need to first run sudo apt-get install libsdl2-mixer-dev on Linux or the equivalent on Mac 


# Controls for Beta demo

## Keyboard

* W,A,S,D to move

* M to show map

* O to kill an enemy in room

* V to show entire map

* I to show Player Stat-Bar

* Arrow keys to shoot basic projectiles.

* 1, 2, 3 to swtich projectile types. (1 = damage, 2 = slow, 3 = enemy damage reduction). 

    * Q can also be used to cycle through options

* Space to switch dungeons

* P to pause

* U to enter camera translation mode

While in translation mode:

* I,J,K,L to move camera between adjacent room cells
* N to reset character and camera to main room

## Controller (Following SDL naming conventions)

* Left analog stick & DPad

* A,B,X,Y to shoot (trying to figure out how to access second analog stick)

* Start to pause

* Select to show map

* Left Shoudler to show/hide stats

* Right Shoulder to cycle projectile types

Design Team Updates:

The design team has a list of improvements/fixes [here](https://docs.google.com/document/d/1Vw37CF8795uhCfMkIPn0JKTlangwVjGw3f4ACLpiLIM/edit?usp=sharing).


Engine Team Updates:

please follow [this](https://docs.google.com/document/d/1m7RXt5DKx1u3NiiAQ-okWMZr8DN_itFcN2jOhSwEcOY/edit?usp=sharing) shareable link to see Engine team changes and fixes.

Level Team Updates:

For Daniel and Tonks, we focused on removing bugs with scene transitions, removing faulty environemnt collisions, adding in preliminary spawners for our third and fourth areas, added in a player information system and textbox, worked out bugs in our projectile/collision system and updated visuals for player projectiles, and locating theme music for each of our four areas. We also helped the engine team with boss room generation, viewing boss rooms with Camera, and reworking all our enemy programming. We also added more rooms and adjusteded many of the hitboxes in the current rooms to give teh game a much smoother feel.   
