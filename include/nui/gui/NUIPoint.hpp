#ifndef __NUIPOINT_HPP__
#define __NUIPOINT_HPP__

namespace NUI {
	class NUIPoint {
	public:
		NUIPoint(std::size_t x, std::size_t y) { m_x = x; m_y = y; }
		std::size_t x() { return m_x; }
		std::size_t y() { return m_y; }

	private:
		std::size_t m_x, m_y;
	};
}
#endif