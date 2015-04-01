#include "PlayerSprite.h"

PlayerSprite::PlayerSprite() 
	: PlayerSprite(39, 140)
{

}

PlayerSprite::PlayerSprite(float startX, float startY)
	: AnimatedObject(startX,startY, 8)
{
	pantsColor	= Color(16, 80, 0);
	shirtColor	= Color(48, 192, 48);
	skinColor	= Color(240, 176, 144);
	hatColor	= Color(80, 32, 0);	
	buildSprite();	
}

void PlayerSprite::draw()
{
	if (allowAnimation)
	{
		if (_holdingVine)
		{
			animationFrame = 8;
		}
		else
		{
			// Falling sprite
			if (_falling && _jumping == false)
			{
				animationFrame = 0;
			}
			else
			{
				// Climbing sprite
				if (_climbing)
				{
					// Switches between the climbing animations
					animate(6, 7);
				}
				else
				{
					if (_walking)
					{
						// Animate the walking
						animate(1, 5);
					}
					else
					{
						animationFrame = 0;
					}
				}
			}

			// Jumping, and taking hit sprite
			if ((_jumping)
				|| (_takingHit && _falling == false) && (_climbing == false)
				|| (_falling) && (this->y() + (this->height() / 2.0) < 96)) // Makes the player open the legs, when there's room for it, when falling
			{
				animationFrame = 5;
			}
		}
		// UPDATES THE SPRITE (ANIMATION)
		if (_dead == false || _falling) // Prevents the animation to change when the player is dead, 												
		{											// but allows to change to the falling sprite, for the case the player falls into the pit
			// Rebuilds the sprite, with the new animation sprite
			Sprite::clear();
			buildSprite();
		}
	}
	else
	{
		Sprite::clear();
		buildSprite();
	}

	Sprite::draw();
}

void PlayerSprite::DRAW_ON_DEBUG_MODE()
{	
	drawAllRectanglesOutlines();
}

void PlayerSprite::animate(int minFrameNum, int maxFramenum)
{
	frames++;

	if (_climbing)
	{
		animationRefreshInterval = CLIMBING_ANIMATION_REFRESH_INTERVAL;
	}
	else
	{
		animationRefreshInterval = DEFAULT_ANIMATION_REFRESH_INTERVAL;
	}
	if (frames % animationRefreshInterval == 0)
	{
		if (_walking || (_climbing && _climbingDirection != NONE))
		{			
			animationFrame++;
		}
		if (animationFrame > maxFramenum)
		{
			animationFrame = minFrameNum;
		}

		if (frames >= INT_MAX)
		{
			frames = 0;
		}
	}
}
/* AnimationFrame:
	0 - Player Stoped / Begining to fall
	1 to 5 - Player Walking
	5 - Player Jumping / Taking Hit / Falling 
	6 to 7 - Climbing
	8 - Swinging
*/
			
