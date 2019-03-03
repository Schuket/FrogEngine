/********************************************************************************
** Form generated from reading UI file 'QfeMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QFEMAINWINDOW_H
#define UI_QFEMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include "qfeeditorinspector.h"
#include "qfeeditortree.h"
#include "qfeinspectordock.h"
#include "qfetreeviewdock.h"

QT_BEGIN_NAMESPACE

class Ui_QfeMainWindowClass
{
public:
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionInspector;
    QAction *actionTreeView;
    QAction *actionAddEmptyObject;
    QAction *actionAddCube;
    QAction *actionAddSphere;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuSimulation;
    QMenu *menuWindow;
    QMenu *menuCreate;
    QMenu *menuAdd;
    QMenu *menuObject;
    QfeTreeViewDock *TreeViewDock;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QfeEditorTree *EngineTree;
    QfeInspectorDock *InspectorDock;
    QWidget *dockWidgetContents_2;
    QHBoxLayout *horizontalLayout;
    QfeEditorInspector *Inspector;
    QDockWidget *RenderDock;
    QWidget *dockWidgetContents_4;
    QHBoxLayout *horizontalLayout_3;
    QWidget *RenderWidget;

    void setupUi(QMainWindow *QfeMainWindowClass)
    {
        if (QfeMainWindowClass->objectName().isEmpty())
            QfeMainWindowClass->setObjectName(QStringLiteral("QfeMainWindowClass"));
        QfeMainWindowClass->resize(1418, 720);
        actionStart = new QAction(QfeMainWindowClass);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        actionStop = new QAction(QfeMainWindowClass);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        actionInspector = new QAction(QfeMainWindowClass);
        actionInspector->setObjectName(QStringLiteral("actionInspector"));
        actionInspector->setCheckable(true);
        actionTreeView = new QAction(QfeMainWindowClass);
        actionTreeView->setObjectName(QStringLiteral("actionTreeView"));
        actionTreeView->setCheckable(true);
        actionAddEmptyObject = new QAction(QfeMainWindowClass);
        actionAddEmptyObject->setObjectName(QStringLiteral("actionAddEmptyObject"));
        actionAddCube = new QAction(QfeMainWindowClass);
        actionAddCube->setObjectName(QStringLiteral("actionAddCube"));
        actionAddSphere = new QAction(QfeMainWindowClass);
        actionAddSphere->setObjectName(QStringLiteral("actionAddSphere"));
        centralWidget = new QWidget(QfeMainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QfeMainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QfeMainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1418, 21));
        menuSimulation = new QMenu(menuBar);
        menuSimulation->setObjectName(QStringLiteral("menuSimulation"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuCreate = new QMenu(menuWindow);
        menuCreate->setObjectName(QStringLiteral("menuCreate"));
        menuAdd = new QMenu(menuBar);
        menuAdd->setObjectName(QStringLiteral("menuAdd"));
        menuObject = new QMenu(menuAdd);
        menuObject->setObjectName(QStringLiteral("menuObject"));
        QfeMainWindowClass->setMenuBar(menuBar);
        TreeViewDock = new QfeTreeViewDock(QfeMainWindowClass);
        TreeViewDock->setObjectName(QStringLiteral("TreeViewDock"));
        TreeViewDock->setFocusPolicy(Qt::ClickFocus);
        TreeViewDock->setFloating(false);
        TreeViewDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidgetContents->sizePolicy().hasHeightForWidth());
        dockWidgetContents->setSizePolicy(sizePolicy);
        dockWidgetContents->setFocusPolicy(Qt::ClickFocus);
        horizontalLayout_2 = new QHBoxLayout(dockWidgetContents);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        EngineTree = new QfeEditorTree(dockWidgetContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        EngineTree->setHeaderItem(__qtreewidgetitem);
        EngineTree->setObjectName(QStringLiteral("EngineTree"));
        sizePolicy.setHeightForWidth(EngineTree->sizePolicy().hasHeightForWidth());
        EngineTree->setSizePolicy(sizePolicy);
        EngineTree->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout_2->addWidget(EngineTree);

        TreeViewDock->setWidget(dockWidgetContents);
        QfeMainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), TreeViewDock);
        InspectorDock = new QfeInspectorDock(QfeMainWindowClass);
        InspectorDock->setObjectName(QStringLiteral("InspectorDock"));
        InspectorDock->setMouseTracking(false);
        InspectorDock->setFocusPolicy(Qt::ClickFocus);
        InspectorDock->setFloating(false);
        InspectorDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
        InspectorDock->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        sizePolicy.setHeightForWidth(dockWidgetContents_2->sizePolicy().hasHeightForWidth());
        dockWidgetContents_2->setSizePolicy(sizePolicy);
        dockWidgetContents_2->setFocusPolicy(Qt::ClickFocus);
        horizontalLayout = new QHBoxLayout(dockWidgetContents_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Inspector = new QfeEditorInspector(dockWidgetContents_2);
        Inspector->setObjectName(QStringLiteral("Inspector"));
        sizePolicy.setHeightForWidth(Inspector->sizePolicy().hasHeightForWidth());
        Inspector->setSizePolicy(sizePolicy);
        Inspector->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout->addWidget(Inspector);

        InspectorDock->setWidget(dockWidgetContents_2);
        QfeMainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(4), InspectorDock);
        RenderDock = new QDockWidget(QfeMainWindowClass);
        RenderDock->setObjectName(QStringLiteral("RenderDock"));
        RenderDock->setFocusPolicy(Qt::ClickFocus);
        RenderDock->setFloating(false);
        RenderDock->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QStringLiteral("dockWidgetContents_4"));
        sizePolicy.setHeightForWidth(dockWidgetContents_4->sizePolicy().hasHeightForWidth());
        dockWidgetContents_4->setSizePolicy(sizePolicy);
        dockWidgetContents_4->setFocusPolicy(Qt::ClickFocus);
        horizontalLayout_3 = new QHBoxLayout(dockWidgetContents_4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        RenderWidget = new QWidget(dockWidgetContents_4);
        RenderWidget->setObjectName(QStringLiteral("RenderWidget"));
        sizePolicy.setHeightForWidth(RenderWidget->sizePolicy().hasHeightForWidth());
        RenderWidget->setSizePolicy(sizePolicy);
        RenderWidget->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout_3->addWidget(RenderWidget);

        RenderDock->setWidget(dockWidgetContents_4);
        QfeMainWindowClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), RenderDock);

        menuBar->addAction(menuSimulation->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuBar->addAction(menuAdd->menuAction());
        menuSimulation->addAction(actionStart);
        menuSimulation->addAction(actionStop);
        menuWindow->addAction(menuCreate->menuAction());
        menuCreate->addAction(actionInspector);
        menuCreate->addAction(actionTreeView);
        menuAdd->addAction(actionAddEmptyObject);
        menuAdd->addAction(menuObject->menuAction());
        menuObject->addAction(actionAddCube);
        menuObject->addAction(actionAddSphere);

        retranslateUi(QfeMainWindowClass);

        QMetaObject::connectSlotsByName(QfeMainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *QfeMainWindowClass)
    {
        QfeMainWindowClass->setWindowTitle(QApplication::translate("QfeMainWindowClass", "QfeMainWindow", Q_NULLPTR));
        actionStart->setText(QApplication::translate("QfeMainWindowClass", "Start", Q_NULLPTR));
        actionStop->setText(QApplication::translate("QfeMainWindowClass", "Stop", Q_NULLPTR));
        actionInspector->setText(QApplication::translate("QfeMainWindowClass", "Inspector", Q_NULLPTR));
        actionTreeView->setText(QApplication::translate("QfeMainWindowClass", "TreeView", Q_NULLPTR));
        actionAddEmptyObject->setText(QApplication::translate("QfeMainWindowClass", "EmptyObject", Q_NULLPTR));
        actionAddCube->setText(QApplication::translate("QfeMainWindowClass", "Cube", Q_NULLPTR));
        actionAddSphere->setText(QApplication::translate("QfeMainWindowClass", "Sphere", Q_NULLPTR));
        menuSimulation->setTitle(QApplication::translate("QfeMainWindowClass", "Simulation", Q_NULLPTR));
        menuWindow->setTitle(QApplication::translate("QfeMainWindowClass", "Window", Q_NULLPTR));
        menuCreate->setTitle(QApplication::translate("QfeMainWindowClass", "Add", Q_NULLPTR));
        menuAdd->setTitle(QApplication::translate("QfeMainWindowClass", "Add", Q_NULLPTR));
        menuObject->setTitle(QApplication::translate("QfeMainWindowClass", "Object", Q_NULLPTR));
        TreeViewDock->setWindowTitle(QApplication::translate("QfeMainWindowClass", "Project View", Q_NULLPTR));
        InspectorDock->setWindowTitle(QApplication::translate("QfeMainWindowClass", "Inspector", Q_NULLPTR));
        RenderDock->setWindowTitle(QApplication::translate("QfeMainWindowClass", "Scene", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QfeMainWindowClass: public Ui_QfeMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QFEMAINWINDOW_H
