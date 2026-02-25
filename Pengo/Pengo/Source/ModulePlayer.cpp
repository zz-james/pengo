#include "ModulePlayer.h"
#include "ModuleDebug.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBlocks.h"
#include "ModuleEnemies.h"
#include "ModuleWalls.h"
#include "ModuleFonts.h"
#include "ScenePoints.h"
#include "Score.h"
#include "SDL_mixer/include/SDL_mixer.h"

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.GenerateAnimation({ 0, 0, 16, 16 }, 1, 1);

	// move upwards
	walkUpAnim.GenerateAnimation({ 64, 0, 32, 16 }, 1, 2);
	walkUpAnim.loop = true;
	walkUpAnim.speed = 0.1f;

	walkDownAnim.GenerateAnimation({ 0, 0, 32, 16 }, 1, 2);
	walkDownAnim.loop = true;
	walkDownAnim.speed = 0.1f;

	walkLeftAnim.GenerateAnimation({ 32, 0, 32, 16 }, 1, 2);
	walkLeftAnim.loop = true;
	walkLeftAnim.speed = 0.1f;

	walkRightAnim.GenerateAnimation({ 96, 0, 32, 16 }, 1, 2);
	walkRightAnim.loop = true;
	walkRightAnim.speed = 0.1f;

	pushUpAnim.GenerateAnimation({ 64, 16, 32, 16 }, 1, 2);
	pushUpAnim.loop = false;
	pushUpAnim.speed = 0.1f;

	pushDownAnim.GenerateAnimation({ 0, 16, 32, 16 }, 1, 2);
	pushDownAnim.loop = false;
	pushDownAnim.speed = 0.1f;

	pushLeftAnim.GenerateAnimation({ 32, 16, 32, 16 }, 1, 2);
	pushLeftAnim.loop = false;
	pushLeftAnim.speed = 0.1f;

	pushRightAnim.GenerateAnimation({ 96, 16, 32, 16 }, 1, 2);
	pushRightAnim.loop = false;
	pushRightAnim.speed = 0.1f;

	dieAnim.GenerateAnimation({ 0, 32, 32, 16 }, 1, 2);
	dieAnim.loop = true;
	dieAnim.speed = 0.1f;

	direction = Directions::Down;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::CleanUp() {
	App->textures->Unload(texture);

	return true;
}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("assets/sprites/pengos.png");
	currentAnimation = &idleAnim;

	gridPosition.x = 6;
	gridPosition.y = 6;

	targetPosition.x = gridPosition.x * 16 + 8;
	targetPosition.y = gridPosition.y * 16 + 32;

	position.x = gridPosition.x * 16 + 8;
	position.y = gridPosition.y * 16 + 32;

	destroyed = false;
	spawnDelay = 0;

	dead = false;
	deadPause = 0;
	deadPause2 = 0;
	deadPause3 = 0;
	paused = false;

	return ret;

}

