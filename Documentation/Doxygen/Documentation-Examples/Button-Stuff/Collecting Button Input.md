Collecting Button Input {#collectingbuttoninput}
============
- After creating a button, create an object of the `DiscordCoreAPI::ButtonCollector` class, passing into its constructor the `DiscordCoreAPI::InputEventData` that resulted from the call to `DiscordCoreAPI::InputEvents::respondToInputEventAsync`, when the button was created.
- Call the `DiscordCoreAPI::ButtonCollector::collectButtonData()` function from the instance of the ButtonCollector. NOTE: The arguments for this function are as follows:  
`getButtonDataForAllNew` = Whether or not it accepts button presses from everyone or just the individual selected with the `targetUser` argument.   
`maxWaitTimeInMsNew` = The maximum number of milliseconds that the collector will wait for button presses.   
`maxNumberOfPressesNew` = The maximum number of button presses that the collector will collect.   
`targetUser` = The target user, if `getButtonDataForAllNew` is disabled.
- Collect a result of type `std::vector<DiscordCoreAPI::ButtonResponseData>` and deal with the button responses as you see fit! Keep in mind that you could set up a voting message by using `getButtonDataForAllNew` and having multiple presses allowed.
```cpp
/// Test.hpp-Header for the "test" command.
/// https://github.com/RealTimeChris/DiscordCoreAPI

#pragma once

#include "Index.hpp"

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
			DiscordCoreAPI::InputEvents::deleteInputEventResponseAsync(args.eventData).get();

			DiscordCoreAPI::RespondToInputEventData dataPackage {args.eventData};
			dataPackage.addButton(false, "test_button", "Test Button", "✅", DiscordCoreAPI::ButtonStyle::Danger);
			dataPackage.addContent("Test Response");
			dataPackage.addMessageEmbed(EmbedData {.description = "TESTING!", .title = "Test Title"});
			dataPackage.type = DiscordCoreAPI::InputEventResponseType::Interaction_Response;
			auto inputEventData = InputEvents::respondToInputEventAsync(dataPackage).get();

			DiscordCoreAPI::ButtonCollector buttonCollector {inputEventData};
			auto results = buttonCollector.collectButtonData(false, 2334, 1, "").get();
			for (auto value: results) {
				cout << value.userId << endl;
			}
			DiscordCoreAPI::InputEvents::deleteInputEventResponseAsync(inputEventData).get();
		}
	};
}
```
