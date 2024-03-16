#include "Coroutine.h"

namespace cpproutine
{
	const uint64_t Coroutine::null = 0;
	std::unordered_map<UUID, Coroutine> CoroutineManager::Coroutines;
}