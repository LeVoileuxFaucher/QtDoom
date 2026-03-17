#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QMainWindow>
#include <QStackedWidget>
#include "menupage.h"
#include "gamepage.h"
#include "levelpage.h"

class UIManager : public QWidget
{
    Q_OBJECT

public:
    UIManager(QGraphicsView *view, QWidget *parent = nullptr);
    GamePage* getGamePage();
    MenuPage* getMenuPage();
    LevelPage* getLevelPage();
    void changeButtons();
    void setupNextSelect();
    void updateHighlight();
    void activateSelectedButton();

private:
    QStackedWidget *stackedWidget;
    MenuPage *menuPage;
    GamePage *gamePage;
    LevelPage *levelPage;
    bool potTurns=false;
    bool shootPress=false;

signals:
    void startGame();
    void keyReleaseSig(QKeyEvent *event);
    void keyPressSig(QKeyEvent *event);
    void pauseGame();

public slots:
    void potIsTurning();
    void potStops();
    void shootPressed();
    void shootReleased();
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void updateBalles(int value);
    void updateVie(int value);
};

#endif // UIMANAGER_H
