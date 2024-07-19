#include "dashboard.h"
#include "login_dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 创建登录对话框
    LoginDialog loginDialog;

    // 如果登录成功，则显示Dashboard窗口
    if (loginDialog.exec() == QDialog::Accepted) {
        Dashboard app;
        app.show();
        return a.exec();
    }

    // 如果登录失败或者取消，程序退出
    return 0;
}
