#pragma once
#include <QString>
#include <QList>

struct ImportedClip {
    QString name;
    int startFrame;
    int totalFrames;
};

class ImportManager : public QObject {
    Q_OBJECT
public:
    explicit ImportManager(QObject *parent = nullptr) = default;

signals:
    void clipsLoaded(const QList<ImportedClip> &clips);
};

