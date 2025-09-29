#pragma once
#ifndef DELEGATE_H
#define DELEGATE_H

#include <functional>

#include "framework/Core.h"
// #include "framework/Object.h"

namespace ly
{
	class Object;

	template<typename... Args>
	class Delegate
	{
	public:
		/// <summary>
		/// given an object and a member function pointer, bind the function to the delegate
		/// </summary>
		/// <typeparam name="ClassName"></typeparam>
		/// <param name="obj"></param>
		/// <param name="callback"></param>
		template<typename ClassName>
		void BindAction(weak<Object> obj, void(ClassName::*callback)(Args...)) // second argument means a pointer to a member function of ClassName that takes Args... as parameters and returns the void
		{
			// create a lambda that captures the object and the member function pointer (they are all pointers)
			std::function<bool(Args...)> callbackFunc = [obj, callback](Args... args)->bool // return type of this lambda is bool
			{
				if (!obj.expired())
				{
					// we cast the pointer from object pointer because thats what that pointer actually is
					(static_cast<ClassName*>(obj.lock().get())->*callback)(args...);
					return true; // indicate that the call was successful
				}
				return false; // indicate that the call failed because the object is no longer valid
			};

			m_Callbacks.push_back(callbackFunc);
		}

		/// <summary>
		/// go through all the callbacks and call them with the provided arguments
		/// broadcasting to everyone who is trying to listen by calling their bound functions
		/// One of the downside of this approach is that it only gets cleaned up when you broadcast
		/// so if you have a lot of dead callbacks and never broadcast, they will stay in the list forever
		/// </summary>
		/// <param name="...args"></param>
		void Broadcast(Args... args)
		{
			// iterate through all the callbacks and call them with the provided arguments
			for (auto& iter = m_Callbacks.begin(); iter != m_Callbacks.end();)
			{
				// if the callback returns true, it means the object is still valid and we can move to the next callback
				if ((*iter)(args...))
				{
					iter++;
				}
				else
				{
					iter = m_Callbacks.erase(iter); // remove the callback if the object is no longer valid
				}
			}
		}

	private:
		List<std::function<bool(Args...)>> m_Callbacks;
	};
}

#endif // DELEGATE_H
