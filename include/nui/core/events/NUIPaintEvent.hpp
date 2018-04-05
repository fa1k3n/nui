#ifndef NUIPAINTEVENT_HPP
#define NUIPAINTEVENT_HPP

#include "NUIEvent.hpp"
#include <NUITypes.hpp>

namespace NUI {
    class NUIPaintEvent : public NUIEvent {
     public:
             NUIPaintEvent(NUIBoundingRect rect) : NUIEvent(NUIEvent::Paint) {
                     m_rect = rect;
             }

             NUIBoundingRect rect() { return m_rect; }
     private:
             NUIBoundingRect m_rect;
     };
}

#endif /* NUIPAINTEVENT_HPP */

