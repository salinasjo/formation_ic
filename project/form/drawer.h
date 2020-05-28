#ifndef DRAWER_H
#define DRAWER_H

#include <QWidget>
#include <QLabel>
#include <QFileSystemWatcher>
#include <include/DiscreteMap.h>

namespace Ui {
class drawer;
}

class drawer : public QWidget
{
    Q_OBJECT

public:
    explicit drawer(DiscreteMap & _dMap,QWidget *parent = nullptr);
    ~drawer() override;

signals:
    void signalPointSelected(double x, double y, double z, double fuel, double time, double angle);

private slots:
    void paintEvent(QPaintEvent*) override;
    void on_drawer_customContextMenuRequested(const QPoint &pos);
    void mousePressEvent(QMouseEvent *event) override;
    void AddPoint();
    void DeletePoint();
    void ExportTrajectory();
    void VerifyTrajectory();
    void OnZChanged(double z);
    void IsLoaded(QString fileName);
private:
    void AddControls();
    void SendSignalPointSelected(double x, double y, double z, double fuel, double time, double angle);



private:
    Ui::drawer *ui;
    DiscreteMap & _dMap;

    QPoint _lastAddedPoint;
    unsigned int _lastSelectedIndex;
    QFileSystemWatcher _watcher;

    void ShowContextMenu(const QPoint&);
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;


};

#endif // DRAWER_H
