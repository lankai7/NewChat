 #include "chatmessage.h"
#include <QFontMetrics>
#include <QPaintEvent>
#include <QDateTime>
#include <QPainter>
#include <QMovie>
#include <QLabel>
#include <QDebug>

ChatMessage::ChatMessage(QWidget *parent) : QWidget(parent)
{
    // 获取当前窗口部件的字体设置，并进行修改
    QFont te_font = this->font();
    te_font.setFamily("MicrosoftYaHei");  // 设置字体为“微软雅黑”
    te_font.setPointSize(12);             // 设置字体大小为12点
    this->setFont(te_font);               // 应用修改后的字体设置

    // 加载左侧和右侧的头像图片
    m_leftPixmap = QPixmap("://res/bak/1.jpg");
    m_rightPixmap = QPixmap("://res/bak/1.jpg");

}

void ChatMessage::setText(QString text, QString time, QSize allSize, QString id,ChatMessage::User_Type userType)
{
    m_msg = text;
    m_userType = userType;
    m_time = time;
    m_curTime = QDateTime::fromTime_t(time.toInt()).toString("ddd hh:mm");
    m_allSize = allSize;
    m_id = id;

    this->update();
}

void ChatMessage::setPicture(QPixmap pixmap, QString time, QSize allSize, QString id, ChatMessage::User_Type userType)
{
    m_msg = "";
    m_pic = pixmap;
    m_userType = userType;
    m_time = time;
    m_curTime = QDateTime::fromTime_t(time.toInt()).toString("ddd hh:mm");
    m_allSize = allSize;
    m_id = id;
    m_picRect = QRect(this->width()-allSize.width()*0.8-iconWH-iconSpaceW-iconRectW-iconTMPH,iconTMPH + 15,allSize.width()*0.8,allSize.height()*0.8);
    //painter.drawPixmap(m_picRect, m_pic);
    this->update();
}

QSize ChatMessage::fontRect(QString str = "")
{
    m_msg = str;

    m_kuangWidth = this->width() - kuangTMP - 2*(iconWH+iconSpaceW+iconRectW);
    m_textWidth = m_kuangWidth - 2*textSpaceRect;
    m_spaceWid = this->width() - m_textWidth;
    m_iconLeftRect = QRect(iconSpaceW, iconTMPH + 7, iconWH, iconWH);
    m_iconRightRect = QRect(this->width() - iconSpaceW - iconWH, iconTMPH +7, iconWH, iconWH);


    QSize size = getRealString(m_msg); // 整个的size

    qDebug() << "fontRect Size:" << size;
    int hei = size.height() < minHei ? minHei : size.height();

    m_sanjiaoLeftRect = QRect(iconWH+iconSpaceW+iconRectW, m_lineHeight/2 + 10, sanJiaoW, hei - m_lineHeight);
    m_sanjiaoRightRect = QRect(this->width() - iconRectW - iconWH - iconSpaceW - sanJiaoW, m_lineHeight/2+10, sanJiaoW, hei - m_lineHeight);

    if(size.width() < (m_textWidth+m_spaceWid)) {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3 + 10, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
        m_kuangRightRect.setRect(this->width() - size.width() + m_spaceWid - 2*textSpaceRect - iconWH - iconSpaceW - iconRectW - sanJiaoW,
                                 m_lineHeight/4*3 + 10, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
    } else {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3 + 10, m_kuangWidth, hei-m_lineHeight);
        m_kuangRightRect.setRect(iconWH + kuangTMP + iconSpaceW + iconRectW - sanJiaoW, m_lineHeight/4*3 + 10, m_kuangWidth, hei-m_lineHeight);
    }
    m_textLeftRect.setRect(m_kuangLeftRect.x()+textSpaceRect, m_kuangLeftRect.y()+iconTMPH,
                           m_kuangLeftRect.width()-2*textSpaceRect, m_kuangLeftRect.height()-2*iconTMPH);
    m_textRightRect.setRect(m_kuangRightRect.x()+textSpaceRect, m_kuangRightRect.y()+iconTMPH,
                            m_kuangRightRect.width()-2*textSpaceRect, m_kuangRightRect.height()-2*iconTMPH);


    m_idLeftRect.setRect(m_kuangLeftRect.x()-25, m_kuangLeftRect.y()+iconTMPH - 30,
                            2*textSpaceRect + iconWH*2 , 20);
    m_idRightRect.setRect(m_kuangRightRect.x()+m_kuangRightRect.width()-75, m_kuangRightRect.y()+iconTMPH - 30,
                            2*textSpaceRect + iconWH*2 , 20);
    return QSize(size.width(), hei + 15);
}

