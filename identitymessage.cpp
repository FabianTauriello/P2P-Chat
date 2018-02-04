#include "identitymessage.h"

IdentityMessage::IdentityMessage(const QString &sender, const QDateTime &timestamp)
    : Message(sender, timestamp) {

}

QByteArray IdentityMessage::data() const {

}
