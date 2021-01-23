#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QDir>

int main(int argc, char *argv[]) {
// 以读写方式打开主目录下的1.json文件，若该文件不存在则会自动创建
    QFile file(QDir::homePath() + "/1.json");
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
    } else {
        qDebug() <<"File open!";
    }
// 使用QJsonObject对象插入键值对。
    QJsonObject jsonObject;
    jsonObject.insert("name", "tom");
    jsonObject.insert("age", "18");
    jsonObject.insert("time", QDateTime::currentDateTime().toString());

// 使用QJsonDocument设置该json对象
    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObject);

// 将json以文本形式写入文件并关闭文件。
    file.write(jsonDoc.toJson());
    file.close();

    qDebug() << "Write to file";
    return 0;
}