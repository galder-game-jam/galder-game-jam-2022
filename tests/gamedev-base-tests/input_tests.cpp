//
// Created by robin on 28.10.22.
//

#include "catch.hpp"
#include "fakeit.hpp"
#include "../../src/raylib-template-library/RaylibTemplateLibrary.h"

using namespace fakeit;
using namespace ggj;

TEST_CASE( "Test input manager by faking keyPressed - Expect 'A'-key returned as pressed, and 'B' as not pressed", "[input]" )
{
    Mock<IInputManager<ggj::KeyboardKey>> fakeInput;
    Fake(Method(fakeInput, keyPressed));
    When(Method(fakeInput, keyPressed).Using(ggj::KeyboardKey::A)).Return(true);
    IInputManager<ggj::KeyboardKey> &input = fakeInput.get();

    REQUIRE(input.keyPressed(ggj::KeyboardKey::A));
    REQUIRE(!input.keyPressed(ggj::KeyboardKey::B));
}

TEST_CASE( "Test lambda called when input has been queried - Expect variable changed after call", "[input]" )
{
    std::string str;

    Mock<IInputManager<ggj::KeyboardKey>> fakeInput;
    Fake(Method(fakeInput, keyPressed));
    When(Method(fakeInput, keyPressed).Using(ggj::KeyboardKey::A)).AlwaysDo([&](ggj::KeyboardKey key)
    {
        str = "'A' was pressed!";
        return true;
    });
    IInputManager<ggj::KeyboardKey> &input = fakeInput.get();

    REQUIRE(str.empty());
    REQUIRE(input.keyPressed(ggj::KeyboardKey::A));
    REQUIRE(str == "'A' was pressed!");
}