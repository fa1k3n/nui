#include <NUIApp>
#include <NUILabel>
#include <functional>

using namespace NUI;

NUIApp* nuiApp = nullptr;

void NCursesPainter::init() {
        // Initialize ncurses
    initscr(); 
    noecho();
    timeout(0);
    
    
    if(has_colors() == TRUE)
            start_color();

    // Make black into black, not just gray
    init_color(COLOR_BLACK, 0, 0, 0);
}

NUIApp::NUIApp(IPainter* painter) {		
    nuiApp = this;
    if(!painter) {
        NCursesPainter p;
        p.init();
    }
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
    //return static_cast<NUIWindow*>(nuiApp->m_childs.front());
    return nuiApp->m_win; 
}

extern NUIObject* tmpobj;
NUIObject* NUIApp::focusObject() {
    return tmpobj;
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