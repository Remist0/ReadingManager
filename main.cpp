#include <iostream>
#include <string>

#include "ReadingManager.h"
#include "Utils/TestRunner.h"


void ReadingManagerTest()
{
	CourseraModernCPP::ReadingManager manager;
	ASSERT_EQUAL(manager.Cheer(1), 0.0f);
	manager.Read(1, 10);
	ASSERT_EQUAL(manager.Cheer(1), 1.0f);
	manager.Read(2, 5);
	ASSERT_EQUAL(manager.Cheer(1), 1.0f);
	ASSERT_EQUAL(manager.Cheer(2), 0.0f);
	manager.Read(2, 10);
	ASSERT_EQUAL(manager.Cheer(1), 0.0f);
	ASSERT_EQUAL(manager.Cheer(2), 0.0f);
	manager.Read(3, 5);
	ASSERT_EQUAL(manager.Cheer(1), 0.5f);
	ASSERT_EQUAL(manager.Cheer(2), 0.5f);
	ASSERT_EQUAL(manager.Cheer(3), 0.0f);
}


int main()
{
	{
		CourseraModernCPP::TestRunner tr;
		RUN_TEST(tr, ReadingManagerTest);
	}

	{
		CourseraModernCPP::ReadingManager manager;

		uint32_t queryCount;
		std::cin >> queryCount;

		for (uint32_t queryIdx = 0; queryIdx < queryCount; ++queryIdx)
		{
			std::string queryType;
			std::cin >> queryType;
			uint32_t userId;
			std::cin >> userId;

			if (queryType == "READ")
			{
				int pageCount;
				std::cin >> pageCount;
				manager.Read(userId, pageCount);
			}
			else if (queryType == "CHEER")
			{
				std::cout << manager.Cheer(userId) << std::endl;
			}
		}
	}

	return 0;
}