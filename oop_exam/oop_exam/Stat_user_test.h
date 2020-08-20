#pragma once
#include "Test_status.h"

#include <string>
using std::string;

#include <map>


class Stat_user_test
{
protected: string      test_name,
				       section_name;
	
		   unsigned    rating = 0,
			           time = 0,
		               total_answers = 0,
					   correct_answers = 0;
	
		   
	
public:    unsigned    id;
	       Test_status test_status;
	
		   std::map<unsigned, unsigned> answer_list;

	       Stat_user_test() = default;
	      ~Stat_user_test() = default;
  explicit Stat_user_test(unsigned, string, string, Test_status, unsigned = 0, unsigned = 0, unsigned = 0, unsigned = 0);

		   void     update_user_stat(unsigned, unsigned, unsigned = 0, unsigned = 0);
	
		   void     show_stat_test()      const;
	
		   string   get_test_name()       const;
		   string   get_section_name()    const;
	
		   unsigned get_rating()          const;
		   unsigned get_time()            const;
		   unsigned get_total_answers()   const;
		   unsigned get_correct_answers() const;
	
		   bool save_user_test_list(std::ofstream&);
		   bool load_user_test_list(std::ifstream&);
private:
};