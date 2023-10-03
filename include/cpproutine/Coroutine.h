#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>
#include <cassert>

#include "UUID.h"
#include "IEnumerator.h"

namespace cpproutine
{
	class CoroutineManager;

	/// <summary>
	/// Coroutine construct
	/// </summary>
	struct Coroutine
	{
		Coroutine() = default;

		Coroutine(UUID id, IEnumerator function)
			: Function(function)
		{
			Id = id;
		}

		Coroutine(const Coroutine& coroutine)
		{
			Id = coroutine.Id;
			Function = coroutine.Function;
		}

		/// <summary>
		/// Get the UUID of the coroutine
		/// </summary>
		/// <returns>The UUID</returns>
		UUID GetUUID() { return Id; }

		bool operator==(const Coroutine& coroutine)
		{
			return Id == coroutine.Id;
		}
	private:
		UUID Id;
		IEnumerator Function;

		friend CoroutineManager;
	};

	/// <summary>
	/// A static class that manages the coroutines that you pass for execution
	/// </summary>
	class CoroutineManager
	{
	public:
		/// <summary>
		/// Constructs a coroutine from the given IEnumerator function and sumbits it for execution
		/// </summary>
		/// <param name="function">IEnumerator function</param>
		/// <returns>Coroutine construct of the IEnumerator function</returns>
		static Coroutine StartCoroutine(IEnumerator function)
		{
			UUID uuid;
			Coroutines.emplace(uuid, Coroutine(uuid, function));
			auto pair = Coroutines.find(uuid);
			pair->second.Function.resume();

			return pair->second;
		}

		/// <summary>
		/// Stops the given coroutine from execution
		/// </summary>
		/// <param name="coroutine">The coroutine construct</param>
		static void StopCoroutine(Coroutine coroutine)
		{
			auto it = Coroutines.find(coroutine.Id);
			if (it != Coroutines.end())
			{
				Coroutines.erase(it);
			}
		}

		/// <summary>
		/// The function that executes every sumbited coroutine (Use this on your game loop, without this coroutines don't work)
		/// </summary>
		static void Update()
		{
			for (auto& pair : Coroutines)
			{
				auto& Function = pair.second.Function;
				std::shared_ptr<YieldReturnType> Timer = pair.second.Function.GetValue();
				if (Timer->IsDone())
				{
					Function.resume();
				}
			}

			for (auto it = Coroutines.begin(); it != Coroutines.end();)
			{
				auto Timer = it->second.Function.GetValue();
				if (Timer->IsStopped())
				{
					std::cout << "In" << std::endl;
					it = Coroutines.erase(it);
				}
				else
				{
					++it;
				}
			}
		}

		static std::unordered_map<UUID, Coroutine> Coroutines;
	};
}