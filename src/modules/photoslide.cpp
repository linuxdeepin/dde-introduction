#include "photoslide.h"

#include <DHiDPIHelper>
#include <QPainter>

DWIDGET_USE_NAMESPACE

PhotoSlide::PhotoSlide(QWidget *parent)
    : ModuleInterface(parent)
{
    m_selectBtn->hide();

    container_label_ = new QLabel(this);

    pos_animation_ = new QPropertyAnimation(container_label_, "pos", this);

    opacity_effect_ = new QGraphicsOpacityEffect(container_label_);
    container_label_->setGraphicsEffect(opacity_effect_);
    opacity_animation_ = new QPropertyAnimation(opacity_effect_, "opacity", this);
    opacity_animation_->setKeyValueAt(0.0, 0.0);
    opacity_animation_->setKeyValueAt(0.1, 1.0);
    opacity_animation_->setKeyValueAt(0.9, 1.0);
    opacity_animation_->setKeyValueAt(1.0, 0.0);

    null_animation_ = new QVariantAnimation(this);

    animation_group_ = new QParallelAnimationGroup(this);
    animation_group_->setLoopCount(-1);

    connect(animation_group_, &QParallelAnimationGroup::currentLoopChanged, this, &PhotoSlide::updateSlideImage);

    updateBigIcon();
}

void PhotoSlide::updateBigIcon()
{
    const QSize size(700, 450);
    setFixedSize(size);
    container_label_->setFixedSize(size);

    QStringList list;
    for (int i = 1; i != 9; i++) {
        list << QString(":/resources/slide_big/0%1.jpg").arg(i);
    }

    setPhotoList(list);

    pos_animation_->setKeyValueAt(0.0, QPoint(-50, 0));
    pos_animation_->setKeyValueAt(0.1, QPoint(0, 0));
    pos_animation_->setKeyValueAt(0.9, QPoint(0, 0));
    pos_animation_->setKeyValueAt(1.0, QPoint(50, 0));
}

void PhotoSlide::updateSmallIcon()
{
    const QSize size(550, 346);
    setFixedSize(size);
    container_label_->setFixedSize(size);

    QStringList list;
    for (int i = 1; i != 9; i++) {
        list << QString(":/resources/slide_small/0%1.jpg").arg(i);
    }

    setPhotoList(list);

    pos_animation_->setKeyValueAt(0.0, QPoint(-50, 0));
    pos_animation_->setKeyValueAt(0.1, QPoint(15, 0));
    pos_animation_->setKeyValueAt(0.9, QPoint(15, 0));
    pos_animation_->setKeyValueAt(1.0, QPoint(50, 0));
}

void PhotoSlide::updateSelectBtnPos() {}

void PhotoSlide::start(bool disable_slide, bool disable_animation, int duration)
{
    // Read the first slide image.
    slide_index_ = 0;
    updateSlideImage();

    if (disable_slide) {
        qDebug() << "slide disabled";
        return;
    }

    animation_group_->clear();
    if (disable_animation) {
        qDebug() << "slide animation disabled";
        null_animation_->setDuration(duration);
        animation_group_->addAnimation(null_animation_);
    }
    else {
        pos_animation_->setDuration(duration);
        animation_group_->addAnimation(pos_animation_);
        opacity_animation_->setDuration(duration);
        animation_group_->addAnimation(opacity_animation_);
    }
    animation_group_->start();
}

void PhotoSlide::stop()
{
    animation_group_->stop();
}

void PhotoSlide::setPhotoList(const QStringList &list)
{
    if (m_photoList == list) return;

    m_photoList = list;
}

void PhotoSlide::updateSlideImage()
{
    const QString filepath(m_photoList[slide_index_]);

    if (QFile::exists(filepath)) {
        QPixmap pixmap = DHiDPIHelper::loadNxPixmap(filepath);
        //        pixmap = pixmap.scaled(700, 450, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        container_label_->setPixmap(pixmap);
    }
    else {
        qWarning() << "slide file not found:" << filepath;
    }

    container_label_->show();
    slide_index_ = (slide_index_ + 1) % m_photoList.length();
}
