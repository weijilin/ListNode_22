#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>

#if 0
class Date
{
	friend bool Less(Date* pLeft, Date* pRight);
public:

	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

private:
	int _year;
	int _month;
	int _day;
};


#include <queue>
#include <functional>

// 用函数指针提供比较的规则
bool Less(Date* pLeft, Date* pRight)
{
	if (pLeft->_day < pRight->_day)
		return true;

	return false;
}

typedef bool(*Compare)(Date* pLeft, Date* pRight);

int main()
{
	Date d1(2019, 9, 15);
	Date d2(2019, 9, 16);
	Date d3(2019, 9, 14);

	priority_queue<Date*, vector<Date*>, Compare> q(Less);
	q.push(&d1);
	q.push(&d2);
	q.push(&d3);
	return 0;
}
#endif

#if 0
class Date
{
	friend class Less;
public:

	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

private:
	int _year;
	int _month;
	int _day;
};


#include <queue>
#include <functional>

class Less
{
public:
	bool operator()(const Date* pLeft, const Date* pRight)
	{
		return pLeft->_day < pRight->_day;
	}
};


int main()
{
	Date d1(2019, 9, 15);
	Date d2(2019, 9, 16);
	Date d3(2019, 9, 14);

	Less min;
	min(&d1, &d2);  // 仿函数 || 函数对象---像函数调用一样的对象
	//min.operator()(&d1, &d2);

	priority_queue<Date*, vector<Date*>, Less> q;
	q.push(&d1);
	q.push(&d2);
	q.push(&d3);
	return 0;
}
#endif

#include <vector>

namespace bite
{
	template<class T, class Container = vector<T>, class Compare = less<T>>
	class priority_queue
	{
	public:
		priority_queue()
		{}

		template<class Iterator>
		priority_queue(Iterator first, Iterator last)
			: c(first, last)
		{
			int root = ((c.size() - 2) >> 1);
			for (; root >= 0; --root)
				_AdjustDown(root);
		}

		void push(const T& data)
		{
			c.push_back(data);
			_AdjustUP(c.size() - 1);
		}

		void pop()
		{
			if (empty())
				return;

			// 将堆顶元素与堆中最后一个元素进行交换
			swap(c.front(), c.back());
			c.pop_back();
			_AdjustDown(0);
		}

		size_t size()const
		{
			return c.size();
		}

		bool empty()const
		{
			return c.empty();
		}

		const T& top()const
		{
			return c.front();
		}
	private:
		// parent的左右子树已经满足堆的性质
		void _AdjustDown(int parent)
		{
			size_t child = parent * 2 + 1;
			while (child < c.size())
			{
				// 找两个孩子中较大的孩子
				Compare com;
				if (child + 1 < c.size() && com(c[child], c[child + 1]))
					child += 1;

				// 检测parent是否满足堆的性质
				if (com(c[parent], c[child]))
				{
					swap(c[parent], c[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
					return;
			}
		}

		void _AdjustUP(int child)
		{
			int parent = ((child - 1) >> 1);
			while (child)
			{
				Compare com;
				if (com(c[parent], c[child]))
				{
					swap(c[parent], c[child]);
					child = parent;
					parent = ((child - 1) >> 1);
				}
				else
					return;
			}
		}
	private:
		Container c;
	};
}

class Date
{
	friend class Less;
public:

	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

private:
	int _year;
	int _month;
	int _day;
};

class Less
{
public:
	bool operator()(const Date* pLeft, const Date* pRight)
	{
		return pLeft->_day < pRight->_day;
	}
};

#include <functional>

int main()
{
	int array[] = { 4, 2, 8, 9, 3, 7, 0, 6, 5, 1 };
	bite::priority_queue<int> q1;
	for (auto e : array)
		q1.push(e);

	bite::priority_queue<int, vector<int>, greater<int>> q2(array, array + sizeof(array) / sizeof(array[0]));


	Date d1(2019, 9, 15);
	Date d2(2019, 9, 16);
	Date d3(2019, 9, 14);
	bite::priority_queue<Date*, vector<Date*>, Less> q3;
	q3.push(&d1);
	q3.push(&d2);
	q3.push(&d3);
	return 0;
}
