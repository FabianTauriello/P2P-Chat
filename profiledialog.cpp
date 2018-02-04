#include "profiledialog.h"
#include "ui_profiledialog.h"
#include <iostream>
#include <QFileDialog>

ProfileDialog::ProfileDialog(const QString nickname, QString location, QString timeZone, QWidget *parent)
    : QDialog(parent), _nickname(nickname), _location(location), _timeZone(timeZone), ui(new Ui::ProfileDialog) {
    ui->setupUi(this);
    setWindowTitle("Edit Profile");
    ui->profileLocation->setText(_location);
    ui->profileTimeZone->setText(_timeZone);
    ui->profileLocation->setEnabled(false);
    ui->profileTimeZone->setEnabled(false);
}

ProfileDialog::~ProfileDialog() {
    delete ui;
}

void ProfileDialog::setProfileNickname(const QString nickname) {
    ui->profileNickname->setText(nickname);
    _nickname = nickname;
}

void ProfileDialog::setLocation(QString location) {
    _location = location;
}

void ProfileDialog::setTimeZone(QString timeZone) {
    _timeZone = timeZone;
}

QString ProfileDialog::nickname() const {
    return _nickname;
}

QString ProfileDialog::location() const {
    return _location;
}

QString ProfileDialog::timeZone() const {
    return _timeZone;
}

void ProfileDialog::setProfilePicture(const QImage &img) {
    ui->profilePicture->setPixmap(QPixmap::fromImage(img));
}

void ProfileDialog::on_editLocationButton_clicked() {
    ui->profileLocation->setEnabled(true);
}

void ProfileDialog::on_editTimeZoneButton_clicked() {
    ui->profileTimeZone->setEnabled(true);
}

void ProfileDialog::on_buttonBox_accepted() {
    ui->profileLocation->setEnabled(false);
    ui->profileTimeZone->setEnabled(false);

    _location = ui->profileLocation->text();
    ui->profileLocation->setText(_location);
    _timeZone = ui->profileTimeZone->text();
    ui->profileTimeZone->setText(_timeZone);
}

void ProfileDialog::on_editProfilePictureButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Choose A New Profile Picture...", "", tr("Images (*.png)"));
    if (QString::compare(fileName, QString()) != 0) {
        // picture selected
        QImage profileImage;
        profileImage.load(fileName);
        ui->profilePicture->setPixmap(QPixmap::fromImage(profileImage));
    }
}
