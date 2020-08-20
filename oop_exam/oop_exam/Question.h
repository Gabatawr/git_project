#pragma once

#include <list>

#include <string>
using std::string;


class Question
{
protected: unsigned correct_ans = 0,
		            user_choice = 0;

    static unsigned counter_id;
	
public:    Question();
	      ~Question() = default;
  explicit Question(string&);
	
    static unsigned get_counter_id();
	static void     set_counter_id(unsigned);
		   unsigned id = 0;

		   string             ask;
		   std::list <string> ans;
	
		   void     def_user_choice();
		   void     set_user_choice(unsigned = 777);
		   unsigned get_user_choice() const;
	
		   void     set_correct_ans();
		   unsigned get_correct_ans() const;
	
		   void edit();
	
		   void replace_ask();
	
		   void new_answer();
	       void del_answer();

		   bool save(std::ofstream&);
		   bool load(std::ifstream&);
private:
};

