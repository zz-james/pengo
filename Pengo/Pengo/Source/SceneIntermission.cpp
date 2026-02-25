#include "SceneIntermission.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntermission::SceneIntermission(bool startEnabled) : Module(startEnabled)
{
	sky.GenerateAnimation({ 0,0, 896, 416 }, 4, 4);
	sky.speed = 0.02f;
	sky.loop = false;

	ground.GenerateAnimation({ 0, 432, 224, 184 }, 1, 1);

	pengoAnim.GenerateAnimation({ 227,599, 255, 17 }, 1, 15);
	pengoAnim.speed = 0.022;
	pengoAnim.loop = false;

	pengoPos[0] = fPoint(100.0f, 100.0f);
	pengoPos[1] = fPoint(180.0f, 140.0f);
	pengoPos[2] = fPoint(50.0f, 155.0f);
	pengoPos[3] = fPoint(7.0f, 210.0f);
	pengoPos[4] = fPoint(100.0f, 300.0f);

	currentPos = pengoPos[0];
}

SceneIntermission::~SceneIntermission()
{

}

// Load assets
bool SceneIntermission::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	texture = App->textures->Load("assets/sprites/Intro.png");

	App->audio->PlayMusic("assets/Themes/Intermission.ogg", 1.0f);

	return ret;
}

#include "SDL_mixer/include/SDL_mixer.h"

Update_Status SceneIntermission::Update()
{
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneMenu, 90);
		Mix_HaltMusic();
	}

	if (currentPos.DistanceTo(pengoPos[currentIndex]) < 5) {
		currentIndex++;
		if (currentIndex > 4) {
			Mix_HaltMusic();
			App->fade->FadeToBlack(this, (Module*)App->sceneMenu, 90);
		}
	}

	if (currentIndex < 5) {
		fPoint diff = (pengoPos[currentIndex] - currentPos);
		fPoint norm;
		norm.x = diff.x / ((diff.x > 0 ? diff.x : -diff.x) + (diff.y > 0 ? diff.y : -diff.y));
		norm.y = diff.y / ((diff.x > 0 ? diff.x : -diff.x) + (diff.y > 0 ? diff.y : -diff.y));
		currentPos += fPoint(norm.x * pengoSpeed, norm.y * pengoSpeed);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntermission::PostUpdate()
{
	sky.Update();
	pengoAnim.Update();

	App->render->Blit(texture, 0, 0, &sky.GetCurrentFrame());

	App->render->Blit(texture, 0, 104, &ground.GetCurrentFrame());

	App->render->Blit(texture, currentPos.x, currentPos.y, &pengoAnim.GetCurrentFrame());
	

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneIntermission::CleanUp()
{
	App->textures->Unload(texture);

	return true;
}
