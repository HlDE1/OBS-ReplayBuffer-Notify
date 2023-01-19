#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QScreen>
#include <QString>
#include <QLabel>
#include <QPropertyAnimation>
#include <QThread>
#include <QTimer>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>

#include <iostream>
#include <fstream>
//Linker -> General -> OutputFile= $(OutDir)$(TargetName)$(TargetExt)
//$(OutDir)obs-notify$(TargetExt)
using namespace std;

int wWidth = 450;
int wHeight = 130;

int GetTextWidth(QString labelText, int fontSize)
{

	QFont myFont("Segoe UI", fontSize);
	QFontMetrics fm(myFont);
	int labelWidth = fm.horizontalAdvance(labelText);
	return labelWidth;
}

QPropertyAnimation* AnimationPreset(int Duration, MainWindow& w, int startX, int endX)
{
	QPropertyAnimation* animation = new QPropertyAnimation(&w, "geometry");

	animation->setDuration(Duration);
	animation->setStartValue(QRect(startX, 50, wWidth, wHeight));
	animation->setEndValue(QRect(endX, 50, wWidth, wHeight));
	return animation;
}


QLabel* CustomLabel(MainWindow& w, QString labelText, bool isCentered = false, int FontSize = 25)
{
	QLabel* label = new QLabel(labelText, &w);
	int labelWidth = GetTextWidth(labelText, FontSize);
	int labelHeight = label->height();
	label->setFixedSize(labelWidth, labelHeight);

	qDebug("%s %i", labelText, labelWidth);
	if (isCentered)
		label->move((wWidth - labelWidth) / 2, (wHeight - labelHeight) / 2);

	QString styleQString = QString("color: %1;font-size: %2px").arg("white").arg(FontSize);
	string styleString = styleQString.toStdString();
	const char* formattedStyle = styleString.c_str();
	label->setStyleSheet(formattedStyle);

	return label;
}


void setArgVariables(char* argv[], function<void()> func)
{
	try
	{
		func();
	}
	catch (exception(ex))
	{
		//qDebug("%s", ex.what());
		//ofstream errorLog;
		//errorLog.open("ErrorLog.txt", std::ios_base::app); // append instead of overwrite
		//errorLog << "Data";

		ofstream MyFile("ErrorLog.txt");
		MyFile << ex.what();
	}
}


void SetTextFile(const char* FileText)
{
	ofstream MyFile("Test.txt");
	MyFile << FileText;
}


int main(int argc, char* argv[])
{

	QApplication a(argc, argv);

	/*if (argc != 8)
	{
		//ofstream MyFile("filename.txt");
		//MyFile << argc;

		QTimer::singleShot(1, &a, SLOT(quit()));
		return a.exec();
	}
	*/





	/*float animationHoldTime = 2500;
	float animationFadeTime = 400;
	bool showNotification = true;
	bool showPath = true;
	bool isSound = true;
	float NotificationVolume = 0.2f;
	*/

	//obs-notify.exe 2500.00 400.00 false false false 50 KOK
	float animationHoldTime = strtod(argv[1], NULL) == 0 ? 2700 : strtod(argv[1], NULL); //2500.00
	float animationFadeTime = strtod(argv[2], NULL) == 0 ? 400 : strtod(argv[2], NULL);  //400.00f;
	bool showNotification = !stricmp(argv[3], "true");
	bool showPath = !stricmp(argv[4], "true");
	bool isSound = !stricmp(argv[5], "true");
	float NotificationVolume = strtod(argv[6], NULL) / 100;
	QString PathText = argv[7]; //R"(D:\Coding\OBS Plugin\Qt Animation VS\obs-notify-animationVS\x64\Release)";//argv[7];

	//ofstream MyFile("Test.txt");
	//MyFile << showNotification;// << argv[3] << stricmp(argv[3], "true");//<< showPath << isSound;

	//qDebug("%B", showNotification);
	//SetTextFile((char*)showNotification);

	MainWindow w;
	QRect screenRect = a.primaryScreen()->geometry();

	QString labelText = "Replay saved";
	QLabel* label = CustomLabel(w, labelText, true);

	if (showPath)
	{
		QLabel* pathLabel = CustomLabel(w, PathText, false, 12);
		pathLabel->move(0, (wHeight - pathLabel->height()));
	}

	QMediaPlayer* player = new QMediaPlayer(&w);
	QAudioOutput* audioOutput = new QAudioOutput(&w);


	player->setAudioOutput(audioOutput);
	audioOutput->setVolume(NotificationVolume);
	player->setSource(QUrl::fromLocalFile(R"(D:/Coding/OBS Plugin/Testing2/NotifySound.wav)"));


	w.setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow);
	w.move(screenRect.left() - wWidth, screenRect.top() + 50);
	//w.move(screenRect.left(), screenRect.top() + 50);
	w.setFixedSize(wWidth, wHeight);
	w.setStyleSheet("background-color: rgb(4, 2, 25);");

	QPropertyAnimation* startAnimation = AnimationPreset(animationFadeTime, w, -wWidth, showNotification ? 0 : -wWidth);
	QPropertyAnimation* closeAnimation = AnimationPreset(animationFadeTime, w, 0, -wWidth);


	QObject::connect(closeAnimation, &QPropertyAnimation::finished, &w, std::function([&]()
		{
			QApplication::quit();
		}));

	QObject::connect(startAnimation, &QPropertyAnimation::finished, &w, std::function([&]()
		{
			if (!showNotification)
			{
				QTimer::singleShot(2000, &a, SLOT(quit()));
				return;
			}
			QTimer::singleShot(animationHoldTime, closeAnimation, SLOT(start()));
		}));



	startAnimation->start();
	


	if (isSound)
		player->play();

	w.show();
	return a.exec();
}
