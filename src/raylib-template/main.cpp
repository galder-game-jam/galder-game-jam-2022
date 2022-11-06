#include <iostream>
#include "../raylib-template-library/RaylibTemplateLibrary.h"
#include "di.hpp"
#include "fmt/printf.h"
#include "fmt/color.h"
#include "raylib-cpp.hpp"

#include <filesystem>

//Returns the absolute path of the executable
std::filesystem::path abs_exe_path()
{
    #if defined(_MSC_VER)
    wchar_t path[FILENAME_MAX] = { 0 };
        GetModuleFileNameW(nullptr, path, FILENAME_MAX);
        return std::filesystem::path(path);
    #else
    char path[FILENAME_MAX];
    ssize_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
    return std::filesystem::path(std::string(path, (count > 0) ? count: 0));
    #endif
}

std::filesystem::path abs_exe_directory()
{
    #if defined(_MSC_VER)
    wchar_t path[FILENAME_MAX] = { 0 };
        GetModuleFileNameW(nullptr, path, FILENAME_MAX);
        return std::filesystem::path(path).parent_path().string();
    #else
    char path[FILENAME_MAX];
    ssize_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
    return std::filesystem::path(std::string(path, (count > 0) ? count: 0)).parent_path().string();
    #endif
}

auto buildInjector(dev::ILogger &logger, raylib::Window &window)
{
    auto injector = boost::di::make_injector(
            boost::di::bind<dev::IGameManager>().to<dev::GameManager>(),
            boost::di::bind<dev::IWorldManager>().to<dev::WorldManager>(),
            boost::di::bind<dev::ITextureManager<dev::TextureName, raylib::Texture>>().to<dev::TextureManager>(),
            boost::di::bind<dev::IMapper>().to<dev::Mapper>(),
            boost::di::bind<dev::IInputManager<dev::KeyboardKey>>().to<dev::InputManager>(),
            boost::di::bind<dev::IResourceManager<dev::ResourceName>>().to<dev::ResourceManager<dev::ResourceName>>(),
            boost::di::bind<dev::IExecutableInfo>().to<dev::ExecutableInfo>(),
            #ifdef GAME_DEV_DEBUG
            boost::di::bind<dev::IDebugManager>().to<dev::DebugManager>(),
            #else
            boost::di::bind<dev::IDebugManager>().to<dev::DummyDebugManager>(),
            #endif
            boost::di::bind<dev::CollisionManager>(),
            boost::di::bind<raylib::Window>().to(window),
            boost::di::bind<dev::ILogger>().to(logger)//.to(dev::ConsoleLogger(dev::LogLevel::Error))
    );

    return injector;
}

struct App
{
    dev::ILogger &logger;
    dev::IExecutableInfo &executableInfo;
    dev::IGameManager &game;
    dev::IResourceManager<dev::ResourceName> &resources;
    raylib::Window &window;

    bool initialize()
    {
        resources.initialize();

        if(!game.initialize())
            return false;

        return true;
    }
};

int main(int argc, char **argv)
{
    int screenWidth = 400;
    int screenHeight = 240;
    raylib::Window window {screenWidth, screenHeight, "Raylib Template"};
    dev::ConsoleLogger l = dev::ConsoleLogger(dev::LogLevel::Debug);

    //Handle dependency injection
    auto injector = buildInjector(l, window);
    App app = injector.create<App>();
    dev::ILogger &logger = app.logger;//game.getLogger();
    app.window.SetTitle("Hello there");

    //Initialize everything
    if(!app.initialize())
        app.logger.critical("App initialization failed!");

    logger.debug("This text is only visible in DEBUG builds");
    logger.debug(fmt::format("PATH!? {0} - {1}", app.executableInfo.getContentRootDirectory().c_str(), app.executableInfo.getExecutableDirectory().c_str()));
    logger.warning("I'm warning you!");
    logger.error("This is dangerous!");

    //raylib::Texture logo("raylib_logo.png");

    SetTargetFPS(60);
    dev::Timer timer;
    while (!window.ShouldClose())
    {
        float timeDelta = timer.secondsElapsed();
        app.game.update(timeDelta);
        timer.restart();
        app.game.draw();
    }

    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}
