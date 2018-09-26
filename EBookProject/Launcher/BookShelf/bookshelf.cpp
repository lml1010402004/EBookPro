#include "bookshelf.h"
#include"application.h"
#include"Utils/commonutils.h"
#include<QApplication>
#include"Application/rfile.h"
#include"Application/pulldownwindow.h"




const int BOOKSHELF_X[12] = {400,500,40,120,260,380,500,130,200,270,360,430};
const int BOOKSHELF_Y[12] = {48,48,120,120,120,120,120,730,730,740,730,730};
const int BOOKSHELF_W[12] = {48,48,60,100,100,100,100,40,40,80,40,40};
const int BOOKSHELF_HE[12] = {48,48,40,40,40,40,40,40,40,40,40,40};



extern int position4[];//for figure out the book clicked.
extern int pulldownwindowrect[];

extern PulldownWindow *pulldownwindow;
extern QProcess *myprocess;
extern QList<localDirectoryItem> *twobookslist;

QString emptypath = ":/mypic/pics/circlempty";

BookShelf::BookShelf(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    this->setFixedHeight(GLOBAL_SCREEN_FIXED_HEIGHT);
    this->setFixedWidth(GLOBAL_SCREEN_FIXED_WIDTH);
    init();

}

BookShelf::~BookShelf()
{
    delete drawbookshelf,statusbar,conditonsItemlist,totalbookinfolist,currentpagebookinfolist,
            list,conditionitem,commonutils;
}

void BookShelf::init(){

    drawbookshelf = new DrawBookshelf;
    statusbar = new StatusBar(this);
    commonutils = new commonUtils;

    condition_selected_index = 3;
    targetbookindex = -1;




    conditonsItemlist = new QList<ConditionItem>;
    totalbookinfolist = new QList<localDirectoryItem>;
    currentpagebookinfolist = new QList<localDirectoryItem>;
    nineareas = new QList<QRect*>;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            myqrect = new QRect;
            myqrect->setX(position4[0]+position4[1]*j);
            myqrect->setY(position4[2]+position4[3]*i);
            myqrect->setWidth(position4[4]);
            myqrect->setHeight(position4[5]);
            nineareas->append(myqrect);
        }
    }


    list.clear();
    list.append(tr("Read"));
    list.append(tr("Name"));
    list.append(tr("Time"));
    list.append(tr("Author"));
    for(int i=0;i<list.size();i++){
        conditionitem.setCircle_icon_path(emptypath);
        conditionitem.setText_str(list.at(i));
        conditonsItemlist->append(conditionitem);
    }

    totalbookinfolist = Database::getInstance()->getAllDataFromTouchedTable();


    total_pages = getTotalPagesForEachCondition(totalbookinfolist);
    if(total_pages>0){
        current_page = 1;
        currentpagebookinfolist =  getCurrentPageBooklist(totalbookinfolist,current_page);
    }else{
        current_page =0;
    }
    initView();
    initConnection();
}

void BookShelf::initView(){

    rectlist = new QList<myQRect*>;
    for(int i =0;i<12;i++){
        myrect = new myQRect;
        myrect->rect.setX(BOOKSHELF_X[i]);
        myrect->rect.setY(BOOKSHELF_Y[i]);
        myrect->rect.setWidth(BOOKSHELF_W[i]);
        myrect->rect.setHeight(BOOKSHELF_HE[i]);
        myrect->isPressed = false;
        RFIle::assignMacroDefinition(BOOK_SHELF_MODULE,myrect,i);
        rectlist->append(myrect);
    }

}

void BookShelf::initConnection(){
    QObject::connect(this,SIGNAL(updateDataSignal()),this,SLOT(updateDataSlot()));
}

void BookShelf::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    statusbar->drawBattery(painter,100);
    statusbar->drawWifiStatus(painter,true);
    statusbar->drawSystemTime(painter,commonUtils::getCurrentTime());
    statusbar->drawPullDownRectangle(painter);

    drawbookshelf->drawHomeButton(painter,rectlist->at(BSM_HOME_BUTTON));
    QLineF line(0,100,600,100);
    painter->drawLine(line);



    drawbookshelf->drawNineBooks(painter,currentpagebookinfolist);
    drawbookshelf->drawCurrentPageandTotalPages(painter,current_page,total_pages,rectlist->at(BSM_PAGES_CONTENT));
    drawbookshelf->drawArrangeTextView(painter,rectlist->at(BSM_TEXT),tr("Sort"));
    drawbookshelf->drawHomeButton(painter,rectlist->at(BSM_HOME_BUTTON));

    drawbookshelf->drawTheFirstandLastPageIcon(painter,rectlist->at(BSM_FIRST_PAGE),rectlist->at(BSM_LAST_PAGE));

    drawbookshelf->drawTheNextandEndPageIcon(painter,rectlist->at(BSM_NEXT_PAEG),rectlist->at(BSM_END_PAGE));

    drawbookshelf->drawSelectedCondition(painter,conditonsItemlist,condition_selected_index);
}

