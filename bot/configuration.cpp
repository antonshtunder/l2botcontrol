#include "configuration.h"

#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include "bot/botinstance.h"
#include "mainwindow.h"

Configuration::Configuration(BotInstance *botInstance):
    _botInstance(botInstance)
{
    _targeting = Targeting::MOB_IN_AREA;
    _attack = true;
    _pickUpItems = true;
}

SkillUsage *Configuration::getSkillUsage(SkillRepresentation &skillRepresentation)
{
    if(!_skillUsages.contains(skillRepresentation.id))
    {
        _skillUsages[skillRepresentation.id] = std::make_shared<SkillUsage>(_botInstance, skillRepresentation);
    }
    return _skillUsages[skillRepresentation.id].get();
}

QList<QPointF> &Configuration::getNodes()
{
    return _nodes;
}

void Configuration::addNode(const QPointF &node)
{
    _nodes.append(node);
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

        QJsonArray nodes;
        for(auto node : _nodes)
        {
            QJsonObject nodeObj;
            nodeObj.insert("x", node.x());
            nodeObj.insert("y", node.y());
            nodes.append(nodeObj);
        }
        confJson.insert("nodes", nodes);
        confJson.insert("attack", _attack);
        confJson.insert("pickUpItems", _pickUpItems);

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
        auto nodes = jsonConf.value("nodes").toArray();
        if(nodes.size() > 0)
            _nodes.clear();
        for(auto node : nodes)
        {
            auto nodeObj = node.toObject();
            _nodes.append({nodeObj.value("x").toDouble(), nodeObj.value("y").toDouble()});
        }
        _attack = jsonConf.value("attack").toBool();
        _pickUpItems = jsonConf.value("pickUpItems").toBool();
        MainWindow::instance()->updateUI(true);
    }
    else
    {
        qDebug() << "failed to load configuration";
    }
}

QPainterPath Configuration::getNodeArea()
{
    QPainterPath area;
    int i = 0;
    for(auto &node : _nodes)
    {
        if(i == 0)
        {
            area.moveTo(node);
        }
        else
        {
            area.lineTo(node);
        }
        ++i;
    }
    area.closeSubpath();

    return area;
}

Targeting Configuration::getTargeting() const
{
    return _targeting;
}

void Configuration::setTargeting(const Targeting &targeting)
{
    _targeting = targeting;
}

QString Configuration::getAssistPlayerName() const
{
    return _assistPlayerName;
}

void Configuration::setAssistPlayerName(const QString &assistPlayerName)
{
    _assistPlayerName = assistPlayerName;
}

QList<std::shared_ptr<ItemUsage> > &Configuration::getItemUsages()
{
    return _itemUsages;
}

void Configuration::removeItemUsage(ItemUsage *itemUsage)
{
    for(auto usage : _itemUsages)
    {
        qDebug() << "a = " << itemUsage;
        qDebug() << "b = " << usage.get();
        if(usage.get() == itemUsage)
        {
            qDebug() << "item usage removed";
            _itemUsages.removeOne(usage);
            return;
        }
    }
}

bool Configuration::getAttackingEnabled() const
{
    return _attack;
}

void Configuration::setAttackingEnabled(bool attackingEnabled)
{
    _attack = attackingEnabled;
}

bool Configuration::getPickUpItems() const
{
    return _pickUpItems;
}

void Configuration::setPickUpItems(bool pickUpItems)
{
    _pickUpItems = pickUpItems;
}
