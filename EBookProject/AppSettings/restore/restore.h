#ifndef RESTORE_H
#define RESTORE_H

#include <QMainWindow>
#include<QPaintEvent>
#include<QMouseEvent>
#include<QPainter>

class Restore : public QMainWindow
{
    Q_OBJECT
public:
    explicit Restore(QWidget *parent = 0);
    ~Restore();
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void init();

signals:

public slots:
};

#endif // RESTORE_H
