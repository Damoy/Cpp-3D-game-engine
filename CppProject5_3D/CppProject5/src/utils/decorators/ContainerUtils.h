#pragma once

#include <map>

// Simple tools
namespace ContainerUtils {

	template<typename K, typename V>
	bool mapContains(const std::map<K, V>& map, const K& key) {
		return map.count(key) != 0;
	}
}