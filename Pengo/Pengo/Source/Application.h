#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"
#include <cstdint>

#define NUM_MODULES 36

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class SceneIntro;
class SceneIntermission;
class SceneMenu;
class ScenePoints;
class SceneLevel;
class SceneLevel1;
class SceneLevel2;
class SceneLevel3;
class SceneLevel4;
class SceneLevel5;
class SceneLevel6;
class SceneLevel7;
class SceneLevel8;
class SceneLevel9;
class SceneLevel10;
class SceneLevel11;
class SceneLevel12;
class SceneLevel13;
class SceneLevel14;
class SceneLevel15;
class SceneLevel16;

class ModuleParticles;
class ModuleEnemies;
class ModuleBlocks;
class ModuleWalls;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender;
class ModuleDebug;
class ModuleUI;
class Score;
class ModuleStars;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	Update_Status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;

	SceneIntro* sceneIntro = nullptr;
	SceneIntermission* intermission = nullptr;
	SceneMenu* sceneMenu = nullptr;
	ScenePoints* scenePoints = nullptr;
	SceneLevel* currentLevel = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;
	SceneLevel2* sceneLevel_2 = nullptr;
	SceneLevel3* sceneLevel_3 = nullptr;
	SceneLevel4* sceneLevel_4 = nullptr;
	SceneLevel5* sceneLevel_5 = nullptr;
	SceneLevel6* sceneLevel_6 = nullptr;
	SceneLevel7* sceneLevel_7 = nullptr;
	SceneLevel8* sceneLevel_8 = nullptr;
	SceneLevel9* sceneLevel_9 = nullptr;
	SceneLevel10* sceneLevel_10 = nullptr;
	SceneLevel11* sceneLevel_11 = nullptr;
	SceneLevel12* sceneLevel_12 = nullptr;
	SceneLevel13* sceneLevel_13 = nullptr;
	SceneLevel14* sceneLevel_14 = nullptr;
	SceneLevel15* sceneLevel_15 = nullptr;
	SceneLevel16* sceneLevel_16 = nullptr;

	int levelNum = 0;
	

	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleWalls* walls = nullptr;
	ModuleBlocks* blocks = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleRender* render = nullptr;
	ModuleDebug* debug = nullptr;
	ModuleUI* ui = nullptr;
	Score* score = nullptr;
	ModuleStars* stars = nullptr;

	float gameTime = 0.0f;

private:
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	uint64_t frameStart;
	int frameTime;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__