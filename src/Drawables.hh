/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_DRAWABLES_INC
#	define ENTROPY_THEIA_DRAWABLES_INC

#	include "Drawable.hh"
#	include <Entropy/PolymorphicList.hh>

	namespace Entropy
	{
		namespace Theia
		{
			class Drawables :
				public Drawable
			{
				public:
					Drawables(Screen &);
					virtual ~Drawables();
					virtual void Update(const std::chrono::duration<double> &);
				protected:
					virtual void UpdateModel() {}
					virtual void UpdateScreen(const Screen &);
					virtual void UpdateCamera(const Camera &);
				public:
					void addDrawable(const std::shared_ptr<Drawable> &);
					template<typename T, typename ...Args>
					std::shared_ptr<T> emplaceDrawable(Args && ...);
					//void removeDrawable(const std::shared_ptr<Drawable> &);
					void clearDrawables();
				protected:
					virtual void NewDrawable(const std::shared_ptr<Drawable> &);
				protected:
					Screen &getScreen();
				private:
					Screen &_screen;
					PolymorphicList<Drawable> _draws;
			};
		}
	}

#	include "Drawables.impl.hh"

#endif
