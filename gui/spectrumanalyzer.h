#ifndef SPECTRUMANALYZER_H
#define SPECTRUMANALYZER_H

#include <QGraphicsItem>
#include "ringbuffer.h"

#define MOVING_AVG_PERIOD 128
#define MAX_SAMPLES 4096

class FrequencyTickBuilder;

class SpectrumAnalyzer : public QGraphicsItem
{
public:
    SpectrumAnalyzer(FrequencyTickBuilder *xTickBuilder);

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void updateFrameDelta();
private:
    QLineF pointForSample(qreal frequency, qreal max_psd, qreal max_psd_moving_avg);
    inline qint64 frame_dt();

private:
    FrequencyTickBuilder *xTickBuilder;
    RingBuffer<qreal, MOVING_AVG_PERIOD> max_psds;
    QLineF lines[MAX_SAMPLES];
    qreal last_psds[MAX_SAMPLES];
    qint64 last_frame_time;
};

#endif // SPECTRUMANALYZER_H
