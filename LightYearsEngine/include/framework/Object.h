#pragma once
#ifndef OBJECT_H
#define OBJECT_H

namespace ly
{
	class Object 
	{
	public:
		Object() noexcept;
		virtual ~Object() noexcept;
		
		void Destroy();
		bool IsPendingDestroy() const noexcept { return m_IsPendingDestroy; }

	private:
		bool m_IsPendingDestroy;
	};
}

#endif // OBJECT_H
