#include "SaveLoad.h"


const char* SaveLoad::PathFile = "default.save";

std::ofstream* SaveLoad::FileOut = nullptr;
std::ifstream* SaveLoad::FileIn  = nullptr;

// -------------------------------------------------------

void SaveLoad::Open(StreamType type)
{
	if (type == Out) FileOut = new std::ofstream(PathFile, std::ios::binary, std::ios::trunc);
	if (type == In)  FileIn  = new std::ifstream(PathFile, std::ios::binary);
}

void SaveLoad::Close(StreamType type)
{
	if (type == Out) { FileOut->close(); delete FileOut; FileOut = nullptr; }
	if (type == In)  { FileIn ->close(); delete FileIn;  FileIn  = nullptr; }
}

// -------------------------------------------------------

void SaveLoad::SaveSrt(std::string str)
{
	int  intTmp;
	char charTmp; 
	FileOut->write(reinterpret_cast<char*>(&(intTmp = str.length())), sizeof(int));
	for (auto& it_s : str) FileOut->write(&(charTmp = it_s), sizeof(char));
}

void SaveLoad::SaveInt(int num)
{
	int intTmp;
	FileOut->write(reinterpret_cast<char*>(&(intTmp = num)), sizeof(int));
}

// -------------------------------------------------------

std::string SaveLoad::LoadSrt()
{
	int  intTmp;
	char charTmp;
	std::string strTmp;
	
	FileIn->read(reinterpret_cast<char*>(&intTmp), sizeof(int));
	strTmp.resize(intTmp);
	for (unsigned j = 0; j < static_cast<int>(strTmp.size()); ++j)
		if (FileIn->read(&charTmp, sizeof(char)))
			strTmp[j] = charTmp;

	return strTmp;
}

int SaveLoad::LoadInt()
{
	int intTmp;
	FileIn->read(reinterpret_cast<char*>(&intTmp), sizeof(unsigned));
	return intTmp;
}
