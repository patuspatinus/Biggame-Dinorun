#ifndef LCHARACTER_H_INCLUDED
#define LCHARACTER_H_INCLUDED

#define CHAR1 1
#define CHAR2 2
#define CHAR3 3
class Character
{
public:
	const int GRAVITY = 10;

	Character();

	bool OnGround();

	void HandleEvent(SDL_Event& e,Mix_Chunk *gJump, bool &mute);

	void Move();

	void Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture);

	int GetPosX();

	int GetPosY();

private:
	int posX, posY;

	bool status;
};


Character::Character()
{
	posX = SCREEN_WIDTH - 1100;
	posY = GROUND - 6;

	status = 0;
}

bool Character::OnGround()
{
	return posY == GROUND - 6;
}
void Character::HandleEvent(SDL_Event& e, Mix_Chunk *gJump, bool& mute)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_SPACE:
			{
				if (OnGround())
				{
				    if (!mute){
                        Mix_PlayChannel(-1, gJump, 0);
				    }
					status = JUMP;
				}
			}
		}
	}
}

void Character::Move()
{
	if (status == JUMP && posY >= MAX_HEIGHT)
	{
		posY += -GRAVITY;
	}
	if (posY <= MAX_HEIGHT)
	{
		status = FALL;
	}
    if (status == FALL && posY < GROUND - 6)
	{
		posY += GRAVITY;
	}
}

void Character::Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture)
{
	gCharacterTexture.Render(posX, posY, gRenderer, currentClip);
}

int Character::GetPosX()
{
	return posX;
}

int Character::GetPosY()
{
	return posY;
}


#endif // LCHARACTER_H_INCLUDED
