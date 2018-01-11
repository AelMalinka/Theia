/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_TYPES_INC
#	define ENTROPY_THEIA_TYPES_INC

#	include "Exception.hh"
#	include <glm/glm.hpp>

	namespace Entropy
	{
		namespace Theia
		{
			using Matrix = glm::mat4;
			using Vertex = glm::vec3;
			using Vertex2D = glm::vec2;
			using FullVertex = glm::vec4;
			using Dimension = glm::mat4::value_type;
			using ScreenVertex = glm::ivec2;
			using ScreenDimension = glm::ivec2::value_type;

			ENTROPY_ERROR_INFO(MatrixInfo, Matrix);
			ENTROPY_ERROR_INFO(VertexInfo, Vertex);
			ENTROPY_ERROR_INFO(Vertex2DInfo, Vertex2D);
			ENTROPY_ERROR_INFO(FullVertexInfo, FullVertex);
			ENTROPY_ERROR_INFO(DimensionInfo, Dimension);
			ENTROPY_ERROR_INFO(ScreenVertexInfo, ScreenVertex);
			ENTROPY_ERROR_INFO(ScreenDimensionInfo, ScreenDimension);
		}
	}

#endif
