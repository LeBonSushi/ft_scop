#include "Application.h"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	Application app(ac, std::vector<std::string>(av, av + ac));

	app.init();
	app.run();
	app.stop();
}