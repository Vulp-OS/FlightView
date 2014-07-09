#include "fft_widget.h"
fft_widget::fft_widget(frameWorker *fw, image_t image_type, QWidget *parent) :
    QWidget(parent)
{
    qcp = NULL;
    this->fw = fw;
    fps = 0;
    zero_const_box.setText("Set constant FFT term to zero");
    zero_const_box.setChecked(true);
}
fft_widget::~fft_widget()
{

}

void fft_widget::initQCPStuff()
{
    qcp = new QCustomPlot(this);
    fft_bars = new QCPBars(qcp->xAxis,qcp->yAxis);
    qcp->addPlottable(fft_bars);
    fft_bars->setName("Magnitude of FFT average pixel value");
    //fft_bars->setP
    freq_bins = QVector<double>(MEAN_BUFFER_LENGTH/2);
    double nyquist_freq = (double)max_fps[fw->camera_type()]/2;
    double increment = nyquist_freq/(MEAN_BUFFER_LENGTH/2);
    fft_bars->setWidth(increment);
    for(int i = 0; i < MEAN_BUFFER_LENGTH/2; i++)
    {
        freq_bins[i] = increment*i;
    }
    //rfft_data_vec = QVector<double>(MEAN_BUFFER_LENGTH/2);
    //rfft_data = new float[MEAN_BUFFER_LENGTH/2];
    qvbl.addWidget(qcp);
    qvbl.addWidget(&zero_const_box);
    this->setLayout(&qvbl);
}


void fft_widget::handleNewFrame()

{
    if(qcp == NULL)
    {
        initQCPStuff();
    }
    if(fps%4==0 && !this->isHidden())
    {
        QMutexLocker ml(&fw->vector_mutex);
        //printf("const term in vec:%f\n",fw->rfft_data_vec[0]);

        if(zero_const_box.isChecked())
        {
            fw->rfft_data_vec[0]=0;
        }

        fft_bars->setData(freq_bins,fw->rfft_data_vec);
        ml.unlock();

        fft_bars->rescaleAxes();

        qcp->replot();
    }
}
