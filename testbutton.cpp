#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include "LDefine.h"
#include "programform.h"
#include "LTexture.h"
#include "LEnemy.h"
#include "LSpecialFruit.h"
#include "LCharacter.h"
#include "LButton.h"
#include "LGamebase.h"

using namespace std;


LTexture gPlayButtonTexture;
LTexture gHelpButtonTexture;
LTexture gExitButtonTexture;
LTexture gBackgroundTexture;
LTexture gSpriteSheetTexture;
LTexture gMenuTexture;
LTexture gPauseButtonTexture;
LTexture gContinueButtonTexture;
LTexture gTextTextureYourScore;
LTexture gTextTextureBestScore;
LTexture gAudioButtonTexture;
LTexture gMuteButtonTexture;
LTexture gScoreTexture;
LTexture gHighScoreTexture;
LTexture gReturnButtonTexture;
LTexture gMenuInstructionTexture;
LTexture gInstructionTexture1;
LTexture gInstructionTexture2;
LTexture gInstructionTexture3;
LTexture gAuthorTexture;
LTexture gLoseTexture;
LTexture gEndgameTexture;
LTexture gTextSpecialFruitTime;
LTexture gSpecialFruitTime;

SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gAudioButton[BUTTON_AUDIO_TOTAL];
SDL_Rect gMuteButton[BUTTON_AUDIO_TOTAL];
SDL_Rect gReturnButton[BUTTON_TOTAL];
SDL_Rect gEnemyClips2[ONGROUND_ANIMATION_TOTAL];
SDL_Rect gEnemyClips1[INAIR_ANIMATION_TOTAL];
SDL_Rect gEnemyClips3[ONGROUND_ANIMATION_TOTAL];
SDL_Rect gEnemyClips4[ONGROUND_ANIMATION_TOTAL];
SDL_Rect gSpecialFruit[SPECIALFRUIT_ANIMATION];
SDL_Rect gGiantFruit[SPECIALFRUIT_ANIMATION];
SDL_Rect gTinyFruit[SPECIALFRUIT_ANIMATION];


SDL_Window* gWindow;
SDL_Renderer* gRenderer;

LButton PlayButton(PLAY_BUTTON_POSX, PLAY_BUTTON_POSY);
LButton HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
LButton ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
LButton PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
LButton ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);
LButton AudioButton(AUDIO_BUTTON_POSX, AUDIO_BUTTON_POSY);
LButton MuteButton(AUDIO_BUTTON_POSX,AUDIO_BUTTON_POSY);
LButton ReturnButton(RETURN_BUTTON_POSX,RETURN_BUTTON_POSY);

TTF_Font* gFont = nullptr;
TTF_Font* gFontInstruction = nullptr;
TTF_Font* gFontGameover = nullptr;

SDL_Color textColor = { 0, 0, 0 };
SDL_Color textInstructionColor = {255,255,255};

Mix_Music* gMusic = nullptr;
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gEat = nullptr;

