#pragma once
#include <fstream>

class SaveLoad
{//---------------------------------------------------
protected:  enum StreamType { Out, In };
protected://------------------------------------------
    static  std::ofstream* FileOut;
    static  std::ifstream* FileIn;
public://---------------------------------------------
    static  const char*    PathFile;
protected://------------------------------------------
    static  void           Open     (StreamType);
    static  void           Close    (StreamType);
public://---------------------------------------------
    virtual void           Save     () = 0;
    static  void           SaveSrt  (std::string str);
    static  void           SaveInt  (int num);
	
    virtual void           Load     () = 0;
    static  std::string    LoadSrt  ();
    static  int            LoadInt  ();
	
    virtual               ~SaveLoad () = default;
};//--------------------------------------------------
