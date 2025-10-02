#include <iostream>

#include "Core/System/SingletonInstanceControl.HPP"
#include "Core/Application.HPP"

#include <boost/locale.hpp>

const char* const APPLICATION_UNIQUE_ID = PROJECT_NAME"{653E7F71-A1D6-FC07-B783-D707B1724F26}";
const char* const APPLICATION_TEXT_DOMAIN = "StyxTelegramBotFramework";

int main(int argc, char* argv[])
{
	boost::locale::generator Generator;
	Generator.add_messages_path("./Language");
	Generator.add_messages_domain(APPLICATION_TEXT_DOMAIN);
	std::locale::global(Generator(""));
	std::cout.imbue(std::locale());
	std::cerr.imbue(std::locale());

	try {
		SingletonInstanceControl Protect(APPLICATION_UNIQUE_ID);

		Application APP;
		APP.Initialize();
		APP.Start();

	} catch (const std::runtime_error& Error) {
		std::cerr << boost::locale::translate("Startup Failure") << " : " << Error.what() << std::endl;
		std::cerr << boost::locale::translate("Do Not Run This Application Repeatedly") << std::endl;
		return 404;
	}

	return 0;
}