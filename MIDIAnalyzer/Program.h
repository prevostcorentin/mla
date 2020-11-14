#pragma once
#include <string>
class Program
{
	public:
		Program(std::string file_name);
		void Run();

	private:
		std::string file_name;
};

