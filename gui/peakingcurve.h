#ifndef PEAKINGCURVE_H
#define PEAKINGCURVE_H

#include "curvepoint.h"
#include "filtercurve.h"

#include <QBrush>
#include <QGraphicsItem>
#include <QObject>
#include <QPen>

#include <memory>

typedef enum SplinePart {
    SplineLeft,
    SplineRight,
} SplinePart;

class PeakingCurve : public QObject, public FilterCurve
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit PeakingCurve(QPen pen, QBrush brush, bool guiOnly = false, QObject *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QPointF controlPoint() const override;

    // FilterCurve interface
public:
    void reset() override;

private:
    void updateSplineGeometry();

public slots:
    void pointPositionChanged(CurvePoint *point);
    void pointSlopeChanged(int delta);
signals:
    void resync(FilterCurve *curve);
    void filterParamsChanged(ShimFilterPtr filter, PeakingCurve *curve);

private:
    QPointF p0, p1, c1, c2, ip;
    std::unique_ptr<QPainterPath> lineSpline, fillSpline;
};

#endif // PEAKINGCURVE_H
