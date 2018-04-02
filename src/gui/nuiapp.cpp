#include <NUIApp>
#include <NUIWindow>

#include <NUILabel>
#include <functional>

using namespace NUI;

NUIApp* nuiApp = nullptr;

NUIApp::NUIApp() {		
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


extern NUILabel* tmplbl;
NUIObject* NUIApp::focusObject() {
	return tmplbl;
}

void NUIApp::handleKeyPress() {
	int ch = getch();

	NUIApp::NUIPostEvent(NUIApp::focusObject(), new NUIKeyEvent(ch, (char)ch));
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
	auto invoker = std::function<void()>(std::bind(&NUIObject::event, recv, event));
	nuiApp->m_eventQueue.push(invoker);	
}

void NUIApp::NUISendEvent(NUIObject* recv, NUIEvent* event) {
	recv->event(event);
}

