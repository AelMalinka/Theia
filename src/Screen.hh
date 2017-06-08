/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_SCREEN_INC
#	define ENTROPY_THEIA_SCREEN_INC

#	include "Types.hh"
#	include <tuple>
#	include <vector>
#	include <functional>

	namespace Entropy
	{
		namespace Theia
		{
			class Screen
			{
				public:
					Screen();
					virtual ~Screen();
					virtual void addCallback(const std::function<void(Screen &)> &);
					virtual void clearCallbacks();
					virtual void setFoV(const Dimension);
					virtual void setNearClipping(const Dimension);
					virtual void setFarClipping(const Dimension);
				public:
					virtual const Matrix &Perspective() const;
					virtual const Matrix &Orthogonal() const;
					virtual Dimension Width() const;
					virtual Dimension Height() const;
					virtual Dimension Aspect() const;
					virtual const Dimension &NearClipping() const;
					virtual const Dimension &FarClipping() const;
					virtual const Dimension &FoV() const;
				protected:
					virtual void Update();
					virtual void RunCallbacks();
					virtual void Resize(const ScreenDimension width, const ScreenDimension height);
				protected:
					virtual Matrix &Perspective();
					virtual Matrix &Orthogonal();
					virtual Dimension &NearClipping();
					virtual Dimension &FarClipping();
					virtual Dimension &FoV();
					virtual ScreenDimension &Width();
					virtual ScreenDimension &Height();
				private:
					Matrix _perspective;
					Matrix _orthogonal;
					std::tuple<ScreenDimension, ScreenDimension> _size;
					std::tuple<Dimension, Dimension> _clipping;
					Dimension _fov;
					std::vector<std::function<void(Screen &)>> _cbs;
			};
		}
	}

#endif
