#ifndef DUMBAI_H
#define DUMBAI_H



#define ALLEGRO_NO_MAGIC_MAIN



#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>//fonts
#include <allegro5/allegro_ttf.h>//fonts
#include "../LivingEntity/Character.h"


#ifdef STATICDLL_EXPORTS
#define STATICDLL_API __declspec(dllexport)
#else
#define STATICDLL_API __declspec(dllimport)
#endif



namespace StaticDLL {


	class DumbAI
	{
	public:
		STATICDLL_API DumbAI(Character *character, Map *map);



		STATICDLL_API void Update();


		STATICDLL_API void Draw();



	private:


		Map *map_;

		Character *character_;

	};
}
#endif