#include "Program.h"

int main(int argc, char* argv)
{
	Program program(std::to_string(argv[1]));
	program.Run();
}