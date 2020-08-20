#pragma once

#include "Stat_user_test.h"

class Stat
{
protected: unsigned total_attempts = 0,
					total_completed = 0,
					total_paused = 0,
					avg_time = 0,
			        avg_rating = 0;
	
public:    Stat() = default;
  virtual ~Stat() = default;

   virtual void show_stat_base();
	
           void update_base_stat(Stat_user_test* = nullptr);

		   bool save_stat(std::ofstream&);
		   bool load_stat(std::ifstream&);
private:
};
