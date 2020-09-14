#pragma once
#include "I_Editor.h"

class txt_Editor : public I_Editor
{
	void create()  override;
	void open()    override;
	void save()    override;
	void save_as() override;
	void print()   override;
};