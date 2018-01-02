#include "GWModelMainWindow.h"
#include "ui_GWModelMainWindow.h"

CGWModelMainWindow::CGWModelMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CGWModelMainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/resource/images/cloud.png"));
    this->setWindowTitle(QStringLiteral("地质体模型工具"));
    m_viewModel = new QStandardItemModel(this);
    this->ui->tableView->setModel(m_viewModel);
    this->ui->tableView->verticalHeader()->hide();
    connect(this->ui->tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(slotRowDoubleClicked(QModelIndex)));
    m_blockWidth  = MODEL_XSCALE;
    m_blockHeight = MODEL_YSCALE;
    initTableView();
    preparationTableContent();
    initQwtPlot();
}

CGWModelMainWindow::~CGWModelMainWindow()
{
    delete ui;
    if(m_viewModel) {
        delete m_viewModel;
        m_viewModel = NULL;
    }
    if(m_reflectDelegate) {
        delete m_reflectDelegate;
        m_reflectDelegate = NULL;
    }
    if(m_roughDelelegate) {
        delete m_roughDelelegate;
        m_roughDelelegate = NULL;
    }
    if(m_settingWindow) {
        delete m_settingWindow;
        m_settingWindow = NULL;
    }
    if(m_plotcanvas) {
        delete m_plotcanvas;
        m_plotcanvas = NULL;
    }
}

/*
 * Function     :on_configButton_clicked
 * Summary      :重新配置模型相应参数
 * Parameters:
 * Return       :
 */
void CGWModelMainWindow::on_configButton_clicked()
{
    int curRow = this->ui->tableView->currentIndex().row();
    QString contentString;
    for(int i = 0; i < m_viewModel->columnCount(); i++)
    {
        QModelIndex curIndex = m_viewModel->index(curRow,i);
        contentString += " " +  m_viewModel->data(curIndex).toString();
    }
    qDebug() << contentString;
}

/*
 * Function     :on_importAction_triggered
 * Summary      :导入模型文件
 * Parameters:
 * Return       :
 */
void CGWModelMainWindow::on_importAction_triggered()
{
    QStringList currPaths = QFileDialog::getOpenFileNames(this,tr("Open Model File"),".",tr("Model Files(*.ico)"));
    if(currPaths.length() != 0) {
        foreach (QString temp, currPaths) {
            qDebug() << "You selected: " + temp;
        }
    } else {
        qDebug() << "You didn't select any files.";
    }
}

/*
 * Function   :on_exportAction_triggered
 * Summary     :发布模型文件
 * Parameters:
 * Return       :
 */
void CGWModelMainWindow::on_exportAction_triggered()
{
    QString fileName = QFileDialog::getSaveFileName();
    if(!fileName.isNull()) {
        qDebug() << fileName << "has saved.";
    } else {
        qDebug() << "The file is null";
    }

}

/*
 * Function   :initTableView
 * Summary     :初始化导入表格中的内容
 * Parameters:
 * Return       :
 */
void CGWModelMainWindow::initTableView()
{
    QStringList titleList;
    titleList << QStringLiteral("模型名称") << QStringLiteral("UID") << QStringLiteral("颜色")
              << QStringLiteral("漫反射纹理") << QStringLiteral("凹凸纹理") << QStringLiteral("属性");
    unsigned int columnCnt = titleList.count();
    m_viewModel->setColumnCount(columnCnt);
    unsigned int iCycle = 0;
    foreach (QString temp, titleList) {
        m_viewModel->setHeaderData(iCycle++,Qt::Horizontal, temp);
    }

    for(unsigned int i = 0; i < 5; i++)
    {
        m_viewModel->setItem(i, 0, new QStandardItem("00000"));
        m_viewModel->setItem(i, 1, new QStandardItem("20120202"));
        m_viewModel->setData(m_viewModel->index(i,2), QColor(150,150,150), Qt::BackgroundColorRole);
        m_viewModel->setItem(i, 3, new QStandardItem("18"));
        m_viewModel->setItem(i, 4, new QStandardItem("12"));
        m_viewModel->setItem(i, 5, new QStandardItem("1111"));
    }
}

/*
 * Function   :initQwtPlot
 * Summary     :初始化曲线图
 * Parameters:
 * Return       :
 */
void CGWModelMainWindow::initQwtPlot()
{
    m_settingWindow = new CGWSettingWindow();
    ui->horizontalLayout_2->addWidget(m_settingWindow,0);
    m_settingWindow->show();

    QwtText titleText(QStringLiteral("地质体模型分块示意图"));
    titleText.setColor(QColor("white"));
    ui->qwtPlot->setTitle(titleText);
    ui->qwtPlot->setAxisTitle(QwtPlot::xBottom, QStringLiteral("X坐标"));
    ui->qwtPlot->setAxisTitle(QwtPlot::yLeft,QStringLiteral("Y坐标"));
    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,QWTPLOT_XSCALE);
    ui->qwtPlot->setAxisScale(QwtPlot::yLeft,0,QWTPLOT_YSCALE);
    //设置网格线
    QwtPlotGrid *grid = new  QwtPlotGrid;
    grid->enableX( true );
    grid->enableY( true );
    grid->setMajorPen( Qt::yellow, 0, Qt::DotLine );
    grid->attach(ui->qwtPlot);
    //设置背景颜色
    m_plotcanvas = new QwtPlotCanvas();
    m_plotcanvas->setLineWidth(2);
    m_plotcanvas->setFrameStyle(QFrame::Box | QFrame::Sunken);
    m_plotcanvas->setBorderRadius(10);
    QPalette canvasPalette(QColor("black"/*50,50,50*/));
    canvasPalette.setColor(QPalette::Foreground, QColor("Indigo"));
    m_plotcanvas->setPalette(canvasPalette);
    ui->qwtPlot->setCanvas(m_plotcanvas);
    //设置曲线颜色
    m_plotdata = new QwtPointSeriesData();
    m_plotcurve = new QwtPlotCurve("Rectangle");
    m_plotcurve->setData(m_plotdata);
    m_plotcurve->setStyle(QwtPlotCurve::Lines);
    m_plotcurve->setPen(QPen(Qt::red));
    m_plotcurve->attach(ui->qwtPlot);
    /*
    //使用滚轮放大/缩小
    (void) new QwtPlotMagnifier( ui->qwtPlot->canvas() );
    //使用鼠标左键平移
    (void) new QwtPlotPanner( ui->qwtPlot->canvas() );
    */
    setModelBlock(4,4);
     m_plotdata->setSamples(m_pointVec);
}

