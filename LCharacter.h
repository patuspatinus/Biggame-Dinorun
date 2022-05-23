#ifndef LCHARACTER_H_INCLUDED
#define LCHARACTER_H_INCLUDED

class Character
{
public:
	Character(int &type);

	void ChangeY(int NewY);

	bool OnGround(int &type);

	void HandleEvent(SDL_Event& e,Mix_Chunk *gJump, bool &mute, int& type);

	void Move(int &type);

	void Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture);

	int GetPosX();

	int GetPosY();

private:
	int posX, posY;

	bool status;
};


Character::Character(int &type)
{
    posX = SCREEN_WIDTH - 900;
    if (type == 1){
	    posY = GROUND;
    }else{
        if (type == 2){
            posY = GROUND - 10;
        }else{
            posY = GROUND + 20;
        }
    }
	status = 0;
}
void Character:: ChangeY(int NewY){
    posY = NewY;
}
bool Character::OnGround(int &type)
{
    if (type == 1){
        return posY == GROUND;
    }else{
        if (type == 2){
            return posY == (GROUND - 10);
        }else{
            return posY == (GROUND + 20);
        }
    }
}
void Character::HandleEvent(SDL_Event& e, Mix_Chunk *gJump, bool& mute, int& type)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_SPACE:
			{
				if (OnGround(type))
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

void Character::Move(int& type)
{
    int JUMPGROUND;
    if (type == 1){
        JUMPGROUND = GROUND;
    }else{
        if (type == 2){
            JUMPGROUND = GROUND - 10;
        }else{
            JUMPGROUND = GROUND + 20;
        }
    }
	if (status == JUMP && posY >= MAX_HEIGHT)
	{
		posY += -GRAVITY;
	}
	if (posY <= MAX_HEIGHT)
	{
		status = FALL;
	}
    if (status == FALL && posY < JUMPGROUND)
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
