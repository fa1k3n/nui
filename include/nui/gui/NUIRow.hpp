#ifndef __NUI_ROW_HPP__
#define __NUI_ROW_HPP__

#include <NUIObject>

namespace NUI {
	class NUIRow : public NUIObject {
	public:
		NUIRow(NUIObject* parent = nullptr);

		NUIReal getHeight() { return 1; }
		void draw(NUIBoundingRect& rect, NUIGfxCntx* cntx = nullptr) override;

		static NUIRow create(NUIObject *parent=nullptr) { return NUIRow(parent); }
	};
}
#endif