#include <boost/test/unit_test.hpp>

#include "template_engine.hpp"
#include "generator.hpp"

struct MockGenerator : public tome::IGenerator
{
    MockGenerator() : IGenerator()
    {

    }

    MockGenerator(const tome::IGenerator::engine_ptr& engine) : IGenerator(engine)
    {

    }

    //Overrides.
    virtual ~MockGenerator()
    {

    }

    virtual std::vector<tome::IGenerator::file> generate(const tome::ModelDescriptor& descriptor)
    {
        //Supress unusued parameter warning.
        (void)descriptor;
        return std::vector<tome::IGenerator::file>();
    }
};

struct MockTemplateEngine : public tome::ITemplateEngine
{
    virtual std::string render(const std::string& tmpl)
    {
        (void)tmpl;
        return "";
    }

    virtual std::string render(const std::string& tmpl, std::vector<std::string>* p_errors)
    {
        (void)tmpl;
        (void)p_errors;
        return "";
    }

    virtual bool has_context()
    {
        return true;
    }
};



BOOST_AUTO_TEST_SUITE(Generator_Tests)

BOOST_AUTO_TEST_CASE(TestHasEngineReturnsCorrectValues)
{
    MockGenerator gen;
    tome::IGenerator::engine_ptr engine = boost::make_shared<MockTemplateEngine>();

    BOOST_REQUIRE(gen.has_engine() == false);

    tome::IGenerator::engine_ptr ptr = gen.get_engine();
    BOOST_REQUIRE(ptr == NULL);

    gen.set_engine(engine);

    BOOST_REQUIRE(gen.has_engine() == true);

    ptr = gen.get_engine();
    BOOST_REQUIRE(ptr != NULL);
}

BOOST_AUTO_TEST_SUITE_END()
