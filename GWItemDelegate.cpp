#include "GWItemDelegate.h"

CGWItemDelegate::CGWItemDelegate()
{
}

CGWItemDelegate::~CGWItemDelegate()
{
}

QWidget *CGWItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox *editor = new QComboBox(parent);
    for (int i = 0, size = m_strList.count(); i < size; i++)
    {
        editor->addItem(m_strList.at(i));
    }
    return editor;
}

void CGWItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int tindex = comboBox->findText(text);
    comboBox->setCurrentIndex(tindex);
}

void CGWItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString text = comboBox->currentText();
    model->setData(index,text,Qt::EditRole);
}

void CGWItemDelegate::setItemList(const QStringList &strList)
{
    m_strList = strList;
}

QStringList CGWItemDelegate::getItemList()
{
    return m_strList;
}
