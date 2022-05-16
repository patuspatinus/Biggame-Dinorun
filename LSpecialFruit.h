#ifndef LSPECIALFRUIT_H_INCLUDED
#define LSPECIALFRUIT_H_INCLUDED

class SpecialFruit
{
public:
    int posX;

    SpecialFruit(int _type = 0);

    ~SpecialFruit();

	void LoadFromFile(std::string path, SDL_Renderer* gRenderer);

	void Move(const int& acceleration, bool & checkappear);

	void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);

	int GetPosX();

	int GetPosY();

	int GetWidth();

	int GetHeight();
private:
	int posY;

	int type;

	int eWidth, eHeight;

	SDL_Texture *SpecialFruitTexture;
};

SpecialFruit::SpecialFruit(int _type)
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	type = _type;
 	if (type == IN_AIR_ENEMY)
	{
		posX = rand() % (SCREEN_WIDTH + RANGE) + SCREEN_WIDTH;
		posY = GROUND - 140;
	}
	SpecialFruitTexture = nullptr;
}

SpecialFruit::~SpecialFruit()
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

	if (SpecialFruitTexture != nullptr)
	{
		SpecialFruitTexture = nullptr;
	}
}

void SpecialFruit::LoadFromFile(std::string path, SDL_Renderer* gRenderer)
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

	SpecialFruitTexture = tmpTexture;
}

void SpecialFruit::Move(const int &acceleration, bool& checkappear)
{
	posX += -(ENEMY_SPEED + acceleration);
	if ((posX + MAX_ENEMY_WIDTH < 0) && (checkappear))
	{
		posX = rand() % (SCREEN_WIDTH + RANGE) + SCREEN_WIDTH;
        posY = rand() % (ENEMY_MAX_HEIGHT - ENEMY_MIN_HEIGHT + 1) + ENEMY_MIN_HEIGHT;
        checkappear = false;
	}
}

void SpecialFruit::Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
	SDL_Rect renderSpace = { posX, posY, eWidth, eHeight };
	if (currentClip != nullptr)
	{
		renderSpace.w = currentClip->w;
		renderSpace.h = currentClip->h;
	}
	SDL_RenderCopy(gRenderer, SpecialFruitTexture, currentClip, &renderSpace);
}

int SpecialFruit::GetPosX()
{
	return posX;
}

int SpecialFruit::GetPosY()
{
	return posY;
}

int SpecialFruit::GetWidth()
{
	return eWidth;
}

int SpecialFruit::GetHeight()
{
	return eHeight;
}

#endif // LSPECIALFRUIT_H_INCLUDED
