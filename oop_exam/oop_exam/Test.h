#pragma once

#include "Question.h"
#include "Stat_test.h"

#include <vector>

#include "User.h"


class Test : public Stat_test
{	
protected:
	static unsigned counter_id;

public:    Test();
	      ~Test() = default;

	static unsigned get_counter_id();
	static void     set_counter_id(unsigned);
	
		   unsigned id;
	
	       std::vector<Question*> questions;

		   void add_questions();
		   void scan();

		   Stat_user_test* testing(User*, string, string);

		   bool save(std::ofstream&);
		   bool load(std::ifstream&);
	
private:
};

