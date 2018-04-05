#ifndef NUIWIDGET_HPP
#define NUIWIDGET_HPP

#include <NUIObject>
#include <NUITypes.hpp>
#include <signals/signal.hpp>

#include <events/NUIPaintEvent.hpp>
#include <events/NUIResizeEvent.hpp>
#include <events/NUIMoveEvent.hpp>
#include <events/NUIKeyEvent.hpp>


namespace NUI {
    class NUIWidget : public NUIObject {
    public:
        NUIWidget(NUIObject* parent = nullptr);

        virtual ~NUIWidget();

        virtual NUIWidget& setWidth(NUIReal width);
         virtual NUIReal getWidth() { return m_width; }

         virtual NUIWidget& setHeight(NUIReal height);
         virtual NUIReal getHeight() { return m_height; }

         virtual NUIBoundingRect rect() { return NUIBoundingRect{m_x, m_y, m_width, m_height}; }

         NUIWidget& setX(NUIReal x);
         NUIReal getX() { return m_x; }
         Signals::signal<NUIReal> xChanged;

         NUIWidget& setY(NUIReal y);
         NUIReal getY() { return m_y; }
         Signals::signal<NUIReal> yChanged;

         NUIColor getColor();
         NUIWidget& setColor(NUIColor color);
         
         Signals::signal<NUIChar> keyPressed;
         
         virtual bool event(NUIEvent* event);

         void update(); 
         void repaint();
         
    protected:
                virtual void paintEvent(NUIPaintEvent* event);
                virtual void resizeEvent(NUIResizeEvent* event);
                virtual void moveEvent(NUIMoveEvent* event);
                virtual void keyEvent(NUIKeyEvent* event);
                
                NUIReal m_x, m_y;
                NUIReal m_width, m_height;
    private:

    };
}
#endif /* NUIWIDGET_HPP */

