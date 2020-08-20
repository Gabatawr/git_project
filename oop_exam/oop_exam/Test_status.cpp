#include "Test_status.h"


Test_status::Test_status(Status status) : status(status) {}

string Test_status::print () const
{
	if (status == paused)    return "paused";
	if (status == completed) return "completed";

	else                     return "unknown";
}