void BookShelf::mousePressEvent(QMouseEvent *event)
{

    int x = event->x();
    int y = event->y();
    targetwidgetindex = commonUtils::getTheTargetWidget(x,y,rectlist);
    if(targetwidgetindex>-1){
        rectlist->at(targetwidgetindex)->isPressed = true;
        if(targetwidgetindex>2&&targetwidgetindex<7){
            condition_selected_index  = targetwidgetindex;
        }
        this->repaint();
    }

    if(x>pulldownwindowrect[0]&&x<(pulldownwindowrect[0]+pulldownwindowrect[2])&&
            y<pulldownwindowrect[3]){
        if(pulldownwindow==NULL){
            pulldownwindow = new PulldownWindow(this);
        }
        pulldownwindow->show();
    }

}

void BookShelf::mouseReleaseEvent(QMouseEvent *event)
{

    if(targetwidgetindex>-1){
        rectlist->at(targetwidgetindex)->isPressed = false;
        switch (targetwidgetindex){
        case BSM_SEARCH_BUTTON:
            break;
        case BSM_HOME_BUTTON:
            this->close();
            break;
        case BSM_TEXT:

            break;
        case BSM_READ_ORDER_ITEM:
            current_page =1;
            emit updateDataSignal();
            break;
        case BSM_READ_BOOK_NAME:
            current_page =1;
            emit updateDataSignal();
            break;
        case BSM_READ_TIME:
            current_page =1;
            emit updateDataSignal();
            break;
        case BSM_READ_BOOK_AUTHOR:
            current_page =1;
            emit updateDataSignal();
            break;
        case BSM_FIRST_PAGE:
            current_page =1;
            emit updateDataSignal();
            break;
        case BSM_LAST_PAGE:
            if(current_page>1){
                current_page--;
                emit updateDataSignal();
            }
            break;
        case BSM_NEXT_PAEG:
            if(current_page<total_pages){
                current_page++;
                emit updateDataSignal();
            }
            break;
        case BSM_END_PAGE:
            current_page = total_pages;
            emit updateDataSignal();
            break;

        default:
            break;
        }
        this->repaint();
        targetwidgetindex = -1;
    }

    QString bookname = getTheTargetBookPathforFBReader(event->x(),event->y(),currentpagebookinfolist);
    if(!bookname.isEmpty()){
        if(targetbookindex>-1&&targetbookindex<9){
            commonutils->deleteAndInsertBooktoTable(currentpagebookinfolist->at(targetbookindex));
            targetbookindex = -1;
        }else{
            return;
        }
        commonutils->openBookFromFBreader(myprocess,bookname);
    }

}

void BookShelf::mouseMoveEvent(QMouseEvent *event)
{

}

QString BookShelf::getTheTargetBookPathforFBReader(int x, int y, QList<localDirectoryItem> *currentpagebookinfolist)
{
    QString bookname = "";

    for(int i=0;i<9;i++){
        if(x>nineareas->at(i)->x()&&x<nineareas->at(i)->x()+nineareas->at(i)->width()
                &&y>nineareas->at(i)->y()&&y<nineareas->at(i)->y()+nineareas->at(i)->height()){
            targetbookindex = i;
        }
    }
    if(targetbookindex>-1){
        bookname = currentpagebookinfolist->at(targetbookindex).file_path;
    }
    return bookname;
}



int BookShelf::getTotalPagesForEachCondition(QList<localDirectoryItem> *list){

    int temp =0;
    qDebug()<<"list.size()=="<<list->size();
    if(list->size()%9==0){
        temp = list->size()/9;
    }else{
        temp = list->size()/9+1;
    }

    qDebug()<<"totalpages--temp=="<<temp;
    return temp;
}


QList<localDirectoryItem>* BookShelf::getCurrentPageBooklist(QList<localDirectoryItem> *list, int currentpage){
    QList<localDirectoryItem> *temp = new QList<localDirectoryItem>;
    temp = commonUtils::getCurrentPageBooks(list,currentpage,9);//9 means max books number on each page.
    return temp;
}

void BookShelf::processFinisheds(){
    twobookslist = Database::getInstance()->getLastTwoRecordsFromTouchedTable();
}

void BookShelf::updateDataSlot(){
    totalbookinfolist->clear();
    switch (condition_selected_index) {
    case BSM_READ_ORDER_ITEM:
        totalbookinfolist = Database::getInstance()->getAllDataFromTouchedTable();
        total_pages = getTotalPagesForEachCondition(totalbookinfolist);
        break;
    case BSM_READ_BOOK_NAME:
        totalbookinfolist = Database::getInstance()->getAllDataFromTotalBooklistTable("name");
        total_pages = getTotalPagesForEachCondition(totalbookinfolist);
        break;
    case BSM_READ_TIME:
        totalbookinfolist = Database::getInstance()->getAllDataFromTotalBooklistTable("xid");
        total_pages = getTotalPagesForEachCondition(totalbookinfolist);
        break;
    case BSM_READ_BOOK_AUTHOR:
        totalbookinfolist = Database::getInstance()->getAllDataFromTotalBooklistTable("author");
        total_pages = getTotalPagesForEachCondition(totalbookinfolist);
        break;
    default:
        break;
    }
    currentpagebookinfolist = commonUtils::getCurrentPageBooks(totalbookinfolist,current_page,9);
    this->repaint();

}
