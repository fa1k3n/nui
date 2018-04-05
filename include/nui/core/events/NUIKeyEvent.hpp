#ifndef NUIKEYEVENT_HPP
#define NUIKEYEVENT_HPP

#include "NUIEvent.hpp"
#include <NUITypes.hpp>

namespace NUI {
    class NUIKeyEvent : public NUIEvent {
    public:
        NUIKeyEvent(NUIReal keyCode, NUIChar key) : NUIEvent(NUIEvent::KeyPress) ,
                m_keyCode(keyCode),
                m_key(key) {}
        NUIReal keyCode() { return m_keyCode; }
        NUIChar key() { return m_key; }
    private:
        NUIReal m_keyCode;
        NUIChar m_key;
    };
}

#endif /* NUIKEYEVENT_HPP */

