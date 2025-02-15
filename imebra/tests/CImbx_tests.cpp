// imebra_tests.cpp : Defines the entry point for the console application.
//
#include <gtest/gtest.h>

#include "testsSettings.h"
#include <imebra/imebra.h>

#if defined(IMEBRA_LOGGING_LOG4CXX)
#include <log4cxx/logger.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/patternlayout.h>
#endif

int main(int argc, char **argv)
{
    tests::settings& settings = tests::settings::getSettings();

    for(int scanArguments(0); scanArguments != argc; ++scanArguments)
    {
        std::string argument = argv[scanArguments];
        settings.set(argument);
    }

    ::testing::InitGoogleTest(&argc, argv);

#if defined(IMEBRA_LOGGING_LOG4CXX)
    if(!settings.get("--testLogFile").empty())
    {
        ::log4cxx::LayoutPtr testLayout = new ::log4cxx::PatternLayout("%r [%t] %-5p %c - %m%n");
        ::log4cxx::AppenderPtr testAppender = new ::log4cxx::FileAppender(testLayout, settings.get("--testLogFile"), false);
        ::log4cxx::Logger::getRootLogger()->addAppender(testAppender);
        ::log4cxx::Logger::getRootLogger()->setLevel(::log4cxx::Level::getInfo());
    }
#endif

    return RUN_ALL_TESTS();
}


