#pragma once
#include <QWidget>
#include <QListWidget>

struct AssetItem {
    QString name;
    QString path;
    int duration;
};

class ProjectAssets : public QWidget {
    Q_OBJECT
public:
    explicit ProjectAssets(QWidget *parent = nullptr);
    void addAsset(const QString &name, const QString &path, int duration);

signals:
    void assetImported(const AssetItem &item);

private:
    QListWidget *list;
};

