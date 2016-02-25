#ifndef DEFINITIONS_H
#define DEFINITIONS_H


#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL{
	class EnumDLL{
		public:
			enum KEYS{UP,DOWN,LEFT,RIGHT};
			enum STATES{DEFAULT = -2,NONE = -1, QUIT, RETURN, MAINMENU,OPTIONS,MAPOPTIONS, LOAD, ABOUT, SAVE, NEW, EDITORMODE, EDITORMAINMENU, EDITORMAPOPTIONS, EDITORSCREENOPTIONS};
			enum STATEDIRECTION{NA,PUSH,POP,POPPUSH,POPTOFIRST};
			enum TILETYPE{EMPTY,SOLID};
			enum OPTIONTYPES{NOOPTION,WIDTHOPTION,HEIGHTOPTION};
	};

	class Constants{
		public:
			static const int TileSize = 20;
	};

}




#endif