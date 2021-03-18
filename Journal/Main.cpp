#include "App.h"
#include "IOWinConsole.h"

int main(int argc, char* argv[])
{
	IOWinConsole io;
	App app = App(&io);
	app.Go();
}