#include <NUILabel>
#include <NUIApp>

using namespace NUI;

NUILabel::NUILabel(NUIObject* parent) : NUIObject(parent)
	, m_text("") {

}

NUILabel& NUILabel::setText(NUIString const &txt) {
	m_text = txt;
	emit textChanged(txt);
	update();
	return *this;
}		

NUILabel& NUILabel::setTextColor(NUIColor color) {
	NUIColorPair pair = NUIColorPair::getColorPair(m_objectID);
	pair.setFg(color);
	return *this;
}

void NUILabel::draw(NUIBoundingRect& rect, NUIGfxCntx* cntx) {
	// CHeck that string fits inside bounding rect
	std::string contStr(m_text.c_str());

	m_x = rect.x;
	m_y = rect.y;
	m_width = rect.width;
	m_height = rect.height;

	// If we are to cut the string we want an ellipsis in
	// the end, e.g. 3 chars 
	if (contStr.length() > rect.width) {
		contStr = contStr.substr(0, rect.width - 3);
		contStr += "...";
	}

	wattron(cntx, COLOR_PAIR(NUIColorPair::getColorPair(m_objectID).index));
	mvwprintw(cntx, rect.y, rect.x, contStr.c_str());
	wattroff(cntx, COLOR_PAIR(NUIColorPair::getColorPair(m_objectID).index));
}

#include <iostream>
void NUILabel::paintEvent(NUIPaintEvent* event) {
	NUIWindow* win = NUIApp::focusWindow();
	NUIBoundingRect r = event->rect();
	draw(r, win->m_pWin);
	NUIObject::paintEvent(event);
}


