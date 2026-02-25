#include "SceneLevel1.h"
#include "ModuleDebug.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleBlocks.h"
#include "ModuleWalls.h"
#include "ModuleEnemies.h"
#include "ModuleFadeToBlack.h"
#include "ModuleUI.h"
#include "ModuleStars.h"
#include "ModuleParticles.h"
#include "SDL_mixer/include/SDL_mixer.h"

SceneLevel1::SceneLevel1(bool startEnabled) : SceneLevel(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	App->audio->PlayFx(1, 0);
	App->player->Enable();
	App->blocks->Enable();
	App->walls->Enable();
	App->enemies->Enable();
	App->ui->Enable();
	App->particles->Enable();
	App->stars->Enable();

	App->enemies->NextColor();
	int color = App->enemies->GetColor();
	App->blocks->SetEggColor(color);
	App->levelNum = 1;


	bool ret = true;

	win = false;

	App->audio->PlayMusic("assets/Themes/Popcorn/Main BGM (Popcorn).ogg", 1.0f);
	

	App->enemies->AddEnemy(1, 5);
	App->enemies->AddEnemy(3, 3);
	App->enemies->AddEnemy(11, 13);
	
	
	App->blocks->AddBlock(Block_Type::EGG, 3, 14);
	App->blocks->AddBlock(Block_Type::EGG, 9, 1);
	App->blocks->AddBlock(Block_Type::EGG, 9, 9);
	App->blocks->AddBlock(Block_Type::EGG, 11, 5);

	App->blocks->AddBlock(Block_Type::DIAMOND, 3, 11);
	App->blocks->AddBlock(Block_Type::DIAMOND, 5, 5);
	App->blocks->AddBlock(Block_Type::DIAMOND, 11, 7);

	App->audio->PlayFx(12, 0);

	App->blocks->AddBlock(Block_Type::NORMAL, 1, 0);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 1);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 2);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 4);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 6);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 8);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 9);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 11);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 12);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 13);
	App->blocks->AddBlock(Block_Type::NORMAL, 1, 14);
	App->blocks->AddBlock(Block_Type::NORMAL, 2, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 2, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 1);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 5);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 8);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 9);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 10);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 12);
	App->blocks->AddBlock(Block_Type::NORMAL, 3, 13);
	App->blocks->AddBlock(Block_Type::NORMAL, 4, 1);
	App->blocks->AddBlock(Block_Type::NORMAL, 4, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 4, 5);
	App->blocks->AddBlock(Block_Type::NORMAL, 4, 11);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 0);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 1);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 6);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 8);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 9);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 11);
	App->blocks->AddBlock(Block_Type::NORMAL, 5, 13);
	App->blocks->AddBlock(Block_Type::NORMAL, 6, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 6, 5);
	App->blocks->AddBlock(Block_Type::NORMAL, 6, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 6, 13);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 1);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 2);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 5);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 9);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 10);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 11);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 12);
	App->blocks->AddBlock(Block_Type::NORMAL, 7, 13);
	App->blocks->AddBlock(Block_Type::NORMAL, 8, 1);
	App->blocks->AddBlock(Block_Type::NORMAL, 8, 5);
	App->blocks->AddBlock(Block_Type::NORMAL, 8, 9);
	App->blocks->AddBlock(Block_Type::NORMAL, 8, 13);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 4);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 5);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 6);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 7);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 8);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 11);
	App->blocks->AddBlock(Block_Type::NORMAL, 9, 13);
	App->blocks->AddBlock(Block_Type::NORMAL, 10, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 10, 11);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 0);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 1);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 2);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 3);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 4);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 6);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 9);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 10);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 11);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 12);
	App->blocks->AddBlock(Block_Type::NORMAL, 11, 14);

	App->walls->AddWall(Wall_Type::HORIZONTAL, 8, 24);
	App->walls->AddWall(Wall_Type::HORIZONTAL, 8, 272);
	App->walls->AddWall(Wall_Type::VERTICAL, 0, 24);
	App->walls->AddWall(Wall_Type::VERTICAL, 216, 24);


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->currentLevel = this;

	
	return ret;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------

	win = App->enemies->VictoryCheck(win);

	if (App->debug->ascending == true)
	{
		App->debug->ascending = false;
		win = true;

	}


	if (win) 
	{
		App->player->stayInLevel = false;
		App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneLevel_2, 90);
		App->audio->PlayFx(0, 0);

	}

	if (App->debug->descending == true)
	{
		App->debug->descending = false;
		App->fade->FadeToBlack((Module*)App->currentLevel, (Module*)App->sceneMenu, 90);
	}


	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->blocks->Disable();
	App->walls->Disable();
	App->enemies->Disable();
	App->ui->Disable();
	App->particles->Disable();
	App->stars->Disable();

	return true;
}
