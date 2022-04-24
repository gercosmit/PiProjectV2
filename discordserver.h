#ifndef DISCORDCHANNEL_H
#define DISCORDCHANNEL_H

#include <QJsonArray>
#include <QJsonObject>
#include <QList>

class DiscordUser
{
public:
    DiscordUser(QString username, QString status) :
        username(username),
        status(status)
    {};
    QString username;
    QString status;
};

class DiscordChannel
{
public:
    DiscordChannel(QString id, QString name) :
        id(id),
        name(name)
    {};
    QString id;
    QString name;
    void AddUser(DiscordUser user) { users.append(user); }
    int Size() { return users.size(); }
    QList<DiscordUser> users;
};

class DiscordServer
{
public:
    DiscordServer();
    DiscordServer(QJsonArray channelArray, QJsonArray memberArray);
    int AmountOfChannels() { return channels.size(); }
    QList<DiscordChannel> channels;
private:
    void CreateChannels(QJsonArray channelArray);
    void FillChannels(QJsonArray memberArray);
};

#endif // DISCORDCHANNEL_H
