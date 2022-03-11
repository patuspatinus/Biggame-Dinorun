#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Big game by patuspatinus";

#define GROUND 510
#define MAX_HEIGHT 280
#define BASE_OFFSET_SPEED 0

bool JUMP = 1;
bool FALL = 0;

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if ( SDL_WaitEvent(&e) != 0 &&
                (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
SDL_Texture* loadTexture( string path, SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == nullptr )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}
class LTexture
{
public:
    LTexture();

    ~LTexture();

    void Free();

    //bool LoadFromRenderedText(std::string textureText, TTF_Font* gFont, SDL_Color textColor, SDL_Renderer* gRenderer);

    bool LoadFromFile(std::string path, SDL_Renderer *gRenderer);

    void Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);

    int GetWidth();

    int GetHeight();

private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};

LTexture::LTexture()
{
    mTexture = nullptr;

    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    Free();
}

void LTexture::Free()
{
    if (mTexture != nullptr)
    {
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

/*bool LTexture::LoadFromRenderedText(std::string textureText,TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *gRenderer)
{
	Free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return mTexture != NULL;
}*/

bool LTexture::LoadFromFile(std::string path, SDL_Renderer *gRenderer)
{
    Free();

    SDL_Texture* tmpTexture = nullptr;

    SDL_Surface* tmpSurface = IMG_Load(path.c_str());
    if (tmpSurface == nullptr)
    {
        logSDLError(cout, "Can not load image.", IMG_GetError);
    }
    else
    {
        SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

        tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
        if (tmpTexture == nullptr)
        {
            logSDLError(cout,"Can not create texture from surface.", SDL_GetError);
        }
        else
        {
            mWidth = tmpSurface->w;
            mHeight = tmpSurface->h;
        }

        SDL_FreeSurface(tmpSurface);
    }

    mTexture = tmpTexture;

    return mTexture != nullptr;
}

void LTexture::Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
    SDL_Rect renderSpace = { x, y, mWidth, mHeight };

    if (clip != nullptr)
    {
        renderSpace.w = clip->w;
        renderSpace.h = clip->h;
    }

    SDL_RenderCopy(gRenderer, mTexture, clip, &renderSpace);
}

int LTexture::GetWidth()
{
    return mWidth;
}

int LTexture::GetHeight()
{
    return mHeight;
}
class Character
{
public:
	const int GRAVITY = 12;

	Character();

	bool OnGround();

	void HandleEvent(SDL_Event& e);

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
	posY = GROUND;

	status = 0;
}

bool Character::OnGround()
{
	return posY == GROUND;
}
void Character::HandleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_SPACE:
			{
				if (OnGround())
				{
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
    if (status == FALL && posY < GROUND)
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
const int WALKING_ANIMATION_FRAMES = 6;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
LTexture gSpriteSheetTexture;
SDL_Window* gWindow;
SDL_Renderer* gRenderer;
Character Character;
LTexture gBackgroundTexture;
//Tai anh
bool loadMedia()
{
    //Loading success flag
    bool success = 1;
    if (!gBackgroundTexture.LoadFromFile("Background 3.png", gRenderer))
    {
        cout << "Failed to load background image" << endl;
        success = false;
    }
    //Load sprite sheet texture
    if( !gSpriteSheetTexture.LoadFromFile("char 1.png",gRenderer))
    {
        printf( "Failed to load walking animation texture!\n" );
        success = 0;
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

    return success;
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
// Main
int main(int argc, char* argv[])
{

    initSDL(gWindow, gRenderer);

    // Your drawing code here
    // use SDL_RenderPresent(renderer) to show it


    //Create vsynced renderer for window
    if (!loadMedia())
    {
        printf("Failed to load media!\n");
    }
    else
    {
        int OffsetSpeed_Ground = BASE_OFFSET_SPEED;
        vector <double> OffsetSpeed_Bkgr(12, BASE_OFFSET_SPEED);
        //Current animation frame
        int frame = 0;
        bool quit = false;
        SDL_Event ev;
        SDL_Rect* currentClip = nullptr;
        while (!quit){
            while(SDL_PollEvent(&ev) != 0)
		{
			// Getting the events
			if(ev.type == SDL_QUIT)
				quit = false;
            Character.HandleEvent(ev);
		}
        RenderScrollingBackground(OffsetSpeed_Bkgr, gBackgroundTexture, gRenderer);
        Character.Move();
        //Render current frame
        currentClip = &gSpriteClips[ frame / 4];
        Character.Render(currentClip, gRenderer,gSpriteSheetTexture);
        //Update screen
        SDL_RenderPresent(gRenderer);
        //Go to next frame
        frame++;
        //Cycle animation
        if( frame / 4 >= WALKING_ANIMATION_FRAMES ){
            frame = 0;
        }
        }
    }
    waitUntilKeyPressed();
    quitSDL(gWindow,gRenderer);
    return 0;
}
