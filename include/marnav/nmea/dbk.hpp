#ifndef MARNAV_NMEA_DBK_HPP
#define MARNAV_NMEA_DBK_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief DBK - Depth Below Keel
///
/// @note This sentence appears to be deprecated, use @ref marnav::nmea::dpt "DPT" instead.
///
/// @code
///        1   2 3   4 5   6
///        |   | |   | |   |
/// $--DBK,x.x,f,x.x,M,x.x,F*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Depth feet
/// 2. Depth feet unit
///    - f = feet
/// 3. Depth meters
/// 4. Depth meters unit
///    - M = meters
/// 5. Depth Fathoms
/// 6. Depth Fathoms
///    - F = Fathoms
///
class dbk : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::DBK;
	constexpr static const char * TAG = "DBK";

	dbk();
	dbk(const dbk &) = default;
	dbk & operator=(const dbk &) = default;
	dbk(dbk &&) = default;
	dbk & operator=(dbk &&) = default;

protected:
	dbk(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<units::feet> depth_feet_;
	utils::optional<units::meters> depth_meter_;
	utils::optional<units::fathoms> depth_fathom_;

public:
	utils::optional<units::length> get_depth_feet() const;
	utils::optional<units::length> get_depth_meter() const;
	utils::optional<units::length> get_depth_fathom() const;

	void set_depth_feet(units::length t) noexcept;
	void set_depth_meter(units::length t) noexcept;
	void set_depth_fathom(units::length t) noexcept;
};
}
}

#endif
