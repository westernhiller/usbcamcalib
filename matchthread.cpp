#include "matchthread.h"
#include "calibdialog.h"

using namespace std;
using namespace cv;

MatchThread::MatchThread(QObject* parent)
    : QThread(parent)
    , m_arrayIndex(0)
{
    CalibDialog* pDlg = static_cast<CalibDialog*>(parent);
    m_pConfig = pDlg->getConfig();
    m_pImageBuffer = pDlg->getImageBuffer();
}

MatchThread::~MatchThread()
{
    requestInterruption();
    quit();
    wait();
}

bool MatchThread::chessboardStable(vector<Point2f>corners_l, vector<Point2f>corners_r)
{
    if (m_leftCorners.size() < 10) {
        m_leftCorners.push_back(corners_l);
        m_rightCorners.push_back(corners_r);
        return false;
    }
    else {
        m_leftCorners[m_arrayIndex % 10] = corners_l;
        m_rightCorners[m_arrayIndex % 10] = corners_r;
        m_arrayIndex++;
        double error = 0.0;
        for (int i = 0; i < m_leftCorners.size(); i++) {
            for (int j = 0; j < m_leftCorners[i].size(); j++) {
                error += abs(corners_l[j].x - m_leftCorners[i][j].x) + abs(corners_l[j].y - m_leftCorners[i][j].y);
                error += abs(corners_r[j].x - m_rightCorners[i][j].x) + abs(corners_r[j].y - m_rightCorners[i][j].y);
            }
        }
        int th = 1000;

        if (error < th)
        {
            m_leftCorners.clear();
            m_rightCorners.clear();
            m_arrayIndex = 0;
            return true;
        }
        else
            return false;
    }
}

void MatchThread::run()
{
    if(!m_pImageBuffer)
        return;

    Rect right_rect(0, 0, 1280, 960);
    Rect left_rect(1280, 0, 1280, 960);

    while (!isInterruptionRequested())
    {
        FRAMEINFO* pFrameInfo = m_pImageBuffer->readImage();
        if(pFrameInfo && pFrameInfo->matImg.data)
        {
            Mat image_left = Mat(pFrameInfo->matImg, left_rect).clone();
            Mat image_right = Mat(pFrameInfo->matImg, right_rect).clone();
            bool found_l = false, found_r = false;
            vector<Point2f> corners_l, corners_r;

            found_l = findChessboardCorners(image_left, boardSize, corners_l, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);
            found_r = findChessboardCorners(image_right, boardSize, corners_r, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);
            if (found_l && found_r && chessboardStable(corners_l, corners_r))
            {

            }

        }
        usleep(1000);
    }
}

