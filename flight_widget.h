#ifndef FLIGHT_WIDGET_H
#define FLIGHT_WIDGET_H

#include <unistd.h>

#include <QObject>
#include <QWidget>
#include <QSplitter>

#include <qcustomplot.h>

#include "gpsmanager.h"

#include "frame_worker.h"
#include "frameview_widget.h"
#include "qledlabel.h"

class flight_widget : public QWidget
{
    Q_OBJECT

    frameWorker *fw;

    frameview_widget *waterfall_widget;
    frameview_widget *dsf_widget;

    gpsManager *gps;

    QSplitter lrSplitter;
    QSplitter rhSplitter;
    QGridLayout layout;
    QVBoxLayout rhLayout;
    QGroupBox flightControls;
    QGridLayout flightControlLayout;

    // stand-in items for flight controls:
    QPushButton resetStickyErrorsBtn;
    QCheckBox instBtn;
    QLabel gpsLEDLabel;
    QLedLabel gpsLED;
    QLabel cameraLinkLEDLabel;
    QLedLabel cameraLinkLED;
    QLabel aircraftLbl;

    // GPS Text Labels:
    QLabel gpsLatText;
    QLabel gpsLatData;
    QLabel gpsLongText;
    QLabel gpsLongData;
    QLabel gpsHeadingText;
    QLabel gpsHeadingData;
    QLabel gpsAltitudeText;
    QLabel gpsAltitudeData;

    // GPS Plots:
    QCustomPlot gpsPitchRollPlot;
    QCustomPlot gpsHeadingPlot;


    uint16_t redRow;
    uint16_t greenRow;
    uint16_t blueRow;

public:
    explicit flight_widget(frameWorker *fw, QWidget *parent = nullptr);
    const unsigned int slider_max = (1<<16) * 1.1;
    bool slider_low_inc = false;
    double getCeiling();
    double getFloor();
    void toggleDisplayCrosshair();

public slots:
    void handleNewFrame();
    void receiveGPS();

    // Notify:
    void startDataCollection(QString secondaryLogFilename);
    void stopDataCollection();

    void handleNewColorScheme(int scheme);
    void colorMapScrolledY(const QCPRange &newRange);
    void colorMapScrolledX(const QCPRange &newRange);
    void setScrollX(bool Yenabled);
    void setScrollY(bool Xenabled);
    void updateCeiling(int c);
    void updateFloor(int f);
    void rescaleRange();
    void setCrosshairs(QMouseEvent *event);
    void debugThis();

signals:
    void statusMessage(QString);
    void connectToGPS(QString host, int port);
    void beginSecondaryLog(QString filename);
    void stopSecondaryLog();


};

#endif // FLIGHT_WIDGET_H
