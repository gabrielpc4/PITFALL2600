#include "IntroScreen.h"
IntroScreen::IntroScreen()
	: background(Point(0, 20), Point(WORLD_WINDOW_WIDTH, WORLD_WINDOW_HEIGHT), Color(16, 80, 0)),
	  tunnelTop(Point(150, 210), Point(390, 225), Color(148, 91, 0)),
	  ground(Point(150, 225), Point(390, 255), Color(187, 147, 0)),
	  sky(Point(150, 255), Point(390, 350), Color(0, 131, 0)),
	  treeTrunk1(Point(193, 255), Point(207, 350), Color(83, 43, 0)),
	  treeTrunk2(Point(334, 255), Point(348, 350), Color(83, 43, 0)),
	  playerSprite(230, 250),
	  water(158, 231, Color(BLUE), STATIC_HOLE)
{
	frames = 0;
	crocodiles.push_back(Crocodile(200, 235));
	crocodiles.push_back(Crocodile(258, 235));
	crocodiles.push_back(Crocodile(316, 235));
	staticCrocodiles.push_back(Crocodile(200, 235));
	staticCrocodiles.push_back(Crocodile(258, 235));
	staticCrocodiles.push_back(Crocodile(316, 235));
	treasures.push_back(Treasure(220, 170, MONEY_BAG));
	treasures.push_back(Treasure(220, (treasures[0].y() - 35), SILVER_BAR));
	treasures.push_back(Treasure(220, (treasures[1].y() - 35), GOLD_BAR));
	treasures.push_back(Treasure(222, (treasures[2].y() - 35), DIAMOND_RING));
	for (unsigned i = 0; i < crocodiles.size(); i++)
	{
		staticCrocodiles[i].canAnimate(false);
		staticCrocodiles[i].setAnimationFrame(1);
	}
	PlaySound(TEXT("sounds/PitfallTheme.wav"), NULL, SND_ASYNC | SND_FILENAME);
}

void IntroScreen::show()
{
	frames++;

	background.draw();

	printText("PITFALL 2600", Point(190, WORLD_WINDOW_HEIGHT - 35), 2);

	output1(330, 336, "by Gabriel Pinheiro de Carvalho");
	
	glPushMatrix();
	glScalef(0.8, 0.8, 0.8);
	glTranslatef(80, 65, 0);
	

	tunnelTop.draw();
	ground.draw();
	sky.draw();
	treeTrunk1.draw();
	treeTrunk2.draw();
	water.draw();

	for (unsigned i = 0; i < crocodiles.size(); i++)
	{		
		staticCrocodiles[i].draw();
	}

	glColor3ub(72, 72, 0);
	glBegin(GL_POLYGON);
	glVertex2i(240, 285);
	glVertex2i(243, 285);
	glVertex2i(273, 350);
	glVertex2i(270, 350);
	glEnd();

	PlayerSprite playerSprite(230, 250);
	playerSprite.canAnimate(false);
	playerSprite.setAnimationFrame(8);

	playerSprite.draw();
	glPopMatrix();

	glPushMatrix();	
	glTranslatef(-3, 0 , 0);
	output1(170, 210, "Objective: Collect 10 treasures to win the game");

	output1(10, 210, "Controls:");
	output1(30, 200, "Walk: LEFT or RIGHT");
	output1(30, 190, "Jump: SPACE or UP ");
	output1(30, 180, "Climb Ladder: UP ");
	output1(20, 160, "While Climbing Ladders:");
	output1(30, 150, "Climb Up  : UP ");
	output1(30, 140, "Climb Down: DOWN ");
	output1(20, 130, "When reached the top:");
	output1(30, 120, "Climb Out Left : LEFT");
	output1(30, 110, "Climb Out Right: RIGHT or SPACE");
	output1(20, 90, "While Swinging on Vines:");
	output1(30, 80, "Release Vine: UP or DOWN or SPACE");


	output1(20, 60, "Cheats:");
	output1(30, 50, "D: Enable/Disable DEBUG MODE");
	output1(30, 37, "[On Debug Mode]");
	output1(30, 27, "G: God Mode  L: 99 lives  H: Toggle Collision Boxes  PageUp: Next Scenario  PageDown: Previous Scenario");	

	for (unsigned i = 0; i < treasures.size(); i++)
	{
		treasures[i].canAnimate(false);
		treasures[i].draw();

		string treasureValue(": ");
		treasureValue += std::to_string(treasures[i].value());
		treasureValue += " points";
							
		output1(treasures[1].rightX() + 5, treasures[i].y() + 10, (char*)treasureValue.c_str());
	}

	output1(345, 185, "Hint:");
	glPushMatrix();
	glScalef(0.7, 0.7, 0);
	glTranslatef(340, -90, 0);
	tunnelTop.draw();
	ground.draw();
	sky.draw();
	treeTrunk1.draw();
	treeTrunk2.draw();
	water.draw();

	for (unsigned i = 0; i < crocodiles.size(); i++)
	{
		this->crocodiles[i].draw();
	}	

	glPopMatrix();
	glPushMatrix();
	glScalef(0.7, 0.7, 0);
	playerSprite.setX(620);
	playerSprite.setY(156);
	playerSprite.setAnimationFrame(0);	
	playerSprite.draw();
	glPopMatrix();

	output1(335, 75, "Stay on top of the crocodile's eyes to ");
	output1(348, 65, "stay alive when it's mouth opens");
	
	if (frames <= 15)
	{
		printText("Press Space Bar to Start", Point(180, 5), 1);		
	}
	else if (frames >= 30)
	{
		frames = 0;
	}
	glutSwapBuffers();
}

void IntroScreen::printText(string text, Point p, float size)
{
	glColor3f(1.0, 1.0, 1.0);
	char *c;
	float scale = size * 0.1;
	float orientation = 0;
	glPushMatrix();
	glTranslatef(p.x(), p.y(), 0);
	glScalef(scale, scale, scale);
	glRotatef(orientation, 0, 0, 1);
	for (c = (char*)text.c_str(); *c; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
}

void IntroScreen::output1(int x, int y, char *string)
{
	glColor3f(1.0, 1.0, 1.0);
	int len, i;
	glRasterPos2i(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
	}
		
}

IntroScreen::~IntroScreen()
{
}
