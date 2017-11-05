#include "include/UIControler.h"

int main() {
	UIControler ui;

	ui.Start();
	while (ui.GetReturnCode() != UIControler::Stop)
		ui.Transform(ui.GetReturnCode());

	return 0;
}
