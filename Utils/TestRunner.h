#pragma once

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>


namespace CourseraModernCPP {

	// Simple testing system.

	class TestRunner
	{
	public:
		template <class TestFunc>
		void RunTest(TestFunc func, const std::string& testName)
		{
			try
			{
				func();
				std::cerr << testName << " OK" << std::endl;
			}
			catch (std::exception& e)
			{
				++m_failNum;
				std::cerr << testName << " fail: " << e.what() << std::endl;
			}
			catch (...)
			{
				++m_failNum;
				std::cerr << "Unknown exception caught" << std::endl;
			}
		}

		~TestRunner()
		{
			if (m_failNum > 0)
			{
				std::cerr << m_failNum << " unit tests failed. Terminate" << std::endl;
				exit(1);
			}
		}

	private:
		int m_failNum = 0;
	};

	template <class T>
	std::ostream& operator << (std::ostream& os, const std::vector<T>& s)
	{
		os << "{";
		bool first = true;
		for (const auto& x : s)
		{
			if (!first)
			{
				os << ", ";
				first = false;
			}
			os << x;
		}
		return os << "}";
	}

	template <class T>
	std::ostream& operator << (std::ostream& os, const std::set<T>& s)
	{
		os << "{";
		bool first = true;
		for (const auto& x : s)
		{
			if (!first)
			{
				os << ", ";
				first = false;
			}
			os << x;
		}
		return os << "}";
	}

	template <class K, class V>
	std::ostream& operator << (std::ostream& os, const std::map<K, V>& m)
	{
		os << "{";
		bool first = true;
		for (const auto& kv : m)
		{
			if (!first)
			{
				os << ", ";
				first = false;
			}
			os << kv.first << ": " << kv.second;
		}
		return os << "}";
	}

	template<class T, class U>
	void AssertEqual(const T& t, const U& u, const std::string& hint)
	{
		if (!(t == u))
		{
			std::ostringstream os;
			os << "Assertion failed: " << t << " != " << u;
			if (!hint.empty())
				os << " hint: " << hint;
			throw std::runtime_error(os.str());
		}
	}

	inline void Assert(bool b, const std::string& hint)
	{
		AssertEqual(b, true, hint);
	}
}

#define ASSERT_EQUAL(x, y) {													\
	std::ostringstream __assert_equal_private_oss;								\
	__assert_equal_private_oss													\
	<< #x << " != " << #y << ", "												\
	<< __FILE__ << ":" << __LINE__;												\
	CourseraModernCPP::AssertEqual(x, y, __assert_equal_private_oss.str());		\
}

#define ASSERT(x) {														\
	std::ostringstream __assert_equal_private_oss;						\
	__assert_equal_private_oss << #x << " is false, "					\
	<< __FILE__ << ":" << __LINE__;										\
	CourseraModernCPP::Assert(x, __assert_equal_private_oss.str());		\
}

#define RUN_TEST(tr, func)	\
	tr.RunTest(func, #func)

