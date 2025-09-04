#include "Application.h"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	Application app;

	app.init();
	app.run();
	app.stop();
}