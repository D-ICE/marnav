#ifndef __AIS__DECODE__HPP__
#define __AIS__DECODE__HPP__

#include "message.hpp"
#include <vector>

namespace marnav
{
namespace ais
{
std::unique_ptr<message> make_message(const std::vector<std::pair<std::string, int>> & v) throw(
	std::invalid_argument);

std::vector<std::pair<std::string, int>> encode_message(const message & msg) throw(
	std::invalid_argument);
}
}

#endif
