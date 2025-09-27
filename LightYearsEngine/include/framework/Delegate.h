#pragma once
#ifndef DELEGATE_H
#define DELEGATE_H

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
	template<typename... Args>
	class Delegate
	{
	public:
		template<typename ClassName>
		void BindAction(weak<Object> obj, void(ClassName::*callback)(Args...)) // second argument means a pointer to a member function of ClassName that takes Args... as parameters and returns the void
		{

		}

	private:

	};
}

#endif // DELEGATE_H
