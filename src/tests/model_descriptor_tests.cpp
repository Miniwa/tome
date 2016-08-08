#include <boost/test/unit_test.hpp>

#include "model_descriptor.hpp"
#include "field_descriptor.hpp"

BOOST_AUTO_TEST_SUITE(ModelDescriptor_Tests)

BOOST_AUTO_TEST_CASE(DefaultConstructorSetsProperValues)
{
    tome::ModelDescriptor descriptor("person");

    BOOST_REQUIRE(descriptor.get_name() == "person");
    BOOST_REQUIRE(descriptor.get_package() == "");
}

BOOST_AUTO_TEST_CASE(PackageConstructorSetsProperValues)
{
    tome::ModelDescriptor descriptor("person", "miniwa.data");

    BOOST_REQUIRE(descriptor.get_name() == "person");
    BOOST_REQUIRE(descriptor.get_package() == "miniwa.data");
}

BOOST_AUTO_TEST_CASE(GetFieldThrowsOnInvalidIndex)
{
    tome::ModelDescriptor descriptor("person");

    BOOST_CHECK_THROW(descriptor.get_field(10), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(AddAndGetFieldWorks)
{
    tome::ModelDescriptor descriptor("person");
    tome::FieldDescriptor field("salary", tome::FIELD_TYPE_INT32, true);

    descriptor.add_field(field);

    tome::FieldDescriptor* field_added = descriptor.get_field(0);

    BOOST_REQUIRE(field_added->get_name() == field.get_name());
    BOOST_REQUIRE(field_added->get_type() == field.get_type());
    BOOST_REQUIRE(field_added->is_required() == field.is_required());

}

BOOST_AUTO_TEST_CASE(GetFieldCountReturnsCorrectValues)
{
    tome::ModelDescriptor descriptor("person");

    BOOST_REQUIRE(descriptor.get_field_count() == 0);

    tome::FieldDescriptor field("salary", tome::FIELD_TYPE_INT32, true);
    descriptor.add_field(field);

    BOOST_REQUIRE(descriptor.get_field_count() == 1);
}

BOOST_AUTO_TEST_SUITE_END()
