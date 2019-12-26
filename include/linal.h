#pragma once

#include <vector>
#include <assert.h>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <time.h>
#include <functional>

#if defined(__cplusplus)
	#define _LINAL_BEGIN	namespace linal {
	#define _LINAL_END		}
	#define _LINAL ::linal::
#endif

_LINAL_BEGIN
	template<typename elementT>
	struct matrix
		: public _STD vector< _STD vector<elementT> >
	{
		// where [i] is column, [i][j] is column element
	public:
		typedef typename _STD vector< _STD vector<elementT> > base_t;

		matrix() _NOEXCEPT_OP(_STD is_nothrow_default_constructible<_Alloc>::value)
			: base_t()
		{	// construct empty vector
		}

		explicit matrix(const _Alloc& _Al) _NOEXCEPT
			: _Mybase(_Al)
		{
		}

		explicit matrix(size_type _Count)
			: base_t(_Count)
		{	}

		matrix(size_type _Count, const value_type& _Val)
			: base_t(_Count, _Val)
		{
		}

		matrix(size_type _Count, const value_type& _Val, const _Alloc& _Al)
			: base_t(_Count, _Val, _Al)
		{
		}

		matrix(const _Myt& _Right)
			: base_t(_Right)
		{
		}

		matrix(const _Myt& _Right, const _Alloc& _Al)
			: base_t(_Right, _Al)
		{
		}

		template<class _Iter,
			class = typename enable_if<_Is_iterator<_Iter>::value,
			void>::type>
			matrix(_Iter _First, _Iter _Last)
			: base_t(_First, _Last)
		{
		}

		template<class _Iter,
			class = typename enable_if<_Is_iterator<_Iter>::value,
			void>::type>
			matrix(_Iter _First, _Iter _Last, const _Alloc& _Al)
			: base_t(_First, _Last, _Al)
		{
		}

		matrix(_XSTD initializer_list<value_type> _Ilist,
			const _Alloc& _Al = allocator_type())
			: base_t(_STD move(_Ilist), _Al)
		{
		}

		matrix& operator=(_XSTD initializer_list<value_type> _Ilist)
		{	// assign initializer_list
			assign(_Ilist.begin(), _Ilist.end());
			return (*this);
		}
	};

	struct scalar
	{
		template<typename fIterT, typename sIterT>
		static auto vect_x_vect(fIterT fBegin, fIterT fend, sIterT sBegin, sIterT sEnd) -> decltype((*fBegin) * (*sBegin))
		{
			assert(_STD distance(fBegin, fend) == _STD distance(sBegin, sEnd));

			decltype((*fBegin) * (*sBegin)) res = 0;
			for (; fBegin != fend; ++fBegin, ++sBegin)
				res += (*fBegin) * (*sBegin);

			return res;
		}
		template<typename fIterT, typename elementT>
		static _STD vector<double> vect_x_mtx(fIterT fBegin, fIterT fend, _LINAL matrix<elementT> const &mtx)
		{
			_STD vector<double> output;
			output.reserve(mtx.size());
			for (size_t row(0); row < mtx.size(); ++row)
				output.emplace_back(vect_x_vect(fBegin, fend, mtx[row].begin(), mtx[row].end()));

			return _STD move(output);
		}
	};
_LINAL_END