QSize ChatMessage::getRealString(QString src)
{
    QFontMetricsF fm(this->font());
    m_lineHeight = fm.lineSpacing();
    int nCount = src.count("\n");
    int nMaxWidth = 0;
    if(nCount == 0) {
        nMaxWidth = fm.width(src);
        QString value = src;
        if(nMaxWidth > m_textWidth) {
            nMaxWidth = m_textWidth;
            int size = m_textWidth / fm.width(" ");
            int num = fm.width(value) / m_textWidth;
            num = ( fm.width(value) ) / m_textWidth;
            nCount += num;
            QString temp = "";
            for(int i = 0; i < num; i++) {
                temp += value.mid(i*size, (i+1)*size) + "\n";
            }
            src.replace(value, temp);
        }
    } else {
        for(int i = 0; i < (nCount + 1); i++) {
            QString value = src.split("\n").at(i);
            nMaxWidth = fm.width(value) > nMaxWidth ? fm.width(value) : nMaxWidth;
            if(fm.width(value) > m_textWidth) {
                nMaxWidth = m_textWidth;
                int size = m_textWidth / fm.width(" ");
                int num = fm.width(value) / m_textWidth;
                num = ((i+num)*fm.width(" ") + fm.width(value)) / m_textWidth;
                nCount += num;
                QString temp = "";
                for(int i = 0; i < num; i++) {
                    temp += value.mid(i*size, (i+1)*size) + "\n";
                }
                src.replace(value, temp);
            }
        }
    }
    return QSize(nMaxWidth+m_spaceWid, (nCount + 1) * m_lineHeight+2*m_lineHeight);
}

void ChatMessage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//消锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));

    if(m_userType == User_Type::User_She) { // 用户
        //头像
        painter.drawRoundedRect(m_iconLeftRect,m_iconLeftRect.width(),m_iconLeftRect.height());
        painter.drawPixmap(m_iconLeftRect, m_leftPixmap);

        //框加边
        QColor col_KuangB(234, 234, 234);
        /*painter.setBrush(QBrush(col_KuangB));
        painter.drawRoundedRect(m_kuangLeftRect.x()-1,m_kuangLeftRect.y()-1 + 10,m_kuangLeftRect.width()+2,m_kuangLeftRect.height()+2,4,4);
        //框*/
        QColor col_Kuang(251, 254, 109);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangLeftRect,4,4);

        //三角
        QPointF points[3] = {
            QPointF(m_sanjiaoLeftRect.x(), 40),
            QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 35),
            QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 45),
        };
        QPen pen;
        pen.setColor(col_Kuang);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        //三角加边
        /*QPen penSanJiaoBian;
        penSanJiaoBian.setColor(col_KuangB);
        painter.setPen(penSanJiaoBian);
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 24));
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 36));
        */
        //id
        //id
        QPen penid;
        penid.setColor(Qt::darkGray);
        painter.setPen(penid);
        QFont f = this->font();
        f.setPointSize(10);
        QTextOption op(Qt::AlignHCenter | Qt::AlignVCenter);
        painter.setFont(f);
        painter.drawText(m_idLeftRect, m_id, op);

        //内容
        QPen penText;
        penText.setColor(QColor(51,51,51));
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textLeftRect, m_msg,option);
    }  else if(m_userType == User_Type::User_Me) { // 自己
        //头像
        painter.drawRoundedRect(m_iconRightRect,m_iconRightRect.width(),m_iconRightRect.height());
        painter.drawPixmap(m_iconRightRect, m_rightPixmap);

        //文字
        if(m_msg!=""){
            //框
            QColor col_Kuang(75,164,242);
            painter.setBrush(QBrush(col_Kuang));
            painter.drawRoundedRect(m_kuangRightRect,4,4);

            //三角
            QPointF points[3] = {
                QPointF(m_sanjiaoRightRect.x()+m_sanjiaoRightRect.width(), 40),
                QPointF(m_sanjiaoRightRect.x(), 35),
                QPointF(m_sanjiaoRightRect.x(), 45),
            };
            QPen pen;
            pen.setColor(col_Kuang);
            painter.setPen(pen);
            painter.drawPolygon(points, 3);
            /*---------------------文字内容------------------------*/
            QPen penText;
            penText.setColor(Qt::white);
            painter.setPen(penText);
            QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
            option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
            painter.setFont(this->font());
            painter.drawText(m_textRightRect,m_msg,option);
        }
        /*---------------------图片内容------------------------*/
        else{
            painter.drawPixmap(m_picRect, m_pic);

        }
        //id
        QPen penid;
        penid.setColor(Qt::black);
        painter.setPen(penid);
        QFont f = this->font();
        f.setPointSize(10);
        QTextOption op(Qt::AlignHCenter | Qt::AlignVCenter);
        painter.setFont(f);
        painter.drawText(m_idRightRect, m_id, op);


    }  else if(m_userType == User_Type::User_Time) { // 时间
        QPen penText;
        penText.setColor(QColor(153,153,153));
        painter.setPen(penText);
        QTextOption option(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        QFont te_font = this->font();
        te_font.setFamily("MicrosoftYaHei");
        te_font.setPointSize(10);
        painter.setFont(te_font);
        painter.drawText(this->rect(),m_curTime,option);
    }
};
