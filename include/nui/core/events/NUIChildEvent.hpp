#ifndef NUICHILDEVENT_HPP
#define NUICHILDEVENT_HPP

#include "NUIEvent.hpp"
#include <NUITypes.hpp>

namespace NUI {
    class NUIObject;
    class NUIChildEvent : public NUIEvent {
    public:
        NUIChildEvent(NUIObject* child) : NUIEvent(NUIEvent::Child) ,
                m_child(child) {}
        NUIObject* child() { return m_child; }
    private:
        NUIObject* m_child;
    };
}

#endif /* NUICHILDEVENT_HPP */

