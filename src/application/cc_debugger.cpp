/*
 * cc_tool.cpp
 *
 * Created on: Aug 3, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#include <boost/regex.hpp>
#include "common.h"
#include "version.h"
#include "log.h"
#include "timer.h"
#include "programmer/cc_programmer.h"
#include "cc_debugger.h"

//==============================================================================
static void print_hex_dump(const ByteVector &data)
{
	size_t total_size = data.size();
	size_t offset = 0;

	while (total_size)
	{
		size_t size = std::min(total_size, (size_t)40);
		std::cout << binary_to_hex(&data[offset], size, "") << "\n";
		offset += size;
		total_size -= size;
	}
}

//==============================================================================
static void load_flash_data(const OptionFileInfo &file_info, DataSectionStore &section_store,
		bool allow_overlapping_records)
{
	if (file_info.type == "hex")
	{
		DataSectionStore sections;
		hex_file_load(file_info.name, sections, false,
				allow_overlapping_records);
		section_store.add_sections(sections, true);

		size_t n = 0;
		log_info("main, loaded hex file %s", file_info.name.c_str());
		foreach (const DataSection &item, section_store.sections())
			log_info(" section %02u, address: %06Xh, size: %06Xh",
					n++, item.address, item.size());
	}

	if (file_info.type == "bin")
	{
		ByteVector data;
		binary_file_load(file_info.name, data);

		DataSection section(file_info.offset, data);
		section_store.add_section(section, true);

		log_info("main, loaded bin file %s, size: %u", file_info.name.c_str(),
				data.size());
	}
}

//==============================================================================
static std::ostream& operator <<(std::ostream &os, const CC_ProgrammerInfo &o)
{
	os << "   Name: " << o.name << "\n";
	os << "   Debugger ID: " << o.debugger_id << "\n";
	os << std::hex << std::setfill('0') << std::uppercase;
	os << "   Version: 0x" << std::setw(4) << o.fw_version << "\n";
	os << "   Revision: 0x" << std::setw(4) << o.fw_revision << "\n";
	os << std::dec;

	return os;
}

//==============================================================================
static std::ostream& operator <<(std::ostream &os, const UnitInfo &o)
{
	os << "   Name: " << o.name << "\n";
	os << std::hex << std::setfill('0') << std::uppercase;
	os << "   Revision: 0x" << std::setw(2) << (uint_t)o.revision << "\n";
	os << "   Internal ID: 0x" << std::setw(2) << (uint_t)o.internal_ID << "\n";
	os << "   ID: 0x" << std::setw(4) << o.ID << "\n";
	os << std::dec;
	os << "   Flash size: ";
	if (!o.flash_size)
		os << "n/a" << "\n";
	else
		os << o.flash_size << " KB" << "\n";
	os << "   Flash page size: " << o.flash_page_size << "\n";
	os << "   RAM size: ";
	if (!o.ram_size)
		os << "n/a" << "\n";
	else
		os << o.ram_size << " KB" << "\n";
	os << std::dec;
	return os;
}

//==============================================================================
void CC_Debugger::init_options(po::options_description &desc)
{
    desc.add_options()
        ("debugger,D", 
        "Start Debugger");
	
    desc.add_options()
        ("debug-prompt,P", po::value<String>(&option_debugger_prompt_)->implicit_value("debug>"),
        "Debugger Prompt, if '-P NULL' then prompt will be null (\\0) character");

    desc.add_options()
        ("debug-addr,Z", po::value<String>(&option_debugger_address_),
        "Debugger will listen for incomming connections on this address. e.g.    '-Z 9876', '-Z 127.0.0.1:9876'");
}

//==============================================================================
bool CC_Debugger::read_options(const po::options_description &desc, const po::variables_map &vm)
{
	if (!CC_Base::read_options(desc, vm))
		return false;

	if (vm.count("debugger"))
	{
		//String value = vm["debugger"].as<String>();

	}

	return true;
}

//==============================================================================
bool CC_Debugger::validate_debugger_address()
{
	return true;
}

//==============================================================================
void CC_Debugger::process_tasks() {

}

//==============================================================================
CC_Debugger::CC_Debugger() 
{}

//==============================================================================
CC_Debugger::~CC_Debugger() 
{}
