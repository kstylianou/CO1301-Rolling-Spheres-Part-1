//Kyriakos Stylianou

// Gaming Assigment.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;
#define STATE_FORWORD    1
#define STATE_BACKWORD   2
#define STATE_LEFTWORD   3
#define STATE_RIGHTWORD  4

// Update: Move sphares forword 
int sphereMoveForword(IModel* sphere1, float sphereSpeed, float maxDistance, int  STATE_MOVE_RIGHT, float maxDown, int state)
{
	//(a) Update: Move sphares forword:
	sphere1->MoveZ(sphereSpeed);

	//(b) Tresmitions: If sphere moved far enough forwards, go to state STATE_MOVE_RIGHT
	if (sphere1->GetZ() > maxDistance)
	{
		state = STATE_MOVE_RIGHT;
	}


	// The spheres stop rotating if they leave the ground, and start rotating if they touch the ground again
	if (sphere1->GetY() <= maxDown)
	{
		sphere1->RotateX(sphereSpeed);

	}

	return state;
}

// Update: Move sphares backwords:
int sphereMoveBackword(IModel* sphere1, float sphereSpeed, float minDistance, int  STATE_MOVE_LEFT, float maxDown, int state)
{

	//(a) Update: Move sphares backwords:
	sphere1->MoveZ(-sphereSpeed);


	//(b) Tresmitions: If sphere moved far enough backwords, go to state STATE_MOVE_LEFT
	if (sphere1->GetZ() < minDistance)
	{
		state = STATE_MOVE_LEFT;
	}

	// The spheres stop rotating if they leave the ground, and start rotating if they touch the ground again
	if (sphere1->GetY() <= maxDown)
	{
		sphere1->RotateX(-sphereSpeed);

	}

	return state;
}

// Move sphares Leftword:
int sphereMoveLeftword(IModel* sphere1, float sphereSpeed, float LeftRightDistance, int  STATE_ROLL_FORWORD, float maxDown, int state)
{

	//(a) Update: Move sphares Leftword:
	sphere1->MoveX(-sphereSpeed);


	//(b) Tresmitions: If sphere moved far enough Leftword, go to state STATE_ROLL_FORWORD
	if (sphere1->GetX() < -LeftRightDistance)
	{
		state = STATE_ROLL_FORWORD;
	}

	// The spheres stop rotating if they leave the ground, and start rotating if they touch the ground again
	if (sphere1->GetY() <= maxDown)
	{
		sphere1->RotateZ(sphereSpeed);

	}

	return state;
}

// Move sphares Rightwords
int sphereMoveRightword(IModel* sphere1, float sphereSpeed, float LeftRightDistance, int  STATE_ROLL_BACKWORD, float maxDown, int state)
{

	//(a) Update: Move sphares Rightwords:
	sphere1->MoveX(sphereSpeed);

	//(b) Tresmitions: If sphere moved far enough Rightword, go to state STATE_ROLL_BACKWORD
	if (sphere1->GetX() > LeftRightDistance)
	{
		state = STATE_ROLL_BACKWORD;
	}

	// The spheres stop rotating if they leave the ground, and start rotating if they touch the ground again
	if (sphere1->GetY() <= maxDown)
	{
		sphere1->RotateZ(-sphereSpeed);

	}

	return state;
}

