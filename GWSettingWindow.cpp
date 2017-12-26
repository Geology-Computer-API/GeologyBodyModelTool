#include "GWSettingWindow.h"
#include "ui_GWSettingWindow.h"

CGWSettingWindow::CGWSettingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CGWSettingWindow)
{
    ui->setupUi(this);
    QRect rect = this->geometry();
    ui->dockWidget->setGeometry(rect);
    ui->dockWidget->setWindowTitle(QStringLiteral("参数设置"));
}

CGWSettingWindow::~CGWSettingWindow()
{
    delete ui;
}

/*
 * Function    :setBlockWidth
 * Summary      :设置分块宽度
 * Parameters:widthSize  设置的分块宽度大小
 * Return       :
 */
void CGWSettingWindow::setBlockWidth(const int &widthSize)
{
    QString curString = QString("%1").arg(widthSize);
    ui->widthComboBox->setCurrentText(curString);
}

/*
 * Function    :setBlockHeight
 * Summary      :设置分块高度
 * Parameters:heightSize 设置的分块高度大小
 * Return       :
 */
void CGWSettingWindow::setBlockHeight(const int &heightSize)
{
    QString curString = QString("%1").arg(heightSize);
    ui->heightComboBox->setCurrentText(curString);
}

/*
 * Function     :getBlockWidth
 * Summary      :获取分块宽度大小
 * Parameters:
 * Return       :int 获取的分块宽度大小
 */
int CGWSettingWindow::getBlockWidth()
{
    return ui->widthComboBox->currentText().toInt();
}

/*
 * Function     :getBlockHeight
 * Summary      :获取分块高度大小
 * Parameters:
 * Return       :int 获取的分块高度大小
 */
int CGWSettingWindow::getBlockHeight()
{
    return ui->heightComboBox->currentText().toInt();
}

/*
 * Function    :setGradingSize
 * Summary      :设置分级大小
 * Parameters:size 设置的分级大小
 * Return       :
 */
void CGWSettingWindow::setGradingSize(const int &size)
{
    QString curString = QString("%1").arg(size);
    ui->gradeComboBox->setCurrentText(curString);
}

/*
 * Function    :getGradingSize
 * Summary      :获取分级大小
 * Parameters:
 * Return       :int 返回分级大小
 */
int CGWSettingWindow::getGradingSize()
{
    return ui->gradeComboBox->currentText().toInt();
}
