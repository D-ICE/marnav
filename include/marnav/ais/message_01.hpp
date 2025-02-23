#ifndef MARNAV_AIS_MESSAGE_01_HPP
#define MARNAV_AIS_MESSAGE_01_HPP

#include <marnav/ais/message.hpp>
#include <marnav/ais/rate_of_turn.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/units/units.hpp>
#include <marnav/utils/mmsi.hpp>
#include <optional>

namespace marnav
{
namespace ais
{
/// @brief Position Report Class A
class message_01 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::position_report_class_a;
	constexpr static std::size_t SIZE_BITS = 168u;

	message_01();
	message_01(const message_01 &) = default;
	message_01 & operator=(const message_01 &) = default;
	message_01(message_01 &&) = default;
	message_01 & operator=(message_01 &&) = default;

protected:
	message_01(message_id id);
	message_01(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t             > repeat_indicator = 0;
	bitset_value<  8, 30, uint32_t             > mmsi = 0;
	bitset_value< 38,  4, navigation_status    > nav_status = navigation_status::not_defined;
	bitset_value< 42,  8, int8_t               > rot = rate_of_turn::no_information_available;
	bitset_value< 50, 10, uint32_t             > sog = sog_not_available;
	bitset_value< 60,  1, bool                 > position_accuracy = false;
	bitset_value< 61, 28, uint32_t             > longitude_minutes = longitude_not_available; // in 10000 minutes
	bitset_value< 89, 27, uint32_t             > latitude_minutes = latitude_not_available; // in 10000 minutes
	bitset_value<116, 12, uint32_t             > cog = cog_not_available;
	bitset_value<128,  9, uint32_t             > hdg = hdg_not_available;
	bitset_value<137,  6, uint32_t             > timestamp = timestamp_not_available;
	bitset_value<143,  2, maneuver_indicator_id> maneuver_indicator = maneuver_indicator_id::not_available;
	bitset_value<148,  1, bool                 > raim = false;
	bitset_value<149, 19, uint32_t             > radio_status = 0;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	navigation_status get_nav_status() const noexcept { return nav_status; }
	rate_of_turn get_rot() const noexcept;
	std::optional<units::knots> get_sog() const noexcept;
	bool get_position_accuracy() const noexcept { return position_accuracy; }
	std::optional<double> get_cog() const noexcept;
	std::optional<uint32_t> get_hdg() const noexcept;

	/// @todo Handle special values (61..63)
	uint32_t get_timestamp() const noexcept { return timestamp; }

	maneuver_indicator_id get_maneuver_indicator() const noexcept { return maneuver_indicator; }
	bool get_raim() const noexcept { return raim; }
	uint32_t get_radio_status() const noexcept { return radio_status; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_nav_status(navigation_status t) noexcept { nav_status = t; }
	void set_rot(rate_of_turn t) noexcept;

	void set_sog_unavailable();
	void set_sog(units::velocity t);

	void set_position_accuracy(bool t) noexcept { position_accuracy = t; }
	void set_cog(std::optional<double> t) noexcept;
	void set_hdg(std::optional<uint32_t> t) noexcept;
	void set_timestamp(uint32_t t) noexcept { timestamp = t; }
	void set_maneuver_indicator(maneuver_indicator_id t) noexcept { maneuver_indicator = t; }
	void set_raim(bool t) noexcept { raim = t; }
	void set_radio_status(uint32_t t) noexcept { radio_status = t; }

	std::optional<geo::longitude> get_lon() const;
	std::optional<geo::latitude> get_lat() const;
	void set_lon_unavailable();
	void set_lat_unavailable();
	void set_lon(const geo::longitude & t);
	void set_lat(const geo::latitude & t);
};
}
}

#endif