void PlayerSprite::buildSprite()
{
	if (_climbing == false || allowAnimation == false)
	{
		buildBasicShape();
	}

	switch (animationFrame)
	{
		// 0 - Player Stopped / Beginning to fall
		case(0) :
		{
			Rect rightFeet(Point(0, 0), Point(7, 2), pantsColor);
			Rect leftFeet(Point(4, 4), Point(11, 6), pantsColor);

			this->push_back(rightFeet);
			this->push_back(leftFeet);


			Rect rightLeg(Point(0, 2), Point(4, 14), pantsColor);
			Rect leftLeg(Point(4, 6), Point(7, 14), pantsColor);

			this->push_back(rightLeg);
			this->push_back(leftLeg);


			Rect rightArm(Point(7, 24), Point(11, 28), shirtColor);
			this->push_back(rightArm);

			Rect rightHand(Point(11, 26), Point(15, 30), shirtColor);
			this->push_back(rightHand);
		}break;

		// 1 to 5 - Player Walking
		case (1) :
		{
			Rect rightFeet(Point(-7, 4), Point(-3, 10), pantsColor);
			this->push_back(rightFeet);

			Polygons rightLeg(pantsColor);
			rightLeg.push_back(Rect(Point(-3, 8), Point(4, 10)));
			rightLeg.push_back(Rect(Point(0, 10), Point(4, 14)));
			rightLeg.push_back(Rect(Point(4, 12), Point(8, 14)));

			this->push_back(rightLeg);

			Rect leftLeg(Point(7, 6), Point(11, 16), pantsColor);

			this->push_back(leftLeg);

			Polygons leftFeet(pantsColor);
			leftFeet.push_back(Rect(Point(11, 2), Point(15, 6)));
			leftFeet.push_back(Rect(Point(15, 4), Point(18, 6)));

			this->push_back(leftFeet);

			Rect leftArm(Point(-4, 22), Point(0, 30), shirtColor);
			this->push_back(leftArm);

			Rect rightArm(Point(7, 22), Point(11, 26), shirtColor);
			this->push_back(rightArm);

			Rect rightRand(Point(11, 24), Point(15, 28), shirtColor);
			this->push_back(rightRand);
		}break;
		case(2) :
		{
			Rect leftFeet(Point(4, 0), Point(11, 2), pantsColor);
			this->push_back(leftFeet);

			Rect rightFeet(Point(-4, 4), Point(0, 10), pantsColor);
			this->push_back(rightFeet);

			Polygons rightLeg(pantsColor);
			rightLeg.push_back(Rect(Point(0, 8), Point(11, 10)));
			rightLeg.push_back(Rect(Point(11, 8), Point(15, 14)));
			rightLeg.push_back(Rect(Point(4, 12), Point(11, 16)));

			this->push_back(rightLeg);

			Rect leftLeg(Point(4, 2), Point(7, 12), pantsColor);

			this->push_back(leftLeg);

			Rect rightRand(Point(7, 20), Point(12, 24), shirtColor);
			this->push_back(rightRand);
		}break;
		case(3) :
		{
			Rect rightFeet(Point(0, 0), Point(3, 2), pantsColor);
			this->push_back(rightFeet);

			Rect leftFeet(Point(11, 4), Point(14, 6), pantsColor);
			this->push_back(leftFeet);

			Polygons rightLeg(pantsColor);
			rightLeg.push_back(Rect(Point(-4, 2), Point(0, 12)));
			rightLeg.push_back(Rect(Point(0, 8), Point(3, 14)));
			this->push_back(rightLeg);

			Polygons leftLeg(pantsColor);
			leftLeg.push_back(Rect(Point(7, 6), Point(11, 10)));
			leftLeg.push_back(Rect(Point(11, 10), Point(14, 16)));
			leftLeg.push_back(Rect(Point(7, 12), Point(11, 18)));
			this->push_back(leftLeg);

			Rect rightRand(Point(7, 22), Point(12, 26), shirtColor);
			this->push_back(rightRand);
		}break;
		case(4) :
		{
			Rect rightFeet(Point(-11, 2), Point(-7, 8), pantsColor);
			this->push_back(rightFeet);

			Rect leftFeet(Point(11, 6), Point(18, 8), pantsColor);
			this->push_back(leftFeet);

			Polygons rightLeg(pantsColor);
			rightLeg.push_back(Rect(Point(-7, 6), Point(-4, 12)));
			rightLeg.push_back(Rect(Point(-4, 8), Point(0, 14)));
			rightLeg.push_back(Rect(Point(0, 12), Point(4, 14)));

			this->push_back(rightLeg);

			Polygons leftLeg(pantsColor);
			leftLeg.push_back(Rect(Point(11, 6), Point(14, 16)));
			leftLeg.push_back(Rect(Point(7, 12), Point(11, 18)));
			this->push_back(leftLeg);

			Rect leftArm(Point(-4, 22), Point(0, 30), shirtColor);
			this->push_back(leftArm);

			Rect rightArm(Point(7, 22), Point(11, 26), shirtColor);
			this->push_back(rightArm);

			Rect rightRand(Point(11, 24), Point(15, 28), shirtColor);
			this->push_back(rightRand);
		}break;

		// 5 - Player Jumping / Taking Hit / Falling
		case(5) :
		{
			Rect rightFeet(Point(-11, 14), Point(-3, 16), pantsColor);
			this->push_back(rightFeet);

			Rect leftFeet(Point(12, 10), Point(19, 12), pantsColor);
			this->push_back(leftFeet);

			Polygons rightLeg(pantsColor);
			rightLeg.push_back(Rect(Point(-7, 12), Point(4, 14)));
			rightLeg.push_back(Rect(Point(-3, 10), Point(4, 12)));

			this->push_back(rightLeg);

			Polygons leftLeg(pantsColor);
			leftLeg.push_back(Rect(Point(12, 10), Point(16, 18)));
			leftLeg.push_back(Rect(Point(7, 16), Point(12, 20)));
			this->push_back(leftLeg);

			Rect leftArm(Point(-3, 26), Point(0, 30), shirtColor);
			this->push_back(leftArm);

			Rect leftHand(Point(-7, 22), Point(-3, 28), shirtColor);
			this->push_back(leftHand);

			Rect rightArm(Point(7, 26), Point(12, 30), shirtColor);
			this->push_back(rightArm);

			Rect rightRand(Point(12, 28), Point(16, 32), shirtColor);
			this->push_back(rightRand);
		}break;

		// CLIMBING SPRITE
		case(6) :
		{
			// BUILDS THE CLIMBING SPRITE IN THE CASE 6 AND 7
		}
		case(7) :
		{
			buildClimbingSprite();
		}break;

		// Swinging Sprite
		case(8) :
		{
			buildSwingingSprite();
		}break;
		default:
		{
		
		}break;
	}



	if (allowAnimation)
	{
		// Makes the player sprite change its looking direction or animates the climbing sprite
		if ((_lookingDirection != RIGHT
			&& _climbing == false)	// Prevents the clmbing sprite being mirrored twice
			|| animationFrame == 7) // Reverses the climbing sprite to make the climbing animation
		{
			this->mirrorX();
		}
	}
	

	this->update();
	
}

