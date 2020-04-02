#include "calibdialog.h"
#include <QLayout>
#include "canvas.h"
#include "global.h"

using namespace std;
using namespace cv;

CalibDialog::CalibDialog(QString cfgfile, QWidget *parent)
    : QDialog(parent)
{
    m_pConfig = new CamConfig(cfgfile);
    m_pImageBuffer = new ImageBuffer("stereo", 10, m_pConfig->width(), m_pConfig->height(), CV_8UC3);

    m_pCapturer = new CaptureThread(this);
    m_pMatcher = new MatchThread(this);

    connect(m_pMatcher, SIGNAL(updateImages(QImage, QImage)), this, SLOT(updateImages(QImage, QImage)));

    QHBoxLayout* pLayout = new QHBoxLayout();
    Canvas* leftImage = new Canvas();
    Canvas* rightImage = new Canvas();

    connect(this, SIGNAL(updateLeftImage(QImage)), leftImage, SLOT(updateImage(QImage)));
    connect(this, SIGNAL(updateRightImage(QImage)), rightImage, SLOT(updateImage(QImage)));

    pLayout->addWidget(leftImage);
    pLayout->addWidget(rightImage);
    setLayout(pLayout);

    m_pMatcher->start();
    m_pCapturer->start();
}

CalibDialog::~CalibDialog()
{
    if(m_pConfig)
        delete m_pConfig;
}

void CalibDialog::updateImages(QImage leftImage, QImage rightImage)
{
    emit updateLeftImage(leftImage);
    emit updateRightImage(rightImage);
}
