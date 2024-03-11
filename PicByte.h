#ifndef PICBYTE_H
#define PICBYTE_H
#include <QFile>
#include <QByteArray>
#include <QPixmap>


/*图片与二进制之间的转换*/

class PicByte
{
public:
    PicByte();
    bool index = false;

    // 读取图片文件为二进制数据
    QByteArray readImageAsByteArray(const QString &filePath);

    // 从二进制数据创建QPixmap对象
    QPixmap createPixmapFromByteArray(const QByteArray &data);

    //检测是否为图片
    bool isPicture();
};

#endif // PICBYTE_H
