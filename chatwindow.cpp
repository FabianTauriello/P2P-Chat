#include "chatwindow.h"
#include "htmldelegate.h"
#include "messagefactory.h"
#include "textmessage.h"
#include "imagemessage.h"
#include "privatemessage.h"
#include "filemessage.h"
#include "actionmessage.h"
#include "identitymessage.h"
#include "ui_chatwindow.h"
#include "profiledialog.h"
#include "imagedialog.h"
#include <QPixmap>
#include <QBuffer>
#include <iostream>
#include <QFileDialog>

ChatWindow::ChatWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ChatWindow), imageDialog(new ImageDialog), profileDialog(new ProfileDialog("", "", "")), _fileName{""}, _receivedMessage{nullptr} {
    ui->setupUi(this);
    connect(&client, &p2pnetworking::Client::newMessage, this, &ChatWindow::handleMessage);
    connect(&client, &p2pnetworking::Client::newParticipant, this, &ChatWindow::newParticipant);
    connect(&client, &p2pnetworking::Client::participantLeft, this, &ChatWindow::participantLeft);
    ui->listView->setModel(&historyModel);
    // The HTMLDelegate allows display of HTML formatted text, a subset of HTML is supported.
    // See http://doc.qt.io/qt-5/richtext-html-subset.html - also can be found in built-in help.
    HTMLDelegate *delegate = new HTMLDelegate(this);
    ui->listView->setItemDelegate(delegate);
    ui->openImageButton->setVisible(false);
    ui->lineEdit->setPlaceholderText("Enter your message here...Please");
    //setStyleSheet("background-color: #59ffff;");
}

ChatWindow::~ChatWindow() {
    delete ui;
}

void ChatWindow::handleMessage(QSharedPointer<Message> message) {

    if (QSharedPointer<TextMessage> txt = qSharedPointerDynamicCast<TextMessage>(message)) {
        // Text message received
        appendMessage(txt->sender(), txt->message());
    } else if (QSharedPointer<ImageMessage> img = qSharedPointerDynamicCast<ImageMessage>(message)) {
        // Image message received
        setReceivedMessage(img);
        //ui->openImageButton->setVisible(true);
        appendMessage(img->sender(), "Has sent you an image!");

        //std::cout << img->data().toStdString() << std::endl;
        //std::cout << "----------------------------------------------" << std::endl;
        //std::cout << img->img().toStdString() << std::endl;

        QImage image;
        image = QImage::fromData(img->img());
        QLabel *newLabel = new QLabel(this);
        newLabel->setWindowFlag(Qt::Window);
        newLabel->setPixmap(QPixmap::fromImage(image));
        newLabel->show();
    } else if (QSharedPointer<PrivateMessage> pMsg = qSharedPointerDynamicCast<PrivateMessage>(message)) {
        // Private message received
    } else if (QSharedPointer<FileMessage> file = qSharedPointerDynamicCast<FileMessage>(message)) {
        // File message received
    } else if (QSharedPointer<ActionMessage> action = qSharedPointerDynamicCast<ActionMessage>(message)) {
        // Action message received
    } else if (QSharedPointer<IdentityMessage> identity = qSharedPointerDynamicCast<IdentityMessage>(message)) {
        // Identity message received
    }

}

void ChatWindow::appendMessage(const QString &from, const QString &message) {
    QString newLine = "<strong style=\"width:150px\">";
    newLine += from;
    newLine += ":</strong>  ";
    newLine += message;
    chatHistory << newLine;
    while (chatHistory.size() > 100) {
        chatHistory.removeFirst();
    }
    historyModel.setStringList(chatHistory);
}

void ChatWindow::newParticipant(const QString &nick) {
    ui->participantsListWidget->addItem(nick);
}

void ChatWindow::participantLeft(const QString &nick) {
    QList<QListWidgetItem *> toRemove = ui->participantsListWidget->findItems(nick, Qt::MatchExactly);
    foreach (QListWidgetItem *item, toRemove) {
        ui->participantsListWidget->removeItemWidget(item);
        delete item;
    }
}

void ChatWindow::on_sendButton_clicked() {
    // Create the shared pointer containing a TextMessage.
    QSharedPointer<TextMessage> message(new TextMessage(client.nickName(), ui->lineEdit->text()));
    // Send to all connected users
    client.sendMessage(message);
    // Display for this computer (messages from this user are not passed to this user from the
    // network) - no point sending data to yourself!
    handleMessage(message);
    ui->lineEdit->clear();

}

void ChatWindow::on_startButton_clicked() {
    std::cout << "in startButton method" << std::endl;
    client.setUserName(ui->usernameEdit->text());
    profileDialog->setProfileNickname(ui->usernameEdit->text());
    client.start();
    ui->startButton->setEnabled(false);
    ui->usernameEdit->setEnabled(false);
}

// TODO: This function and associated button is for testing purposes only, remove before submission.
void ChatWindow::on_testMessageButton_clicked() {
    std::cout << "test button pressed" << std::endl;
    MessageFactory::runTest();
}

void ChatWindow::on_editMyProfileButton_clicked() {
    profileDialog->setProfileNickname(client.nickName());
    profileDialog->exec();
}

void ChatWindow::on_pictureButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Choose An Image...", "", tr("Images (*.jpg *.png *.gif)"));
    setFileName(fileName);
    if (QString::compare(fileName, QString()) != 0) {
        // picture now selected

        //ui->lineEdit->setText(fileName);
        //setSelectedImage(true);

        QByteArray imageData;
        //imageData += fileName;
        //imageData += Message::Separator;
        QFile imageFile(fileName);
        if (imageFile.open(QIODevice::ReadOnly)) {
            imageData += imageFile.readAll();
            imageFile.close();
        }
        QSharedPointer<ImageMessage> message(new ImageMessage(client.nickName(), imageData));
        //std::cout << imageData.toStdString() << std::endl;
        client.sendMessage(message);
    }
}

void ChatWindow::setFileName(QString &fileName) {
    _fileName = fileName;
}

QString ChatWindow::fileName() const {
    return _fileName;
}

void ChatWindow::setReceivedMessage(const QSharedPointer<Message> &receivedMessage) {
    _receivedMessage = receivedMessage;
}

QSharedPointer<Message> ChatWindow::receivedMessage() const {
    return _receivedMessage;
}

//void ChatWindow::setSelectedImage(bool selected) {
//    _imageSelected = selected;
//}

void ChatWindow::on_openImageButton_clicked() {

//    QImage image;
//    std::cout << image.isNull() << std::endl;
//    image = QImage::fromData(receivedMessage()->data());
//    std::cout << image.isNull() << std::endl;

//    ui->label_2->setPixmap(QPixmap::fromImage(image));



}
