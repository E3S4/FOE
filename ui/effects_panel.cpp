#include "effects_panel.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTreeWidget>
#include <QDrag>

EffectsPanel::EffectsPanel(QWidget *p): QWidget(p) {
    auto *layout = new QVBoxLayout(this);
    auto *search = new QLineEdit;  search->setPlaceholderText("Search Effects…");
    auto *tree   = new QTreeWidget;
    tree->setHeaderHidden(true);
    auto *blurCat = new QTreeWidgetItem(tree, {"Blur"});
    new QTreeWidgetItem(blurCat, {"Gaussian Blur"});
    new QTreeWidgetItem(blurCat, {"Directional Blur"});
    tree->expandAll();
    tree->setStyleSheet(R"(
    QTreeWidget {
        background: #303030;
        color: #ffffff;
        selection-background-color: #505050;
    }
    QTreeWidget::item {
        height: 24px;
    }
)");
    layout->addWidget(search);
    layout->addWidget(tree);
}

