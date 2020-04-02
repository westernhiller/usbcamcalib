#ifndef CAMCONFIG_H
#define CAMCONFIG_H

#include <QString>

class CamConfig
{
public:
    CamConfig(QString);
    ~CamConfig();

    bool    loadConfig(QString);
    bool    saveConfig();

    inline QString camId() { return m_camid;}
    inline int width() { return m_nWidth;}
    inline int height() { return m_nHeight;}

private:
    QString m_cfgFile;
    QString m_camid;
    int m_nWidth;
    int m_nHeight;
};

#endif // CAMCONFIG_H

