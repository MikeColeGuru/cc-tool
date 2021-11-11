/*
 * cc_base.h
 *
 *  Created on: Nov 30, 2011
 *      Author: st
 */

#ifndef _CC_BASE_H_
#define _CC_BASE_H_

#include <boost/program_options.hpp>
#include "data/binary_file.h"
#include "data/hex_file.h"
#include "data/read_target.h"
#include "data/data_section_store.h"
#include "programmer/cc_programmer.h"

namespace po = boost::program_options;

class CC_Base : boost::noncopyable
{
public:
	CC_Base();
	virtual ~CC_Base();
	bool execute(po::options_description &, po::variables_map &);
	void init_options(po::options_description &);

protected:
	/// @return false if application should exit

	virtual bool read_options(const po::options_description &, const po::variables_map &);
	virtual void process_tasks();
	UnitInfo unit_info_;
	CC_Programmer programmer_;
	bool option_allow_overlapping_records_;

private:
	void on_help(const po::options_description &);
	bool init_programmer();
	bool init_unit();

	bool option_fast_interface_speed_;
	// String option_unit_name_;
	// String option_device_address_;
	// String option_log_name_;
};

#endif // !_CC_BASE_H_
