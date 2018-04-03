#ifndef NUITYPES_HPP
#define NUITYPES_HPP

#include <string>

#define NUI_COLOR_BASE 20      // Baseoffset for color indexes

namespace NUI {
    typedef std::size_t    NUIReal;
    typedef std::string   NUIString;
    typedef char            NUIChar;
    typedef bool            NUIBool;
    typedef short           NUIColor;
    typedef std::size_t    NUIColorIndex;

    class NUIPoint {
    public:
           NUIPoint(std::size_t x, std::size_t y) { m_x = x; m_y = y; }
           std::size_t x() { return m_x; }
           std::size_t y() { return m_y; }

    private:
           std::size_t m_x, m_y;
    };

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
       
               struct NUIBoundingRect {
                NUIReal x, y, width, height;
        };
}

#endif /* NUITYPES_HPP */

