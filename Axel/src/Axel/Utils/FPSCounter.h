#pragma once

#include "Axel/Log.h"
#include "Axel/Core.h"
#include <vector>

namespace Axel {
	class FPSCounter {
	public:
		static void init(const int& avaregeOverLastNumbers) {
			for (int i = 0; i < avaregeOverLastNumbers; i++)
			{
				m_fpsValues.push_back(0);
			}
			m_it = m_fpsValues.begin();
		}

		static void addNewFPSValue(const float& value) {
			AX_CORE_ASSERT(!m_fpsValues.empty(), "FPS values cant be empty! Is it initialized?");
			*m_it = value;
			++m_it;

			if (m_it == FPSCounter::m_fpsValues.end())
			{
				m_it = m_fpsValues.begin();
			}
		}

		static float getFPS() {
			float sum = 0;
			for (auto& value : m_fpsValues) {
				sum += value;
			}
			return (sum / m_fpsValues.size());
		}
	private:
		static std::vector<float> m_fpsValues;
		static std::vector<float>::iterator m_it;
	private:
		FPSCounter() = default;
	};

	std::vector<float> FPSCounter::m_fpsValues;
	std::vector<float>::iterator FPSCounter::m_it;
}