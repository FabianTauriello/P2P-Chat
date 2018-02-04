#include "privatechat.h"
#include "ui_privatechat.h"

PrivateChat::PrivateChat(QWidget *parent)
    : QDialog(parent), ui(new Ui::PrivateChat) {
    ui->setupUi(this);
    setWindowTitle("Private Chat");
}

PrivateChat::~PrivateChat() {
    delete ui;
}
