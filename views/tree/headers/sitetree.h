#ifndef SITETREE_H
#define SITETREE_H
#include <QTreeWidget>
#include <QWidget>
#include <QtWidgets>

class SiteTree : public QTreeWidget
{
    Q_OBJECT
public:
    explicit SiteTree(QWidget *parent = nullptr, QString filePath = nullptr);
    bool checkTransfer(QString source, QString destination);
    void transfer(QString source, QString destination);
    int extractLayerId(QString string);
    int extractHorizonId(QString string);
    void openItem(QString itemText);
private:
    QString filePath;
    QPoint currentDragItemPosition;
    int horizonId; //Global variable used to open the create layer view with a predefined horizon id
    int layerId;
    int objectId;
public slots:
    void showContextMenu(const QPoint& pos);
    void openCL();
    void openVH();
    void openVL();
    void openVO();
    void deleteHorizon();
    void createObject();
    void openItem(QTreeWidgetItem* item,int column);
protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void keyPressEvent(QKeyEvent *event);
signals:
    void openCL(int horizonId);
    void deleteHorizon(int horizonId);
    void openCO(int layerId);
    void openVH(int horizonId);
    void openVL(int layerId);
    void openVO(int objectId);

};

#endif // SITETREE_H
