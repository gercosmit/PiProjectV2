#include "discordserver.h"

DiscordServer::DiscordServer()
{

}

DiscordServer::DiscordServer(QJsonArray channelArray, QJsonArray memberArray)
{
    CreateChannels(channelArray);
    FillChannels(memberArray);
}

void DiscordServer::CreateChannels(QJsonArray channelArray)
{
    for (int channelIndex = 0; channelIndex < channelArray.size(); ++channelIndex)
    {
        QJsonObject channel = channelArray[channelIndex].toObject();
        if (!channel["id"].isNull() && !channel["name"].isNull())
        {
            channels.append(DiscordChannel(channel["id"].toString(), channel["name"].toString()));
        }
    }
}

void DiscordServer::FillChannels(QJsonArray memberArray)
{
    for (int memberIndex = 0; memberIndex < memberArray.size(); ++memberIndex)
    {
        QJsonObject member = memberArray[memberIndex].toObject();
        if (!member["username"].isNull() && !member["channel_id"].isNull() && !member["status"].isNull())
        {
            for (auto &channel : channels)
            {
                if (channel.id == member["channel_id"].toString())
                {
                    channel.AddUser(DiscordUser(member["username"].toString(), member["status"].toString()));
                }
            }
        }
    }
}
