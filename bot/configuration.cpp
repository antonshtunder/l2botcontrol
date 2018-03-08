#include "configuration.h"

#include <QFile>
#include <QDebug>
#include <QJsonDocument>

Configuration::Configuration(BotInstance *botInstance):
    _botInstance(botInstance)
{

}

SkillUsage *Configuration::getSkillUsage(SkillRepresentation &skillRepresentation)
{
    if(!_skillUsages.contains(skillRepresentation.id))
    {
        _skillUsages[skillRepresentation.id] = std::make_shared<SkillUsage>(_botInstance, skillRepresentation);
    }
    return _skillUsages[skillRepresentation.id].get();
}

void Configuration::saveConfiguration(QString path)
{
    QFile confFile(path);
    if(confFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonDocument jsonDoc;

        QJsonObject confJson;
        QJsonArray skillUsages;

        for(auto skillUsage : _skillUsages)
        {
            skillUsages.append(skillUsage->createJsonRepresentation());
        }
        confJson.insert("skillUsages", skillUsages);

        jsonDoc.setObject(confJson);
        confFile.write(jsonDoc.toJson());
    }
    else
    {
        qDebug() << "failed to save configuration";
    }
}

void Configuration::loadConfiguration(QString path)
{
    QFile confFile(path);
    if(confFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        _skillUsages.clear();
        QJsonParseError error;
        auto jsonString = confFile.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString, &error);

        auto jsonConf = jsonDoc.object();
        auto skillUsages = jsonConf.value("skillUsages").toArray();
        for(auto skillUsage : skillUsages)
        {
            auto object = skillUsage.toObject();
            auto realSkillUsage = SkillUsage::createFromJson(object, _botInstance);
            if(realSkillUsage != NULL)
            {
                _skillUsages[realSkillUsage->getId()] = std::shared_ptr<SkillUsage>(realSkillUsage);
            }
        }
    }
    else
    {
        qDebug() << "failed to load configuration";
    }
}
