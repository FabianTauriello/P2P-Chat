#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "./Networking/client.h"
#include "message.h"
#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>
#include "imagedialog.h"
#include "profiledialog.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0);
    ~ChatWindow();

public slots:
    void handleMessage(QSharedPointer<Message> message);

    void appendMessage(const QString &from, const QString &message);

private slots:
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);

    void on_sendButton_clicked();

    void on_startButton_clicked();

    void on_testMessageButton_clicked();

    void on_editMyProfileButton_clicked();

    void on_pictureButton_clicked();

    //void setSelectedImage(bool selected);
    void setFileName(QString &fileName);
    QString fileName() const;
    void setReceivedMessage(const QSharedPointer<Message> &receivedMessage);
    QSharedPointer<Message> receivedMessage() const;

    void on_openImageButton_clicked();

private:
    Ui::ChatWindow *ui;
    ImageDialog *imageDialog;
    ProfileDialog *profileDialog;

    p2pnetworking::Client client;
    QStringList chatHistory;
    QStringListModel historyModel;

    QString _fileName;
    //bool _imageSelected = false;
    QSharedPointer<Message> _receivedMessage;
};

#endif // CHATWINDOW_H
