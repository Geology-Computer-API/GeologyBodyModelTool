#ifndef GWMODELMAINWINDOW_H
#define GWMODELMAINWINDOW_H

/*******************************************
 *单       位：正元地理信息有限责任公司
 *作       者：ZCF
 *创建时间：2017-08-02
 *描       述：地质体模型工具
 * ******************************************/

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDebug>
#include <QVariant>
#include <QColorDialog>
#include <QFileDialog>
#include <QDockWidget>
#include <QLineEdit>

#include "qwt_point_data.h"
#include "qwt_plot_curve.h"
#include "qwt_plot_magnifier.h"
#include "qwt_plot_panner.h"
#include "qwt_plot_canvas.h"
#include "qwt_plot_grid.h"

#include "GWItemDelegate.h"
#include "GWSettingWindow.h"

#define QWTPLOT_XSCALE 200
#define QWTPLOT_YSCALE 220
#define MODEL_XSCALE 100
#define MODEL_YSCALE 200

namespace Ui {
class CGWModelMainWindow;
}

class CGWModelMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CGWModelMainWindow(QWidget *parent = 0);
    ~CGWModelMainWindow();

private slots:
    void on_configButton_clicked();
    void on_importAction_triggered();
    void on_exportAction_triggered();
    /******双击单元格事件******/
    void slotRowDoubleClicked(const QModelIndex &index);
    void on_settingButton_clicked();

protected:
    /******初始化表格内容******/
    void initTableView();
    /******初始化图表******/
    void initQwtPlot();
    /**初始化单元格排序及控件**/
    void preparationTableContent();
    /***模型分块*************/
    void setModelBlock(const int&w = 2,const int& h = 2);

private:
    Ui::CGWModelMainWindow *ui;
    QStandardItemModel*        m_viewModel;
    CGWItemDelegate*             m_reflectDelegate;
    CGWItemDelegate*             m_roughDelelegate;
    CGWSettingWindow*           m_settingWindow;
    int                                    m_blockWidth;
    int                                    m_blockHeight;
    QVector<QPointF>             m_pointVec;
    QwtPointSeriesData *      m_plotdata;
    QwtPlotCurve *                 m_plotcurve;
    QwtPlotCanvas *               m_plotcanvas;
};

#endif // GWMODELMAINWINDOW_H
