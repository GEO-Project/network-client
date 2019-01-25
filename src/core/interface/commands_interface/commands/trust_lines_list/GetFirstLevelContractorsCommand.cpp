#include "GetFirstLevelContractorsCommand.h"

GetFirstLevelContractorsCommand::GetFirstLevelContractorsCommand(
    const CommandUUID &uuid,
    const string& commandBuffer):

    BaseUserCommand(
        uuid,
        identifier())
{
    auto check = [&](auto &ctx) { if(_attr(ctx) == '\n'){throw ValueError("GetFirstLevelContractorsCommand: there is no input ");}};
    auto equivalent_add = [&](auto &ctx) { mEquivalent = _attr(ctx); };

    try
    {
        parse(commandBuffer.begin(), commandBuffer.end(), char_[check]);
        parse(commandBuffer.begin(), commandBuffer.end(), *(int_[equivalent_add]) > '\n');
    }
    catch (...)
    {
        throw ValueError("GetFirstLevelContractorsCommand: can't parse command");
    }
}

const string &GetFirstLevelContractorsCommand::identifier()
{
    static const string identifier = "GET:contractors";
    return identifier;
}

const SerializedEquivalent GetFirstLevelContractorsCommand::equivalent() const
{
    return mEquivalent;
}

CommandResult::SharedConst GetFirstLevelContractorsCommand::resultOk(
    string& neighbors) const
{
    return make_shared<const CommandResult>(
        identifier(),
        UUID(),
        200,
        neighbors);
}

