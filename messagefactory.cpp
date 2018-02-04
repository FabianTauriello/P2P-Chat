#include "messagefactory.h"
#include "textmessage.h"
#include "imagemessage.h"
#include "privatemessage.h"
#include "filemessage.h"
#include "actionmessage.h"
#include "identitymessage.h"
#include <QDebug>
#include <QFile>
#include <iostream>

MessageFactory::MessageFactory() {
}

// DATA COMING IN HERE IS NOT FILTERED - the runTest shows the format
QSharedPointer<Message> MessageFactory::create(const QString &sender, const QByteArray &data,
                                               int type) const {
//    std::cout << "In MessageFactory create function" << std::endl;
//    std::cout << "TYPE: " << type << " - ";
    switch (type) {
    case Message::TextMessage:
        // As with std::shared_ptr, a QSharedPointer to a base class can hold a derived class pointer.
        std::cout << "Data in create function (text case): " << data.toStdString() << std::endl;
        return QSharedPointer<Message>(new TextMessage(sender, QString::fromUtf8(data)));
    case Message::ImageMessage:
        //std::cout << "Data in create function (Image case): " << data.toStdString() << std::endl;
        return QSharedPointer<Message>(new ImageMessage(sender, data));
    case Message::PrivateMessage:
        std::cout << "In PrivateMessage case" << std::endl;
        return QSharedPointer<Message>(new PrivateMessage(sender));
    case Message::FileMessage:
        std::cout << "In FileMessage case" << std::endl;
        return QSharedPointer<Message>(new FileMessage(sender));
    case Message::ActionMessage:
        std::cout << "In ActionMessage case" << std::endl;
        return QSharedPointer<Message>(new ActionMessage(sender));
    case Message::IdentityMessage:
        std::cout << "In IdentityMessage case" << std::endl;
        return QSharedPointer<Message>(new IdentityMessage(sender));
    }
    return nullptr;
}

void MessageFactory::runTest() {
    QByteArray imageData;
    {
        // This reads a file from the resources.
        // See Qt documentation on The Qt Resource System.
        QFile imageFile(":/test/unisa-48px.png");
        if (imageFile.open(QIODevice::ReadOnly)) {
            imageData = imageFile.readAll();
            imageFile.close();
        }
    }
    QByteArray fileData;
    {
        // This reads a file from the resources.
        // See Qt documentation on The Qt Resource System.
        QFile file(":/test/Helpful Links.docx");
        if (file.open(QIODevice::ReadOnly)) {
            fileData = file.readAll();
            file.close();
        }
    }

    // Example data for each message type note you should always use the defined constants, not hard
    // coded strings for generating these (see TextMessage).
    QByteArray textMessageData = QByteArrayLiteral("1|Hello World!");
    QByteArray identityMessageData = QByteArrayLiteral("0|David|Adelaide|+930|") + imageData;
    QByteArray imageMessageData = QByteArrayLiteral("4|unisa.png|") + imageData;
    QByteArray fileMessageData = QByteArrayLiteral("3|Helpful Links.docx|") + fileData;
    QByteArray actionMessageData = QByteArrayLiteral("2|JOIN|David@10.1.1.10");
    QByteArray privateMessageData = QByteArrayLiteral("5|David@10.1.1.10|Hi, David!");

    MessageFactory factory;

    QByteArray data = stripTypeId(textMessageData);
    QSharedPointer<Message> textMessage = factory.create("none", data, Message::TextMessage);
    //std::cout << "TESTING DATA FOR TEXT: " << data.toStdString() << std::endl;
    data = stripTypeId(identityMessageData);
    QSharedPointer<Message> identityMessage = factory.create("none", data, Message::IdentityMessage);
    data = stripTypeId(imageMessageData);
    QSharedPointer<Message> imageMessage = factory.create("none", data, Message::ImageMessage);
    //std::cout << "TESTING DATA FOR IMAGE: " << data.toStdString() << std::endl;
    data = stripTypeId(fileMessageData);
    QSharedPointer<Message> fileMessage = factory.create("none", data, Message::FileMessage);
    data = stripTypeId(actionMessageData);
    QSharedPointer<Message> actionMessage = factory.create("none", data, Message::ActionMessage);
    data = stripTypeId(privateMessageData);
    QSharedPointer<Message> privateMessage = factory.create("none", data, Message::PrivateMessage);

    // Without a complete implementation of message types, only test can be to see if a valid pointer
    // was created by MessageFactory::create();
    if (textMessage == nullptr) {
        qDebug() << "TextMessage is not implemented in MessageFactory::create().";
    } else {

    }
    if (identityMessage == nullptr) {
        qDebug() << "IdentityMessage is not implemented in MessageFactory::create().";
    }
    if (imageMessage == nullptr) {
        qDebug() << "ImageMessage is not implemented in MessageFactory::create().";
    } else {

    }
    if (fileMessage == nullptr) {
        qDebug() << "FileMessage is not implemented in MessageFactory::create().";
    }
    if (actionMessage == nullptr) {
        qDebug() << "ActionMessage is not implemented in MessageFactory::create().";
    }
    if (privateMessage == nullptr) {
        qDebug() << "PrivateMessage is not implemented in MessageFactory::create().";
    }
}

QByteArray MessageFactory::stripTypeId(const QByteArray &array) {
    int pos = array.indexOf('|');
    return array.mid(pos + 1);
}