void PlayerSprite::buildBasicShape()
{
	Rect hips(Point(0, 14), Point(7, 20), pantsColor);
	this->push_back(hips);

	Rect torso(Point(0, 20), Point(7, 34), shirtColor);
	this->push_back(torso);

	Rect neck(Point(0, 34), Point(4, 36), skinColor);
	Rect face(Point(0, 36), Point(7, 40), skinColor);
	Rect hat(Point(0, 40), Point(7, 42), hatColor);
	this->push_back(neck);
	this->push_back(face);
	this->push_back(hat);
}

void PlayerSprite::buildClimbingSprite()
{
	Rect leftFeet(Point(0, 8), Point(7, 10), pantsColor);
	this->push_back(leftFeet);

	Polygons leftLeg(pantsColor);
	leftLeg.push_back(Rect(Point(4, 10), Point(7, 16)));
	leftLeg.push_back(Rect(Point(0, 14), Point(4, 22)));
	leftLeg.push_back(Rect(Point(4, 18), Point(7, 24)));
	leftLeg.push_back(Rect(Point(4, 18), Point(7, 24)));
	this->push_back(leftLeg);

	Rect butt(Point(7, 20), Point(11, 24), pantsColor);
	this->push_back(butt);

	Rect rightFeet(Point(11, 0), Point(18, 2), pantsColor);
	this->push_back(rightFeet);

	Rect rightLeg(Point(11, 2), Point(15, 24), pantsColor);
	this->push_back(rightLeg);

	Rect torso(Point(7, 24), Point(15, 36), shirtColor);
	this->push_back(torso);

	Polygons leftArm(shirtColor);
	leftArm.push_back(Rect(Point(4, 30), Point(7, 34)));
	leftArm.push_back(Rect(Point(0, 32), Point(4, 36)));
	this->push_back(leftArm);

	Rect leftHand(Point(0, 36), Point(4, 38), skinColor);
	this->push_back(leftHand);

	Rect rightArm(Point(15, 26), Point(18, 32), shirtColor);
	this->push_back(rightArm);

	Rect head(Point(7, 38), Point(15, 42), skinColor);
	this->push_back(head);

	Rect hat(Point(7, 42), Point(15, 44), hatColor);
	this->push_back(hat);
}

