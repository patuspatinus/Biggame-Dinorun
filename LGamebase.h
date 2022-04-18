#ifndef LGAMEBASE_H_INCLUDED
#define LGAMEBASE_H_INCLUDED

int i = 0;

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
	LButton& HelpButton,
	bool& QuitMenu,
	bool& Play)
{
	if (e->type == SDL_QUIT)
	{
		QuitMenu = true;
	}

	if (HelpButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			HelpButton.currentSprite = BUTTON_MOUSE_IN;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Play = true;
			QuitMenu = true;
			//Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			HelpButton.currentSprite = BUTTON_MOUSE_IN;
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
			HandleContinueButton(e,ContinueButton, gContinueButtonTexture,  gRenderer, gContinueButton, Continue_game);
			break;
		}
	}
	else
	{
		PauseButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}
void RenderScrollingBackground(std::vector <double>& offsetSpeed,
	LTexture &gBackgroundTexture,
	SDL_Renderer* gRenderer)
{

	for (int i = 0; i < 12; ++i)
	{
		offsetSpeed[i] -= 5;
		if (offsetSpeed[i] < -gBackgroundTexture.GetWidth())
		{
			offsetSpeed[i] = 0;
		}
		gBackgroundTexture.Render(offsetSpeed[i],0, gRenderer);
		gBackgroundTexture.Render(offsetSpeed[i] + gBackgroundTexture.GetWidth(),0, gRenderer);
	}
}
#endif // LGAMEBASE_H_INCLUDED