// Update Game Controls
void updateGameControls(I3DEngine* myEngine, IModel* sphere1, IModel* sphere2, IModel* sphere3, float& sphereSpeed, float maxUp, float maxDown, int& STATE_ROLL_FORWORD, int& STATE_ROLL_BACKWORD, int& STATE_MOVE_LEFT, int& STATE_MOVE_RIGHT, string blue, string indigo, string violet, bool& skinChange1, bool& skinChange2, bool& skinChange3, int& state, int& state1, int& state2) {

	// Increase the speed of both spheres
	if (myEngine->KeyHit(Key_Z))
	{
		sphereSpeed = sphereSpeed + 0.1;

	}

	// Decrease the speed of both spheres
	if (myEngine->KeyHit(Key_X))
	{
		sphereSpeed = sphereSpeed - 0.1;
	}
	// The player is able to press the Escape key to quit the game
	if (myEngine->KeyHit(Key_Escape))
	{
		myEngine->Stop();
	}
	// The player is able to slowly raise the spheres along the y - axis
	if (myEngine->KeyHeld(Key_Up))
	{
		if (sphere1->GetY() < maxUp && sphere2->GetY() < maxUp && sphere3->GetY() < maxUp)
		{
			sphere1->MoveY(sphereSpeed);
			sphere2->MoveY(sphereSpeed);
			sphere3->MoveY(sphereSpeed);
		}
	}

	// The player is able to slowly lower the spheres along the y-axis
	if (myEngine->KeyHeld(Key_Down))
	{
		if (sphere1->GetY() > maxDown && sphere2->GetY() > maxDown && sphere3->GetY() > maxDown)
		{
			sphere1->MoveY(-sphereSpeed);
			sphere2->MoveY(-sphereSpeed);
			sphere3->MoveY(-sphereSpeed);
		}
	}

	// The player is able to hit the ‘R’ key to reverse the direction of the spheres.
	if (myEngine->KeyHit(Key_R))
	{
		if (STATE_ROLL_FORWORD == 1)
		{
			STATE_ROLL_FORWORD = 2;
			STATE_ROLL_BACKWORD = 1;
			STATE_MOVE_LEFT = 4;
			STATE_MOVE_RIGHT = 3;
		}
		else
		{
			STATE_ROLL_FORWORD = 1;
			STATE_ROLL_BACKWORD = 2;
			STATE_MOVE_LEFT = 3;
			STATE_MOVE_RIGHT = 4;
		}
		if (state == STATE_ROLL_FORWORD) {
			state = STATE_ROLL_BACKWORD;
		}
		else if (state == STATE_ROLL_BACKWORD) {
			state = STATE_ROLL_FORWORD;
		}
		if (state == STATE_MOVE_LEFT) {
			state = STATE_MOVE_RIGHT;
		}
		else if (state == STATE_MOVE_RIGHT) {
			state = STATE_MOVE_LEFT;
		}
		if (state1 == STATE_ROLL_FORWORD) {
			state1 = STATE_ROLL_BACKWORD;
		}
		else if (state1 == STATE_ROLL_BACKWORD) {
			state1 = STATE_ROLL_FORWORD;
		}
		if (state1 == STATE_MOVE_LEFT) {
			state1 = STATE_MOVE_RIGHT;
		}
		else if (state1 == STATE_MOVE_RIGHT) {
			state1 = STATE_MOVE_LEFT;
		}
		if (state2 == STATE_ROLL_FORWORD) {
			state2 = STATE_ROLL_BACKWORD;
		}
		else if (state2 == STATE_ROLL_BACKWORD) {
			state2 = STATE_ROLL_FORWORD;
		}
		if (state2 == STATE_MOVE_LEFT) {
			state2 = STATE_MOVE_RIGHT;
		}
		else if (state2 == STATE_MOVE_RIGHT) {
			state2 = STATE_MOVE_LEFT;
		}
	}

	// When the player hits the ‘E’ key, cycle the three colours of the spheres around
	if (myEngine->KeyHit(Key_E))
	{

		if (skinChange1 == true)
		{
			sphere1->SetSkin(blue);
			sphere2->SetSkin(violet);
			sphere3->SetSkin(indigo);
			skinChange1 = false;
			skinChange2 = true;
		}

		else if (skinChange2 == true)
		{
			sphere1->SetSkin(indigo);
			sphere2->SetSkin(blue);
			sphere3->SetSkin(violet);
			skinChange2 = false;
			skinChange3 = true;
		}

		else if (skinChange3 == true)
		{
			sphere1->SetSkin(violet);
			sphere2->SetSkin(indigo);
			sphere3->SetSkin(blue);
			skinChange3 = false;
			skinChange1 = true;
		}
	}
}

// Update camera movements
void updateCamera(I3DEngine* myEngine, ICamera* camera, float stepCamera)
{
	// The ‘W’ key causes the camera to move forwards
	if (myEngine->KeyHeld(Key_W))
	{
		camera->MoveLocalZ(stepCamera);
	}

	// The ‘S’ key causes the camera to move backwards.
	if (myEngine->KeyHeld(Key_S))
	{
		camera->MoveLocalZ(-stepCamera);
	}

	// The ‘D’ key causes the camera to move rightwards.
	if (myEngine->KeyHeld(Key_D))
	{
		camera->MoveLocalX(stepCamera);
	}

	// The ‘A’ key causes the camera to move leftwards.
	if (myEngine->KeyHeld(Key_A))
	{
		camera->MoveLocalX(-stepCamera);
	}

	//Left-Right Rotations:
	float angleLR = myEngine->GetMouseMovementX();
	camera->RotateY(angleLR);

	//Up-Down Rotation:
	float angleUD = myEngine->GetMouseMovementY();
	camera->RotateLocalX(angleUD);
}

// Update sphere state
void UpdateSpheres(IModel* sphere1, float& sphereSpeed, float maxDistance, float minDistance, float LeftRightDistance, int& STATE_MOVE_RIGHT, int& STATE_MOVE_LEFT, int& STATE_ROLL_FORWORD, int& STATE_ROLL_BACKWORD, float maxDown, int& state) {
	switch (state)
	{

	case STATE_FORWORD:
		state = sphereMoveForword(sphere1, sphereSpeed, maxDistance, STATE_MOVE_RIGHT, maxDown, state);
		break;

	case STATE_BACKWORD:
		state = sphereMoveBackword(sphere1, sphereSpeed, minDistance, STATE_MOVE_LEFT, maxDown, state);
		break;

	case STATE_LEFTWORD:
		state = sphereMoveLeftword(sphere1, sphereSpeed, LeftRightDistance, STATE_ROLL_FORWORD, maxDown, state);
		break;

	case STATE_RIGHTWORD:
		state = sphereMoveRightword(sphere1, sphereSpeed, LeftRightDistance, STATE_ROLL_BACKWORD, maxDown, state);
		break;
	}
}

