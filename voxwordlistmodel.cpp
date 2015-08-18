#include "voxwordlistmodel.h"

#include <QDebug>

voxWordListModel::voxWordListModel(const voxcardSystem& vSys, QObject *parent) :
   QStandardItemModel(parent), filterItems(0)
{
    updateModel(vSys.dict.values());
}

void voxWordListModel::updateModel(const QList<voxCard>& filteredList)
{
    if(columnCount() > 0){
        this->clear();
    }

    QList<QStandardItem*> termList;
    QList<QStandardItem*> defList;

    QList<voxCard>::const_iterator iter = filteredList.begin();

    for(iter; iter != filteredList.end(); iter++){
        QStandardItem* termPtrItem = new QStandardItem(iter->learnTerm);
        QStandardItem* defPtrItem = new QStandardItem(iter->nativeTerm);

        termList.append(termPtrItem);
        defList.append(defPtrItem);
    }


    insertColumn(0, termList);
    insertColumn(1, defList);

    setHorizontalHeaderLabels(QStringList() << tr("Term") << tr("Definition"));
    filterItems = filteredList.size();
}
