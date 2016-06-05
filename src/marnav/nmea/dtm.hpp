#ifndef __NMEA__DTM__HPP__
#define __NMEA__DTM__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(dtm)

/// @brief DTM - Datum Reference
///
/// @code
///          1  2  3   4  5   6  7  8    9
///          |  |  |   |  |   |  |  |    |
/// $ --DTM,ref,x,llll,c,llll,c,aaa,ref*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Local datum code.
///    - W84 = WGS84
/// 2. Local datum subcode. May be blank.
/// 3. Latitude offset (minutes)
/// 4. Latitude hemisphere
///    - N = North
///    - S = South
/// 5. Longitude offset (minutes)
/// 6. Longitude hemisphere
///    - E = East
///    - W = West
/// 7. Altitude offset in meters
/// 8. Datum name. What’s usually seen here is "W84", the standard WGS84 datum used by GPS.
///    - W84 = WGS84
///
/// @note Datum code, subcode and datum name are truncated to 5 characters.
///
class dtm : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(dtm)

public:
	constexpr static const sentence_id ID = sentence_id::DTM;
	constexpr static const char * TAG = "DTM";

	dtm();
	dtm(const dtm &) = default;
	dtm & operator=(const dtm &) = default;

protected:
	dtm(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	std::string ref = "W84";
	utils::optional<std::string> subcode;
	double lat_offset = 0.0;
	direction lat_hem = direction::north;
	double lon_offset = 0.0;
	direction lon_hem = direction::east;
	double altitude = 0.0;
	std::string name = "W84";

public:
	NMEA_GETTER(ref)
	NMEA_GETTER(subcode)
	NMEA_GETTER(lat_offset)
	NMEA_GETTER(lat_hem)
	NMEA_GETTER(lon_offset)
	NMEA_GETTER(lon_hem)
	NMEA_GETTER(altitude)
	NMEA_GETTER(name)

	void set_ref(const std::string & t) noexcept;
	void set_subcode(const std::string & t) noexcept;
	void set_lat_offset(double t, direction h);
	void set_lon_offset(double t, direction h);
	void set_altitude(double t) { altitude = t; }
	void set_name(const std::string & t) noexcept;
};
}
}

#endif
