#include "PlayerSprite.h"

PlayerSprite::PlayerSprite() : PlayerSprite(39, 140, 0, RIGHT, false)
{

}



PlayerSprite::PlayerSprite(int startX, int startY, int animationFrame, int direction, bool climbing)
{
	Color legColor = Color(16, 80, 0);
	Color armColor = Color(48, 192, 48);

	if (climbing == false)
	{
		buildBasicShape();
	
	
	
		switch (animationFrame)
		{
		case(0) :
		{
			Rect rightFeet(Point(0, 0), Point(8, 2), legColor);
			Rect leftFeet(Point(4, 4), Point(11, 6), legColor);

			Sprite::push_back(rightFeet);
			Sprite::push_back(leftFeet);


			Rect rightLeg(Point(0, 2), Point(4, 14), legColor);
			Rect leftLeg(Point(4, 6), Point(8, 14), legColor);

			Sprite::push_back(rightLeg);
			Sprite::push_back(leftLeg);


			Rect rightArm(Point(8, 24), Point(11, 28), armColor);
			Sprite::push_back(rightArm);

			Rect rightHand(Point(11, 26), Point(15, 30), armColor);
			Sprite::push_back(rightHand);
		}break;
		case (1) :
		{
			Rect rightFeet(Point(-7, 4), Point(-3, 10), legColor);
			Sprite::push_back(rightFeet);

			Polygon rightLeg(legColor);
			rightLeg.push_back(Rect(Point(-3, 8), Point(4, 10)));
			rightLeg.push_back(Rect(Point(0, 10), Point(4, 14)));
			rightLeg.push_back(Rect(Point(4, 12), Point(8, 14)));

			Sprite::push_back(rightLeg);

			Rect leftLeg(Point(8, 6), Point(11, 16), legColor);

			Sprite::push_back(leftLeg);

			Polygon leftFeet(legColor);
			leftFeet.push_back(Rect(Point(11, 2), Point(15, 6)));
			leftFeet.push_back(Rect(Point(15, 4), Point(18, 6)));

			Sprite::push_back(leftFeet);

			Rect leftArm(Point(-4, 22), Point(0, 30), armColor);
			Sprite::push_back(leftArm);

			Rect rightArm(Point(8, 22), Point(11, 26), armColor);
			Sprite::push_back(rightArm);

			Rect rightRand(Point(11, 24), Point(15, 28), armColor);
			Sprite::push_back(rightRand);
		}break;
		case(2) :
		{
			Rect leftFeet(Point(4, 0), Point(11, 2), legColor);
			Sprite::push_back(leftFeet);

			Rect rightFeet(Point(-4, 4), Point(0, 10), legColor);
			Sprite::push_back(rightFeet);

			Polygon rightLeg(legColor);
			rightLeg.push_back(Rect(Point(0, 8), Point(11, 10)));
			rightLeg.push_back(Rect(Point(11, 8), Point(15, 14)));
			rightLeg.push_back(Rect(Point(4, 12), Point(11, 16)));

			Sprite::push_back(rightLeg);

			Rect leftLeg(Point(4, 2), Point(7, 12), legColor);

			Sprite::push_back(leftLeg);

			Rect rightRand(Point(8, 20), Point(12, 24), armColor);
			Sprite::push_back(rightRand);
		}break;
		case(3) :
		{
			Rect rightFeet(Point(0, 0), Point(3, 2), legColor);
			Sprite::push_back(rightFeet);

			Rect leftFeet(Point(11, 4), Point(14, 6), legColor);
			Sprite::push_back(leftFeet);

			Polygon rightLeg(legColor);
			rightLeg.push_back(Rect(Point(-4, 2), Point(0, 12)));
			rightLeg.push_back(Rect(Point(0, 8), Point(3, 14)));
			Sprite::push_back(rightLeg);

			Polygon leftLeg(legColor);
			leftLeg.push_back(Rect(Point(7, 6), Point(11, 10)));
			leftLeg.push_back(Rect(Point(11, 10), Point(14, 16)));
			leftLeg.push_back(Rect(Point(7, 12), Point(11, 18)));
			Sprite::push_back(leftLeg);

			Rect rightRand(Point(8, 22), Point(12, 26), armColor);
			Sprite::push_back(rightRand);
		}break;
		case(4) :
		{
			Rect rightFeet(Point(-11, 2), Point(-7, 8), legColor);
			Sprite::push_back(rightFeet);

			Rect leftFeet(Point(11, 6), Point(18, 8), legColor);
			Sprite::push_back(leftFeet);

			Polygon rightLeg(legColor);
			rightLeg.push_back(Rect(Point(-7, 6), Point(-4, 12)));
			rightLeg.push_back(Rect(Point(-4, 8), Point(0, 14)));
			rightLeg.push_back(Rect(Point(0, 12), Point(4, 14)));

			Sprite::push_back(rightLeg);

			Polygon leftLeg(legColor);
			leftLeg.push_back(Rect(Point(11, 6), Point(14, 16)));
			leftLeg.push_back(Rect(Point(7, 12), Point(11, 18)));
			Sprite::push_back(leftLeg);

			Rect leftArm(Point(-4, 22), Point(0, 30), armColor);
			Sprite::push_back(leftArm);

			Rect rightArm(Point(8, 22), Point(11, 26), armColor);
			Sprite::push_back(rightArm);

			Rect rightRand(Point(11, 24), Point(15, 28), armColor);
			Sprite::push_back(rightRand);
		}break;
		case(5) :
		{
			Rect rightFeet(Point(-11, 14), Point(-3, 16), legColor);
			Sprite::push_back(rightFeet);

			Rect leftFeet(Point(12, 10), Point(19, 12), legColor);
			Sprite::push_back(leftFeet);

			Polygon rightLeg(legColor);
			rightLeg.push_back(Rect(Point(-7, 12), Point(4, 14)));
			rightLeg.push_back(Rect(Point(-3, 10), Point(4, 12)));

			Sprite::push_back(rightLeg);

			Polygon leftLeg(legColor);
			leftLeg.push_back(Rect(Point(12, 10), Point(16, 18)));
			leftLeg.push_back(Rect(Point(8, 16), Point(12, 20)));
			Sprite::push_back(leftLeg);

			Rect leftArm(Point(-3, 26), Point(0, 30), armColor);
			Sprite::push_back(leftArm);

			Rect leftHand(Point(-7, 22), Point(-3, 28), armColor);
			Sprite::push_back(leftHand);

			Rect rightArm(Point(8, 26), Point(12, 30), armColor);
			Sprite::push_back(rightArm);

			Rect rightRand(Point(12, 28), Point(16, 32), armColor);
			Sprite::push_back(rightRand);
		}break;
		default:;
		}

		if (direction != RIGHT)
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
			this->mirrorX();
		}break;
		}
	
	}
}

