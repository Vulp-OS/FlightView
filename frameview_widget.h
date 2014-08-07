#ifndef FRAMEVIEW_WIDGET_H
#define FRAMEVIEW_WIDGET_H

#include <QWidget>
#include <QThread>
#include <QImage>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include <QMutex>
#include <atomic>
#include "frame_c_meta.h"

#include "frame_worker.h"
#include "image_type.h"
#include "qcustomplot.h"
//#include "view_widget_interface.h"

class frameview_widget :public QWidget//, public view_widget_interface
{
    Q_OBJECT
    //Q_INTERFACES(view_widget_interface)
    QVBoxLayout layout ;
    QCustomPlot * qcp;
    QCPColorMap * colorMap;
    QCPColorMapData * colorMapData;
    QCPColorScale * colorScale;
    QLabel fpsLabel;
    double fps;
    unsigned long seconds_elapsed = 0;
    QTimer fpstimer;
    QTimer rendertimer;
    bool outputGrayScale;
    frameWorker * fw;

    volatile double ceiling;
    volatile double floor;
    int frHeight;
    int frWidth;
    unsigned int count = 0;
    unsigned int old_count = 0;
    //int crosshair_x=-1,crosshair_y=-1;
public:
    explicit frameview_widget(frameWorker * fw, image_t image_type , QWidget *parent = 0);
    ~frameview_widget();
    QPushButton toggleGrayScaleButton;
    double getCeiling();
    double getFloor();
    image_t image_type;
    unsigned int slider_max = (1<<16) * 1.1;
    bool slider_low_inc = false;
protected:
    void keyPressEvent(QKeyEvent *event);
signals:
    void startCapturing();
public slots:
    void handleNewFrame();
    void updateFPS();
    void toggleGrayScale();

    void colorMapScrolledY(const QCPRange &newRange);
    void colorMapScrolledX(const QCPRange &newRange);
    void colorMapDataRangeChanged(const QCPRange &newRange);
    void updateCeiling(int c);
    void updateFloor(int f);
    void rescaleRange();
    void setCrosshairs(QMouseEvent * event);

};

#endif // FRAMEVIEW_WIDGET_H
