#ifndef LGAMEBASE_H_INCLUDED
#define LGAMEBASE_H_INCLUDED

void HandlePlayButton(SDL_Event* e,
	LButton& PlayButton,
	bool& QuitMenu,
	bool& Play)
	//Mix_Chunk* gClick)
{
	if (e->type == SDL_QUIT)
	{
		QuitMenu = true;
	}

	if (PlayButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PlayButton.currentSprite = BUTTON_MOUSE_IN;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Play = true;
			QuitMenu = true;
			//Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			PlayButton.currentSprite = BUTTON_MOUSE_IN;
			break;
		}
	}
	else
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}
void HandleHelpButton(SDL_Event* e,
    SDL_Rect(&gReturnButton)[BUTTON_TOTAL],
	LButton& HelpButton,
	LButton& ReturnButton,
	LTexture gReturnButtonTexture,
	LTexture gMenuBackground,
	LTexture gInstructionTexture1,
	LTexture gInstructionTexture2,
	LTexture gInstructionTexture3,
	LTexture gAuthorTexture,
	SDL_Renderer *gRenderer,
	bool& QuitGame)
{
	if (e->type == SDL_QUIT)
	{
		QuitGame = true;
	}

	if (HelpButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			HelpButton.currentSprite = BUTTON_MOUSE_IN;
			break;
		case SDL_MOUSEBUTTONDOWN:
			//Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			HelpButton.currentSprite = BUTTON_MOUSE_IN;
			bool instruction = false;
			while (!instruction){
                do{
                    if (e->type == SDL_QUIT){
                        instruction = true;
                        QuitGame = true;
                    }else{
                        if (ReturnButton.IsInside(e, RETURN_BUTTON)){

                            switch(e->type){
                            case SDL_MOUSEMOTION:
                                ReturnButton.currentSprite = BUTTON_MOUSE_IN;
                                break;

                            case SDL_MOUSEBUTTONDOWN:
                                instruction = true;
                                ReturnButton.currentSprite = BUTTON_MOUSE_IN;
                                break;
                            }
                        }else{
                            ReturnButton.currentSprite = BUTTON_MOUSE_OUT;
                        }

                    }
                        gMenuBackground.Render(0,0,gRenderer);

                        SDL_Rect* currentClip_Return = &gReturnButton[ReturnButton.currentSprite];
                        ReturnButton.Render(currentClip_Return, gRenderer,gReturnButtonTexture);

                        gInstructionTexture1.Render(INSTRUCTIONS_POSX1, INSTRUCTIONS_POSY1, gRenderer);
                        gInstructionTexture2.Render(INSTRUCTIONS_POSX2, INSTRUCTIONS_POSY2, gRenderer);
                        gInstructionTexture3.Render(INSTRUCTIONS_POSX3, INSTRUCTIONS_POSY3, gRenderer);
                        gAuthorTexture.Render(AUTHOR_POSX,AUTHOR_POSY, gRenderer);

                        SDL_RenderPresent(gRenderer);

                }while (SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
			}
			break;
		}
	}
	else
	{
		HelpButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}
void HandleExitButton(SDL_Event* e,
	LButton& ExitButton,
	bool& Quit)
{
	if (ExitButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			ExitButton.currentSprite = BUTTON_MOUSE_IN;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Quit = true;
			ExitButton.currentSprite = BUTTON_MOUSE_IN;
			//Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
			break;
		}
	}
	else
	{
		ExitButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}
void HandleMuteButton(SDL_Event* e,
    LButton MuteButton,
    bool &mute)
{
          if (MuteButton.IsInside(e, SMALL_BUTTON)){
            switch (e->type){
            case SDL_MOUSEMOTION:
                MuteButton.currentSprite = BUTTON_MOUSE_IN;
                break;
            case SDL_MOUSEBUTTONDOWN:
                MuteButton.currentSprite = BUTTON_MOUSE_IN;
                mute = false;
                break;
            }
        }else{
            MuteButton.currentSprite = BUTTON_TOTAL;
        }

}
void HandleAudioButton(SDL_Event* e,
    LButton& AudioButton,
    bool &mute)
{
    if (AudioButton.IsInside(e, SMALL_BUTTON)){
        switch (e->type){
        case SDL_MOUSEMOTION:
            AudioButton.currentSprite = BUTTON_MOUSE_IN;
            break;
        case SDL_MOUSEBUTTONDOWN:
            AudioButton.currentSprite = BUTTON_MOUSE_IN;
            mute = true;
            break;
        }
    }else{
        AudioButton.currentSprite = BUTTON_MOUSE_OUT;
    }
}

void HandleContinueButton(SDL_Event* e,
    LButton ContinueButton,
	LTexture gContinueButtonTexture,
	SDL_Renderer* gRenderer,
	SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
	bool& Continue_game)
{
	bool Back_game = false;
	while (!Back_game)
	{
		do
		{
			if (ContinueButton.IsInside(e, SMALL_BUTTON))
			{
				switch (e->type)
				{
				case SDL_MOUSEMOTION:
					ContinueButton.currentSprite = BUTTON_MOUSE_IN;
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
					ContinueButton.currentSprite = BUTTON_MOUSE_IN;
					Continue_game = true;
					Back_game = true;
					//Mix_ResumeMusic();
				}
                break;
				}
			}
			else
			{
				ContinueButton.currentSprite = BUTTON_MOUSE_OUT;
			}

			SDL_Rect* currentClip_Continue = &gContinueButton[ContinueButton.currentSprite];
			ContinueButton.Render(currentClip_Continue, gRenderer, gContinueButtonTexture);

			SDL_RenderPresent(gRenderer);
		} while (SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION);
	}
}
void HandlePauseButton(SDL_Event* e,
    LButton& PauseButton,
	LButton ContinueButton,
	SDL_Renderer* gRenderer,
	SDL_Rect (&gContinueButton)[BUTTON_TOTAL],
	LTexture gContinueButtonTexture,
	bool &Continue_game)
{
	if (PauseButton.IsInside(e, SMALL_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PauseButton.currentSprite = BUTTON_MOUSE_IN;
			break;
		case SDL_MOUSEBUTTONDOWN:
			PauseButton.currentSprite = BUTTON_MOUSE_IN;
			break;
		case SDL_MOUSEBUTTONUP:
			Continue_game = false;
			//Mix_PauseMusic();
			HandleContinueButton(e,ContinueButton, gContinueButtonTexture,  gRenderer, gContinueButton, Continue_game);
			break;
		}
	}
	else
	{
		PauseButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}
void RenderScrollingBackground(double &offsetSpeed,
	LTexture &gBackgroundTexture,
	SDL_Renderer* gRenderer,
	int speed)
{
		offsetSpeed -= 5 + speed;
		if (offsetSpeed < -gBackgroundTexture.GetWidth())
		{
			offsetSpeed = 0;
		}
		gBackgroundTexture.Render(offsetSpeed,0, gRenderer);
		gBackgroundTexture.Render(offsetSpeed + gBackgroundTexture.GetWidth(),0, gRenderer);
}
bool checkcollision1(Character Character, SDL_Rect* a,Enemy enemy2, SDL_Rect* b){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    bool collide = false;

	leftA = Character.GetPosX();
	rightA = Character.GetPosX() + a->w;
	topA = Character.GetPosY();
	bottomA = Character.GetPosY() + a->h;


    //Calculate the sides of rect B
    leftB = enemy2.GetPosX();
    rightB = enemy2.GetPosX() + enemy2.GetWidth();
    topB = enemy2.GetPosY();
    bottomB = enemy2.GetPosY() + enemy2.GetHeight();

     if( bottomA - 19 <= topB )
    {
        return false;
    }

    if( topA + 19 >= bottomB )
    {
        return false;
    }

    if( rightA - 17 <= leftB )
    {
        return false;
    }

    if( leftA + 17 >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
bool checkcollision2(Character Character, SDL_Rect* a,Enemy enemy1, SDL_Rect* b){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    bool collide = false;

	leftA = Character.GetPosX();
	rightA = Character.GetPosX() + a->w;
	topA = Character.GetPosY();
	bottomA = Character.GetPosY() + a->h;


    //Calculate the sides of rect B
    leftB = enemy1.GetPosX();
    rightB = enemy1.GetPosX() + 128;
    topB = enemy1.GetPosY();
    bottomB = enemy1.GetPosY() + 128;

    if( bottomA - 55  <= topB )
    {
        return false;
    }

    if( topA + 55 >= bottomB )
    {
        return false;
    }

    if( rightA - 55 <= leftB  )
    {
        return false;
    }

    if( leftA + 55 >= rightB )
    {
        return false;
    }
    //If none of the sides from A are outside B
    return true;
}
bool checkcollisionImmuneFruit(Character Character, SDL_Rect* a,SpecialFruit Immune, SDL_Rect* b){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    bool collide = false;

	leftA = Character.GetPosX();
	rightA = Character.GetPosX() + a->w;
	topA = Character.GetPosY();
	bottomA = Character.GetPosY() + a->h;


    //Calculate the sides of rect B
    leftB = Immune.GetPosX();
    rightB = Immune.GetPosX() + 90;
    topB = Immune.GetPosY();
    bottomB = Immune.GetPosY() + 90;

    if( bottomA - 30  <= topB )
    {
        return false;
    }

    if( topA + 30 >= bottomB )
    {
        return false;
    }

    if( rightA - 30 <= leftB  )
    {
        return false;
    }

    if( leftA + 30 >= rightB )
    {
        return false;
    }
    //If none of the sides from A are outside B
    return true;
}
bool checkcollisionGiantFruit(Character Character, SDL_Rect* a,SpecialFruit Mutant, SDL_Rect* b){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    bool collide = false;

	leftA = Character.GetPosX();
	rightA = Character.GetPosX() + a->w;
	topA = Character.GetPosY();
	bottomA = Character.GetPosY() + a->h;


    //Calculate the sides of rect B
    leftB = Mutant.GetPosX();
    rightB = Mutant.GetPosX() + 50;
    topB = Mutant.GetPosY();
    bottomB = Mutant.GetPosY() + 62;

    if( bottomA - 30  <= topB )
    {
        return false;
    }

    if( topA + 30 >= bottomB )
    {
        return false;
    }

    if( rightA - 30 <= leftB  )
    {
        return false;
    }

    if( leftA + 30 >= rightB )
    {
        return false;
    }
    //If none of the sides from A are outside B
    return true;
}
int UpdateScore(int& time,
	int& speed,
	int& score)
{
	if (time == TIME_MAX)
	{
		speed += SPEED_INCREASEMENT;
	}

	if (time > TIME_MAX)
	{
		time = 0;
	}
	if (time % 5 == 0)
	{
		score += SCORE_INCREASEMENT;
	}

	time += TIME_INCREASEMENT;

	return time;
}
void HighScore(int score, int& highscore){
    if (score > highscore){
        highscore = score;
    }
}
void GenerateEnemyChar(//Enemy& enemy1,
	Enemy& enemy2,
	Enemy& enemy1,
    SDL_Rect(&gEnemyClips2)[ONGROUND_ANIMATION_TOTAL],
    SDL_Rect(&gEnemyClips1)[INAIR_ANIMATION_TOTAL],
	SDL_Renderer * gRenderer)
{
	enemy2.LoadFromFile("cactus1.png", gRenderer);
	{
	    gEnemyClips2[0].x = 0;
	    gEnemyClips2[0].y = 0;
	    gEnemyClips2[0].w = 60;
	    gEnemyClips2[0].h = 96;
	}

	enemy1.LoadFromFile("Bat_Fly.png", gRenderer);
	{
		gEnemyClips1[0].x = 0;
		gEnemyClips1[0].y = 0;
		gEnemyClips1[0].w = 128;
		gEnemyClips1[0].h = 128;

		gEnemyClips1[1].x = 128 * 1;
		gEnemyClips1[1].y = 0;
		gEnemyClips1[1].w = 128;
		gEnemyClips1[1].h = 128;

		gEnemyClips1[2].x = 128 * 2;
		gEnemyClips1[2].y = 0;
		gEnemyClips1[2].w = 128;
		gEnemyClips1[2].h = 128;

		gEnemyClips1[3].x = 128 * 3;
		gEnemyClips1[3].y = 0;
		gEnemyClips1[3].w = 128;
		gEnemyClips1[3].h = 128;
	}
}
void GenerateSpecialFruit(SpecialFruit& Immune,
    SDL_Rect (&gSpecialFruit1)[SPECIALFRUIT_ANIMATION],
    SpecialFruit& Mutant,
    SDL_Rect (&gSpecialFruit2)[SPECIALFRUIT_ANIMATION],
    SDL_Renderer *gRenderer)
{
    Immune.LoadFromFile("Immunefruit.png", gRenderer);
    {
        gSpecialFruit1[0].x = 0;
        gSpecialFruit1[0].y = 0;
        gSpecialFruit1[0].w = 90;
        gSpecialFruit1[0].h = 90;
    }
    Mutant.LoadFromFile("Mutantfruit.png", gRenderer);
    {
        gSpecialFruit2[0].x = 0;
        gSpecialFruit2[0].y = 0;
        gSpecialFruit2[0].w = 50;
        gSpecialFruit2[0].h = 62;
    }
}
void EndGame(SDL_Event* e,
    SDL_Renderer *gRenderer,
    bool& Play_Again,
    LTexture gLoseTexture,
    LTexture gEndgameTexture)
{
    if (Play_Again)
    {
        bool Out = false;
        while(!Out){
            while (SDL_PollEvent(e) != 0)
			{
				if (e->type == SDL_QUIT)
				{
					Play_Again = false;
				}

				if (e->type == SDL_KEYDOWN)
				{
					switch (e->key.keysym.sym)
					{
					case SDLK_SPACE:
						Out = true;
						break;
					case SDLK_ESCAPE:
						Out = true;
						Play_Again = false;
						break;
					}
				}
			}
			gLoseTexture.Render(GAMEOVER_POSX,GAMEOVER_POSY,gRenderer);
            gEndgameTexture.Render(ENDGAME_POSX,ENDGAME_POSY,gRenderer);

			SDL_RenderPresent(gRenderer);
		}
    }
}
int UpdateSpecialFruitTime(int &time,
    int speed,
    bool& immune)
{
    if (time == 0){
        immune = false;
    }
    if (speed % 10000000000 == 0){
        time--;
    }
    speed++;
    return time;
}
#endif // LGAMEBASE_H_INCLUDED
