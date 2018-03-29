#include <NUIObject>
#include <NUIApp>


using namespace NUI;

NUIReal NUIObject::nObjects = 0;

NUIObject::NUIObject(NUIObject* parent) :
	m_parent(parent),
	m_width(0),
	m_height(0),
	m_objectID(NUIObject::nObjects) {
	NUIObject::nObjects++;
	if(parent) {
		parent->addChild(this);
	}
	NUIColorPair::setColorPair(NUIColorPair{m_objectID, COLOR_WHITE, COLOR_BLACK});
}

NUIObject& NUIObject::addChild(NUIObject* obj) {
	m_childs.push_back(obj);
	update();
	return *this;
}		

NUIObject& NUIObject::setWidth(NUIReal width) {
	m_width = width;
	return *this;
}

NUIObject& NUIObject::setHeight(NUIReal height) {
	m_height = height;
	return *this;
}

NUIObject& NUIObject::setX(NUIReal x) {
	m_x = x;
	emit xChanged(x);
	return *this;
}

NUIObject& NUIObject::setY(NUIReal y) {
	m_y = y;
	emit yChanged(y);
	return *this;
}

NUIColor NUIObject::getColor() {
	return NUIColorPair::getColorPair(m_objectID).bg;
}

NUIObject& NUIObject::setColor(NUIColor color) {
	NUIColorPair pair = NUIColorPair::getColorPair(m_objectID);
	pair.setBg(color);
	return *this;
}

void NUIObject::update() {
	NUIApp::NUIPostEvent(this, new NUIPaintEvent(NUIBoundingRect{m_x, m_y, m_width, m_height}));
}

bool NUIObject::event(NUIEvent* event) {
	if(event->type() == NUIEvent::Paint) {
		NUIPaintEvent* e = static_cast<NUIPaintEvent*>(event);
		paintEvent(e);
		return true;
	}

	return false;
}

void NUIObject::paintEvent(NUIPaintEvent* event) {
	wrefresh(NUIApp::focusWindow()->m_pWin);
	refresh();
}
