#include <NUIWindow>
#include <NUIApp>
#include <NUILabel>
#include <NUIRow.hpp>

#include <signals/signal.hpp>

NUI::NUILabel* tmplbl;
int main(void) {
	NUI::NUIApp app;
	NUI::NUIWindow win;

	NUI::NUILabel lbl(&win);
	lbl.setText("Keypress:").setX(10).setY(5);

	NUI::NUILabel lblInp(&win);
	lblInp.setTextColor(COLOR_BLACK).setColor(COLOR_GREEN).setWidth(1).setX(19).setY(5);

	NUI::NUILabel lbl2(&win);
	lbl2.setWidth(25).setX(25).setY(5).setColor(COLOR_MAGENTA);
	tmplbl = &lbl2;
	
	Signals::connect(&lbl2, &NUI::NUILabel::keyPressed,  [&](NUI::NUIChar key) {
		lbl2.setColor(lbl2.getColor() == COLOR_MAGENTA ? COLOR_RED : COLOR_MAGENTA);
		lblInp.setText(NUI::NUIString(1, key));
	});

	bool running = true;
	app.mainloop(&running);

	return 0;
}