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
/// CommandController.hpp - Wrangler header for the command controller.
/// May 20, 2021
/// https://discordcoreapi.com
/// \file CommandController.hpp

#pragma once

#include <discordcoreapi/FoundationEntities.hpp>
#include <discordcoreapi/CoRoutine.hpp>

namespace DiscordCoreAPI {

	/// \brief A class for handling commands from user input.
	class DiscordCoreAPI_Dll CommandController {
	  public:
		CommandController(DiscordCoreClient*);

		/// \brief Registers a function to be called.
		/// \param functionNames A vector of strings to be accepted as function names.
		/// \param baseFunction A unique_ptr to the function to be called.
		void registerFunction(const std::vector<std::string>& functionNames, std::unique_ptr<BaseFunction> baseFunction);

		/// \brief For returning the contained map of functions.
		/// \returns A map containing the function names as well as unique_ptrs to the functions.
		std::map<std::vector<std::string>, std::unique_ptr<BaseFunction>>& getFunctions();

		CoRoutine<void> checkForAndRunCommand(CommandData commandData);

	  protected:
		DiscordCoreClient* discordCoreClient{ nullptr };

		std::unique_ptr<BaseFunction> createFunction(const std::string& functionName);

		std::unique_ptr<BaseFunction> getCommand(const std::string& commandName);
	};

};// namespace DiscordCoreAPI
