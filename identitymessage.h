#ifndef IDENTITYMESSAGE_H
#define IDENTITYMESSAGE_H
#include "message.h"


class IdentityMessage : public Message {
public:
    /**
     * @brief IdentityMessage constructor
     * @param sender the sender of this message
     * @param timestamp the creation or received time of this message
     */
    IdentityMessage(const QString &sender, const QDateTime &timestamp = QDateTime::currentDateTime());
    /**
     * @brief data convert data to the format required by the network.
     * @return a QByteArray containing a network compatible representation of this IdentityMessage.
     */
    QByteArray data() const override;
};

#endif // IDENTITYMESSAGE_H
