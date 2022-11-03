#include <marnav/nmea/mmb.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
constexpr sentence_id mmb::ID;
constexpr const char * mmb::TAG;

mmb::mmb()
	: sentence(ID, TAG, talker::weather_instruments)
{
}

mmb::mmb(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) < 4)
		throw std::invalid_argument{"invalid number of fields in mmb"};

	utils::optional<char> unit;

	read(*(first + 0), pressure_inches_of_mercury_);
	read(*(first + 1), unit);
	if (unit.has_value() && unit.value() != 'I')
		throw std::invalid_argument{"First unit in mmb frame is not 'I'"};

	read(*(first + 2), pressure_bars_);
	read(*(first + 3), unit);
	if (unit.has_value() && unit.value() != 'B')
		throw std::invalid_argument{"Second unit in mmb frame is not 'B'"};
}

void mmb::append_data_to(std::string & s) const
{
	append(s, format(pressure_inches_of_mercury_, 1));
	append(s, 'I');
	append(s, format(pressure_bars_, 1));
	append(s, 'B');
}
}
}
