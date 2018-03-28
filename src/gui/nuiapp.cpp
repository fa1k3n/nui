#include <NUIApp>
#include <NUIWindow>

using namespace NUI;

NUIApp* nuiApp = nullptr;

NUIApp::NUIApp() :
	m_running(false) {
		nuiApp = this;
}

/** Destructor */
NUIApp::~NUIApp() {
}

bool NUIApp::isKeyPressed() {
	int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return true;
    } else {
        return false;
    }
}

 NUIWindow* NUIApp::focusWindow() {
 	return nuiApp->m_win; 
 }

void NUIApp::handleKeyPress() {
	emit keyPressed(getch());
}


/** Initialize */
void NUIApp::mainloop(volatile bool* running) {
	NUIBoundingRect rect{0, 0, m_win->getWidth(), m_win->getHeight()};

	while(*running) {
		if(isKeyPressed()) handleKeyPress();
		m_win->draw(rect);  // Should be event
	}

	use_default_colors();
}

void NUIApp::NUIPostEvent(NUIObject* recv, NUIEvent* event) {
	recv->event(event);
}

