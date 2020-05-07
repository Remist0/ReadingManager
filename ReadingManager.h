#pragma once

#include <map>
#include <set>
#include <vector>

namespace CourseraModernCPP {

	// ReadingManager
	// 1) Should store readed pages for every user.
	// 2) Should "cheer" user with information how many participants he overtook.
	// 3) Should work "fast" for a big number of users (userNum >> maxPages) and "cheer" actions.

	class ReadingManager
	{
	public:
		ReadingManager() : m_pageToUsers{kMaxPages} {};

		void Read(uint32_t userId, uint32_t pageCount);
		float Cheer(uint32_t userId) const;

	private:
		static const uint32_t kMaxPages = 1000;

		std::map<uint32_t, uint32_t> m_userToPage;
		std::vector<std::set<uint32_t>> m_pageToUsers;
		std::vector<float> m_pageScores;

		void UpdateScores();
	};
}