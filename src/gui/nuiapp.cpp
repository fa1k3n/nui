#include <NUIApp>
#include <NUIWindow>

#include <functional>

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
	while(*running) {
		if(isKeyPressed()) handleKeyPress();

		while(nuiApp->m_eventQueue.size() > 0) {
			nuiApp->m_eventQueue.front()();     // Invoke event
			nuiApp->m_eventQueue.pop();			// And remove
		}
	}

	use_default_colors();
}

void NUIApp::NUIPostEvent(NUIObject* recv, NUIEvent* event) {
	//auto invoker = std::function<void()>(std::bind(&NUIObject::event, recv, event));
	//nuiApp->m_eventQueue.push(invoker);	
	recv->event(event);

}

void NUIApp::NUISendEvent(NUIObject* recv, NUIEvent* event) {
	recv->event(event);
}

