#pragma once

namespace Axel {
	class Timestep {
	public:
		Timestep(float t_time = 0.0f)
			: m_time(t_time)
		{
		}

		operator float() const { return m_time; }

		float getSeconds() const { return m_time; }
		float getMiliseconds() const { return m_time * 1000.0f; }
	private:
		float m_time;
	};
}