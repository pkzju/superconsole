/****************************************************************************
**
** Copyright (C) 2016 pkzju
**
** Version	: 0.0.0.1
** Author	:
**
****************************************************************************/

#ifndef FLYWIDGET_H
#define FLYWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>
#include <QPainter>
#include <QMenu>
#include <QSharedPointer>


class FlyWidget : public QWidget
{
    Q_OBJECT
private:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

private:
    QPoint m_CurrentPos;
    QPixmap m_Pixmap;
public:
    QMenu* settingmenu;
public:
    explicit FlyWidget(QWidget *parent = 0);
    void initData();
    void initUI();
    void initConnect();
    void setMenu(QMenu* menu);
signals:
    void doubleClicked();
public slots:

};

#endif // FLYWIDGET_H
