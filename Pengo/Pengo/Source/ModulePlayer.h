#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

#include "SDL/include/SDL_timer.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);
	
	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	bool CleanUp() override;

	void Reset();

	void SetPosition(int x, int y);


	enum class Directions {
		Up,
		Down,
		Left,
		Right
	};

	bool hasDied = false;

	void Pause() { paused = true; }
	void Unpause() { paused = false; }


public:
	// Position of the player in the map
	iPoint position;
	iPoint targetPosition;
	iPoint gridPosition;

	float xpositionfraction = 0;
	float ypositionfraction = 0;

	bool moving = false;
	bool pushing = false;

	bool dead = false;
	bool instaloss = false;
	bool paused = false;
	// The speed in which we move the player (pixels per frame)
	float speed = 1.0f;

	//Counter to repeat animations
	int deadPause;
	int deadPause2;
	int deadPause3;
	bool stayInLevel = false;
	int lifes;
	

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation walkUpAnim;
	Animation walkDownAnim;
	Animation walkLeftAnim;
	Animation walkRightAnim;
	Animation pushUpAnim;
	Animation pushDownAnim;
	Animation pushLeftAnim;
	Animation pushRightAnim;
	Animation dieAnim;


	// The player's collider

	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	int spawnDelay = 0;

	int lastPressed = NULL;
	
	bool aPressed = true;


private:
	Directions direction;
	void positionToGrid(int gx, int gy, int& x, int& y);
	void gridToPosition(int px, int py, int& x, int& y);
};

#endif //!__MODULE_PLAYER_H__