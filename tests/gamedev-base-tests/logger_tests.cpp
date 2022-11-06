//
// Created by robin on 27.10.22.
//

#include "catch.hpp"
#include "fakeit.hpp"
#include "../../src/raylib-template-library/RaylibTemplateLibrary.h"

using namespace fakeit;
using namespace dev;

TEST_CASE( "Test Logger levels - Expect only logs that should be displayed", "[logger]" )
{
    Mock<ILogger> logger;
    Fake(Method(logger, log));
    ILogger &l = logger.get();

    SECTION("Trace")
    {
        l.setLevel(LogLevel::Trace);

        l.trace("trace");
        l.debug("debug");
        l.information("information");
        l.warning("warning");
        l.error("error");
        l.critical("critical");

        Verify(Method(logger, log)).Exactly(6);

        logger.ClearInvocationHistory();
    }

    SECTION("Debug")
    {
        l.setLevel(LogLevel::Debug);

        l.trace("trace");
        l.debug("debug");
        l.information("information");
        l.warning("warning");
        l.error("error");
        l.critical("critical");

        Verify(Method(logger, log)).Exactly(5);

        logger.ClearInvocationHistory();
    }

    SECTION("Information")
    {
        l.setLevel(LogLevel::Information);

        l.trace("trace");
        l.debug("debug");
        l.information("information");
        l.warning("warning");
        l.error("error");
        l.critical("critical");

        Verify(Method(logger, log)).Exactly(4);

        logger.ClearInvocationHistory();
    }

    SECTION("Warning")
    {
        l.setLevel(LogLevel::Warning);

        l.trace("trace");
        l.debug("debug");
        l.information("information");
        l.warning("warning");
        l.error("error");
        l.critical("critical");

        Verify(Method(logger, log)).Exactly(3);

        logger.ClearInvocationHistory();
    }

    SECTION("Error")
    {
        l.setLevel(LogLevel::Error);

        l.trace("trace");
        l.debug("debug");
        l.information("information");
        l.warning("warning");
        l.error("error");
        l.critical("critical");

        Verify(Method(logger, log)).Exactly(2);

        logger.ClearInvocationHistory();
    }

    SECTION("Critical")
    {
        l.setLevel(LogLevel::Critical);

        l.trace("trace");
        l.debug("debug");
        l.information("information");
        l.warning("warning");
        l.error("error");
        l.critical("critical");

        Verify(Method(logger, log)).Exactly(1);

        logger.ClearInvocationHistory();
    }

    SECTION("None")
    {
        l.setLevel(LogLevel::None);

        l.trace("trace");
        l.debug("debug");
        l.information("information");
        l.warning("warning");
        l.error("error");
        l.critical("critical");

        Verify(Method(logger, log)).Exactly(0);
    }
}