#include "navigationbar.h"

NavigationBar::NavigationBar(QWidget *parent)
    : QWidget(parent),
      m_layout(new QVBoxLayout(this)),
      m_buttonsGroup(new QButtonGroup)
{
    m_buttonsName << tr("Introduction") << tr("Desktop mode") << tr("Icon theme")
                  << tr("Window effect") << tr("Support us") << tr("About us");
    m_layout->setSpacing(0);
    m_layout->setMargin(0);

    setFixedWidth(200);
    initUI();

    connect(m_buttonsGroup, SIGNAL(buttonClicked(int)), this, SIGNAL(currentIndexChanged(int)));
}

NavigationBar::~NavigationBar()
{
}

void NavigationBar::initUI()
{
    m_layout->addStretch();
    for (int i = 0; i < m_buttonsName.count(); ++i) {
        QPushButton *btn = new QPushButton(m_buttonsName.at(i));
        btn->setCheckable(true);
        btn->setObjectName("NavButton");
        btn->setFixedSize(width(), 40);
        m_layout->addWidget(btn);
        m_buttonsGroup->addButton(btn, i);

        if (i == 0) {
            btn->setChecked(true);
        }
    }
    m_layout->addStretch();
}
