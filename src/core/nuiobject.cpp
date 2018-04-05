#include <NUIObject>
#include <NUIApp>


using namespace NUI;

NUIReal NUIObject::nObjects = 0;

NUIObject::NUIObject(NUIObject* parent) :
    m_parent(parent),
    m_objectID(NUIObject::nObjects) {
    NUIObject::nObjects++;
    if(parent) {
        NUIApp::NUIPostEvent(parent, new NUIChildEvent(this));
    } else if (nuiApp) {
        // This is a new top level window
        NUIApp::NUIPostEvent(nuiApp,  new NUIChildEvent(this));
    }
}

NUIObject& NUIObject::addChild(NUIObject* obj) {
	m_childs.push_back(obj);
	return *this;
}		

NUI::NUIObject* tmpobj;
NUIObject& NUIObject::setFocus(NUIBool f) {
    tmpobj = this;
    return *this;
}

bool NUIObject::event(NUIEvent* event) {
    if(event->type() == NUIEvent::Child) {
            NUIChildEvent* e = static_cast<NUIChildEvent*>(event);
            childEvent(e);
            return true;
    }
    return false;
}

void NUIObject::childEvent(NUIChildEvent* event) {
	addChild(event->child());
}


