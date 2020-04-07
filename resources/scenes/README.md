# How to write Files to be parsed as a Scene

1. On the first line, have two integers m,n for the number of ojects and the number of parent child relations

2. On the next m lines have a description of the objects according to the following series of whitespace seperated values (Diferent for Animated Sprites):
	a. An integer to tell the type (0-> the scene being read in, 1-> DisplayObject, 2-> DisplayObjectContainer, 3-> Sprite, 4-> AnimatedSprite, else error)
	b. A string used as an id for the object
	c. A string used as the path to load teh image from
	d. r, g, and b integers used if the isRGB variable is true
	e. A boolean denoting if the object should be visable
	f. A boolean denoting if the object isRGB
	g. w, h: the width and height of the object
	h. An integer used as the speed of the object
	i. A double used as the scaleX of the object
	j. A double used as the scaleY of the object
	k. A double used as the rotation of the object
	l. A double used as the rotationAmount of the object
	m. An integer used as the alpha of the object
	n. An integer used as the pivot.x of the object
	o. An integer used as the pivot.y of the object
	p. An integer used as the position.x the object
	q. An integer used as the position.y of the object
	
3. On the next n lines two strings denoting the id of the parent object followed by the id of it's child