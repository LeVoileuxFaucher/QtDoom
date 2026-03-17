/*
Author: Léanne Héroux
Date: Febuary 24, 2026
File name: levelpage.h
Description: Code for the page where the levels are selected
Modifications:
*/
#ifndef LEVELPAGE_H
#define LEVELPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>

class LevelPage : public QWidget
{
    Q_OBJECT

public:
    LevelPage(QWidget *parent = nullptr);

    QPushButton* quitterButton() const { return m_quitterButton; }
    QPushButton* niveau1Button() const { return m_niveau1Button; }
    QPushButton* niveau2Button() const { return m_niveau2Button; }
    QPushButton* niveau3Button() const { return m_niveau3Button; }
    void level_1Clicked();
    void level_2Clicked();
    void level_3Clicked();
    void level_quitClicked();

private:
    QLabel *m_label;
    QFont fontButton;
    QFont fontLabel;
    QPushButton *m_quitterButton;
    QPushButton *m_niveau1Button;
    QPushButton *m_niveau2Button;
    QPushButton *m_niveau3Button;
    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;
    QHBoxLayout *levelsLayout;
    QVector<QPushButton*> menuButtons;

    int currentIndex=0;
    void addTitleLevel();
    void addQuitButton();
    void addLevelButtons();
    void addQuitButtonLayout();
    void addLevelButtonsLayout();
    void addPageLayout();
    void connectButtons();

public slots:
    void changeButtons();
    void setupNextSelect();
    void updateHighlight();
    void activateSelectedButton();

signals:
    void level_1ClickedSig();
    void level_2ClickedSig();
    void level_3ClickedSig();
    void level_quitClickedSig();
};

#endif // LEVELPAGE_H
