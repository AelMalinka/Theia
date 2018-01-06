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
						virtual void setPosition(const ScreenVertex &);
						virtual void setColor(const Vertex &);
						virtual void setScale(const Dimension &);
						virtual void setTransparency(const Dimension &);
						virtual const ScreenVertex &Position() const;
						virtual const Dimension &Scale() const;
						virtual Vertex Color() const;
						virtual Dimension Transparency() const;
					protected:
						virtual const FullVertex &FullColor() const;
					public:
						virtual const ScreenVertex Size() const = 0;
					private:
						ScreenVertex _pos;
						FullVertex _color;
						Dimension _scale;
				};
			}
		}
	}

#endif
