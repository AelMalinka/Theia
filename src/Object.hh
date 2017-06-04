/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_OBJECT_INC
#	define ENTROPY_THEIA_OBJECT_INC

#	include "Drawable.hh"

	namespace Entropy
	{
		namespace Theia
		{
			class Object :
				public Drawable
			{
				public:
					Object(Program &, const std::string &, const std::string &, const std::string &);
					virtual ~Object();
					virtual void Translate(const Vertex &);
					virtual void Rotate(const Dimension &, const Vertex &);
					virtual void Scale(const Vertex &);
				protected:
					virtual void Update(const std::chrono::duration<double> &);
				private:
					Matrix _model;
					bool _needs_update;
			};
		}
	}

#endif
