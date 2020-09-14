#pragma once
#include "I_Editor.h"

class png_Editor : public I_Editor
{
	void create()  override;
	void open()    override;
	void save()    override;
	void save_as() override;
	void print()   override;

	void menu() override;
	void image_menu();
};