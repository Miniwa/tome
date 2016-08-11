#include <boost/test/unit_test.hpp>

#include "template_error.hpp"
#include "simple_template_engine.hpp"

struct SimpleTemplateEngineFixture
{
    SimpleTemplateEngineFixture()
    {
        engine = tome::SimpleTemplateEngine();
        context = std::map<std::string, std::string>();
        errors = std::vector<std::string>();
        context["test"] = "hello";
        context["atomic"] = "test";
        context["atomic2"] = "atomic";
        context["atomic3"] = "atomic2";
        context["deadlock"] = "$deadlock";
    }

    tome::SimpleTemplateEngine engine;
    std::map<std::string, std::string> context;
    std::vector<std::string> errors;
};

BOOST_FIXTURE_TEST_SUITE(SimpleTemplateEngine_Tests, SimpleTemplateEngineFixture)

BOOST_AUTO_TEST_CASE(DefaultConstructorSetsProperValues)
{
    BOOST_REQUIRE(engine.is_recursive() == false);
    BOOST_REQUIRE(engine.has_context() == false);
}

BOOST_AUTO_TEST_CASE(CheckHasContextFunctionsCorrectly)
{
    BOOST_REQUIRE(engine.has_context() == false);
    engine.set_context(context);
    BOOST_REQUIRE(engine.has_context() == true);
}

BOOST_AUTO_TEST_CASE(CheckRenderThrowsWhenInvokedWithoutContext)
{
    BOOST_CHECK_THROW(engine.render("test"), tome::TemplateError);
}

BOOST_AUTO_TEST_CASE(CheckErrorsAreProperlyReported)
{
    std::string in("$invalid and");
    engine.set_context(context);

    std::string result = engine.render(in, &errors);

    BOOST_REQUIRE(result == "$invalid and");
    BOOST_REQUIRE(errors.size() == 1);
}

BOOST_AUTO_TEST_CASE(CheckRenderThrowsOnError)
{
    std::string in("$invalid");
    engine.set_context(context);

    BOOST_CHECK_THROW(engine.render(in), tome::TemplateError);
}

BOOST_AUTO_TEST_CASE(CheckRenderDoesNotThrowWithoutError)
{
    std::string in("$test");
    engine.set_context(context);

    std::string result = engine.render(in);

    BOOST_REQUIRE(result == "hello");
}

BOOST_AUTO_TEST_CASE(CheckOutputIsCorrect)
{
    std::string in("$test");
    engine.set_context(context);

    std::string result = engine.render(in, &errors);

    BOOST_REQUIRE(result == "hello");
    BOOST_REQUIRE(errors.size() == 0);
}

BOOST_AUTO_TEST_CASE(CheckMultipleOutputIsCorrect)
{
    std::string in("$test and $test");
    engine.set_context(context);

    std::string result = engine.render(in, &errors);

    BOOST_REQUIRE(result == "hello and hello");
    BOOST_REQUIRE(errors.size() == 0);
}

BOOST_AUTO_TEST_CASE(CheckRenderOperationIsAtomic)
{
    std::string in("$$atomic$test");
    engine.set_context(context);

    std::string result = engine.render(in, &errors);

    BOOST_REQUIRE(result == "$testhello");
}

BOOST_AUTO_TEST_CASE(CheckSingle$DoesNotMatchOrReportError)
{
    std::string in("$ and hello");
    engine.set_context(context);

    std::string result = engine.render(in, &errors);

    BOOST_REQUIRE(result == in);
    BOOST_REQUIRE(errors.size() == 0);
}

BOOST_AUTO_TEST_CASE(CheckRecursiveFlagWorksWithTwoSteps)
{
    std::string in("$$atomic and $test");
    engine.set_context(context);
    engine.set_recursive(true);

    std::string result = engine.render(in, &errors);

    BOOST_REQUIRE(result == "hello and hello");
    BOOST_REQUIRE(errors.size() == 0);
}

BOOST_AUTO_TEST_CASE(CheckRecursiveFlagWorksWithFourSteps)
{
    std::string in("$$$$atomic3 and $test");
    engine.set_context(context);
    engine.set_recursive(true);

    std::string result = engine.render(in, &errors);

    BOOST_REQUIRE(result == "hello and hello");
    BOOST_REQUIRE(errors.size() == 0);
}

BOOST_AUTO_TEST_CASE(CheckRecursiveDeadlockDetectionWorks)
{
    std::string in("$deadlock");
    engine.set_context(context);
    engine.set_recursive(true);

    BOOST_CHECK_THROW(engine.render(in, &errors), tome::TemplateError);
}


BOOST_AUTO_TEST_SUITE_END()
