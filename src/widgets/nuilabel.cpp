#include <NUILabel>
#include <NUIApp>

using namespace NUI;

NUILabel::NUILabel(NUIObject* parent) : NUIObject(parent)
	, m_text("")
	, m_sizeFollowContent(true) {

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

void NUILabel::draw(NUIBoundingRect& rect) {
    // CHeck that string fits inside bounding rect
    std::string contStr(m_text.c_str());

    m_x = rect.x;
    m_y = rect.y;
    m_width = rect.width;
    m_height = rect.height;

    // If we are to cut the string we want an ellipsis in
    // the end, e.g. 3 chars 
    if (contStr.length() > rect.width && !m_sizeFollowContent) {
            contStr = contStr.substr(0, rect.width - 3);
            contStr += "...";
    }

    auto cntx = NUIApp::focusWindow()->m_pWin;
    wattron(cntx, COLOR_PAIR(NUIColorPair::getColorPair(m_objectID).index));
    mvwprintw(cntx, rect.y, rect.x, contStr.c_str());
    wattroff(cntx, COLOR_PAIR(NUIColorPair::getColorPair(m_objectID).index));
}

void NUILabel::paintEvent(NUIPaintEvent* event) {
    NUIBoundingRect r = event->rect();
    draw(r);
    NUIObject::paintEvent(event);
}

void NUILabel::keyEvent(NUIKeyEvent* event) {
	setText(m_text + NUI::NUIString(1, event->key()));
	NUIObject::keyEvent(event);
}

void NUILabel::resizeEvent(NUIResizeEvent* event) {
	m_sizeFollowContent = false;
	NUIObject::resizeEvent(event);
}