//Tai anh
bool loadMedia()
{
    //Loading success flag
    bool success = 1;
    if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
    gFont = TTF_OpenFont( "pixelfont.ttf", 16);
    gFontInstruction = TTF_OpenFont( "yoster.ttf", 38);
    gFontGameover = TTF_OpenFont( "pixelfont.ttf", 50);
    if( (gFont == NULL) || (gFontInstruction == NULL) )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        if( !gTextTextureYourScore.LoadFromRenderedText( "Your score: ",gFont, textColor, gRenderer))
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if( !gTextTextureBestScore.LoadFromRenderedText( "Best score: ",gFont, textColor, gRenderer))
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if( !gTextSpecialFruitTime.LoadFromRenderedText( "Time left: ",gFont, textColor, gRenderer))
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if ( !gEndgameTexture.LoadFromRenderedText( "Press 'spacebar' to play again or 'esc' to out", gFont ,textColor, gRenderer))
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if ( !gInstructionTexture1.LoadFromRenderedText( "This is a game based on the dinosaur run", gFontInstruction, textInstructionColor, gRenderer))
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if ( !gInstructionTexture2.LoadFromRenderedText( " game made by Chrome. Just press", gFontInstruction, textInstructionColor, gRenderer))
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if ( !gInstructionTexture3.LoadFromRenderedText( " 'spacebar' to avoid obstacles !", gFontInstruction,textInstructionColor, gRenderer))
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if ( !gAuthorTexture.LoadFromRenderedText( "-patuspatinus-", gFontInstruction,textInstructionColor, gRenderer))
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        if ( !gLoseTexture.LoadFromRenderedText( "Game Over !", gFontGameover ,textColor, gRenderer))
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
    gMusic = Mix_LoadMUS("bensound-jazzyfrenchy (mp3cut.net).mp3");
    if( gMusic == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gJump = Mix_LoadWAV("90130205.mp3");
    if (gJump == NULL)
    {
         printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gEat = Mix_LoadWAV("Super Mario Bros (mp3cut.net).mp3");
    if (gEat == NULL)
    {
         printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    if (!gMenuTexture.LoadFromFile("menu_background.png", gRenderer))
			{
				std::cout << "Failed to load menu image" << std::endl;
				success = false;
			}
    if (!gMenuInstructionTexture.LoadFromFile("menu_background.png", gRenderer))
			{
				std::cout << "Failed to load menu instruction" << std::endl;
				success = false;
			}
    if (!gPlayButtonTexture.LoadFromFile("play_button.png", gRenderer))
			{
                cout << "Failed to load play_button image" << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; i++)
				{
					gPlayButton[i].x = 150 * i;
					gPlayButton[i].y = 0;
					gPlayButton[i].w = 150;
					gPlayButton[i].h = 98;
				}
			}
    if (!gHelpButtonTexture.LoadFromFile("help_button.png", gRenderer))
			{
                cout << "Failed to load help_button image" << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; i++)
				{
					gHelpButton[i].x = 150 * i;
					gHelpButton[i].y = 0;
					gHelpButton[i].w = 150;
					gHelpButton[i].h = 98;
				}
			}
    if (!gExitButtonTexture.LoadFromFile("exit_button.png", gRenderer))
			{
                cout << "Failed to load exit_button image" << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; i++)
				{
					gExitButton[i].x = 150 * i;
					gExitButton[i].y = 0;
					gExitButton[i].w = 150;
					gExitButton[i].h = 98;
				}
			}
    if (!gReturnButtonTexture.LoadFromFile("back_button.png", gRenderer))
			{
                cout << "Failed to load return_button image" << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; i++)
				{
					gReturnButton[i].x = 100 * i;
					gReturnButton[i].y = 0;
					gReturnButton[i].w = 100;
					gReturnButton[i].h = 78;
				}
			}
    if (!gPauseButtonTexture.LoadFromFile("pausebutton.png", gRenderer))
			{
                cout << "Failed to load pause_button image" << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; i++)
				{
					gPauseButton[i].x = 35 * i;
					gPauseButton[i].y = 0;
					gPauseButton[i].w = 35;
					gPauseButton[i].h = 35;
				}
			}
    if (!gContinueButtonTexture.LoadFromFile("continuebutton.png", gRenderer))
			{
                cout << "Failed to load continue_button image" << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; i++)
				{
					gContinueButton[i].x = 35 * i;
					gContinueButton[i].y = 0;
					gContinueButton[i].w = 35;
					gContinueButton[i].h = 35;
				}
			}
    if (!gAudioButtonTexture.LoadFromFile("audiobutton.png", gRenderer))
    {
        cout << "Failed to load audio_button image" << endl;
        success = false;
    }else{
        for (int i = 0; i < BUTTON_AUDIO_TOTAL; i++){
            gAudioButton[i].x = 35 * i;
            gAudioButton[i].y = 0;
            gAudioButton[i].w = 35;
            gAudioButton[i].h = 35;
        }
    }
    if (!gMuteButtonTexture.LoadFromFile("audiobutton.png", gRenderer))
    {
        cout << "Failed to load mute_button image" << endl;
        success = false;
    }else{
        for (int i = 0; i < BUTTON_AUDIO_TOTAL; i++){
            gMuteButton[i].x = 35 * i;
            gMuteButton[i].y = 0;
            gMuteButton[i].w = 35;
            gMuteButton[i].h = 35;
        }
    }
    if (!gBackgroundTexture.LoadFromFile("Background 3.png", gRenderer))
    {
        cout << "Failed to load background image" << endl;
        success = false;
    }
    return success;
}
bool loadCharacter(int type){
    string file;
    bool success = 1;
    if (type == 1){
        file = "char 1.png";
        if( !gSpriteSheetTexture.LoadFromFile(file,gRenderer))
    {
        printf( "Failed to load walking animation texture!\n" );
        success = false;
    }
    else
    {
        //Set sprite clips
        gSpriteClips[ 0 ].x =  57*0;
        gSpriteClips[ 0 ].y =   0;
        gSpriteClips[ 0 ].w =  57;
        gSpriteClips[ 0 ].h = 57;

        gSpriteClips[ 1 ].x =  57*1;
        gSpriteClips[ 1 ].y =   0;
        gSpriteClips[ 1 ].w =  57;
        gSpriteClips[ 1 ].h = 57;

        gSpriteClips[ 2 ].x =  57*2;
        gSpriteClips[ 2 ].y =   0;
        gSpriteClips[ 2 ].w =  57;
        gSpriteClips[ 2 ].h = 57;

        gSpriteClips[ 3 ].x = 57*3;
        gSpriteClips[ 3 ].y =   0;
        gSpriteClips[ 3 ].w =  57;
        gSpriteClips[ 3 ].h = 57;

        gSpriteClips[ 4 ].x = 57*4;
        gSpriteClips[ 4 ].y =   0;
        gSpriteClips[ 4 ].w =  57;
        gSpriteClips[ 4 ].h = 57;

        gSpriteClips[ 5 ].x = 57*5;
        gSpriteClips[ 5 ].y =   0;
        gSpriteClips[ 5 ].w =  57;
        gSpriteClips[ 5 ].h = 57;

    }
    }else{
        if (type == 2){
             file = "char 1 mutant.png";
        if( !gSpriteSheetTexture.LoadFromFile(file,gRenderer))
        {
            printf( "Failed to load walking animation texture!\n" );
            success = false;
        }
        else
        {
            gSpriteClips[ 0 ].x =  75*0;
            gSpriteClips[ 0 ].y =   0;
            gSpriteClips[ 0 ].w = 75;
            gSpriteClips[ 0 ].h = 75;

            gSpriteClips[ 1 ].x =  75*1;
            gSpriteClips[ 1 ].y =   0;
            gSpriteClips[ 1 ].w =  75;
            gSpriteClips[ 1 ].h = 75;

            gSpriteClips[ 2 ].x =  75*2;
            gSpriteClips[ 2 ].y =   0;
            gSpriteClips[ 2 ].w =  75;
            gSpriteClips[ 2 ].h = 75;

            gSpriteClips[ 3 ].x =  75*3;
            gSpriteClips[ 3 ].y =   0;
            gSpriteClips[ 3 ].w =  75;
            gSpriteClips[ 3 ].h = 75;

            gSpriteClips[ 4 ].x =  75*4;
            gSpriteClips[ 4 ].y =   0;
            gSpriteClips[ 4 ].w =  75;
            gSpriteClips[ 4 ].h = 75;

            gSpriteClips[ 5 ].x =  75*5;
            gSpriteClips[ 5 ].y =   0;
            gSpriteClips[ 5 ].w =  75;
            gSpriteClips[ 5 ].h = 75;
        }
        }else{
             file = "char 1 tiny.png";
             if( !gSpriteSheetTexture.LoadFromFile(file,gRenderer))
            {
                printf( "Failed to load walking animation texture!\n" );
                success = false;
            }
            else
            {
        //Set sprite clips
            gSpriteClips[ 0 ].x =  43*0;
            gSpriteClips[ 0 ].y =   0;
            gSpriteClips[ 0 ].w = 43;
            gSpriteClips[ 0 ].h = 43;

            gSpriteClips[ 1 ].x =  43*1;
            gSpriteClips[ 1 ].y =   0;
            gSpriteClips[ 1 ].w =  43;
            gSpriteClips[ 1 ].h = 43;

            gSpriteClips[ 2 ].x =  43*2;
            gSpriteClips[ 2 ].y =   0;
            gSpriteClips[ 2 ].w =  43;
            gSpriteClips[ 2 ].h = 43;

            gSpriteClips[ 3 ].x =  43*3;
            gSpriteClips[ 3 ].y =   0;
            gSpriteClips[ 3 ].w =  43;
            gSpriteClips[ 3 ].h = 43;

            gSpriteClips[ 4 ].x =  43*4;
            gSpriteClips[ 4 ].y =   0;
            gSpriteClips[ 4 ].w =  43;
            gSpriteClips[ 4 ].h = 43;

            gSpriteClips[ 5 ].x =  43*5;
            gSpriteClips[ 5 ].y =   0;
            gSpriteClips[ 5 ].w =  43;
            gSpriteClips[ 5 ].h = 43;
            }
        }
    }
    return success;
}
void Freeall(){
	gMenuTexture.Free();
	gMenuInstructionTexture.Free();
	gSpriteSheetTexture.Free();
	gPlayButtonTexture.Free();
	gHelpButtonTexture.Free();
	gExitButtonTexture.Free();
	gReturnButtonTexture.Free();
	gPauseButtonTexture.Free();
	gContinueButtonTexture.Free();
	//gLoseTexture.Free();
	gTextTextureYourScore.Free();
	gScoreTexture.Free();
	gTextTextureBestScore.Free();
	//gHighScoreTexture.Free();

	gBackgroundTexture.Free();

	//Mix_FreeMusic(gMusic);
	//Mix_FreeMusic(gMenuMusic);
	//Mix_FreeChunk(gClick);
	//Mix_FreeChunk(gLose);
	//Mix_FreeChunk(gJump);
	gMusic = nullptr;
	//gMenuMusic = nullptr;
	//gClick = nullptr;
	//Lose = nullptr;
	//gJump = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}
int main(int argc, char* argv[])
{
    initSDL(gWindow, gRenderer);

    if (!loadMedia())
    {
        printf("Failed to load media!\n");
    }
    else
    {
        bool Quit_Menu = false;
        bool Play_Again = false;
			while (!Quit_Menu)
			{
				SDL_Event e_mouse;
				while (SDL_PollEvent(&e_mouse) != 0)
				{
					if (e_mouse.type == SDL_QUIT)
					{
						Quit_Menu = true;
					}

					bool Quit_Game = false;
					HandlePlayButton(&e_mouse, PlayButton, Quit_Menu, Play_Again);
					HandleHelpButton(&e_mouse,gReturnButton,HelpButton,ReturnButton,gReturnButtonTexture,gMenuInstructionTexture,gInstructionTexture1,gInstructionTexture2,gInstructionTexture3,gAuthorTexture,gRenderer,Quit_Game);
					HandleExitButton(&e_mouse, ExitButton, Quit_Game);
					if (Quit_Game == true)
					{
						return 0;
					}
				}

				gMenuTexture.Render(0, 0, gRenderer);

				SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
				PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);

				SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
				HelpButton.Render(currentClip_Help, gRenderer, gHelpButtonTexture);

				SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
				ExitButton.Render(currentClip_Exit, gRenderer, gExitButtonTexture);

				SDL_RenderPresent(gRenderer);
        }
        // running and scrolling background

        int highscore = -1;

        bool mute = false;

        bool immune = false;

        while(Play_Again){
                double OffsetSpeed_Ground = 0;

                int immuneappear = 200;
                int mutantappear = 100;
                int tinyappear = 50;

                int time = 0;
                int score = 0;

                int specialfruittime = 500;

                int enemyframe = 0;
                int frame = 0;

                int scoreincrease = 0;
                double speedincrease = 0;
                int speedspecialfruitincrease = 0;

                SDL_Event ev;

                Enemy enemy1(IN_AIR_ENEMY);
                Enemy enemy2(ON_GROUND_ENEMY);
                Enemy enemy3(SKY_FALL_ENEMY);
                Enemy enemy4(IN_AIR_ENEMY1);

                GenerateEnemyChar(enemy2,enemy1,enemy3,enemy4,gEnemyClips2,gEnemyClips1,gEnemyClips3,gEnemyClips4,gRenderer);

                SpecialFruit Immune(IN_AIR_ENEMY);
                SpecialFruit Mutant(IN_AIR_ENEMY);
                SpecialFruit Tiny(IN_AIR_ENEMY);

                GenerateSpecialFruit(Immune,gSpecialFruit,Mutant,gGiantFruit,Tiny,gTinyFruit,gRenderer);

                type = 1;

                Character Character(type);

                bool Quit = false;

                bool specialfruitappear1 = false;
                bool specialfruitappear2 = false;
                bool specialfruitappear3 = false;

                bool Continue_game = true;
                    if (!mute){
                        Mix_PlayMusic(gMusic, -1);
                    }
                    while (!Quit){


                        if (loadCharacter(type)){
                                if (Continue_game){
                                    UpdateScore(time, scoreincrease, score);
                                    while(SDL_PollEvent(&ev) != 0){
                                        if(ev.type == SDL_QUIT)
                                        Quit = true;
                                        if (mute){
                                                HandleMuteButton(&ev,MuteButton,mute);
                                                Mix_PauseMusic();
                                        }else{
                                            HandleAudioButton(&ev,AudioButton,mute);
                                            Mix_ResumeMusic();
                                        }
                                        HandlePauseButton(&ev,PauseButton,ContinueButton,gRenderer,gContinueButton,gContinueButtonTexture,Continue_game);
                                        Character.HandleEvent(ev, gJump, mute, type);
                                    }
                                    RenderScrollingBackground(OffsetSpeed_Ground, gBackgroundTexture, gRenderer,speedincrease);
                                    Character.Move(type);

                                    //Render current frame
                                    SDL_Rect* currentClip = &gSpriteClips[ frame / 4];
                                    Character.Render(currentClip, gRenderer,gSpriteSheetTexture);

                                    //Go to next frame
                                    frame++;

                                    //Cycle animation
                                    if( frame / 4 >= WALKING_ANIMATION_FRAMES ){
                                            frame = 0;
                                    }
                                    SDL_Rect* currentClip_Enemy2 = &gEnemyClips2[0];
                                    enemy2.Move(speedincrease);
                                    enemy2.Render(gRenderer,currentClip_Enemy2);

                                    SDL_Rect* currentClip_Enemy1 = &gEnemyClips1[enemyframe / 4];
                                    enemy1.Move(speedincrease);
                                    enemy1.Render(gRenderer,currentClip_Enemy1);

                                    SDL_Rect* currentClip_Enemy3 = &gEnemyClips3[0];
                                    enemy3.Move(speedincrease);
                                    enemy3.Render(gRenderer,currentClip_Enemy3);

                                    SDL_Rect* currentClip_Enemy4 = &gEnemyClips4[0];
                                    enemy4.Move(speedincrease);
                                    enemy4.Render(gRenderer,currentClip_Enemy3);

                                    enemyframe++;

                                    if (enemyframe / 4 >= INAIR_ANIMATION_TOTAL){
                                        enemyframe = 0;
                                    }

                                    SDL_Rect* currentClip_SpecialFruit1 = &gSpecialFruit[0];

                                    if (score > immuneappear){
                                        Immune.Move(speedincrease,specialfruitappear1);
                                        Immune.Render(gRenderer,currentClip_SpecialFruit1);
                                        specialfruitappear1 = false;
                                    }
                                    if (Immune.GetPosX() < 0 && (specialfruitappear1 == false)){
                                        immuneappear += 400;
                                        specialfruitappear1 = true;
                                    }

                                    SDL_Rect* currentClip_SpecialFruit2 = &gGiantFruit[0];
                                    if (score > mutantappear){
                                        Mutant.Move(speedincrease,specialfruitappear2);
                                        Mutant.Render(gRenderer,currentClip_SpecialFruit2);
                                        specialfruitappear2 = false;
                                    }
                                    if (Mutant.GetPosX() < 0 && (specialfruitappear2 == false)){
                                        mutantappear += 400;
                                        specialfruitappear2 = true;
                                    }
                                    SDL_Rect* currentClip_SpecialFruit3 = &gTinyFruit[0];
                                    if (score > tinyappear){
                                        Tiny.Move(speedincrease,specialfruitappear3);
                                        Tiny.Render(gRenderer,currentClip_SpecialFruit3);
                                        specialfruitappear3 = false;
                                    }
                                    if (Tiny.GetPosX() < 0 && (specialfruitappear3 == false)){
                                        tinyappear += 400;
                                        specialfruitappear3 = true;
                                    }

                                    SDL_Rect* currentClip_Pause = &gPauseButton[PauseButton.currentSprite];
                                    PauseButton.Render(currentClip_Pause, gRenderer, gPauseButtonTexture);

                                    SDL_Rect* currentClip_Audio = &gAudioButton[AudioButton.currentSprite];
                                    AudioButton.Render(currentClip_Audio, gRenderer, gAudioButtonTexture);

                                    gTextTextureYourScore.Render(TEXT_YourScore_POSX, TEXT_YourScore_POSY, gRenderer);
                                    if (gScoreTexture.LoadFromRenderedText(std::to_string(score), gFont, textColor, gRenderer))
                                    {
                                            gScoreTexture.Render(SCORE_POSX, SCORE_POSY, gRenderer);
                                    }
                                    gTextTextureBestScore.Render(TEXT_BestScore_POSX, TEXT_BestScore_POSY, gRenderer);
                                    if (highscore != -1){
                                            if (gHighScoreTexture.LoadFromRenderedText(std::to_string(highscore), gFont, textColor,gRenderer))
                                            {
                                                gHighScoreTexture.Render(HIGHSCORE_POSX,HIGHSCORE_POSY,gRenderer);
                                            }
                                    }
                                    if (checkcollisionTinyFruit(Character,currentClip,Tiny,gTinyFruit)){
                                        type = 3;
                                        tinyappear+=400;
                                        specialfruitappear3 = true;
                                        Tiny.changeX(-1500);
                                        if (!mute){
                                            Mix_PlayChannel(-1, gEat, 0);
                                        }
                                    }
                                    if (checkcollisionGiantFruit(Character,currentClip,Mutant,gGiantFruit)){
                                        type = 2;
                                        mutantappear+=400;
                                        specialfruitappear2 = true;
                                        Mutant.changeX(-1500);
                                        if (!mute){
                                            Mix_PlayChannel(-1, gEat, 0);
                                        }
                                    }

                                    if (checkcollisionImmuneFruit(Character,currentClip,Immune,gSpecialFruit)){
                                            immune = true;
                                            immuneappear+=400;
                                            specialfruitappear1 = true;
                                            Immune.changeX(-1500);
                                            if (!mute){
                                                Mix_PlayChannel(-1, gEat, 0);
                                            }

                                    }
                                    if (immune){
                                        UpdateSpecialFruitTime(specialfruittime, speedspecialfruitincrease, immune);
                                        gTextSpecialFruitTime.Render(SPECIALFRUIT_TEXT_POSX, SPECIALFRUIT_TEXT_POSY, gRenderer);
                                        if (gSpecialFruitTime.LoadFromRenderedText(std::to_string(specialfruittime), gFont, textColor, gRenderer))
                                        {
                                            gSpecialFruitTime.Render(SPECIALFRUIT_TIME_POSX, SPECIALFRUIT_TIME_POSY, gRenderer);
                                        }
                                    }
                                    if (!immune){
                                        if (checkcollision1(Character,currentClip,enemy2,currentClip_Enemy2) || checkcollision2(Character,currentClip,enemy1,currentClip_Enemy1) || checkcollision3(Character,currentClip,enemy3,currentClip_Enemy3) || checkcollision4(Character,currentClip,enemy4,currentClip_Enemy4)){
                                            Mix_PauseMusic();
                                            HighScore(score,highscore);
                                            Quit = true;
                                        }
                                    }
                                    SDL_RenderPresent(gRenderer);
                                    }
                                    if (specialfruittime < 0){
                                            specialfruittime = 500;
                                    }
                        }
                    }
                    EndGame(&ev,gRenderer,Play_Again,gLoseTexture,gEndgameTexture);
                }
            }
    Freeall();
    return 0;
}