Update_Status ModulePlayer::Update()
{
	if (deadPause != 100)
	{
		if (dead) deadPause++;
	}
	

	if (lifes - 1 != 0)
	{
		if (deadPause == 100)
		{
			stayInLevel = true;
			dieAnim.loop = false;
			if(deadPause2 != 45) deadPause2++;

			App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->currentLevel, 90);

			if (deadPause2 == 45)
			{
				if(deadPause3 != 75) deadPause3++;

				App->enemies->Reset();

				if (deadPause3 == 75)
				{
					deadPause2 = 0;
					deadPause3 = 0;
					dieAnim.loop = true;
					lifes--;
					App->enemies->Unpause();
					Reset();
				}
			}

		}
	}
	else {
		if (deadPause == 100)
		{
			stayInLevel = false;
			dieAnim.loop = true;
			App->audio->PlayFx(7, 0);
			Mix_HaltMusic();
			App->score->CheckAndSetHighscore();
			App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->scenePoints, 90);
		}
	}

	if (!paused) {
		GamePad& pad = App->input->pads[0];

		if (App->debug->GMODE == 0)
		{
			if (App->enemies->NotStunnedEnemyInPosition(position.x, position.y) || instaloss) {
				instaloss = false;
				dead = true;
				hasDied = true;
				App->audio->PlayFx(16, 0);
				currentAnimation = &dieAnim;
				paused = true;
				App->enemies->Pause();

			}
		}


		if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT || pad.l_x < 0.0f || pad.left == true)
		{
			lastPressed = (int)SDL_SCANCODE_A;
		}

		if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT || pad.l_x > 0.0f || pad.right == true)
		{
			lastPressed = (int)SDL_SCANCODE_D;
		}

		if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT || pad.l_y > 0.0f || pad.down == true)
		{
			lastPressed = (int)SDL_SCANCODE_S;
		}

		if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT || pad.l_y < 0.0f || pad.up == true)
		{
			lastPressed = (int)SDL_SCANCODE_W;
		}

		if (App->input->keys[SDL_SCANCODE_A] == false && App->input->keys[SDL_SCANCODE_D] == false && App->input->keys[SDL_SCANCODE_S] == false && App->input->keys[SDL_SCANCODE_W] == false && pad.l_x == 0.0f && pad.left == false && pad.right == false && pad.l_y == 0.0f && pad.down == false && pad.up == false) {
			lastPressed = (int)SDL_SCANCODE_0;
		}

		if (!dead && !pushing && spawnDelay == 45) {
			switch (lastPressed) {
			case (int)SDL_SCANCODE_A:
				if (!moving) {
					currentAnimation->running = true;
					if (currentAnimation != &walkLeftAnim)
					{
						walkLeftAnim.Reset();
						currentAnimation = &walkLeftAnim;
					}
					direction = Directions::Left;
					if (!App->blocks->BlockInGridPosition(gridPosition.x - 1, gridPosition.y)) {
						gridPosition.x -= 1;
					}
				}
				break;
			case (int)SDL_SCANCODE_D:
				if (!moving) {
					currentAnimation->running = true;
					if (currentAnimation != &walkRightAnim)
					{
						walkRightAnim.Reset();
						currentAnimation = &walkRightAnim;
					}
					direction = Directions::Right;
					if (!App->blocks->BlockInGridPosition(gridPosition.x + 1, gridPosition.y)) {
						gridPosition.x += 1;
					}
				}
				break;
			case (int)SDL_SCANCODE_S:
				if (!moving) {
					currentAnimation->running = true;
					if (currentAnimation != &walkDownAnim)
					{
						walkDownAnim.Reset();
						currentAnimation = &walkDownAnim;
					}
					direction = Directions::Down;
					if (!App->blocks->BlockInGridPosition(gridPosition.x, gridPosition.y + 1)) {
						gridPosition.y += 1;
					}
				}
				break;
			case (int)SDL_SCANCODE_W:
				if (!moving) {
					currentAnimation->running = true;
					if (currentAnimation != &walkUpAnim)
					{
						walkUpAnim.Reset();
						currentAnimation = &walkUpAnim;
					}
					direction = Directions::Up;
					if (!App->blocks->BlockInGridPosition(gridPosition.x, gridPosition.y - 1)) {
						gridPosition.y -= 1;
					}
				}
				break;
			default:
				break;
			}
		}

		if (gridPosition.x < 0) gridPosition.x = 0;
		if (gridPosition.x > 12) gridPosition.x = 12;
		if (gridPosition.y < 0) gridPosition.y = 0;
		if (gridPosition.y > 14) gridPosition.y = 14;

		targetPosition.x = gridPosition.x * 16 + 8;
		targetPosition.y = gridPosition.y * 16 + 32;

		if (position.x < targetPosition.x) {
			xpositionfraction += speed;
			position.x += xpositionfraction;
			xpositionfraction = std::fmod(xpositionfraction, 1.0f);
		}
		else if (position.x > targetPosition.x) {
			xpositionfraction -= speed;
			position.x += xpositionfraction - std::fmod(xpositionfraction, 1.0f);
			xpositionfraction = std::fmod(xpositionfraction, 1.0f);
		}

		if (position.y < targetPosition.y) {
			ypositionfraction += speed;
			position.y += ypositionfraction;
			ypositionfraction = std::fmod(ypositionfraction, 1.0f);
		}
		else if (position.y > targetPosition.y) {
			ypositionfraction -= speed;
			position.y += ypositionfraction - std::fmod(ypositionfraction, 1.0f);
			ypositionfraction = std::fmod(ypositionfraction, 1.0f);
		}

		if (position.x == targetPosition.x && position.y == targetPosition.y) {
			moving = false;
		}
		else {
			moving = true;
		}

		if ((currentAnimation == &pushUpAnim || currentAnimation == &pushDownAnim || currentAnimation == &pushLeftAnim || currentAnimation == &pushRightAnim) && currentAnimation->HasFinished())
		{
			pushing = false;
		}

		if (!moving && currentAnimation != &pushUpAnim && currentAnimation != &pushDownAnim && currentAnimation != &pushLeftAnim && currentAnimation != &pushRightAnim && !dead) {
			currentAnimation->running = false;
		}

		if (!dead && spawnDelay == 45)
		{
			if (!moving && !pushing && (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true)) {
				pushing = true;
				if (aPressed)
				{
					switch (direction) {
					case Directions::Up:
						if (!App->blocks->PositionInMap(gridPosition.x, gridPosition.y - 1)) App->walls->PushWall(0);
						App->blocks->PushBlock(gridPosition.x, gridPosition.y, gridPosition.x, gridPosition.y - 1);
						pushUpAnim.Reset();
						currentAnimation = &pushUpAnim;
						break;
					case Directions::Down:
						if (!App->blocks->PositionInMap(gridPosition.x, gridPosition.y + 1)) App->walls->PushWall(1);
						App->blocks->PushBlock(gridPosition.x, gridPosition.y, gridPosition.x, gridPosition.y + 1);
						pushDownAnim.Reset();
						currentAnimation = &pushDownAnim;
						break;
					case Directions::Left:
						if (!App->blocks->PositionInMap(gridPosition.x - 1, gridPosition.y)) App->walls->PushWall(2);
						App->blocks->PushBlock(gridPosition.x, gridPosition.y, gridPosition.x - 1, gridPosition.y);
						pushLeftAnim.Reset();
						currentAnimation = &pushLeftAnim;
						break;
					case Directions::Right:
						if (!App->blocks->PositionInMap(gridPosition.x + 1, gridPosition.y)) App->walls->PushWall(3);
						App->blocks->PushBlock(gridPosition.x, gridPosition.y, gridPosition.x + 1, gridPosition.y);
						pushRightAnim.Reset();
						currentAnimation = &pushRightAnim;
						break;
					default:
						break;
					}
				}
				aPressed = false;
			}
			if (pad.a == false) aPressed = true;
		}

		if (currentAnimation == &pushUpAnim && currentAnimation->HasFinished()) {
			currentAnimation = &walkUpAnim;
		}
		if (currentAnimation == &pushDownAnim && currentAnimation->HasFinished()) {
			currentAnimation = &walkDownAnim;
		}
		if (currentAnimation == &pushLeftAnim && currentAnimation->HasFinished()) {
			currentAnimation = &walkLeftAnim;
		}
		if (currentAnimation == &pushRightAnim && currentAnimation->HasFinished()) {
			currentAnimation = &walkRightAnim;
		}
	}

	if (deadPause <= 100)
	{
		currentAnimation->Update();
	}

	return Update_Status::UPDATE_CONTINUE;

}

Update_Status ModulePlayer::PostUpdate()
{
	if (spawnDelay != 45) spawnDelay++;

	if (!destroyed && spawnDelay == 45)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return Update_Status::UPDATE_CONTINUE;

}

void ModulePlayer::positionToGrid(int gx, int gy, int& x, int& y) {

	x = (gx - 8) / 16;
	y = (gy - 32) / 16;

}

void ModulePlayer::gridToPosition(int px, int py, int& x, int& y) {

	x = px * 16 + 8;
	y = py * 16 + 32;

}

void ModulePlayer::Reset() {
	if(App->blocks->BlockInGridPosition(6, 6)) {
		App->blocks->DestroyBlock(6, 6);
	}
	SetPosition(6, 6);
	currentAnimation = &idleAnim;

	destroyed = false;

	dead = false;
	deadPause = 0;
	paused = false;
	pushing = false;

}

void ModulePlayer::SetPosition(int x, int y) {
	gridPosition.x = x;
	gridPosition.y = y;

	targetPosition.x = gridPosition.x * 16 + 8;
	targetPosition.y = gridPosition.y * 16 + 32;

	position.x = gridPosition.x * 16 + 8;
	position.y = gridPosition.y * 16 + 32;
}