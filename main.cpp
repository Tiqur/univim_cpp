#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QScreen>
#include <QWindow>

class OverlayWindow : public QMainWindow {
    Q_OBJECT

public:
    OverlayWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_TransparentForMouseEvents);

        // Create a fullscreen window without a frame
        setWindowState(Qt::WindowFullScreen);
        setWindowFlags(windowFlags() | Qt::X11BypassWindowManagerHint);

        // Set geometry to cover all screens
        QRect totalGeometry;
        for (QScreen* screen : QGuiApplication::screens()) {
            totalGeometry = totalGeometry.united(screen->geometry());
        }
        setGeometry(totalGeometry);

        // Create an input-only window to catch events
        QWindow* inputWindow = QWindow::fromWinId(winId());
        if (inputWindow) {
            inputWindow->setFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
            inputWindow->setGeometry(totalGeometry);
        }
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Set the background to transparent
        painter.fillRect(rect(), Qt::transparent);

        // Draw cyan border
        QPen pen(QColor(0, 255, 255));  // Cyan color
        pen.setWidth(5);
        painter.setPen(pen);
        painter.drawRect(rect().adjusted(2, 2, -2, -2));  // Adjust to keep border inside the window
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    OverlayWindow window;
    window.show();

    return app.exec();
}

#include "main.moc"
