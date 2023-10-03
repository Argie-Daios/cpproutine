#pragma once

#include <xhash>

namespace cpproutine
{
	/// <summary>
	/// Universaly Unique Idendifier
	/// </summary>
	class UUID
	{
	public:
		/// <summary>
		/// Generate UUID
		/// </summary>
		UUID();
		/// <summary>
		/// Set UUID
		/// </summary>
		/// <param name="uuid">Given UUID</param>
		UUID(uint64_t uuid);
		UUID(const UUID&) = default;

		operator uint64_t() const { return m_UUID; }
	private:
		uint64_t m_UUID;
	};
}

namespace std {

	template<>
	struct hash<cpproutine::UUID>
	{
		std::size_t operator()(const cpproutine::UUID& uuid) const
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}