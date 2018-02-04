#ifndef IMAGEMESSAGE_H
#define IMAGEMESSAGE_H
#include "message.h"

class ImageMessage : public Message {
public:
    /**
     * @brief ImageMessage constructor
     * @param sender the sender of this message
     * @param timestamp the creation or received time of this message
     */
    ImageMessage(const QString &sender, const QByteArray &img, const QDateTime &timestamp = QDateTime::currentDateTime());
    /**
     * @brief data convert data to the format required by the network.
     * @return a QByteArray containing a network compatible representation of this ImageMessage.
     */
    QByteArray data() const override;

    QByteArray img() const;
private:
    QByteArray _img;
};

#endif // IMAGEMESSAGE_H