/*
 * Function   :preparationTableContent
 * Summary     :对表格内容做预处理
 * Parameters:
 * Return       :
 */
void CGWModelMainWindow::preparationTableContent()
{
    if(0 == m_viewModel->rowCount()) {
        return;
    }
    m_viewModel->sort(0, Qt::AscendingOrder);

    //设置非编辑状态
    for(int i = 0; i<m_viewModel->rowCount();i++)
    {
        m_viewModel->item(i, 0)->setFlags((m_viewModel->item(i,0)->flags()) & (~Qt::ItemIsEditable));
        m_viewModel->item(i, 2)->setFlags((m_viewModel->item(i,2)->flags()) & (~Qt::ItemIsEditable));
    }

    //添加组合框于单元格中
    m_reflectDelegate = new CGWItemDelegate();
    QStringList reflectList;
    reflectList << QString::fromLocal8Bit("白") << QString::fromLocal8Bit("黑") << QString::fromLocal8Bit("红");
    m_reflectDelegate->setItemList(reflectList);
   this->ui->tableView->setItemDelegateForColumn(3,m_reflectDelegate);
    m_roughDelelegate = new CGWItemDelegate();
    QStringList roughList;
    roughList << QString::fromLocal8Bit("凹") << QString::fromLocal8Bit("凸") << QString::fromLocal8Bit("凹凸");
    m_roughDelelegate->setItemList(roughList);
    this->ui->tableView->setItemDelegateForColumn(4,m_roughDelelegate);
}

/*
 * Function    :setModelBlock
 * Summary      :模型分块
 * Parameters:w -分块宽大小  h-分块高大小
 * Return       :
 */
void CGWModelMainWindow::setModelBlock(const int &w, const int &h)
{
    if(w < 1 || h < 1) {
        return;
    }
    m_pointVec.clear();

    int wStep = m_blockWidth / w;
    int hStep = m_blockHeight / h;
    m_pointVec.append(QPointF(0,0));
    m_pointVec.append(QPointF(m_blockWidth,0));
    m_pointVec.append(QPointF(m_blockWidth,m_blockHeight));
    m_pointVec.append(QPointF(0,m_blockHeight));

    int yPoint = 0;
    for(int i = 0; i <= w; i++ )
    {
        static int cnt  = 0;
        if(i == w) {
            m_pointVec.append(QPointF(m_blockWidth,yPoint));
            cnt = 0;
            break;
        }
        for(int s = 0; s < 2; s++)
        {
            m_pointVec.append(QPointF(wStep * i, yPoint));
            cnt++;
            if(0 == i) {
                break;
            }
            if(2 == cnt) {
                cnt = 0;
                if(0 == yPoint) {
                    yPoint = m_blockHeight;
                } else {
                    yPoint = 0;
                }
            }
        }
    }
    int xPoint = m_blockWidth;
    for(int j = 0; j <= h; j++)
    {
        static int cnt = 0;
        if(j == h) {
            m_pointVec.append(QPointF(xPoint,m_blockHeight));
            cnt = 0;
            break;
        }
        for(int s = 0; s < 2; s++)
        {
            m_pointVec.append(QPointF(xPoint,hStep * j));
            cnt++;
            if(0 == j) {
                break;
            }
            if(2 == cnt) {
                cnt = 0;
                if(0 == xPoint) {
                    xPoint = m_blockWidth;
                } else {
                    xPoint = 0;
                }
            }
        }
    }
}

/*
 * Function     :slotRowDoubleClicked
 * Summary      :单元格双击响应槽事件
 * Parameters:index 对应单元格索引
 * Return       :
 */
void CGWModelMainWindow::slotRowDoubleClicked(const QModelIndex &index)
{
    QModelIndex currIndex = this->ui->tableView->currentIndex();
    if((currIndex != index) || (!currIndex.isValid())) {
        return;
    }
    unsigned int currColumn = currIndex.column();
    if(2 == currColumn) {
        QVariant currVar = m_viewModel->data(currIndex,Qt::BackgroundColorRole);
        QColor newColor  = QColorDialog::getColor();
        if((!newColor.isValid()) || (currVar == newColor)) {
            return;
        }
        currVar.setValue(newColor);
        m_viewModel->setData(currIndex, currVar, Qt::BackgroundColorRole);
    }
    qDebug() << "double click table(" << currIndex.row() << "," << currColumn << ")";
}

/*
 * Function    :on_settingButton_clicked
 * Summary      :分级、分块设置
 * Parameters:
 * Return       :
 */
void CGWModelMainWindow::on_settingButton_clicked()
{
    unsigned int width   = m_settingWindow->getBlockWidth();
    unsigned int height = m_settingWindow->getBlockHeight();
    unsigned int grade   = m_settingWindow->getGradingSize();
    qDebug() << "Blocking width:" << width << ", Blocking height:" << height << ", Grading:" << grade;
    setModelBlock(width,height);
    m_plotdata->setSamples(m_pointVec);
}
