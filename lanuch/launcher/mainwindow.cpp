#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_createroom_clicked()
{
   m_cur_opt = create_room;
   Req_login("create_room");
}

void MainWindow::proc_login_reply()
{
    QJsonDocument json_doc = QJsonDocument::fromJson(m_reply->readAll());
    QJsonObject json = json_doc.object();
    if(json["login_result"].toString() == "OK") {
        // qDebug() << "login success";
        if(m_cur_opt == create_room) {
            QProcess pro;
            QStringList argv;
            int room_no = json["room_no"].toInt();

            QMessageBox::information(this, "房间号", "房间号 : " + QString::number(room_no));
            argv.push_back(json["server_IP"].toString());
            argv.push_back(json["server_PORT"].toString());
            pro.startDetached("client.exe", argv, ".");
            qApp->exit();
        }
        else if(m_cur_opt == follow_room) {
            if(json["follow_result"].toString() == "OK") {
                QProcess pro;
                QStringList argv;
                QString room_no = ui->room_no->text();
                argv.push_back(json["server_IP"].toString());
                argv.push_back(json["server_PORT"].toString());
                pro.startDetached("client.exe", argv, ".");
                qApp->exit();
            }
            else {
                QMessageBox::information(this, "跟房失败", "房间不存在");
            }
        }
        else if(m_cur_opt == change_password) {
            // change password
        }
    }
    else {
        QMessageBox::information(this, "登陆失败", "用户名或密码错误");
    }
}

void MainWindow::on_register_2_clicked()
{
    // 启动浏览器并访问注册界面
    QDesktopServices::openUrl(QUrl("http://192.168.153.131"));
}

void MainWindow::on_follow_clicked()
{
    m_cur_opt = follow_room;
    Req_login("follow_room", ui->room_no->text());
}


void MainWindow::Req_login()
{
    // 读出用户名和密码
    QString username = ui->username->text();
    QString password = ui->password->text();
    // 密码签名
    QCryptographicHash md5_hash(QCryptographicHash::Md5);
    md5_hash.addData(password.toUtf8());
    QString md5_password(md5_hash.result().toHex());

    // 拼登陆请求 (Json, 效率不敏感，方便调试)
    QJsonObject json;
    json["username"] = username;
    json["password"] = md5_password;

    QJsonDocument json_doc(json);
    // qDebug() << json_doc.toJson();

    QString output = json_doc.toJson();

    // 发送给登录服务器 (http -> qt网络访问库)
    QNetworkRequest req(QUrl("http://192.168.153.131/login/"));
    req.setHeader(QNetworkRequest::ContentLengthHeader, output.size());
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    m_reply = m_access_mng.post(req, output.toUtf8());
    // 异步处理登录服务器的回复 (connect 服务器回复和回复的处理函数)
    connect(m_reply, SIGNAL(finished()), this, SLOT(proc_login_reply()));
}

void MainWindow::Req_login(QString _opt)
{
    // 读出用户名和密码
    QString username = ui->username->text();
    QString password = ui->password->text();
    // 密码签名
    QCryptographicHash md5_hash(QCryptographicHash::Md5);
    md5_hash.addData(password.toUtf8());
    QString md5_password(md5_hash.result().toHex());

    // 拼登陆请求 (Json, 效率不敏感，方便调试)
    QJsonObject json;
    json["username"] = username;
    json["password"] = md5_password;

    // 将参数填入 opt 键
    json["opt"] = _opt;

    QJsonDocument json_doc(json);
    // qDebug() << json_doc.toJson();

    QString output = json_doc.toJson();

    // 发送给登录服务器 (http -> qt网络访问库)
    QNetworkRequest req(QUrl("http://192.168.153.131/login/"));
    req.setHeader(QNetworkRequest::ContentLengthHeader, output.size());
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    m_reply = m_access_mng.post(req, output.toUtf8());
    // 异步处理登录服务器的回复 (connect 服务器回复和回复的处理函数)
    connect(m_reply, SIGNAL(finished()), this, SLOT(proc_login_reply()));
}

void MainWindow::Req_login(QString _opt, QString _room_no)
{
    // 读出用户名和密码
    QString username = ui->username->text();
    QString password = ui->password->text();
    // 密码签名
    QCryptographicHash md5_hash(QCryptographicHash::Md5);
    md5_hash.addData(password.toUtf8());
    QString md5_password(md5_hash.result().toHex());

    // 拼登陆请求 (Json, 效率不敏感，方便调试)
    QJsonObject json;
    json["username"] = username;
    json["password"] = md5_password;

    // 将参数填入 opt 键
    json["opt"] = _opt;
    json["room_no"] = _room_no;

    QJsonDocument json_doc(json);
    // qDebug() << json_doc.toJson();

    QString output = json_doc.toJson();

    // 发送给登录服务器 (http -> qt网络访问库)
    QNetworkRequest req(QUrl("http://192.168.153.131/login/"));
    req.setHeader(QNetworkRequest::ContentLengthHeader, output.size());
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    m_reply = m_access_mng.post(req, output.toUtf8());
    // 异步处理登录服务器的回复 (connect 服务器回复和回复的处理函数)
    connect(m_reply, SIGNAL(finished()), this, SLOT(proc_login_reply()));
}
