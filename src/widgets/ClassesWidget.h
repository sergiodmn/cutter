#ifndef CLASSESWIDGET_H
#define CLASSESWIDGET_H

#include <memory>

#include "cutter.h"

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QDockWidget>

namespace Ui
{
    class ClassesWidget;
}

class QTreeWidget;
class QTreeWidgetItem;


class ClassesModel: public QAbstractItemModel
{
    Q_OBJECT

private:
    QList<ClassDescription> *classes;

public:
    enum Columns { NAME = 0, TYPE, OFFSET, COUNT };
    enum RowType { CLASS = 0, METHOD = 1, FIELD = 2 };

    static const int OffsetRole = Qt::UserRole;
    static const int NameRole = Qt::UserRole + 1;
    static const int TypeRole = Qt::UserRole + 2;

    explicit ClassesModel(QList<ClassDescription> *classes, QObject *parent = 0);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void beginReload();
    void endReload();
};

Q_DECLARE_METATYPE(ClassesModel::RowType)


class ClassesSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit ClassesSortFilterProxyModel(ClassesModel *source_model, QObject *parent = 0);

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};



class ClassesWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit ClassesWidget(QWidget *parent = nullptr);
    ~ClassesWidget();

private slots:
    void on_classesTreeView_doubleClicked(const QModelIndex &index);

    void refreshClasses();

private:
    std::unique_ptr<Ui::ClassesWidget> ui;

    ClassesModel *model;
    ClassesSortFilterProxyModel *proxy_model;
    QList<ClassDescription> classes;
};


#endif // CLASSESWIDGET_H
