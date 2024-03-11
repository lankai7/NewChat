#include "PicByte.h"

PicByte::PicByte()
{

}
// 读取图片文件为二进制数据
QByteArray PicByte::readImageAsByteArray(const QString &filePath)
{
    QFile file(filePath);
       if (!file.open(QIODevice::ReadOnly)) {
           // 处理文件打开失败的情况
           return QByteArray();
       }
       return file.readAll();
}
// 从二进制数据创建QPixmap对象
QPixmap PicByte::createPixmapFromByteArray(const QByteArray &data)
{
    QPixmap pixmap;
        if (!pixmap.loadFromData(data)) {
            // 处理图片加载失败的情况
            index = false;
            return QPixmap();
        }
        index = true;
        return pixmap;
}

bool PicByte::isPicture()
{
    if(index == true){
        return true;
    }
    else{
        return false;
    }
}
