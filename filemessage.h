#ifndef FILEMESSAGE_H
#define FILEMESSAGE_H
#include "message.h"

class FileMessage : public Message {
public:
    /**
     * @brief FileMessage constructor
     * @param sender the sender of this message
     * @param timestamp the creation or received time of this message
     */
    FileMessage(const QString &sender, const QDateTime &timestamp = QDateTime::currentDateTime());
    /**
     * @brief data convert data to the format required by the network.
     * @return a QByteArray containing a network compatible representation of this FileMessage.
     */
    QByteArray data() const override;
};

#endif // FILEMESSAGE_H
