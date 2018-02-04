#include "imagemessage.h"
#include <iostream>

ImageMessage::ImageMessage(const QString &sender, const QByteArray &img, const QDateTime &timestamp)
    : Message(sender, timestamp), _img{img} {
}

QByteArray ImageMessage::data() const {
    QByteArray data = QByteArray::number(Message::ImageMessage);
    data += Message::Separator;
    data += _img;
    //std::cout << "Inside ImageMessage data method. Data = " << data.toStdString();
    return data;
}

QByteArray ImageMessage::img() const{
    return _img;
}
