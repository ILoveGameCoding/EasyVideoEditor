#include "PlayVideo.h"

PlayVideo::PlayVideo(QObject* parent) : QThread(parent) {

}

void PlayVideo::run() {
    EasyVideoEditor::mutex.lock();
    int startIndex = EveProject::getInstance()->getCurrentFrameNumber();
    int endIndex = EveProject::getInstance()->getFrameList()->size();
    int delay = EveProject::getInstance()->getBaseDelay();
    QLabel* lblVideoFrame = Widgets::getInstance()->contentArea->findChild<QWidget*>("w_videoarea")->findChild<QLabel*>("lbl_videoframe");
    QLabel* lblCurrentPlayTime = Widgets::getInstance()->contentArea->findChild<QWidget*>("w_videoarea")->findChild<QWidget*>("w_videocontrolarea")->findChild<QLabel*>("lbl_currentplaytime");
    QLabel* lblMaxPlayTime = Widgets::getInstance()->contentArea->findChild<QWidget*>("w_videoarea")->findChild<QWidget*>("w_videocontrolarea")->findChild<QLabel*>("lbl_maxplaytime");
    QSlider* sdVideoProgress = Widgets::getInstance()->contentArea->findChild<QWidget*>("w_videoarea")->findChild<QWidget*>("w_videocontrolarea")->findChild<QSlider*>("sd_videoprogress");
    QPushButton* btnPlay = Widgets::getInstance()->contentArea->findChild<QWidget*>("w_videoarea")->findChild<QWidget*>("w_videocontrolarea")->findChild<QPushButton*>("btn_play");;
    QPushButton* btnPause = Widgets::getInstance()->contentArea->findChild<QWidget*>("w_videoarea")->findChild<QWidget*>("w_videocontrolarea")->findChild<QPushButton*>("btn_pause");;
    
    lblMaxPlayTime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(endIndex)));
    sdVideoProgress->setMaximum(endIndex - 1);
    EasyVideoEditor::mutex.unlock();

    cv::TickMeter tickMeter;
    cv::Mat showFrame;
    int loop;
    int loopTemp;

    for (loop = startIndex; loop < endIndex; loop++) {
        tickMeter.reset();
        EasyVideoEditor::mutex.lock();
        tickMeter.start();
        if (EasyVideoEditor::mode != EasyVideoEditor::Mode::MODE_WATCH_PLAY) { 
            EasyVideoEditor::mutex.unlock();
            break; 
        }

        loop = EveProject::getInstance()->getCurrentFrameNumber();
        lblCurrentPlayTime->setText(UsefulFunction::getStringFromMilliseconds(EveProject::getInstance()->getFrameTime(loop)));
        sdVideoProgress->setValue(loop);

        EveProject::getInstance()->getCurrentFrameAndUpdate()->getCommandAppliedFrameData(&showFrame, (loop > loopTemp + 1) || (loop < loopTemp));
        UsefulFunction::showMatToLabel(lblVideoFrame, &showFrame, EasyVideoEditor::resizeData, EasyVideoEditor::top, EasyVideoEditor::down, EasyVideoEditor::left, EasyVideoEditor::right);
        tickMeter.stop();
        EasyVideoEditor::mutex.unlock();

        int processingTime = tickMeter.getTimeMilli();
        if (processingTime < delay) {
            msleep(delay - processingTime);
        }
        loopTemp = loop;
    }

    if (loop == endIndex) {
        EasyVideoEditor::mutex.lock();
        btnPlay->setVisible(true);
        btnPause->setVisible(false);
        EasyVideoEditor::mode = EasyVideoEditor::Mode::MODE_WATCH_PAUSE;
        EasyVideoEditor::mutex.unlock();
    }
}