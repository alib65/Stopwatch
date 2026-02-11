#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QIcon>

class WorkTimer : public QWidget {
    Q_OBJECT

public:
    WorkTimer(QWidget *parent = nullptr) : QWidget(parent) {
        // --- 1. SETUP WINDOW ---
        setWindowTitle("Work Timer");
        resize(400, 300);
        
        // LOAD THE ICON (from resources.qrc)
        setWindowIcon(QIcon(":/icon.png"));

        // Modern Dark Background
        this->setStyleSheet("background-color: #202020;");

        // --- 2. SETUP DISPLAY (00:00:00) ---
        timeLabel = new QLabel("00:00:00");
        timeLabel->setAlignment(Qt::AlignCenter);
        timeLabel->setStyleSheet(
            "QLabel { font-size: 70px; color: white; font-weight: bold; padding: 20px; }"
        );

        // --- 3. SETUP BUTTONS ---
        startPauseBtn = new QPushButton("Start");
        resetBtn = new QPushButton("Reset");

        QString baseButtonStyle = 
            "QPushButton { border-radius: 40px; font-size: 24px; font-weight: bold; color: white; min-width: 80px; min-height: 80px; }";

        startPauseBtn->setStyleSheet(baseButtonStyle + 
            "QPushButton { background-color: #32d74b; }" // iOS Green
            "QPushButton:pressed { background-color: #28a83a; }"
        );

        resetBtn->setStyleSheet(baseButtonStyle + 
            "QPushButton { background-color: #505050; }" // Dark Gray
            "QPushButton:pressed { background-color: #707070; }"
        );

        // --- 4. LAYOUTS ---
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        QHBoxLayout *buttonLayout = new QHBoxLayout();

        buttonLayout->addWidget(resetBtn);
        buttonLayout->addSpacing(20);
        buttonLayout->addWidget(startPauseBtn);
        buttonLayout->setContentsMargins(30, 0, 30, 30);

        mainLayout->addStretch();
        mainLayout->addWidget(timeLabel);
        mainLayout->addStretch();
        mainLayout->addLayout(buttonLayout);

        // --- 5. LOGIC ---
        timer = new QTimer(this);
        timer->setInterval(1000);
        connect(timer, &QTimer::timeout, this, &WorkTimer::updateTimer);
        connect(startPauseBtn, &QPushButton::clicked, this, &WorkTimer::toggleStartPause);
        connect(resetBtn, &QPushButton::clicked, this, &WorkTimer::resetTime);
    }

private:
    QLabel *timeLabel;
    QPushButton *startPauseBtn;
    QPushButton *resetBtn;
    QTimer *timer;
    long long totalSeconds = 0;
    bool isRunning = false;

    void updateTimer() {
        totalSeconds++;
        updateDisplay();
    }

    void updateDisplay() {
        long long hours = totalSeconds / 3600;
        long long minutes = (totalSeconds % 3600) / 60;
        long long seconds = totalSeconds % 60;
        QString timeText = QString("%1:%2:%3")
                           .arg(hours, 2, 10, QChar('0'))
                           .arg(minutes, 2, 10, QChar('0'))
                           .arg(seconds, 2, 10, QChar('0'));
        timeLabel->setText(timeText);
    }

    void toggleStartPause() {
        if (isRunning) {
            timer->stop();
            startPauseBtn->setText("Resume");
            startPauseBtn->setStyleSheet(
                "QPushButton { border-radius: 40px; font-size: 24px; font-weight: bold; color: white; min-width: 80px; min-height: 80px; background-color: #ff9f0a; }" // Orange
                "QPushButton:pressed { background-color: #d48405; }"
            );
            isRunning = false;
        } else {
            timer->start();
            startPauseBtn->setText("Pause");
            startPauseBtn->setStyleSheet(
                "QPushButton { border-radius: 40px; font-size: 24px; font-weight: bold; color: white; min-width: 80px; min-height: 80px; background-color: #ff453a; }" // Red
                "QPushButton:pressed { background-color: #d03025; }"
            );
            isRunning = true;
        }
    }

    void resetTime() {
        timer->stop();
        isRunning = false;
        totalSeconds = 0;
        updateDisplay();
        startPauseBtn->setText("Start");
        startPauseBtn->setStyleSheet(
            "QPushButton { border-radius: 40px; font-size: 24px; font-weight: bold; color: white; min-width: 80px; min-height: 80px; background-color: #32d74b; }" // Green
            "QPushButton:pressed { background-color: #28a83a; }"
        );
    }
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    WorkTimer timerApp;
    timerApp.show();
    return app.exec();
}