void PlayerSprite::buildSwingingSprite()
{
	Polygons legs(pantsColor);
	legs.push_back(Rect(Point(3, 12), Point(10, 18)));
	legs.push_back(Rect(Point(10, 14), Point(14, 20)));
	legs.push_back(Rect(Point(10, 18), Point(21, 20)));
	legs.push_back(Rect(Point(17, 16), Point(25, 18)));
	legs.push_back(Rect(Point(21, 12), Point(25, 16)));
	legs.push_back(Rect(Point(25, 12), Point(28, 14)));

	this->push_back(legs);

	Polygons arms(shirtColor);
	arms.push_back(Rect(Point(7, 30), Point(14, 32)));
	arms.push_back(Rect(Point(10, 32), Point(14, 34)));

	this->push_back(arms);

	Rect hands(Point(10,34), Point(14,40), skinColor);

	this->push_back(hands);
}

void PlayerSprite::push_back(Rect rect)
{
	Polygons p(Sprite::_x, Sprite::_y);

	// Makes the player sprite appear lower, when taking hit from a log
	if (_takingHit && _falling == false && _jumping == false && _climbing == false && allowAnimation)
	{
		rect += Point(0, -10);
	}
	p.push_back(rect);
	vector<Polygons>::push_back(p);
}

void PlayerSprite::push_back(Polygons pol)
{
	Polygons p(Sprite::_x, Sprite::_y);

	// Makes the player sprite appear lower, when taking hit from a log
	if (_takingHit && _falling == false && _jumping == false && _climbing == false && allowAnimation)
	{
		pol += Point(0, -10);
	}
	p.push_back(pol);
	vector<Polygons>::push_back(p);
}

void PlayerSprite::update()
{
	int smallerX = WORLD_WINDOW_WIDTH;
	int smallerY = WORLD_WINDOW_HEIGHT;

	int biggerX = INT_MIN;
	int biggerY = INT_MIN;

	for (vector<Polygons>::iterator currentPolygons = vector<Polygons>::begin(); currentPolygons != vector<Polygons>::end(); ++currentPolygons)
	{
		if (currentPolygons->x() < smallerX)
		{
			smallerX = currentPolygons->x();
		}
		if (currentPolygons->y() < smallerY)
		{
			smallerY = currentPolygons->y();
		}
		if (currentPolygons->rightX() > biggerX)
		{
			biggerX = currentPolygons->rightX();
		}
		if (currentPolygons->topY() > biggerY)
		{
			biggerY = currentPolygons->topY();
		}
	}	
	_width = (biggerX - smallerX);
	_height = (biggerY - smallerY);
	_realY = smallerY;
	_realX = smallerX;
}

void PlayerSprite::mirrorX()
{
	for (unsigned i = 0; i < this->size(); i++)
	{
		Polygons& currentPolygons = this->at(i);		
		currentPolygons.mirrorX(_x);				
	}
	if (_holdingVine)
	{		
		AnimatedObject::shiftSpriteOnly(27, 0);
	}
	else
	{
		if (_climbing)
		{
			AnimatedObject::shiftSpriteOnly(18, 0);
			
		}
		else
		{
			AnimatedObject::shiftSpriteOnly(11, 0);
		}
	}
}

float PlayerSprite::x()
{	
	if (_lookingDirection == LEFT)
	{
		return _x;
	}
	return  _x;
}

float PlayerSprite::rightX()
{
	return PlayerSprite::x() + PLAYER_ANIMATION_0_WIDTH;
}

float PlayerSprite::width()
{
	return PLAYER_ANIMATION_0_WIDTH;
}


float PlayerSprite::topY()
{
	return (_realY + _height);
}

float PlayerSprite::y()
{
	return _realY;
}

