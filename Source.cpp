#define SDL_MAIN_HANDLED

#undef min
#undef max
#undef far
#undef near
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include <iostream>

const int N = 4;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window* window = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

#include "camera.h"
#include "fillTriangle.h"
#include "mesh.h"
#include "objLoader.h"
#include "projection.h"





bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize SDL: %s \n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        window = SDL_CreateWindow("New window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Failed to create window: %s \n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Failed to create renderer: %s \n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("Failed to initialize SDl_image: %s \n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;

}

bool createTexture()
{

    gTexture = SDL_CreateTexture(gRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (gTexture == NULL)
    {
        std::cout << "Unable to create texture\n";
    }


    return gTexture != NULL;
}

int main()
{
    init();

    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            zbuffer[i][j] = 10000.f;
        }
    }

    float v1[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
        // front face
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top-right
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top-right
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // top-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
        // left face
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-right
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-left
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-right
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-right
        // right face
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-left
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // top-left
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
        // bottom face
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // top-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-right
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
        // top face
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f // bottom-left
    };

    float test[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
    };

    float start = SDL_GetTicks();
    Mesh cube;
    float mat[4][4];
    proj(mat);
    for (int i = 0; i < 36; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cube.mVertices.push_back(v1[i * 5 + j]);
        }
    }

    // for(int i = 0; i < 6; i++)
    // {
    //     for(int j = 0; j < 3; j++)
    //     {
    //        cube.mVertices.push_back(test[i*5+j]);
    //     }
    // }

    float cameraMat[N][N];

    bool quit = false;
    SDL_Event e;
    int ctr = 0;
    createTexture();
    argList argument;

    

    Mesh houseMesh;
    loadFromFile("untitled.obj", &houseMesh);
    Mesh temphouseMesh = houseMesh;

    std::cout << "Loaded\n";
    std::cout << temphouseMesh.mVertices.size() << "\n";

    while (!quit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //for quitting
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            //User presses a key
            else if (e.type == SDL_KEYDOWN)
            {

                if (e.key.keysym.sym == SDLK_g)
                {

                    std::cout << "cameraPos: " << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z << "\n";
                    std::cout << "cameraDirection: " << cameraDirection.x << " " << cameraDirection.y << " " << cameraDirection.z << "\n";
                    std::cout << "cameraRight: " << cameraRight.x << " " << cameraRight.y << " " << cameraRight.z << "\n";

                }
                switch (e.key.keysym.sym)
                {
                case SDLK_w:
                    cameraPos = addVec(cameraPos, scalarMulVec(cameraSpeed, cameraFront));
                    break;

                case SDLK_s:
                    cameraPos = subVec(cameraPos, scalarMulVec(cameraSpeed, cameraFront));

                case SDLK_a:
                    cameraPos = subVec(cameraPos, scalarMulVec(cameraSpeed, normalizeVec(crossProduct(cameraFront, cameraUp))));
                    break;

                case SDLK_d:
                    cameraPos = addVec(cameraPos, scalarMulVec(cameraSpeed, normalizeVec(crossProduct(cameraFront, cameraUp))));
                    break;


                }
            }
        }


        //Start

        //  for (int i = 0; i < 36; i++)
        //  {
        //      for (int j = 0; j < 3; j++)
        //      {
        //          //cube.mVertices.push_back(v1[i*5+j]);
        //          cube.mVertices[i * 3 + j] = v1[i * 5 + j];
        //      }
        //  }

        temphouseMesh = houseMesh;

        float start = SDL_GetTicks();

        for (int i = 0; i < SCREEN_HEIGHT; i++)
        {
            for (int j = 0; j < SCREEN_WIDTH; j++)
            {
                zbuffer[i][j] = 10000.f;
            }
        }
        //setup camera parameters
        cameraDirection = normalizeVec(addVec(cameraPos, cameraFront));
        cameraRight = normalizeVec(crossProduct(cameraUp, cameraDirection));
        memset(cameraMat, 0, sizeof(cameraMat));
        cameraMatrix(cameraMat);

        // for(int i = 0; i < 4; i++)
        // {
        //     for(int j = 0; j < 4; j++)
        //     {
        //         std::cout << cameraMat[i][j] << " ";
        //     }
        //     std::cout << "\n";
        // }

        // SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        // SDL_RenderClear(gRenderer);


        rotateMeshY(&temphouseMesh, -55.f);
        //std::cout << "First translation\n";
        translateMesh(&temphouseMesh, 0.f, 0.f);
        // normalizeMesh(&cube);
        cameraTranslation(&temphouseMesh, -cameraPos.x, -cameraPos.y, -cameraPos.z);
        normalizeMesh(&temphouseMesh);
        viewTransformMesh(&temphouseMesh, cameraMat);

        
        

        //std::cout << "Projection\n";

        projectMesh(&temphouseMesh, mat);
        float end = SDL_GetTicks();

        // std::cout << "Projected\n";

      

        //std::cout << end - start << std::endl;
        // quit = true;
        //SDL_Delay(5000);
        // ctr++;
        // if(ctr == 2)
        // quit = true;
    }
    // SDL_Delay(3000);
}




