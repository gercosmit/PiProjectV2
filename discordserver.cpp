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
    for (auto channel : channelArray)
    {
        if (!channel.toObject()["id"].isNull() && !channel.toObject()["name"].isNull())
        {
            channels.append(DiscordChannel(channel.toObject()["id"].toString(), channel.toObject()["name"].toString()));
        }
    }
}

void DiscordServer::FillChannels(QJsonArray memberArray)
{
    for (auto member : memberArray)
    {
        if (!member.toObject()["username"].isNull() && !member.toObject()["channel_id"].isNull() && !member.toObject()["status"].isNull())
        {
            for (auto &channel : channels)
            {
                if (channel.id == member.toObject()["channel_id"].toString())
                {
                    channel.AddUser(DiscordUser(member.toObject()["username"].toString(), member.toObject()["status"].toString()));
                }
            }
        }
    }
}
