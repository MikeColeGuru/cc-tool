/*
 * main.cpp
 *
 * Created on: Jul 28, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#include <boost/regex.hpp>
#include "application/cc_flasher.h"
#include "application/cc_debugger.h"
#include "version.h"
#include "log.h"
#include "main.h"

namespace po = boost::program_options;

//==============================================================================
static void init_log(int argc, char *argv[], String &log_file)
{
	if (log_file.empty())
		log_file = String(MODULE_NAME) + ".log";

	log_get().set_log_file(log_file);
	log_info("main, %s %u.%u", MODULE_NAME, VERSION_MAJOR, VERSION_MINOR);

	String command_line;
	while (argc--)
		command_line += String(*argv++) + " ";
	log_info("main, command line: %s", command_line.c_str());
}

//==============================================================================
void init_options(po::options_description &desc)
{
	desc.add_options()
		("help,h", "produce help message");

	desc.add_options()
		("log", po::value<String>(&option_log_name)->implicit_value(""),
				"create log of all operations");

	desc.add_options()
		("device,d", po::value<String>(&option_device_address),
				"set programmer device usb address 'bus:device'");

	desc.add_options()
		("fast,f", "set fast debug interface speed (by default: slow)");

	desc.add_options()
		("name,n", po::value<String>(&option_unit_name),
				"specify target name e.g. CC2530 etc.");

	desc.add_options()
		("allow-overlapping-records",
				"allow overlapping records in hex files, the last one wins (by default: they are disallowed)");
}

//==============================================================================
int main(int argc, char **argv)
{
	CC_Flasher cc_flasher;
	CC_Debugger cc_debugger;
	
	po::options_description desc;

	init_options(desc);
	cc_flasher.init_options(desc);
	cc_debugger.init_options(desc);

	try
	{
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("debugger")) {
			return cc_debugger.execute(desc, vm) ? EXIT_SUCCESS : EXIT_FAILURE;
		}
		else {
			return cc_flasher.execute(desc, vm) ? EXIT_SUCCESS : EXIT_FAILURE;
		}
		
	}
	catch (po::error& e) // command line error
	{
		std::cout << "  Bad command line options";
		if (strlen(e.what()))
			std::cout << " (" << e.what() << ")";
		std::cout << "\n  Try --help for more information\n";
	}

	return EXIT_FAILURE;
}
