#ifndef __NUI_COLOR_HPP__
#define __NUI_COLOR_HPP__

#define NUI_COLOR_BASE 20      // Baseoffset for color indexes

namespace NUI {
	typedef short NUIColor;
	typedef std::size_t NUIColorIndex;

	struct NUIColorPair {
		NUIColorIndex index;
		NUIColor fg;
		NUIColor bg;
	
		static NUIColorPair getColorPair(NUIColorIndex index) {
			NUIColor fg, bg;
			pair_content(NUI_COLOR_BASE + index, &fg, &bg);
			return NUIColorPair{NUI_COLOR_BASE + index, fg, bg};
		}

		void setFg(NUIColor color) {
			fg = color;
			init_pair(index, color, bg);
		}

		void setBg(NUIColor color) {
			bg = color;
			init_pair(index, fg, color);
		}

		static void setColorPair(NUIColorPair color) {
			init_pair(NUI_COLOR_BASE + color.index, color.fg, color.bg);
		}
	};
}

#endif