// Update Scene
void updateScene(ICamera* camera, IModel* sphere1, IModel* sphere2, IModel* sphere3, float& sphereSpeed, float maxDistance, float minDistance, float LeftRightDistance, int& STATE_MOVE_RIGHT, int& STATE_MOVE_LEFT, int& STATE_ROLL_FORWORD, int& STATE_ROLL_BACKWORD, float maxDown, int& state, I3DEngine* myEngine, float maxUp, string blue, string indigo, string violet, bool& skinChange1, bool& skinChange2, bool& skinChange3, float stepCamera, int& state1, int& state2) {

	UpdateSpheres(sphere1, sphereSpeed, maxDistance, minDistance, LeftRightDistance, STATE_MOVE_RIGHT, STATE_MOVE_LEFT, STATE_ROLL_FORWORD, STATE_ROLL_BACKWORD, maxDown, state);
	UpdateSpheres(sphere2, sphereSpeed, maxDistance, minDistance, LeftRightDistance, STATE_MOVE_RIGHT, STATE_MOVE_LEFT, STATE_ROLL_FORWORD, STATE_ROLL_BACKWORD, maxDown, state1);
	UpdateSpheres(sphere3, sphereSpeed, maxDistance, minDistance, LeftRightDistance, STATE_MOVE_RIGHT, STATE_MOVE_LEFT, STATE_ROLL_FORWORD, STATE_ROLL_BACKWORD, maxDown, state2);


	//-----------------------------------//
	//Update the Game Controls:
	//-----------------------------------//
	updateGameControls(myEngine, sphere1, sphere2, sphere3, sphereSpeed, maxUp, maxDown, STATE_ROLL_FORWORD, STATE_ROLL_BACKWORD, STATE_MOVE_LEFT, STATE_MOVE_RIGHT, blue, indigo, violet, skinChange1, skinChange2, skinChange3, state, state1, state2);

	//-----------------------------------//
	// Update the Camera: Key Controls:
	//-----------------------------------//
	updateCamera(myEngine, camera, stepCamera);


}

// Pause and resume the game 
bool pauseGame(I3DEngine* myEngine, bool bPause)
{
	// The player is able to hit the ‘P’ key as a toggle to pause and resume the game
	if (myEngine->KeyHit(Key_P))
	{

		bPause = !bPause;

	}
	return bPause;
}



void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("./media");

	/**** Set up your scene here ****/

	//Camera//
	ICamera* camera = myEngine->CreateCamera(kManual, 0, 120, -200);

	// rotate the x axis by 20 degrees
	camera->RotateX(20);

	//Meshes //
	IMesh* meshFloor = myEngine->LoadMesh("Floor.x");
	IMesh* meshSphere1 = myEngine->LoadMesh("Sphere.x");


	//Models: // 
	IModel* floor = meshFloor->CreateModel(0, 0, 0);
	IModel* sphere1 = meshSphere1->CreateModel(-50, 10, 0);
	IModel* sphere2 = meshSphere1->CreateModel(50, 10, 50);
	IModel* sphere3 = meshSphere1->CreateModel(25, 10, 0);


	// Skins
	string violet = "violet.png";
	string blue = "blue.png";
	string indigo = "indigo.png";

	// Set color skin to spheres
	sphere1->SetSkin(violet);
	sphere2->SetSkin(indigo);
	sphere3->SetSkin(blue);


	float stepCamera = 0.3;
	const float kGameSpeed = 0.3;
	float sphereSpeed = kGameSpeed;
	float maxDistance = 100.0;
	float minDistance = 0.0;
	float LeftRightDistance = 50.0;
	float maxUp = 100.0;
	float maxDown = 10;
	int State_Roll_UD = 3;
	int state = 1;
	int state1 = 2;
	int state2 = 3;
	int STATE_ROLL_FORWORD = 1;
	int STATE_ROLL_BACKWORD = 2;
	int STATE_MOVE_LEFT = 3;
	int STATE_MOVE_RIGHT = 4;
	bool skinChange1 = true;
	bool skinChange2 = false;
	bool skinChange3 = false;
	bool pause = false;


	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/



		pause = pauseGame(myEngine, pause);
		// Pause and resume the game with key hit "P"
		if (pause != true)
		{
			updateScene(camera, sphere1, sphere2, sphere3, sphereSpeed, maxDistance, minDistance, LeftRightDistance, STATE_MOVE_RIGHT, STATE_MOVE_LEFT, STATE_ROLL_FORWORD, STATE_ROLL_BACKWORD, maxDown, state, myEngine, maxUp, blue, indigo, violet, skinChange1, skinChange2, skinChange3, stepCamera, state1, state2);

		}
	}
	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
