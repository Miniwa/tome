#include <boost/test/unit_test.hpp>

#include "field_type.hpp"
#include "field_descriptor.hpp"

BOOST_AUTO_TEST_SUITE(FieldDescriptor_Tests)

BOOST_AUTO_TEST_CASE(TestConstructorSetsProperValues)
{
    tome::FieldDescriptor descriptor("money", tome::FIELD_TYPE_INT32, true);

    BOOST_REQUIRE(descriptor.get_name() == "money");
    BOOST_REQUIRE(descriptor.get_type() == tome::FIELD_TYPE_INT32);
    BOOST_REQUIRE(descriptor.is_required() == true);
}

BOOST_AUTO_TEST_SUITE_END()
