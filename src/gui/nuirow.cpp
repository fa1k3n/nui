#include <NUIRow.hpp>

using namespace NUI;

#include <iostream>

NUIRow::NUIRow(NUIObject* parent) : NUIObject(parent) {

}

/*
void NUIRow::draw(NUIBoundingRect& rect, NUIGfxCntx* cntx) {
	NUI_UNUSED(rect);
	NUI_UNUSED(cntx);

	int col = 0;
	// Try to fit all childs in the row	
	for(auto child : m_childs) {
		NUIBoundingRect cr{rect.x + col, rect.y, child->getWidth(), child->getHeight()}; 
		child->draw(cr, cntx);
		col += child->getWidth();
	}
}
*/