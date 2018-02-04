#include "privatemessage.h"

PrivateMessage::PrivateMessage(const QString &sender, const QDateTime &timestamp)
    : Message(sender, timestamp) {

}

QByteArray PrivateMessage::data() const {

}
