/*
 * cc_debugger.cpp
 *
 * Created on: Nov 10, 2021
 *     Author: Mike Cole <MikeColeGuru@gmail.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _CC_DEBUGGER_H_
#define _CC_DEBUGGER_H_

#include <boost/program_options.hpp>
#include "data/binary_file.h"
#include "data/hex_file.h"
#include "data/read_target.h"
#include "data/data_section_store.h"
#include "programmer/cc_programmer.h"
#include "application/cc_base.h"

class CC_Debugger : public CC_Base
{
public:
	CC_Debugger();
	virtual ~CC_Debugger();
	void init_options(po::options_description &);

private:
	bool validate_debugger_address();

	virtual bool read_options(const po::options_description &, const po::variables_map &);
	virtual void process_tasks();

	String option_debugger_prompt_;
	String option_debugger_address_; 
};

#endif // !_CC_DEBUGGER_H_
