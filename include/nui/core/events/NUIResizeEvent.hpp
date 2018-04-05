#ifndef NUIRESIZEEVENT_HPP
#define NUIRESIZEEVENT_HPP

#include "NUIEvent.hpp"
#include <NUITypes.hpp>

namespace NUI {
    class NUIResizeEvent : public NUIEvent {
    public:
       NUIResizeEvent(NUIBoundingRect oldSize, NUIBoundingRect newSize) : NUIEvent(NUIEvent::Resize),
               m_oldSize(oldSize),
               m_newSize(newSize) {}

       NUIBoundingRect oldSize() { return m_oldSize; }
       NUIBoundingRect newSize() { return m_newSize; }

    private:
       NUIBoundingRect m_oldSize, m_newSize;
    };
}

#endif /* NUIRESIZEEVENT_HPP */

