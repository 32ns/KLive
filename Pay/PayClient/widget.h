#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWebSocket>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


private:
    Ui::Widget *ui;
    QWebSocket *socket = NULL;
    QTimer *connTimer = NULL;


private slots:
    void connectServer();
    void connected();
    void disconnected();
    void binaryMessageReceived(const QByteArray &message);
};

#endif // WIDGET_H
