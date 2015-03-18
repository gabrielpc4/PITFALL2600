#include "PlayerSprite.h"

PlayerSprite::PlayerSprite() 
	: PlayerSprite(39, 140)
{

}

void PlayerSprite::mirrorX()
{
	for (unsigned i = 0; i < this->vector<Polygon>::size(); i++)
	{
		Polygon& currentPolygon = this->vector<Polygon>::at(i);
		currentPolygon.mirrorX(this->x());
		if (_climbing == false)
		{
			currentPolygon += Point(6, 0);
		}
		else
		{
			currentPolygon += Point(18, 0);
		}
	}
}

PlayerSprite::PlayerSprite(float startX, float startY)
	: Sprite(startX,startY)
{
	frames = 0;	
	buildSprite(0);	
}

void PlayerSprite::animate(int& animationFrame, int minFrameNum, int maxFramenum)
{
	frames++;
	int refreshInterval = ANIMATION_REFRESH_INTERVAL;

	if (_climbing)
	{
		refreshInterval = CLIMBING_ANIMATION_REFRESH_INTERVAL;
	}
	if (frames % refreshInterval == 0)
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

void PlayerSprite::buildSprite(int animationFrame)
{
	Color legColor = Color(16, 80, 0);
	Color armColor = Color(48, 192, 48);

	if (_climbing == false)
	{
		buildBasicShape();

		switch (animationFrame)
		{
		case(0) :
		{
			Rect rightFeet(Point(0, 0), Point(7, 2), legColor);
			Rect leftFeet(Point(3, 4), Point(11, 6), legColor);

			this->push_back(rightFeet);
			this->push_back(leftFeet);


			Rect rightLeg(Point(0, 2), Point(4, 14), legColor);
			Rect leftLeg(Point(4, 6), Point(7, 14), legColor);

			this->push_back(rightLeg);
			this->push_back(leftLeg);


			Rect rightArm(Point(7, 24), Point(11, 28), armColor);
			this->push_back(rightArm);

			Rect rightHand(Point(11, 26), Point(15, 30), armColor);
			this->push_back(rightHand);
		}break;
		case (1) :
		{
			Rect rightFeet(Point(-7, 4), Point(-3, 10), legColor);
			this->push_back(rightFeet);

			Polygon rightLeg(legColor);
			rightLeg.push_back(Rect(Point(-3, 8), Point(4, 10)));
			rightLeg.push_back(Rect(Point(0, 10), Point(4, 14)));
			rightLeg.push_back(Rect(Point(4, 12), Point(8, 14)));

			this->push_back(rightLeg);

			Rect leftLeg(Point(7, 6), Point(11, 16), legColor);

			this->push_back(leftLeg);

			Polygon leftFeet(legColor);
			leftFeet.push_back(Rect(Point(11, 2), Point(15, 6)));
			leftFeet.push_back(Rect(Point(15, 4), Point(18, 6)));

			this->push_back(leftFeet);

			Rect leftArm(Point(-4, 22), Point(0, 30), armColor);
			this->push_back(leftArm);

			Rect rightArm(Point(7, 22), Point(11, 26), armColor);
			this->push_back(rightArm);

			Rect rightRand(Point(11, 24), Point(15, 28), armColor);
			this->push_back(rightRand);
		}break;
		case(2) :
		{
			Rect leftFeet(Point(4, 0), Point(11, 2), legColor);
			this->push_back(leftFeet);

			Rect rightFeet(Point(-4, 4), Point(0, 10), legColor);
			this->push_back(rightFeet);

			Polygon rightLeg(legColor);
			rightLeg.push_back(Rect(Point(0, 8), Point(11, 10)));
			rightLeg.push_back(Rect(Point(11, 8), Point(15, 14)));
			rightLeg.push_back(Rect(Point(4, 12), Point(11, 16)));

			this->push_back(rightLeg);

			Rect leftLeg(Point(4, 2), Point(7, 12), legColor);

			this->push_back(leftLeg);

			Rect rightRand(Point(7, 20), Point(12, 24), armColor);
			this->push_back(rightRand);
		}break;
		case(3) :
		{
			Rect rightFeet(Point(0, 0), Point(3, 2), legColor);
			this->push_back(rightFeet);

			Rect leftFeet(Point(11, 4), Point(14, 6), legColor);
			this->push_back(leftFeet);

			Polygon rightLeg(legColor);
			rightLeg.push_back(Rect(Point(-4, 2), Point(0, 12)));
			rightLeg.push_back(Rect(Point(0, 8), Point(3, 14)));
			this->push_back(rightLeg);

			Polygon leftLeg(legColor);
			leftLeg.push_back(Rect(Point(7, 6), Point(11, 10)));
			leftLeg.push_back(Rect(Point(11, 10), Point(14, 16)));
			leftLeg.push_back(Rect(Point(7, 12), Point(11, 18)));
			this->push_back(leftLeg);

			Rect rightRand(Point(7, 22), Point(12, 26), armColor);
			this->push_back(rightRand);
		}break;
		case(4) :
		{
			Rect rightFeet(Point(-11, 2), Point(-7, 8), legColor);
			this->push_back(rightFeet);

			Rect leftFeet(Point(11, 6), Point(18, 8), legColor);
			this->push_back(leftFeet);

			Polygon rightLeg(legColor);
			rightLeg.push_back(Rect(Point(-7, 6), Point(-4, 12)));
			rightLeg.push_back(Rect(Point(-4, 8), Point(0, 14)));
			rightLeg.push_back(Rect(Point(0, 12), Point(4, 14)));

			this->push_back(rightLeg);

			Polygon leftLeg(legColor);
			leftLeg.push_back(Rect(Point(11, 6), Point(14, 16)));
			leftLeg.push_back(Rect(Point(7, 12), Point(11, 18)));
			this->push_back(leftLeg);

			Rect leftArm(Point(-4, 22), Point(0, 30), armColor);
			this->push_back(leftArm);

			Rect rightArm(Point(7, 22), Point(11, 26), armColor);
			this->push_back(rightArm);

			Rect rightRand(Point(11, 24), Point(15, 28), armColor);
			this->push_back(rightRand);
		}break;
		case(5) :
		{
			Rect rightFeet(Point(-11, 14), Point(-3, 16), legColor);
			this->push_back(rightFeet);

			Rect leftFeet(Point(12, 10), Point(19, 12), legColor);
			this->push_back(leftFeet);

			Polygon rightLeg(legColor);
			rightLeg.push_back(Rect(Point(-7, 12), Point(4, 14)));
			rightLeg.push_back(Rect(Point(-3, 10), Point(4, 12)));

			this->push_back(rightLeg);

			Polygon leftLeg(legColor);
			leftLeg.push_back(Rect(Point(12, 10), Point(16, 18)));
			leftLeg.push_back(Rect(Point(7, 16), Point(12, 20)));
			this->push_back(leftLeg);

			Rect leftArm(Point(-3, 26), Point(0, 30), armColor);
			this->push_back(leftArm);

			Rect leftHand(Point(-7, 22), Point(-3, 28), armColor);
			this->push_back(leftHand);

			Rect rightArm(Point(7, 26), Point(12, 30), armColor);
			this->push_back(rightArm);

			Rect rightRand(Point(12, 28), Point(16, 32), armColor);
			this->push_back(rightRand);

		}break;
		default:;
		}
		
		// Makes the player change looking direction
		if (_lookingDirection != RIGHT)
		{
			this->mirrorX();
		}
	}
	else
	{
		switch (animationFrame)
		{
		case(0) :
		{
			buildClimbingSprite();
		}break;
		case(1) :
		{
			buildClimbingSprite();

			// Reverses the climbing sprite			
			this->mirrorX();
		}break;
		}
	}
	this->update();


}

void PlayerSprite::buildBasicShape()
{
	Rect hips(Point(0, 14), Point(7, 20), Color(16, 80, 0));
	this->push_back(hips);

	Rect torso(Point(0, 20), Point(7, 34), Color(48, 192, 48));
	this->push_back(torso);

	Rect neck(Point(0, 34), Point(4, 36), Color(240, 176, 144));
	Rect face(Point(0, 36), Point(7, 40), neck.color());
	Rect hat(Point(0, 40), Point(7, 42), Color(80, 32, 0));
	this->push_back(neck);
	this->push_back(face);
	this->push_back(hat);
}

void PlayerSprite::buildClimbingSprite()
{
	Color legColor = Color(16, 80, 0);
	Rect leftFeet(Point(0, 8), Point(7, 10), legColor);
	this->push_back(leftFeet);

	Polygon leftLeg(legColor);
	leftLeg.push_back(Rect(Point(4, 10), Point(7, 16)));
	leftLeg.push_back(Rect(Point(0, 14), Point(4, 22)));
	leftLeg.push_back(Rect(Point(4, 18), Point(7, 24)));
	leftLeg.push_back(Rect(Point(4, 18), Point(7, 24)));
	this->push_back(leftLeg);

	Rect butt(Point(7, 20), Point(11, 24), legColor);
	this->push_back(butt);

	Rect rightFeet(Point(11, 0), Point(18, 2), legColor);
	this->push_back(rightFeet);

	Rect rightLeg(Point(11, 2), Point(15, 24), legColor);
	this->push_back(rightLeg);

	Rect torso(Point(7, 24), Point(15, 36), Color(48, 192, 48));
	this->push_back(torso);

	Polygon leftArm(torso.color());
	leftArm.push_back(Rect(Point(4, 30), Point(7, 34)));
	leftArm.push_back(Rect(Point(0, 32), Point(4, 36)));
	this->push_back(leftArm);

	Rect leftHand(Point(0, 36), Point(4, 38), Color(240, 176, 144));
	this->push_back(leftHand);

	Rect rightArm(Point(15, 26), Point(18, 32), torso.color());
	this->push_back(rightArm);

	Rect head(Point(7, 38), Point(15, 42), leftHand.color());
	this->push_back(head);

	Rect hat(Point(7, 42), Point(15, 44), Color(80, 32, 0));
	this->push_back(hat);
}

void PlayerSprite::push_back(Rect rect)
{
	Polygon p(Sprite::_x, Sprite::_y);

	// Makes the player sprite appear lower, when taking hit from a log
	if (_takingHit && _falling == false && _jumping == false && _climbing == false)
	{
		rect += Point(0, -10);
	}
	p.push_back(rect);
	vector<Polygon>::push_back(p);
}

void PlayerSprite::push_back(Polygon pol)
{
	Polygon p(Sprite::_x, Sprite::_y);

	// Makes the player sprite appear lower, when taking hit from a log
	if (_takingHit && _falling == false && _jumping == false && _climbing == false)
	{
		pol += Point(0, -10);
	}
	p.push_back(pol);
	vector<Polygon>::push_back(p);
}

void PlayerSprite::update()
{
	int smallerX = WORLD_WINDOW_WIDTH;
	int smallerY = WORLD_WINDOW_HEIGHT;

	int biggerX = 0;
	int biggerY = 0;

	for (vector<Polygon>::iterator currentPolygon = vector<Polygon>::begin(); currentPolygon != vector<Polygon>::end(); ++currentPolygon)
	{
		if (currentPolygon->x() < smallerX)
		{
			smallerX = currentPolygon->x();
		}
		if (currentPolygon->y() < smallerY)
		{
			smallerY = currentPolygon->y();
		}
		if (currentPolygon->rightX() > biggerX)
		{
			biggerX = currentPolygon->rightX();
		}
		if (currentPolygon->topY() > biggerY)
		{
			biggerY = currentPolygon->topY();
		}
	}
	_width = (biggerX - smallerX);
	_height = (biggerY - smallerY);
	_realY = smallerY;
}

float PlayerSprite::topY()
{
	return (_realY + _height);
}

float PlayerSprite::y()
{
	return _realY;
}


