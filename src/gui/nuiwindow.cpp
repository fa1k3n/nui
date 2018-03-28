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

void NUIWindow::draw(NUIBoundingRect& rect, NUIGfxCntx* cntx) {
	bool redraw = false; //false;
	// Clear scrn if we have dirty region
	//redraw = std::any_of(m_childs.begin(), m_childs.end(), [](NUIObject* obj){ return obj->isDirty(); });

	for(auto obj : m_childs) {
		if(obj->isDirty()) {
			redraw = true;
		}
	}
	// If diry children exists, then redraw screen! 
	// This should be updated to only clear the actual child
	if(redraw) {
		wclear(m_pWin);
		for(auto obj : m_childs) {

			// Here we should calculate the rectangle
			// Get wanted size
			NUIBoundingRect r{obj->getX(), obj->getY(), obj->getWidth(), obj->getHeight()};
			obj->draw(r, m_pWin);
			obj->setDirty(false);
		}
		wrefresh(m_pWin);
		refresh();
		redraw = false;
	}
}