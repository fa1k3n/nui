#include <NUIObject>
#include <NUIApp>


using namespace NUI;

NUIReal NUIObject::nObjects = 0;

NUIObject::NUIObject(NUIObject* parent) :
	m_parent(parent),
	m_width(0),
	m_height(1),
	m_objectID(NUIObject::nObjects) {
	NUIObject::nObjects++;
	if(parent) {
		NUIApp::NUIPostEvent(parent, new NUIChildEvent(this));
	}
	NUIColorPair::setColorPair(NUIColorPair{m_objectID, COLOR_WHITE, COLOR_BLACK});
}

NUIObject& NUIObject::addChild(NUIObject* obj) {
	m_childs.push_back(obj);
	return *this;
}		

NUIObject& NUIObject::setWidth(NUIReal width) {
	NUIBoundingRect oldRect = rect();
	m_width = width;
	NUIApp::NUIPostEvent(this, new NUIResizeEvent(oldRect, rect()));
	return *this;
}

NUIObject& NUIObject::setHeight(NUIReal height) {
	NUIBoundingRect oldRect = rect();
	m_height = height;
	NUIApp::NUIPostEvent(this, new NUIResizeEvent(oldRect, rect()));
	return *this;
}

NUIObject& NUIObject::setX(NUIReal x) {
	auto oldPos = NUIPoint(m_x, m_y);
	m_x = x;
	NUIApp::NUIPostEvent(this, new NUIMoveEvent(oldPos, NUIPoint(m_x, m_y)));
	emit xChanged(x);
	return *this;
}

NUIObject& NUIObject::setY(NUIReal y) {
	auto oldPos = NUIPoint(m_x, m_y);
	m_y = y;
	NUIApp::NUIPostEvent(this, new NUIMoveEvent(oldPos, NUIPoint(m_x, m_y)));
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
	NUIApp::NUIPostEvent(this, new NUIPaintEvent(rect()));
}

void NUIObject::repaint() {
	NUIApp::NUISendEvent(this, new NUIPaintEvent(rect()));
}

bool NUIObject::event(NUIEvent* event) {
	if(event->type() == NUIEvent::Paint) {
		NUIPaintEvent* e = static_cast<NUIPaintEvent*>(event);
		paintEvent(e);
		return true;
	} else if(event->type() == NUIEvent::Resize) {
		NUIResizeEvent* e = static_cast<NUIResizeEvent*>(event);
		resizeEvent(e);
		return true;
	}  else if(event->type() == NUIEvent::Move) {
		NUIMoveEvent* e = static_cast<NUIMoveEvent*>(event);
		moveEvent(e);
		return true;
	} else if(event->type() == NUIEvent::KeyPress) {
		NUIKeyEvent* e = static_cast<NUIKeyEvent*>(event);
		keyEvent(e);
		return true;
	}

	return false;
}

void NUIObject::paintEvent(NUIPaintEvent* event) {
	wrefresh(NUIApp::focusWindow()->m_pWin);
	refresh();
}

void NUIObject::resizeEvent(NUIResizeEvent* event) {
	NUIBoundingRect r = event->newSize();
	m_width = r.width;
	m_height = r.height;
	repaint();
}

void NUIObject::moveEvent(NUIMoveEvent* event) {
	// Clear old location
	mvwprintw(NUIApp::focusWindow()->m_pWin, event->oldPos().y(), event->oldPos().x(), std::string(getWidth()*getHeight(), ' ').c_str());
	m_x = event->newPos().x();
	m_y = event->newPos().y();
	repaint();
}

void NUIObject::keyEvent(NUIKeyEvent* event) {
	emit keyPressed(event->key());
	repaint();
}

void NUIObject::childEvent(NUIChildEvent* event) {
	addChild(event->child());
}


