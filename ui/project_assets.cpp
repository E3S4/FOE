#include "project_assets.h"
#include <QHeaderView>

ProjectAssets::ProjectAssets(QWidget *parent) : QWidget(parent) {
    tree = new QTreeWidget(this);
    tree->setColumnCount(3);
    tree->setHeaderLabels({"Name", "Type", "Path"});
    tree->header()->setSectionResizeMode(QHeaderView::Stretch);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(tree);
    setLayout(layout);

    connect(tree, &QTreeWidget::itemDoubleClicked, this, [this](QTreeWidgetItem *item, int){
        AssetItem asset {
            item->text(0), // name
            item->text(1), // type
            item->text(2)  // path
        };
        emit assetDoubleClicked(asset);
    });
}

void ProjectAssets::addAsset(const QString &name, const QString &type, const QString &path) {
    auto *item = new QTreeWidgetItem(tree);
    item->setText(0, name);
    item->setText(1, type);
    item->setText(2, path);
    tree->addTopLevelItem(item);
}

