#ifndef DEFINITIONS_H
#define DEFINITIONS_H




#ifdef STATICDLL_EXPORTS
   #define STATICDLL_API __declspec(dllexport)
#else
   #define STATICDLL_API __declspec(dllimport)
#endif


namespace StaticDLL{
	enum class KEYS{UP,DOWN,LEFT,RIGHT};
	enum class STATES{DEFAULT = -2,NONE = -1, QUIT, RETURN, MAINMENU,OPTIONS,MAPOPTIONS, LOAD, ABOUT, SAVE, NEW,
		EDITORMODE, EDITORMAINMENU, EDITORMAPOPTIONS, EDITORSCREENOPTIONS, EDITOROPTIONS, 
		TILEIMAGEPICKER, TILETYPEPICKER, TILECOLORPICKER, OBJECTIMAGEPICKER, ENEMYPICKER, ITEMPICKER};
	enum class STATEDIRECTION{NA,PUSH,POP,POPPUSH,POPTOFIRST};
	enum class TILETYPE{EMPTYTILE, SOLIDTILE, COLLISIONTOPTILE, COLLISIONLEFTTILE, COLLISIONRIGHTTILE, ILLUSIONTILE};
	enum class OPTIONTYPES{NOOPTION,WIDTHOPTION,HEIGHTOPTION};
	enum class OVERLAYACTIONS{OVERLAYNONE,OVERLAYOPENING,OVERLAYCLOSING, OVERLAYHEADERCLICKED};
	enum class OVERLAYSTATE{OVERLAYOPENED,OVERLAYCLOSED};

	//enum CHARACTERSTATES{CHARACTERIDLE, CHARACTERMOVING, CHARACTERJUMPING, CHARACTERFALLING, CHARACTERONGROUND};
	enum class CHARACTERYAXISSTATES{CHARACTERJUMPING, CHARACTERFALLING, CHARACTERONGROUND};
	enum class CHARACTERFACINGDIRECTION{CHARACTERLEFT, CHARACTERRIGHT};


	enum class IMAGESETS{PLAYERIMAGESET, TILEIMAGESET, TILECOLORSET, BACKGROUNDIMAGESET, SYSTEMIMAGESET, OBJECTIMAGESET, ENEMYIMAGESET, ITEMIMAGESET};

	enum class ITEMTYPES { NA, KEY, WEAPON };
	enum class OBJECTTYPES { NA, DOOR, LOCKEDDOOR };




	struct Vector
	{
		float x;
		float y;
	};



	class Constants{
		public:
			static const float TileSize() { return 16.0; }


	};

}




#endif