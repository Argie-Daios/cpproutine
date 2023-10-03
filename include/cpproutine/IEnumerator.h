#pragma once

#include <coroutine>
#include <memory>

#include "YieldRetrunType.h"

// Asynchronous return keyword for IEnumerator
#define yield_return co_yield

namespace cpproutine
{
	/// <summary>
	/// The type for coroutine function specification (All the coroutines that you create must return that type)
	/// </summary>
	class IEnumerator
	{
	public:
		struct promise_type
		{
			using coro_handle = std::coroutine_handle<promise_type>;

			auto get_return_object()
			{
				return coro_handle::from_promise(*this);
			}

			auto initial_suspend() { return std::suspend_always(); }
			auto final_suspend() noexcept { return std::suspend_always(); }
			void return_void() {}
			void unhandled_exception() { std::terminate(); }

			auto yield_value(std::shared_ptr<YieldReturnType> value)
			{
				this->value_ = value;
				return std::suspend_always();
			}

			std::shared_ptr<YieldReturnType> value_;
		};
		using coro_handle = std::coroutine_handle<promise_type>;

		IEnumerator() = default;
		IEnumerator(coro_handle handle) : handle_(handle) { assert(handle_); }

		bool resume()
		{
			handle_.resume();
			return not handle_.done();
		}

		std::shared_ptr<YieldReturnType> GetValue()
		{
			return handle_.promise().value_;
		}
	private:
		coro_handle handle_;
	};
}