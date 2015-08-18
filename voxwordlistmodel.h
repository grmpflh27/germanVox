#ifndef VOXWORDLISTMODEL_H
#define VOXWORDLISTMODEL_H

#include <QStandardItemModel>
#include "voxcardsystem.h"

class voxWordListModel : public QStandardItemModel
{
    Q_OBJECT
public:
    voxWordListModel(const voxcardSystem& vSys, QObject *parent);

    void updateModel(const QList<voxCard> &filteredList);

    int filterItems;
};

#endif // VOXWORDLISTMODEL_H
