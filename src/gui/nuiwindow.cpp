#include <NUIWindow>
#include <NUIApp>

#include <algorithm>

using namespace NUI;

NUIWindow::NUIWindow(NUIObject* parent) : NUIObject(parent) {
	nuiApp->setMainWin(this);
	initscr(); 
	noecho();
	timeout(0);

	if(has_colors() == TRUE)
		start_color();

	// Make black into black, not just gray
	init_color(COLOR_BLACK, 0, 0, 0);

	int h, w;
   	getmaxyx(stdscr, h, w);
	m_pWin = newwin(h, w, 0, 0);	
}

NUIWindow::~NUIWindow() {
	endwin();
}

void NUIWindow::paintEvent(NUIPaintEvent* event) {
	wclear(m_pWin);
	for(auto obj : m_childs)
		NUIApp::NUISendEvent(obj, new NUIPaintEvent(obj->rect()));

	NUIObject::paintEvent(event);
}