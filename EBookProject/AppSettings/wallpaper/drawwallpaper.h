#ifndef DRAWWALLPAPER_H
#define DRAWWALLPAPER_H
#include<QPainter>
#include<QPaintEvent>
#include<QLineF>
#include<QRect>
#include"dataitem/wallpaperitem.h"
#include"utils/redefineqrect.h"

class DrawWallPaper
{
public:
    DrawWallPaper();
    ~DrawWallPaper();

    void drawHomeIcon(QPainter *painter,myQRect rect);
    void drawBackIcon(QPainter *painter,myQRect rect);
    void drawWallPapaerItem(QPainter *painter,int index);

private:
    QLineF line;
    QRect rect;

};

#endif // DRAWWALLPAPER_H
