#ifndef NUIEVENT_HPP
#define NUIEVENT_HPP

namespace NUI {
    class NUIEvent {
      public:
              enum NUIEventType {
                      Paint,
                      Resize,
                      Move,
                      KeyPress,
                      Child
              };

              NUIEvent(NUIEventType type) { m_type = type; }
              NUIEventType type() { return m_type; }

      private:
              NUIEventType m_type;
      };
}

#endif /* NUIEVENT_HPP */

