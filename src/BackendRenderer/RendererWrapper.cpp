#include "RendererWrapper.hpp"

#include "FilePaths.hpp"
#include "TextureAtlas.hpp"

#include "SDL2/SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <iostream>

RendererWrapper::RendererWrapper()
{
    initializeSDL();
    initializeImgui();
};

RendererWrapper::~RendererWrapper()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyTexture(backgroundPicture);
    SDL_Quit();
}

void RendererWrapper::initializeSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        std::cerr << "Error: %s\n" << SDL_GetError();
        abort();
    }

#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    auto window_flags =
        (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    window = SDL_CreateWindow("Jellyfish Idle", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

    if (renderer == nullptr)
    {
        std::cerr << "Error while creating renderer\n";
        abort();
    }
}

void RendererWrapper::initializeImgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    (void)io;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
}

void RendererWrapper::startRenderingNewFrame() const
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void RendererWrapper::finalizeRenderingNewFrame()
{
    ImGui::Render();
    SDL_RenderSetScale(renderer, io->DisplayFramebufferScale.x,
                       io->DisplayFramebufferScale.y);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundPicture, nullptr, nullptr);

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

    SDL_RenderPresent(renderer);
}

bool RendererWrapper::processEvent(const SDL_Event &event)
{

    ImGui_ImplSDL2_ProcessEvent(&event);

    if (event.type == SDL_QUIT)
        return true;

    if (event.type == SDL_WINDOWEVENT &&
        event.window.event == SDL_WINDOWEVENT_CLOSE &&
        event.window.windowID == SDL_GetWindowID(window))
        return true;

    return false;
}

void RendererWrapper::setFont()
{
    io->Fonts->AddFontFromFileTTF(
        (std::string(FilePaths::getPath()) + std::string(FilePaths::FontPath))
            .c_str(),
        15);
}

void RendererWrapper::setBackgroundImage()
{
    SDL_Surface *surfaceIcon = SDL_LoadBMP("./assets/images/jellyfish64.bmp");
    assert(surfaceIcon != nullptr);

    SDL_SetWindowIcon(window, surfaceIcon);
    SDL_FreeSurface(surfaceIcon);

    SDL_Surface *surface = SDL_LoadBMP("./assets/images/otherjfish.bmp");
    assert(surface != nullptr);
    backgroundPicture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    assert(backgroundPicture != nullptr);
}

TextureAtlas RendererWrapper::loadTextures()
{
    SDL_Surface *surface = SDL_LoadBMP("./assets/images/loopButton.bmp");
    assert(surface != nullptr);
    auto texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    assert(texture != nullptr);
    TextureAtlas tAtlas;
    tAtlas.loopButton = texture;
    return tAtlas;
}
