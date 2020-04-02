#ifndef MATCHTHREAD_H
#define MATCHTHREAD_H

#include <QThread>
#include "camconfig.h"
#include "imagebuffer.h"

class MatchThread : public QThread
{
    Q_OBJECT
public:
    explicit MatchThread(QObject* parent = nullptr);
    ~MatchThread();

signals:
    void updateImages(QImage, QImage);

protected:
    void            run();

private:
    CamConfig*      m_pConfig;
    ImageBuffer*    m_pImageBuffer;
    vector<vector<Point2f> > m_leftCorners, m_rightCorners;
    int             m_arrayIndex;

    bool chessboardStable(vector<Point2f>corners_l, vector<Point2f>corners_r);
};

#endif // MATCHTHREAD_H
