#include "timeline.h"

Timeline::Timeline(QWidget *parent)
    : QWidget(parent)
{
    setMinimumHeight(150);
    setMouseTracking(true);

    connect(&playbackTimer, &QTimer::timeout, this, &Timeline::advancePlayhead);
    playbackTimer.start(1000 / 24); // Default 24 FPS
}

// --- Core timeline methods ---
void Timeline::addClip(const QString &name, int start, int length, QColor color) {
    m_clips.append({name, start, length, color});
    update();
}

void Timeline::clear() {
    m_clips.clear();
    playheadFrame = 0;
    update();
}

// --- Sync from import system ---
void Timeline::onImportClipsLoaded(const QList<ImportedClip> &clips) {
    clear();
    for (const auto &clip : clips) {
        addClip(clip.name, clip.startFrame, clip.length, QColor(70, 130, 180)); // default blue tone
    }
    update();
}

// --- Playback logic ---
void Timeline::advancePlayhead() {
    playheadFrame++;
    emit playheadMoved(playheadFrame);
    update();
}

// --- External controls ---
void Timeline::setZoom(float zoom, int cursorX) {
    float oldZoom = zoomLevel;
    zoomLevel = std::clamp(zoom, 0.2f, 6.0f);

    if (cursorX >= 0) {
        // Keep zoom centered around cursor
        int oldCenterFrame = (cursorX + scrollOffset) / (basePixelsPerFrame * oldZoom);
        int newCenterFrame = (cursorX + scrollOffset) / (basePixelsPerFrame * zoomLevel);
        scrollOffset += (newCenterFrame - oldCenterFrame) * basePixelsPerFrame * zoomLevel;
    }

    update();
}

void Timeline::setPlayheadFrame(int frame) {
    playheadFrame = std::max(0, frame);
    update();
}

// --- Drawing ---
void Timeline::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(rect(), QColor(25, 25, 25));

    int pixelsPerFrame = static_cast<int>(basePixelsPerFrame * zoomLevel);

    // Time ruler
    p.setPen(QColor(100, 100, 100));
    for (int i = -scrollOffset % (pixelsPerFrame * 10); i < width(); i += pixelsPerFrame * 10) {
        int frameMark = (i + scrollOffset) / pixelsPerFrame;
        p.drawLine(i, 0, i, 20);
        p.drawText(i + 3, 15, QString::number(frameMark));
    }

    // Draw clips
    for (const auto &clip : m_clips) {
        int x = clip.startFrame * pixelsPerFrame - scrollOffset;
        int w = clip.length * pixelsPerFrame;
        QRect rect(x, 30, w, 40);
        if (rect.right() >= 0 && rect.left() <= width()) {
            p.fillRect(rect, clip.color);
            p.setPen(Qt::white);
            p.drawText(rect.adjusted(5, 5, -5, -5), Qt::AlignLeft | Qt::AlignTop, clip.name);
        }
    }

    // Playhead
    int playheadX = playheadFrame * pixelsPerFrame - scrollOffset;
    p.setPen(QPen(Qt::red, 2));
    p.drawLine(playheadX, 0, playheadX, height());
}

// --- Mouse interactions ---
void Timeline::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isScrubbing = true;
        scrubStartX = event->pos().x();
        scrubStartFrame = playheadFrame;
        int pixelsPerFrame = static_cast<int>(basePixelsPerFrame * zoomLevel);
        playheadFrame = (event->pos().x() + scrollOffset) / pixelsPerFrame;
        emit playheadMoved(playheadFrame);
        update();
    }
}

void Timeline::mouseMoveEvent(QMouseEvent *event) {
    if (isScrubbing) {
        int pixelsPerFrame = static_cast<int>(basePixelsPerFrame * zoomLevel);
        int dx = event->pos().x() - scrubStartX;
        playheadFrame = scrubStartFrame + dx / pixelsPerFrame;
        playheadFrame = std::max(0, playheadFrame);
        emit playheadMoved(playheadFrame);
        update();
    }
}

void Timeline::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        isScrubbing = false;
}

void Timeline::wheelEvent(QWheelEvent *event) {
    float delta = event->angleDelta().y() / 240.0f;
    setZoom(zoomLevel + delta * 0.3f, event->position().x());
}

QSize Timeline::sizeHint() const {
    return QSize(2000, 150);
}

