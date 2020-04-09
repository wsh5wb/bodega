In order to compile the file, run the command make. Then to run the executable, run './build/DevTool'
Note: You need gcc8

How to Build a Level:
First, you can load an exisiting scene using the button 'Load Scene' in the top left corner. If not, you can start building a scene from scratch. When loading a text file, you must enter a path. An example path that can be used is './resources/scenes/test.txt'

To begin, simply drag sprites from the resource bottom at the bottom onto the screen and release. To reselect an image, you can click on the sprite's top left corner. To hide or unhide the resource bar, you can click 'h' on your keyboard.

If you ever need more assets/sprites, you can add them to the resources directory.

FUTURE - add an indicator for where to click the sprite - it can sometimes take some work to find.

When you're finished, you can 'save Scene' using the button in the top left corner. This generate a text file at the path you set. 

The rightmost window contains info about the currently selected asset. From here, you can easily view and change the position, pivot point, scale, rotation, and alpha. Additionally, there is a button for copying the currently selected image and another one for deleting it.

Camera Controls:
	W - Pan Up
	A - Pan Left
	S - Pan Down
	D - Pan Right
	Z - Zoom In
	X - Zoom Out

Other controls:
    G - Toggle grid snapping
	H - Toggle Resource Bar visibility
	P - the next object you click will become the parent of the currently selected object
	O - Cancel out the next parent operation
