/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_THEIA_POLYMORPHICLISTITERATOR_IMPL
#	define ENTROPY_THEIA_POLYMORPHICLISTITERATOR_IMPL

#	include "PolymorphicListIterator.hh"

#	include <iterator>

	namespace Entropy
	{
		namespace Theia
		{
			template<typename T>
			PolymorphicListIterator<T>::PolymorphicListIterator(const typename std::list<std::shared_ptr<T>>::iterator &i)
				: _me(i)
			{}

			template<typename T>
			PolymorphicListIterator<T>::PolymorphicListIterator(const typename std::list<std::shared_ptr<T>>::iterator &begin, const typename std::list<std::shared_ptr<T>>::const_iterator &i)
				: _me(begin)
			{
				std::advance(_me, std::distance<typename std::list<std::shared_ptr<T>>::const_iterator>(_me, i));
			}

			template<typename T> PolymorphicListIterator<T>::~PolymorphicListIterator() = default;

			template<typename T>
			T &PolymorphicListIterator<T>::operator * ()
			{
				return *_me->get();
			}

			template<typename T>
			T *PolymorphicListIterator<T>::operator -> ()
			{
				return _me->get();
			}

			template<typename T>
			const T &PolymorphicListIterator<T>::operator * () const
			{
				return *_me->get();
			}

			template<typename T>
			const T *PolymorphicListIterator<T>::operator -> () const
			{
				return _me->get();
			}

			template<typename T>
			PolymorphicListIterator<T> &PolymorphicListIterator<T>::operator ++ ()
			{
				return ++_me;
			}

			template<typename T>
			PolymorphicListIterator<T> &PolymorphicListIterator<T>::operator -- ()
			{
				return --_me;
			}

			template<typename T>
			PolymorphicListIterator<T> &PolymorphicListIterator<T>::operator ++ (int)
			{
				return _me++;
			}

			template<typename T>
			PolymorphicListIterator<T> &PolymorphicListIterator<T>::operator -- (int)
			{
				return _me--;
			}

			template<typename T>
			const PolymorphicListIterator<T> &PolymorphicListIterator<T>::operator ++ () const
			{
				return ++_me;
			}

			template<typename T>
			const PolymorphicListIterator<T> &PolymorphicListIterator<T>::operator -- () const
			{
				return --_me;
			}

			template<typename T>
			const PolymorphicListIterator<T> &PolymorphicListIterator<T>::operator ++ (int) const
			{
				return _me++;
			}

			template<typename T>
			const PolymorphicListIterator<T> &PolymorphicListIterator<T>::operator -- (int) const
			{
				return _me--;
			}

			template<typename T>
			bool PolymorphicListIterator<T>::operator == (const PolymorphicListIterator<T> &o) const
			{
				return _me == o._me;
			}

			template<typename T>
			bool PolymorphicListIterator<T>::operator != (const PolymorphicListIterator<T> &o) const
			{
				return _me != o._me;
			}
		}
	}

#endif
