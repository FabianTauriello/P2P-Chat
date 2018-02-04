#include "filemessage.h"

FileMessage::FileMessage(const QString &sender, const QDateTime &timestamp)
    : Message(sender, timestamp) {

}

QByteArray FileMessage::data() const {

}
