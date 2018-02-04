#include "actionmessage.h"

ActionMessage::ActionMessage(const QString &sender, const QDateTime &timestamp)
    : Message(sender, timestamp) {

}

QByteArray ActionMessage::data() const {

}
