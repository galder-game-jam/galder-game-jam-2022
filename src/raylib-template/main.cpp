#include "../raylib-template-library/RaylibTemplateLibrary.h"
#include "di.hpp"
#include "fmt/color.h"
#include "raylib-cpp.hpp"


auto buildInjector(ggj::ILogger &logger, raylib::Window &window)
{
    auto injector = boost::di::make_injector(
            boost::di::bind<ggj::IGameManager>().to<ggj::GameManager>(),
            boost::di::bind<ggj::IWorldManager>().to<ggj::WorldManager>(),
            boost::di::bind<ggj::ITextureManager<ggj::TextureName, raylib::Texture>>().to<ggj::TextureManager>(),
            boost::di::bind<ggj::IMapper>().to<ggj::Mapper>(),
            boost::di::bind<ggj::IInputManager<ggj::KeyboardKey>>().to<ggj::InputManager>(),
            boost::di::bind<ggj::IResourceManager<ggj::ResourceName>>().to<ggj::ResourceManager<ggj::ResourceName>>(),
            boost::di::bind<ggj::IAnimationManager<ggj::Animation, ggj::AnimationName>>().to<ggj::AnimationManager>(),
            boost::di::bind<ggj::IExecutableInfo>().to<ggj::ExecutableInfo>(),
            #ifdef GAME_DEV_DEBUG
            boost::di::bind<ggj::IDebugManager>().to<ggj::DebugManager>(),
            #else
            boost::di::bind<ggj::IDebugManager>().to<ggj::DummyDebugManager>(),
            #endif
            boost::di::bind<ggj::CollisionManager>(),
            boost::di::bind<raylib::Window>().to(window),
            boost::di::bind<ggj::ILogger>().to(logger)//.to(ggj::ConsoleLogger(ggj::LogLevel::Error))
    );

    return injector;
}

struct App
{
    ggj::ILogger &logger;
    ggj::IExecutableInfo &executableInfo;
    ggj::IGameManager &game;
    ggj::IResourceManager<ggj::ResourceName> &resources;
    ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &animations;
    raylib::Window &window;

    bool initialize()
    {
        resources.initialize();
        animations.initialize();

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
    ggj::ConsoleLogger l = ggj::ConsoleLogger(ggj::LogLevel::Debug);

    //Handle dependency injection
    auto injector = buildInjector(l, window);
    App app = injector.create<App>();
    ggj::ILogger &logger = app.logger;//game.getLogger();
    app.window.SetTitle("Galderino's Gamo Jammo");

    //Initialize everything
    if(!app.initialize())
        app.logger.critical("App initialization failed!");

    logger.debug("This text is only visible in DEBUG builds");
    logger.debug(fmt::format("PATH!? {0} - {1}", app.executableInfo.getContentRootDirectory().c_str(), app.executableInfo.getExecutableDirectory().c_str()));
    logger.warning("I'm warning you!");
    logger.error("This is dangerous!");

    //raylib::Texture logo("raylib_logo.png");

    SetTargetFPS(60);
    ggj::Timer timer;
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
