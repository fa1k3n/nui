#include <NUIWindow>
#include <NUIApp>
#include <NUIWidget.hpp>

#include <algorithm>

using namespace NUI;

NUIWindow::NUIWindow(NUIObject* parent) : NUIWidget(parent) {
    nuiApp->setMainWin(this);

    int h, w;
    getmaxyx(stdscr, h, w);
    m_pWin = newwin(h, w, 0, 0);	
}

NUIWindow::~NUIWindow() {
    endwin();
}

void NUIWindow::paintEvent(NUIPaintEvent* event) {
    wclear(m_pWin);
    for(auto obj : m_childs) {
        auto widget = static_cast<NUIWidget*>(obj);
        NUIApp::NUISendEvent(obj, new NUIPaintEvent(widget->rect()));

    }   
    NUIWidget::paintEvent(event);
}