#ifndef PRIVATEMESSAGE_H
#define PRIVATEMESSAGE_H
#include "message.h"

class PrivateMessage : public Message {
public:
    /**
     * @brief PrivateMessage constructor
     * @param sender the sender of this message
     * @param timestamp the creation or received time of this message
     */
    PrivateMessage(const QString &sender, const QDateTime &timestamp = QDateTime::currentDateTime());
    /**
     * @brief data convert data to the format required by the network.
     * @return a QByteArray containing a network compatible representation of this PrivateMessage.
     */
    QByteArray data() const override;
};

#endif // PRIVATEMESSAGE_H
