#include "login_dialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Neusoft Vehicle Central Control System");

    QLabel *labelTitle = new QLabel("Neusoft VCCS", this);
    labelTitle->setAlignment(Qt::AlignCenter);
    labelTitle->setStyleSheet("font-size: 24px; font-weight: bold;");

    QLabel *labelAccount = new QLabel("Account:", this);
    lineEditAccount = new QLineEdit(this);

    QLabel *labelPassword = new QLabel("Password:", this);
    lineEditPassword = new QLineEdit(this);
    lineEditPassword->setEchoMode(QLineEdit::Password);

    labelError = new QLabel(this);
    labelError->setStyleSheet("color: red;");

    QPushButton *buttonLogin = new QPushButton("Login", this);
    QPushButton *buttonCancel = new QPushButton("Cancel", this);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(labelAccount, lineEditAccount);
    formLayout->addRow(labelPassword, lineEditPassword);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonLogin);
    buttonLayout->addWidget(buttonCancel);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(labelTitle);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(labelError);
    mainLayout->addLayout(buttonLayout);

    connect(buttonLogin, &QPushButton::clicked, this, &LoginDialog::handleLogin);
    connect(buttonCancel, &QPushButton::clicked, this, &LoginDialog::handleCancel);
}

void LoginDialog::handleLogin()
{
    QString account = lineEditAccount->text();
    QString password = lineEditPassword->text();

    if (account == "admin" && password == "1234") {
        accept();
    } else {
        labelError->setText("Account or password error!");
    }
}

void LoginDialog::handleCancel()
{
    reject();
}
