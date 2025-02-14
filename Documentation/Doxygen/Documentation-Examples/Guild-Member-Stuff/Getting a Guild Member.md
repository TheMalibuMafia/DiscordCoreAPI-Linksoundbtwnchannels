Getting a Guild Member {#gettingaguildmember}
============
- Execute the, from the `DiscordCoreAPI::GuildMembers::getCachedGuildMember()` (which collects it from the cache), or `DiscordCoreAPI::GuildMembers::getGuildMemberAsync()` (which collects it from the Discord servers) function, while passing to it a value of type `DiscordCoreAPI::GetGuildMemberData`.
- Call the function with `.get()` added to the end in order to wait for the results now.

```cpp
/// Test.hpp-Header for the "test" command.
/// https://github.com/RealTimeChris/DiscordCoreAPI

#pragma once

#include <Index.hpp>

namespace DiscordCoreAPI {

	class Test : public DiscordCoreAPI::BaseFunction {
	  public:
		Test() {
			this->commandName = "test";
			this->helpDescription = "Testing purposes!";
			DiscordCoreAPI::EmbedData msgEmbed;
			msgEmbed.setDescription("------\nSimply enter !test or /test!\n------");
			msgEmbed.setTitle("__**Test Usage:**__");
			msgEmbed.setTimeStamp(getTimeAndDate());
			msgEmbed.setColor("FeFeFe");
			this->helpEmbed = msgEmbed;
		}

		std::unique_ptr<DiscordCoreAPI::BaseFunction> create() {
			return std::make_unique<Test>();
		}

		virtual void execute(DiscordCoreAPI::BaseFunctionArguments& args) {
			try {
				DiscordCoreAPI::GetGuildMemberData dataPackage;
				dataPackage.guildId = args.eventData.getGuildId();
				dataPackage.guildMemberId = args.eventData.getAuthorId();

				auto guildMember01 = DiscordCoreAPI::GuildMembers::getCachedGuildMember(dataPackage).get();

				auto guildMember02 = DiscordCoreAPI::GuildMembers::getGuildMemberAsync(dataPackage).get();


			} catch (...) {
				rethrowException("Test::execute()");
			}
		}
	};
}
```
