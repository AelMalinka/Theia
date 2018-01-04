/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_UI_ELEMENT_INC
#	define ENTROPY_THEIA_UI_ELEMENT_INC

#	include "Exception.hh"
#	include "../Drawable.hh"

	namespace Entropy
	{
		namespace Theia
		{
			namespace UI
			{
				class Element :
					public Drawable
				{
					public:
						Element();
						virtual ~Element();
						virtual void Update(const std::chrono::duration<double> &);
						virtual void UpdateCamera(const Camera &) {}
					protected:
						virtual void Draw() = 0;
					public:
						void setPosition(const ScreenVertex &);
						void setColor(const Vertex &);
						void setScale(const Dimension &);
						const ScreenVertex &Position() const;
						const Vertex &Color() const;
						const Dimension &Scale() const;
					public:
						virtual const ScreenVertex Size() const = 0;
					private:
						ScreenVertex _pos;
						Vertex _color;
						Dimension _scale;
				};
			}
		}
	}

#endif
