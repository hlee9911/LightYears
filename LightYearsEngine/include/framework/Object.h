#pragma once

#include <memory>

#include "framework/Core.h"
#include "framework/Delegate.h"

namespace ly
{
	// allow us to spit out a weak_ptr of anything that's inheriting from Object
	class Object : public std::enable_shared_from_this<Object> // to create weak_ptr from this
	{
	public:
		Object() noexcept;
		virtual ~Object() noexcept;
		
		virtual void Destroy();
		bool IsPendingDestroy() const noexcept { return m_IsPendingDestroy; }

		weak<Object> GetWeakRef() noexcept;
		weak<const Object> GetWeakRef() const noexcept;

		unsigned int GetUniqueID() const noexcept { return m_UniqueID; }

	public:
		Delegate<Object*> onDestroyed;

	private:
		bool m_IsPendingDestroy;
		unsigned int m_UniqueID;

		static unsigned int s_UniqueIDCounter;
		static unsigned int GetNexAvailableID() noexcept;
	};
}
