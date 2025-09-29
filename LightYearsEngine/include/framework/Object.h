#pragma once
#ifndef OBJECT_H
#define OBJECT_H

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

	public:
		Delegate<Object*> onDestroyed;

	private:
		bool m_IsPendingDestroy;
	};
}

#endif // OBJECT_H