void PlayerSprite::buildBasicShape()
{
	Rect hips(Point(0, 14), Point(8, 20), Color(16, 80, 0));
	Sprite::push_back(hips);

	Rect torso(Point(0, 20), Point(8, 34), Color(48, 192, 48));
	Sprite::push_back(torso);

	Rect neck(Point(0, 34), Point(4, 36), Color(240, 176, 144));
	Rect face(Point(0, 36), Point(8, 42), neck.color());
	Rect hat(Point(0, 42), Point(8, 44), Color(80, 32, 0));
	Sprite::push_back(neck);
	Sprite::push_back(face);
	Sprite::push_back(hat);
}

void PlayerSprite::buildClimbingSprite()
{
	Color legColor = Color(16, 80, 0);
	Rect leftFeet(Point(0, 8), Point(7, 10), legColor);
	Sprite::push_back(leftFeet);

	Polygon leftLeg(legColor);
	leftLeg.push_back(Rect(Point(4, 10), Point(7, 16)));
	leftLeg.push_back(Rect(Point(0, 14), Point(4, 22)));
	leftLeg.push_back(Rect(Point(4, 18), Point(7, 24)));
	leftLeg.push_back(Rect(Point(4, 18), Point(7, 24)));
	Sprite::push_back(leftLeg);

	Rect butt(Point(7, 20), Point(11, 24), legColor);
	Sprite::push_back(butt);

	Rect rightFeet(Point(11, 0), Point(18, 2), legColor);
	Sprite::push_back(rightFeet);

	Rect rightLeg(Point(11, 2), Point(15, 24), legColor);
	Sprite::push_back(rightLeg);

	Rect torso(Point(7, 24), Point(15, 36), Color(48, 192, 48));
	Sprite::push_back(torso);

	Polygon leftArm(torso.color());
	leftArm.push_back(Rect(Point(4, 30), Point(7, 34)));
	leftArm.push_back(Rect(Point(0, 32), Point(4, 36)));
	Sprite::push_back(leftArm);

	Rect leftHand(Point(0, 36), Point(4, 38), Color(240, 176, 144));
	Sprite::push_back(leftHand);

	Rect rightArm(Point(15, 26), Point(18, 32), torso.color());
	Sprite::push_back(rightArm);

	Rect head(Point(7, 38), Point(15, 42), leftHand.color());
	Sprite::push_back(head);

	Rect hat(Point(7, 42), Point(15, 44), Color(80, 32, 0));
	Sprite::push_back(hat);
}




