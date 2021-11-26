#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QDesktopServices>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_createroom_clicked();
    void proc_login_reply();

    void on_register_2_clicked();
    
    void on_follow_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager m_access_mng;
    QNetworkReply *m_reply = NULL;
    enum login_opt{
            create_room,follow_room,change_password
        } m_cur_opt;
    
private:
    void Req_login();
    void Req_login(QString _opt);
    void Req_login(QString _opt, QString _room_no);
};

#endif // MAINWINDOW_H
