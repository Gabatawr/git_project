#pragma once
#include <string>
using std::string;


class Test_status
{
protected: 

public:    Test_status() = default;
	      ~Test_status() = default;
	
		   enum Status { unknown, paused, completed };
  explicit Test_status(Status);

	       Status status = unknown;
	       string print() const;
private:
};