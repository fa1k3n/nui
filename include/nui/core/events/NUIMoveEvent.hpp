#ifndef NUIMOVEEVENT_HPP
#define NUIMOVEEVENT_HPP

#include "NUIEvent.hpp"
#include <NUITypes.hpp>

namespace NUI {
    class NUIMoveEvent : public NUIEvent {
    public:
        NUIMoveEvent(NUIPoint oldPos, NUIPoint newPos) : NUIEvent(NUIEvent::Move) ,
                m_oldPos(oldPos),
                m_newPos(newPos) {}

        NUIPoint newPos() { return m_newPos; }
        NUIPoint oldPos() { return m_oldPos; }

    private:
        NUIPoint m_oldPos, m_newPos;
    };
}

#endif /* NUIMOVEEVENT_HPP */

