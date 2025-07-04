#include "utility.h"
#include <hash-library/md5.h>

namespace slavetats_ng
{
	namespace utility
	{
		static std::vector<std::int32_t> systemTimeToVector(SYSTEMTIME& localTime)
		{
			return {
				localTime.wYear,
				localTime.wMonth,
				localTime.wDayOfWeek + 1,
				localTime.wDay,
				localTime.wHour,
				localTime.wMinute,
				localTime.wSecond,
				localTime.wMilliseconds
			};
		}

		System::System() {
			SYSTEMTIME localTime;
			GetLocalTime(&localTime);
			_last_save_time = localTime;
		}

		void System::set_last_save_time()
		{
			SYSTEMTIME localTime;
			GetLocalTime(&localTime);
			_last_save_time = localTime;
		}

		std::vector<std::int32_t> System::get_last_save_time()
		{
			return systemTimeToVector(_last_save_time);
		}

		std::vector<std::int32_t> System::get_time_since_last_save()
		{
			SYSTEMTIME lastST, currentST, diffST, resultST;
			FILETIME   lastFT, currentFT, diffFT;
			ULARGE_INTEGER lastUL, currentUL, diffUL;
			
			lastST = _last_save_time;

			GetLocalTime(&currentST);
			SystemTimeToFileTime(&currentST, &currentFT);
			currentUL.LowPart = currentFT.dwLowDateTime;
			currentUL.HighPart = currentFT.dwHighDateTime;
			
			SystemTimeToFileTime(&lastST, &lastFT);
			lastUL.LowPart = lastFT.dwLowDateTime;
			lastUL.HighPart = lastFT.dwHighDateTime;

			auto diff = currentUL.QuadPart - lastUL.QuadPart;
			diffUL.QuadPart = diff;
			diffFT.dwLowDateTime = diffUL.LowPart;
			diffFT.dwHighDateTime = diffUL.HighPart;
			FileTimeToSystemTime(&diffFT, &diffST);

			resultST = lastST;
			resultST.wHour = diffST.wHour;
			resultST.wMinute = diffST.wMinute;
			resultST.wSecond = diffST.wSecond;
			resultST.wMilliseconds = diffST.wMilliseconds;

			return systemTimeToVector(resultST);
		}
	
		std::string System::md5_hash(const std::string& a_filename)
		{
			std::ifstream file;
			std::istream* input = NULL;
			const size_t  buffer_size = 144 * 7 * 1024;
			char*         buffer = new char[buffer_size];
			MD5           digest;

			file.open(a_filename.c_str(), std::ios::in | std::ios::binary);
			if (!file) {
				logger::info("Could not open '{}'", a_filename);
				return std::string();
			}
			input = &file;
			while (*input) {
				input->read(buffer, buffer_size);
				std::size_t num_read = size_t(input->gcount());
				digest.add(buffer, num_read);
			}
			file.close();
			delete[] buffer;
			return digest.getHash();
		}
	}





}
