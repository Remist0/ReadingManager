#include "ReadingManager.h"
#include "Utils/Profiler.h"

using namespace CourseraModernCPP;


void ReadingManager::Read(uint32_t userId, uint32_t pageCount)
{
	//LOG_DURATION("ReadingManager::Read");

	if (pageCount >= kMaxPages)
	{
		std::cerr << "Incorrect pageCount for user with id [" << userId << "]" << std::endl;
		return;
	}

	if (!m_userToPage.count(userId))
		m_userToPage.insert({userId, pageCount});
	else
		m_pageToUsers[m_userToPage[userId]].erase(userId);

	m_pageToUsers[pageCount].insert(userId);
	m_userToPage[userId] = pageCount;

	UpdateScores();
}


float ReadingManager::Cheer(uint32_t userId) const
{
	//LOG_DURATION("ReadingManager::Cheer");

	if (!m_userToPage.count(userId))
		return 0.0f;
	else if (m_userToPage.size() == 1)
		return 1.0f;

	return m_pageScores[m_userToPage.at(userId)];
}


void ReadingManager::UpdateScores()
{
	//LOG_DURATION("ReadingManager::UpdateScores");

	const uint32_t userNum = m_userToPage.size();
	// Special cases in Cheer() for this.
	if (userNum == 0 || userNum == 1)
		return;

	uint32_t loosers = 0;
	auto GetScore = [&](uint32_t pageId) -> float
	{
		if (userNum == 1)
			return 1;

		// We shouldn't count user itself, so subtract 1.
		float result = (float)loosers / (userNum - 1);
		loosers += m_pageToUsers[pageId].size();

		return result;
	};
	m_pageScores.clear();
	m_pageScores.resize(kMaxPages);
	for (int i = 0; i < kMaxPages; ++i)
		m_pageScores[i] = GetScore(i);
}