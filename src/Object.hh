/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_OBJECT_INC
#	define ENTROPY_THEIA_OBJECT_INC

#	include "Drawable.hh"

#	include <glm/glm.hpp>

	namespace Entropy
	{
		namespace Theia
		{
			using Vertex = glm::vec3;
			using Point = Vertex::value_type;
			using Matrix = glm::mat4;

			class Object :
				public Drawable
			{
				public:
					Object();
					virtual ~Object();
					virtual void Translate(const Vertex &);
					virtual void Rotate(const Point &, const Vertex &);
					virtual void Scale(const Vertex &);
				protected:
					Matrix &Model();
					const Matrix &Model() const;
				private:
					Matrix _model;
			};
		}
	}

#endif
