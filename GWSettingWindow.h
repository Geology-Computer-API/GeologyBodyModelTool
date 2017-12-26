#ifndef GWSETTINGWINDOW_H
#define GWSETTINGWINDOW_H

/*******************************************
 *单       位：正元地理信息有限责任公司
 *作       者：ZCF
 *创建时间：2017-08-11
 *描       述：创建设置窗口
 * ******************************************/

#include <QMainWindow>

namespace Ui {
class CGWSettingWindow;
}

class CGWSettingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CGWSettingWindow(QWidget *parent = 0);
    ~CGWSettingWindow();

    /*****设置分块宽度大小***********/
    void setBlockWidth(const int& widthSize = 1);
    /*****设置分块高度大小***********/
    void setBlockHeight(const int& heightSize = 1);
    /*****获取分块宽度大小***********/
    int getBlockWidth();
    /*****获取分块高度大小***********/
    int getBlockHeight();
    /*****设置分级大小***************/
    void setGradingSize(const int& size = 2);
    /*****获取分级大小***************/
    int getGradingSize();

private:
    Ui::CGWSettingWindow *ui;
};

#endif // GWSETTINGWINDOW_H
