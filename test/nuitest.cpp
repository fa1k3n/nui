#include <NUIWindow>
#include <NUIApp>
#include <NUILabel>
#include <NUIRow.hpp>

#include <signals/signal.hpp>

int main(void) {
	NUI::NUIApp app;
	NUI::NUIWindow win;

	//NUI::NUIRow row(&win);
	//row.setX(5).setY(5).setWidth(50);
	
	NUI::NUILabel lbl(&win);
	lbl.setTextColor(COLOR_BLACK).setText("Keypress: ").setColor(COLOR_GREEN).setX(10).setY(5).setWidth(15);

	NUI::NUILabel lbl2(&win);
	lbl2.setText("").setX(25).setY(5).setWidth(25).setColor(COLOR_MAGENTA);
	
	Signals::connect(&NUI::NUIApp::keyPressed, &app, [&](NUI::NUIReal ch) {
		NUI::NUIString s(1, (char)ch);
		lbl.setText("Keypress: " + s);
		lbl2.setText(lbl2.getText() + s);
	});

	Signals::connect(&NUI::NUIApp::keyPressed, &app, [&](NUI::NUIReal ch) {

		lbl2.setColor(lbl2.getColor() == COLOR_MAGENTA ? COLOR_RED : COLOR_MAGENTA);
	});

	bool running = true;
	app.mainloop(&running);

	return 0;
}