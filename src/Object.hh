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

			class Object :
				public Drawable
			{
				public:
					Object();
					virtual ~Object();
					virtual void Translate(const Vertex &);
					virtual void Rotate(const Vertex::value_type &, const Vertex &);
					virtual void Scale(const Vertex &);
				protected:
					glm::mat4 &Model();
					const glm::mat4 &Model() const;
				private:
					glm::mat4 _model;
			};
		}
	}

#endif
