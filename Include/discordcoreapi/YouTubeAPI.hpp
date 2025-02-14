/*
	DiscordCoreAPI, A bot library for Discord, written in C++, and featuring explicit multithreading through the usage of custom, asynchronous C++ CoRoutines.

	Copyright 2021, 2022 Chris M. (RealTimeChris)

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
	USA
*/
/// YouTubeAPI.hpp - Header for the YouTube API related stuff.
/// Jun 30, 2021
/// https://discordcoreapi.com
/// \file YouTubeAPI.hpp

#pragma once

#include <discordcoreapi/FoundationEntities.hpp>
#include <discordcoreapi/AudioDecoder.hpp>
#include <discordcoreapi/CoRoutine.hpp>

namespace DiscordCoreInternal {

	class DiscordCoreAPI_Dll YouTubeRequestBuilder {
	  public:
		YouTubeRequestBuilder() noexcept = default;

	  protected:
		static std::string apiKey;
		DiscordCoreAPI::ConfigManager* configManager{ nullptr };
		std::string baseUrl{ "https://www.youtube.com" };
		HttpsClient* httpsClient{ nullptr };

		DiscordCoreAPI::Song constructDownloadInfo(DiscordCoreAPI::Song& newSong, int32_t currentRecursionDepth);

		std::vector<DiscordCoreAPI::Song> collectSearchResults(const std::string& string);

		DiscordCoreAPI::Song collectFinalSong(DiscordCoreAPI::Song& newSong);

		std::string collectApiKey();
	};

	class DiscordCoreAPI_Dll YouTubeAPI : public YouTubeRequestBuilder {
	  public:
		YouTubeAPI(DiscordCoreAPI::ConfigManager*, HttpsClient* httpsClient, const DiscordCoreAPI::Snowflake guildId);

		void weFailedToDownloadOrDecode(const DiscordCoreAPI::Song& newSong, std::stop_token token, int32_t currentReconnectTries);

		void downloadAndStreamAudio(const DiscordCoreAPI::Song& newSong, std::stop_token token, int32_t currentReconnectTries);

		std::vector<DiscordCoreAPI::Song> searchForSong(const std::string& searchQuery);

		DiscordCoreAPI::Song collectFinalSong(DiscordCoreAPI::Song& newSong);

	  protected:
		DiscordCoreAPI::Snowflake guildId{};
		const int32_t maxBufferSize{ 8192 };
		DiscordCoreAPI::Song theSong{};
	};

};// namespace DiscordCoreAPI
