#include <marnav/nmea/mmb.hpp>
#include "type_traits_helper.hpp"
#include <marnav/nmea/nmea.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class Test_nmea_mmb : public ::testing::Test
{
};

TEST_F(Test_nmea_mmb, contruction)
{
	EXPECT_NO_THROW(nmea::mmb mmb);
}

TEST_F(Test_nmea_mmb, properties)
{
	nmea_sentence_traits<nmea::mmb>();
}

TEST_F(Test_nmea_mmb, parse)
{
	auto s = nmea::make_sentence("$WIMMB,29.92,I,1.013,B*54");
	ASSERT_NE(nullptr, s);

	auto mmb = nmea::sentence_cast<nmea::mmb>(s);
	ASSERT_NE(nullptr, mmb);

	auto pressure = mmb->get_pressure_bars();
	EXPECT_NEAR(1.013, pressure.value(), 1e-8);
}

TEST_F(Test_nmea_mmb, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::mmb>(nmea::talker::none, {1, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::mmb>(nmea::talker::none, {3, "@"}));
}

TEST_F(Test_nmea_mmb, empty_to_string)
{
	nmea::mmb mmb;

	EXPECT_STREQ("$WIMMB,,I,,B*57", nmea::to_string(mmb).c_str());
}
}
