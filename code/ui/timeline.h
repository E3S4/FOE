#pragma once
#include <QWidget>
#include <QList>
#include <QColor>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QTimer>

#include "core/import.h" 
    struct ClipItem {
    QString name;
    int startFrame;
    int length;
    QColor color;
};

class Timeline : public QWidget {
    Q_OBJECT
public:
    explicit Timeline(QWidget *parent = nullptr);

    void addClip(const QString &name, int startFrame, int length, const QColor &color);
    void clear();

    void setZoom(float zoom, int cursorX = -1);
    void setPlayheadFrame(int frame);
    int currentFrame() const { return playheadFrame; }
    float currentZoom() const { return zoomLevel; }

signals:
    void playheadMoved(int frame);

public slots:
    void onImportClipsLoaded(const QList<ImportedClip> &clips); // auto called by import system

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    QSize sizeHint() const override;

private slots:
    void advancePlayhead();

private:
    QList<ClipItem> m_clips;
    int playheadFrame = 0;
    float zoomLevel = 1.0f;
    const int basePixelsPerFrame = 5;
    int scrollOffset = 0;
    bool isScrubbing = false;
    int scrubStartX = 0;
    int scrubStartFrame = 0;

    QTimer playbackTimer;
};

