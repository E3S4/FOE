#include "project_assets.h"
#include <QVBoxLayout>

ProjectAssets::ProjectAssets(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    list = new QListWidget;
    layout->addWidget(list);
    setLayout(layout);
}

void ProjectAssets::addAsset(const QString &name, const QString &path, int duration) {
    list->addItem(name);
    emit assetImported({name, path, duration});
}

