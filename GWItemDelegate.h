#ifndef GWITEMDELEGATE_H
#define GWITEMDELEGATE_H

/*******************************************
 *单       位：正元地理信息有限责任公司
 *作       者：ZCF
 *创建时间：2017-08-09
 *描       述：重载单元格代理
 * ******************************************/

#include <QObject>
#include <QItemDelegate>
#include <QComboBox>

class CGWItemDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    CGWItemDelegate();
    ~CGWItemDelegate();

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const ;

    void setItemList(const QStringList& strList);
    QStringList getItemList();

private:
    QStringList m_strList;
};

#endif // GWITEMDELEGATE_H
