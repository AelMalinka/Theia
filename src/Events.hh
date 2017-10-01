/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com> 
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_EVENTS_INC
#	define ENTROPY_THEIA_EVENTS_INC

#	include "IWindow.hh"

	namespace Entropy
	{
		namespace Theia
		{
			class IWindow;

			namespace Events
			{
				class Debug :
					public Event
				{
					public:
						static constexpr std::size_t Id = Event::First;
						enum class Source;
						enum class Severity;
						enum class Type;
					public:
						Debug(const Source &, const Type &, const unsigned int, const Severity &, const std::string &);
						const Source &getSource() const;
						const Type &getType() const;
						const unsigned int &getId() const;
						const Severity &getSeverity() const;
						const std::string &getMessage() const;
					private:
						Severity _severity;
						Source _source;
						Type _type;
						unsigned int _id;
						const std::string _message;
					public:
						enum class Source
						{
							Api = GL_DEBUG_SOURCE_API,
							WindowSystem = GL_DEBUG_SOURCE_WINDOW_SYSTEM,
							ShaderCompiler = GL_DEBUG_SOURCE_SHADER_COMPILER,
							ThirdParty = GL_DEBUG_SOURCE_THIRD_PARTY,
							Application = GL_DEBUG_SOURCE_APPLICATION,
							Other = GL_DEBUG_SOURCE_OTHER
						};
						enum class Severity
						{
							High = GL_DEBUG_SEVERITY_HIGH,
							Medium = GL_DEBUG_SEVERITY_MEDIUM,
							Low = GL_DEBUG_SEVERITY_LOW,
							Notification = GL_DEBUG_SEVERITY_NOTIFICATION
						};
						enum class Type
						{
							Error = GL_DEBUG_TYPE_ERROR,
							UndefinedBehavior = GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR,
							Performance = GL_DEBUG_TYPE_PERFORMANCE,
							Marker = GL_DEBUG_TYPE_MARKER,
							PushGroup = GL_DEBUG_TYPE_PUSH_GROUP,
							PopGroup = GL_DEBUG_TYPE_POP_GROUP,
							Other = GL_DEBUG_TYPE_OTHER,
							DeprecatedBehavior = GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,
							Portability = GL_DEBUG_TYPE_PORTABILITY
						};
				};

				class Show :
					public Event
				{
					public:
						static constexpr std::size_t Id = Debug::Id + 1;
						Show(IWindow &);
						IWindow &Window() const;
					private:
						IWindow &_win;
				};

				class Hide :
					public Event
				{
					public:
						static constexpr std::size_t Id = Show::Id + 1;
						Hide(IWindow &);
						IWindow &Window() const;
					private:
						IWindow &_win;
				};

				class Close :
					public Event
				{
					public:
						static constexpr std::size_t Id = Hide::Id + 1;
						Close(IWindow &);
						const IWindow &Window() const;
					private:
						IWindow &_win;
				};

				class Resize :
					public Event
				{
					public:
						static constexpr std::size_t Id = Close::Id + 1;
						Resize(const ScreenDimension, const ScreenDimension);
						const ScreenDimension &Width() const;
						const ScreenDimension &Height() const;
					private:
						ScreenDimension _width;
						ScreenDimension _height;
				};

				// 2017-06-06 AMR TODO: typing?
				class Key :
					public Event
				{
					public:
						// 2017-09-30 AMR TODO: maybe consolidate?
						static constexpr std::size_t Id = Event::First + 10;
						Key(const int, const int, const int);
						const int &Code() const;
						const int &Action() const;
						const int &Modifiers() const;
						bool hasShift() const;
						bool hasControl() const;
						bool hasAlt() const;
					private:
						int _key;
						int _action;
						int _mods;
				};

				class Mouse :
					public Event
				{
					public:
						static constexpr std::size_t Id = Key::Id + 1;
						Mouse(const Dimension, const Dimension);
						const Dimension &X() const;
						const Dimension &Y() const;
					private:
						 Dimension _x;
						 Dimension _y;
				};
			}
		}
	}

#endif
