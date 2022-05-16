#ifndef LBUTTON_H_INCLUDED
#define LBUTTON_H_INCLUDED
enum LButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_IN = 1,
	BUTTON_TOTAL = 2,
	BUTTON_AUDIO_TOTAL = 3,
};

class LButton
{
public:
    LButtonSprite currentSprite;

	LButton();

	LButton(int x, int y);

	void SetPosition(int x, int y);

	bool IsInside(SDL_Event *e, int size);

	void Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture);

	void ChooseCharacterRender(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture, int type);


private:
	SDL_Point position;

};


LButton::LButton()
{
	position.x = 0;
	position.y = 0;

	currentSprite = BUTTON_MOUSE_OUT;
}

LButton::LButton(int x, int y)
{
	position.x = x;
	position.y = y;

	currentSprite = BUTTON_MOUSE_OUT;
}

void LButton::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

bool LButton::IsInside(SDL_Event *e, int size)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		int button_width, button_height;
		if (size == SMALL_BUTTON)
		{
			button_width = SMALL_BUTTON_WIDTH;
			button_height = SMALL_BUTTON_HEIGHT;
		}else{
		    if (size == COMMON_BUTTON){
                    button_width = COMMON_BUTTON_WIDTH;
			        button_height = COMMON_BUTTON_HEIGHT;
		    }else{
		        button_width = RETURN_BUTTON_WIDTH;
                button_height = RETURN_BUTTON_HEIGHT;
		    }
		}
		SDL_GetMouseState(&x, &y);

		bool inside = true;
		if (x < position.x)
		{
			inside = false;
		}
		else if (x > position.x + button_width)
		{
			inside = false;
		}
		else if (y < position.y)
		{
			inside = false;
		}
		else if (y > position.y + button_height)
		{
			inside = false;
		}
		return inside;
	}
	return false;
}

void LButton::Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture)
{
	gButtonTexture.Render(position.x, position.y, gRenderer, currentClip);
}
#endif // LBUTTON_H_INCLUDED
