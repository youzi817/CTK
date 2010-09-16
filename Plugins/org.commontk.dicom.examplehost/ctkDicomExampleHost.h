#ifndef CTKDICOMEXAMPLEHOST_H
#define CTKDICOMEXAMPLEHOST_H

#include <ctkDicomAbstractHost.h>
#include <org_commontk_dicom_examplehost_Export.h>

#include <QUrl>
#include <QProcess>

class org_commontk_dicom_examplehost_EXPORT ctkDicomExampleHost : public ctkDicomAbstractHost{
    Q_OBJECT
public:
    ctkDicomExampleHost(QWidget* placeholderWidget, int hostPort = 8080, int appPort = 8081);

    virtual void StartApplication(QString AppPath);
    virtual QString generateUID() { return ""; }
    virtual QRect getAvailableScreen(const QRect& preferredScreen);
    virtual QString getOutputLocation(const QStringList& /*preferredProtocols*/) { return ""; }
    virtual void notifyStateChanged(ctkDicomWG23::State state);
    virtual void notifyStatus(const ctkDicomWG23::Status& status);
    const QProcess& getAppProcess() const { return appProcess; }
    ~ctkDicomExampleHost();

signals:
    void stateChangedReceived(ctkDicomWG23::State state);
    void statusReceived(const ctkDicomWG23::Status& status);
    void giveAvailableScreen(QRect rect);

protected:
    QProcess appProcess;
    QWidget* placeholderWidget;
    ctkDicomWG23::State applicationState;
};

#endif // CTKDICOMEXAMPLEHOST_H
