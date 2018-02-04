#include "textmessage.h"
#include <iostream>

TextMessage::TextMessage(const QString &sender, const QString &message, const QDateTime &timestamp)
    : Message(sender, timestamp), _message(message) {
}

QByteArray TextMessage::data() const {
  // The data across the network must start with the type identifier
  QByteArray data = QByteArray::number(Message::TextMessage);
  // then a separator
  data += Message::Separator;
  // Then the data required for the message type.
  data += _message.toUtf8(); // Use QString::toUtf8() to encode all strings for sending.

  //std::cout << "Inside TextMessage data method. Data = " << data.toStdString() << std::endl;
  return data;
}

QString TextMessage::message() const {
  return _message;
}
