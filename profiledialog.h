#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include <QDialog>

namespace Ui {
class ProfileDialog;
}

class ProfileDialog : public QDialog {
    Q_OBJECT

public:
    explicit ProfileDialog(const QString nickname, QString location, QString timeZone, QWidget *parent = 0);
    ~ProfileDialog();

    void setProfileNickname(const QString nickname);
    void setProfilePicture(const QImage &img);
    void setLocation(QString location);
    void setTimeZone(QString timeZone);

    QString location() const;
    QString timeZone() const;
    QString nickname() const;
    Ui::ProfileDialog *uidd() const;

private slots:
    void on_editLocationButton_clicked();

    void on_editTimeZoneButton_clicked();

    void on_buttonBox_accepted();

    void on_profilePicture_linkActivated(const QString &link);

    void on_pushButton_clicked();

    void on_editProfilePictureButton_clicked();

private:

    QString _nickname;
    QString _location;
    QString _timeZone;
    Ui::ProfileDialog *ui;
};

#endif // PROFILEDIALOG_H
