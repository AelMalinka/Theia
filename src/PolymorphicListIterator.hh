/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_POLYMORPHICLISTITERATOR_INC
#	define ENTROPY_THEIA_POLYMORPHICLISTITERATOR_INC

#	include <list>
#	include <memory>

	namespace Entropy
	{
		namespace Theia
		{
			template<typename T>
			class PolymorphicListIterator
			{
				public:
					PolymorphicListIterator(const typename std::list<std::shared_ptr<T>>::iterator &);
					PolymorphicListIterator(const typename std::list<std::shared_ptr<T>>::iterator &, const typename std::list<std::shared_ptr<T>>::const_iterator &);
					~PolymorphicListIterator();
				public:
					T &operator * ();
					T *operator -> ();
					const T &operator * () const;
					const T *operator -> () const;
				public:
					PolymorphicListIterator<T> &operator ++();
					PolymorphicListIterator<T> &operator --();
					PolymorphicListIterator<T> &operator ++(int);
					PolymorphicListIterator<T> &operator --(int);
					const PolymorphicListIterator<T> &operator ++() const;
					const PolymorphicListIterator<T> &operator --() const;
					const PolymorphicListIterator<T> &operator ++(int) const;
					const PolymorphicListIterator<T> &operator --(int) const;
					bool operator == (const PolymorphicListIterator<T> &) const;
					bool operator != (const PolymorphicListIterator<T> &) const;
				private:
					typename std::list<std::shared_ptr<T>>::iterator _me;
			};
		}
	}

#	include "PolymorphicListIterator.impl.hh"

#endif
