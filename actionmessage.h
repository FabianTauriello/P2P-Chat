#ifndef ACTIONMESSAGE_H
#define ACTIONMESSAGE_H
#include "message.h"

class ActionMessage : public Message {
public:
    /**
     * @brief ActionMessage constructor
     * @param sender the sender of this message
     * @param timestamp the creation or received time of this message
     */
    ActionMessage(const QString &sender, const QDateTime &timestamp = QDateTime::currentDateTime());
    /**
     * @brief data convert data to the format required by the network.
     * @return a QByteArray containing a network compatible representation of this ActionMessage.
     */
    QByteArray data() const override;
};

#endif // ACTIONMESSAGE_H
