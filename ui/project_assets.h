#pragma once
#include <QWidget>
#include <QTreeWidget>
#include <QString>
#include <QVBoxLayout>

struct AssetItem {
    QString name;
    QString type; // "Video", "Image", "Audio"
    QString path;
};

class ProjectAssets : public QWidget {
    Q_OBJECT
public:
    explicit ProjectAssets(QWidget *parent = nullptr);

    void addAsset(const QString &name, const QString &type, const QString &path);

signals:
    void assetDoubleClicked(AssetItem asset);

private:
    QTreeWidget *tree;
};

