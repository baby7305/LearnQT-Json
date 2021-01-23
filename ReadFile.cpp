#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

#include <QSysInfo>

#include <cstdlib>
#include <iostream>

using std::cout;

int main( int argc, char *argv[] ) {
    // Qt的一个宏，消除未使用变量的警告，无实际作用
    // 定义为，#define Q_UNUSED(x) (void)x
    Q_UNUSED( argc );
    Q_UNUSED( argv );

    // 如果当前操作系统为windows系统的话
    // 修改控制台的编码为utf8，防止中文乱码
    if ( QSysInfo::productType() == "windows" ||
         QSysInfo::productType() == "winrt" ) {
        system( "chcp 65001" );
    }

    cout << "当前使用的操作系统类型为：";
    cout << QSysInfo::productType().toStdString() << "\n";
    // 默认打开的文件位置为用户桌面的test.txt文件。
    QFile file( QDir::homePath() + "/Desktop/test.json" );
    if ( !file.open( QIODevice::ReadWrite ) ) {
        cout << "文件打开失败!\n";
        exit( 1 );
    }
    cout << "文件打开成功\n";

    QJsonParseError jsonParserError;
    QJsonDocument   jsonDocument =
        QJsonDocument::fromJson( file.readAll(), &jsonParserError );

    if ( !jsonDocument.isNull() &&
         jsonParserError.error == QJsonParseError::NoError ) {
        cout << "文件解析成功\n";
        if ( jsonDocument.isObject() ) {
            QJsonObject jsonObject = jsonDocument.object();
            if ( jsonObject.contains( "postsNum" ) &&
                 jsonObject.value( "postsNum" ).isDouble() ) {
                cout << "postsNum is " << jsonObject.value( "postsNum" ).toInt()
                     << "\n";
            }

            if ( jsonObject.contains( "posts" ) &&
                 jsonObject.value( "posts" ).isArray() ) {
                QJsonArray jsonArray = jsonObject.value( "posts" ).toArray();
                for ( int i = 0; i < jsonArray.size(); i++ ) {
                    if ( jsonArray[ i ].isObject() ) {
                        QJsonObject jsonObjectPost = jsonArray[ i ].toObject();
                        if ( jsonObjectPost.contains( "postID" ) &&
                             jsonObjectPost.contains( "postTitle" ) &&
                             jsonObjectPost.contains( "postContent" ) &&
                             jsonObjectPost.value( "postID" ).isDouble() &&
                             jsonObjectPost.value( "postTitle" ).isString() &&
                             jsonObjectPost.value( "postContent" )
                                 .isString() ) {
                            cout << "posts[" << i << "] :\n";
                            cout << "postID is "
                                 << jsonObjectPost.value( "postID" ).toInt()
                                 << "\n";
                            cout << "postTitle is "
                                 << jsonObjectPost.value( "postTitle" )
                                        .toString()
                                        .toStdString()
                                 << "\n";
                            cout << "postContent is "
                                 << jsonObjectPost.value( "postContent" )
                                        .toString()
                                        .toStdString()
                                 << "\n";
                        }
                    }
                }
            }
        }
    }

    file.close();
    cout << "按任意键退出程序\n";

    return 0;
}