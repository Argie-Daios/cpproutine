#pragma once

#include <chrono>
#include <functional>

namespace cpproutine
{
	/// <summary>
	/// Pure Virtual Class (Do not use this on your coroutines)
	/// </summary>
	class YieldReturnType
	{
	public:
		YieldReturnType() {};

		/// <summary>
		/// Check whenever the current condition is done
		/// </summary>
		/// <returns>True : The condition is done  False : The condition is on proccess</returns>
		virtual bool IsDone() = 0;

		/// <summary>
		/// Check whenever the condition was done and stopped (This is used independent of IsDone())
		/// </summary>
		/// <returns>True : The condition was done  False : The condition is on proccess</returns>
		virtual bool IsStopped() = 0;
	};

	/// <summary>
	/// YieldReturnType Derrived Class (Use this to construct a condition that stops the coroutine for the given time[seconds])
	/// </summary>
	class WaitForSeconds : public YieldReturnType
	{
	public:
		/// <summary>
		/// Construct timer
		/// </summary>
		/// <param name="time">Timer value (on Seconds)</param>
		WaitForSeconds(float time)
		{
			m_Time = time * 1000.0f;
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		WaitForSeconds(const WaitForSeconds&) = default;

		virtual bool IsDone() override
		{
			if (m_Time == 0.0f)
				return false;

			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimepoint).time_since_epoch().count();

			if (end - start >= m_Time)
			{
				m_Time = 0.0f;
				m_Stopped = true;
				return true;
			}

			return false;
		}

		virtual bool IsStopped() { return m_Stopped; }
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
		float m_Time;
		bool m_Stopped = false;
	};

	/// <summary>
	/// YieldReturnType Derrived Class (Use this to construct a condition that stops the coroutine until the condition is met)
	/// </summary>
	class WaitUntil : public YieldReturnType
	{
	public:
		/// <summary>
		/// Construct condition
		/// </summary>
		/// <param name="condition">Condition value (lambda function of type bool, example : [this]() -> bool { return *value*;}</param>
		WaitUntil(std::function<bool()> condition) { m_Condition = condition; }

		WaitUntil(const WaitUntil&) = default;

		virtual bool IsDone() override
		{
			if (m_Condition())
			{
				m_Stopped = true;
				return true;
			}

			return false;
		}

		virtual bool IsStopped() override { return m_Stopped; }
	private:
		std::function<bool()> m_Condition;
		bool m_Stopped = false;
	};

	/// <summary>
	/// Constructs a new condition (std::make_shared wrapper)
	/// </summary>
	/// <returns>A new return type</returns>
	template<typename T, typename ... Args>
	constexpr std::shared_ptr<T> NewReturnType(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
