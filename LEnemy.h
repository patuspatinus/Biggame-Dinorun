#ifndef LENEMY_H_INCLUDED
#define LENEMY_H_INCLUDED

class Enemy
{
public:
	Enemy(int _type = 0);

	~Enemy();

	void LoadFromFile(std::string path, SDL_Renderer* gRenderer);

	void Move(double& acceleration);

	void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);

	int GetPosX();

	int GetPosY();

	int GetWidth();

	int GetHeight();
private:
	int posX, posY;

	int eWidth, eHeight;

	int type;

	SDL_Texture *EnemyTexture;
};

Enemy::Enemy(int _type)
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	type = _type;
 	if (type == IN_AIR_ENEMY)
	{
		posX = -(rand() % (SCREEN_WIDTH + RANGE)) - SCREEN_WIDTH;
		posY = GROUND - 180;
	}
	else {
        if (type == ON_GROUND_ENEMY)
            {
                posX = rand() % (SCREEN_WIDTH + RANGE) + SCREEN_WIDTH;
                posY = GROUND - 43;
            }else{
                if (type == SKY_FALL_ENEMY){
                    posX = SCREEN_WIDTH - 400;
                    posY = -(rand() % (SCREEN_HEIGHT + 1000)) - SCREEN_HEIGHT;
                }else{
                    posX = rand() % (SCREEN_WIDTH + RANGE) + SCREEN_WIDTH;
                    posY = GROUND - 80;
                }
            }
	}
	EnemyTexture = nullptr;
}

Enemy::~Enemy()
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	if (EnemyTexture != nullptr)
	{
		EnemyTexture = nullptr;
	}
}
void Enemy::LoadFromFile(std::string path, SDL_Renderer* gRenderer)
{
	SDL_Texture* tmpTexture = nullptr;

	SDL_Surface* tmpSurface = IMG_Load(path.c_str());
	if (tmpSurface == nullptr)
	{
		logSDLError(std::cout ,"Can not load image.", IMG_GetError);
	}
	else
	{
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

		tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
		if (tmpTexture == nullptr)
		{
			logSDLError(std::cout ,"Can not create texture from surface.", SDL_GetError);
		}
		else
		{
			eWidth = tmpSurface->w;
			eHeight = tmpSurface->h;
		}

		SDL_FreeSurface(tmpSurface);
	}

	EnemyTexture = tmpTexture;
}
void Enemy::Move(double &acceleration)
{
    if (type == ON_GROUND_ENEMY){
        posX += -(ENEMY_SPEED + acceleration);
        if (posX < - MAX_ENEMY_WIDTH )
        {
            posX = rand() % (SCREEN_WIDTH + RANGE) + SCREEN_WIDTH;
		}
    }else{
        if (type == IN_AIR_ENEMY){
            posX += (ENEMY_SPEED + acceleration);
            if (posX > SCREEN_WIDTH + MAX_ENEMY_WIDTH)
        {
            posX = -(rand() % (SCREEN_WIDTH + RANGE)) - SCREEN_WIDTH;
        }
        }else{
            if (type == SKY_FALL_ENEMY){
                if (posY >= 400){
                posX-= (8 + acceleration);
                if (posX < - MAX_ENEMY_WIDTH){
                    posX = SCREEN_WIDTH - 400;
                    posY = -(rand() % (SCREEN_HEIGHT + 10000)) - SCREEN_HEIGHT;
                }
            }else{
                 posY += (ENEMY_SPEED + acceleration);
            }
            }else{
                posX+= -(10+ acceleration);
                if (posX < - MAX_ENEMY_WIDTH - 100)
                {
                    posX = rand() % (SCREEN_WIDTH + RANGE) + SCREEN_WIDTH;
                }
            }
        }
    }
}

void Enemy::Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
	SDL_Rect renderSpace = { posX, posY, eWidth, eHeight };
	if (currentClip != nullptr)
	{
		renderSpace.w = currentClip->w;
		renderSpace.h = currentClip->h;
	}
	SDL_RenderCopy(gRenderer, EnemyTexture, currentClip, &renderSpace);
}
int Enemy::GetPosX()
{
	return posX;
}

int Enemy::GetPosY()
{
	return posY;
}

int Enemy::GetWidth()
{
	return eWidth;
}

int Enemy::GetHeight()
{
	return eHeight;
}

#endif // LENEMY_H_INCLUDED
