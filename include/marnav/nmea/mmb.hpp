#ifndef MARNAV_NMEA_MMB_HPP
#define MARNAV_NMEA_MMB_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>
#include <marnav/units/units.hpp>

namespace marnav
{
namespace nmea
{
/// @brief MMB - Barometric Pressure
///
/// @code
///        1   2 3   4
///        |   | |   |
/// $--MMB,x.x,I,x.x,B*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Barometric pressure, inches of mecury
/// 2. Barometric pressure unit
///    - I = Inches of mercury
/// 3. Barometric pressure, bars
/// 4. Barometric pressure unit
///    - B = Bars
///
class mmb : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::MMB;
	constexpr static const char * TAG = "MMB";

	mmb();
	mmb(const mmb &) = default;
	mmb & operator=(const mmb &) = default;
	mmb(mmb &&) = default;
	mmb & operator=(mmb &&) = default;

protected:
	mmb(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> pressure_inches_of_mercury_;
	utils::optional<double> pressure_bars_;

public:
	utils::optional<double> get_pressure_inches_of_mercury() const { return pressure_inches_of_mercury_; }
	utils::optional<double> get_pressure_bars() const { return pressure_bars_; }

	void set_pressure_inches_of_mercury(double t) { pressure_inches_of_mercury_ = t; }
	void set_pressure_bars(double t) { pressure_bars_ = t; }
};
}
}

#endif
