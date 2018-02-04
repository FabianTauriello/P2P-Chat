#ifndef PRIVATECHAT_H
#define PRIVATECHAT_H

#include <QDialog>

namespace Ui {
class PrivateChat;
}

class PrivateChat : public QDialog {
    Q_OBJECT

public:
    explicit PrivateChat(QWidget *parent = 0);
    ~PrivateChat();

private:
    Ui::PrivateChat *ui;
};

#endif // PRIVATECHAT_H
