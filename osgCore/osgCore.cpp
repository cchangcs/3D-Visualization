// osgCore.cpp : ���� DLL Ӧ�ó���ĵ���������
//



#include "stdafx.h"
#include "osgCoreLib.h"
#include <Windows.h>
#include <tchar.h>
osgCoreLib* mOSG;

extern "C" __declspec(dllexport) int osgRun(HWND hWnd, bool isfullscreen, int recwidth, int recheight);
extern "C"  __declspec(dllexport) void showChinabound(bool isShowChinaBoundary);
extern "C"  __declspec(dllexport) void fillWorld(bool isFillWorld);
extern "C"  __declspec(dllexport) void showDenggao(bool isShowDengGao);
extern "C"  __declspec(dllexport) void flyTo(double flylat, double flylon, double flyhei);
extern "C"  __declspec(dllexport) void trackFly(bool isTrackFly);
extern "C"  __declspec(dllexport) void trackCar(bool isTrackCar);
extern "C"  __declspec(dllexport) void trackPerson(bool isTrackPerson);
extern "C"  __declspec(dllexport) void testJu(bool isTestJu);
extern "C"  __declspec(dllexport) void setFace();
extern "C"  __declspec(dllexport) void setLine();
extern "C"  __declspec(dllexport) void setPoint();
extern "C"  __declspec(dllexport) void flyXian();
extern "C"  __declspec(dllexport) void flyYanliang();
extern "C"  __declspec(dllexport) void flyAirport();
extern "C"  __declspec(dllexport) void swapStereo();
extern "C"  __declspec(dllexport) void monitor();
extern "C"  __declspec(dllexport) void replyFly(bool isStartFly);
extern "C"  __declspec(dllexport) void replyCar(bool isStartCar);
extern "C"  __declspec(dllexport) void drawFlyLine();
extern "C"  __declspec(dllexport) void clearFlyLine();
extern "C"  __declspec(dllexport) void drawCarLine();
extern "C"  __declspec(dllexport) void clearCarLine();
extern "C"  __declspec(dllexport) void drawPersonLine();
extern "C"  __declspec(dllexport) void clearPersonLine();
extern "C"  __declspec(dllexport) void DoPreLineNow(bool isStart);
extern "C"  __declspec(dllexport) void DoPreLineNow2(bool isStart);
extern "C"  __declspec(dllexport) void DoPreLineNow3(bool isStart);
extern "C"  __declspec(dllexport) void readFlyCoords(char * filename);
extern "C"  __declspec(dllexport) void readCarCoords(char * filename);
extern "C"  __declspec(dllexport) void readPersonCoords(char * filename);

extern "C"  __declspec(dllexport) void addFLyAndMove(char * filename, bool start);

extern "C"  __declspec(dllexport) void addCarAndMove(char * filename, bool start);

extern "C"  __declspec(dllexport) void addPersonAndMove(char * filename, bool start);

extern "C"  __declspec(dllexport) void drawPollution();

extern "C"  __declspec(dllexport) void drawLink();


extern "C"  __declspec(dllexport) void showImageLayer2015();
extern "C"  __declspec(dllexport) void hideImageLayer2015();

extern "C"  __declspec(dllexport) void showImageLayer2017();
extern "C"  __declspec(dllexport) void hideImageLayer2017();

extern "C"  __declspec(dllexport) void showCliassificationImageLayer2015();
extern "C"  __declspec(dllexport) void hideCliassificationImageLayer2015();

extern "C"  __declspec(dllexport) void showCliassificationImageLayer2017();
extern "C"  __declspec(dllexport) void hideCliassificationImageLayer2017();

extern "C"  __declspec(dllexport) void showTransferImage();
extern "C"  __declspec(dllexport) void hideTransferImage();
extern "C"  __declspec(dllexport) void showXinJiangImage();
extern "C"  __declspec(dllexport) void hideXinJiangImage();

extern "C"  __declspec(dllexport) void showSlopeImage();
extern "C"  __declspec(dllexport) void hideSlopeImage();

extern "C"  __declspec(dllexport) void showAspectImage();
extern "C"  __declspec(dllexport) void hideAspectImage();

extern "C"  __declspec(dllexport) void showPollutionImage();
extern "C"  __declspec(dllexport) void hidePollutionImage();

extern "C"  __declspec(dllexport) void showClassLabel();

extern "C"  __declspec(dllexport) void showSpectrumImage2018();
extern "C"  __declspec(dllexport) void hideSpectrumImage2018();

extern "C"  __declspec(dllexport) void showSpectrumImage2019();
extern "C"  __declspec(dllexport) void hideSpectrumImage2019();

extern "C"  __declspec(dllexport) void showSpectrumClassificationImage2018();
extern "C"  __declspec(dllexport) void hideSpectrumClassificationImage2018();

extern "C"  __declspec(dllexport) void showSpectrumClassificationImage2019();
extern "C"  __declspec(dllexport) void hideSpectrumClassificationImage2019();

extern "C"  __declspec(dllexport) void showSpectrumTransferImage();
extern "C"  __declspec(dllexport) void hideSpectrumTransferImage();

extern "C"  __declspec(dllexport) void hideLink();


extern "C"  __declspec(dllexport) void addTerrain();

extern "C"  __declspec(dllexport) void addPersonPoint();

extern "C"  __declspec(dllexport) void modifyPerson(int label);

extern "C"  __declspec(dllexport) void addSensorNetwork();

extern "C"  __declspec(dllexport) void hideSensorNetwork();

extern "C"  __declspec(dllexport) int Add(int x, int y) {
	return x + y;
}

int osgRun(HWND hWnd, bool isfullscreen, int recwidth, int recheight)
{
	/*osgViewer::Viewer viewer;
	viewer.setSceneData(osgDB::readNodeFile("arcgisonline.earth"));
	return viewer.run();*/
	mOSG = new osgCoreLib(hWnd);
	mOSG->InitOSG(isfullscreen, recwidth, recheight);
	return 1;
}


//��ʾ������
void showChinabound(bool isShowChinaBoundary)
{
	if (isShowChinaBoundary)
	{
		mOSG->addChinaBoundaryes();
	}
	else
	{
		mOSG->rmvChinaBoundaryes();
	}
}

//���
void fillWorld(bool isFillWorld) {
	mOSG->FillWorld(isFillWorld);
}


//��ʾ�ȸ�
void showDenggao(bool isShowDengGao) {
	mOSG->ShowDengGao(isShowDengGao);
}

//����
void flyTo(double flylat, double flylon, double flyhei) {
	mOSG->FlyTo(flylon, flylat, flyhei);
}

//���ٷɻ�
void trackFly(bool isTrackFly) {
	mOSG->isTrackFly(isTrackFly);
}

//���ٳ���
void trackCar(bool isTrackCar) {
	mOSG->isTrackCar(isTrackCar);
}

//��������
void trackPerson(bool isTrackPerson) {
	mOSG->isTrackPerson(isTrackPerson);
}

//����
void testJu(bool isTestJu) {
	mOSG->isTestJu(isTestJu);
}

//ת��Ϊ��ṹ
void setFace() {
	int moduleStyle = 0;
	mOSG->setModule(moduleStyle);
}

//ת��Ϊ�߽ṹ
void setLine() {
	int moduleStyle = 1;
	mOSG->setModule(moduleStyle);
}

//ת��Ϊ��ṹ
void setPoint() {
	int moduleStyle = 2;
	mOSG->setModule(moduleStyle);
}

//��������
void flyXian()
{
	mOSG->FlyTo(109.35, 34.45, 400000);
}
//��������
void flyYanliang()
{
	mOSG->FlyTo(109.22735, 34.65471, 40000);
}

//��������
void flyAirport()
{
	mOSG->FlyTo(109.1347, 34.3834, 1000);
}

//��������
void swapStereo()
{
	mOSG->swapStereo();
}

//��Ƶ���
void monitor() {
	//����·��
	mOSG->clearFlyLine();
	mOSG->clearCarLine();
	mOSG->clearPersonLine();
	mOSG->drawFlyLine();
	mOSG->drawCarLine();
	mOSG->drawPersonLine();
	mOSG->DoPreLineNow(false);
	mOSG->DoPreLineNow2(false);;
	mOSG->DoPreLineNow3(false);

	//���˻������������˿�ʼ�ƶ�
	mOSG->DoPreLineNow(true);
	mOSG->DoPreLineNow2(true);
	mOSG->DoPreLineNow3(true);;
}
//�ɻ���Ƶ�ط�
void replyFly(bool isStartFly)
{
	mOSG->clearFlyLine();
	mOSG->clearCarLine();
	mOSG->clearPersonLine();
	mOSG->drawFlyLine();

	mOSG->DoPreLineNow(isStartFly);
	mOSG->DoPreLineNow2(false);;
	mOSG->DoPreLineNow3(false);
}

//������Ƶ�ط�
void replyCar(bool isStartCar) {
	mOSG->clearFlyLine();
	mOSG->clearCarLine();
	mOSG->clearPersonLine();
	mOSG->drawCarLine();
	isStartCar = !isStartCar;
	mOSG->DoPreLineNow2(isStartCar);;
	mOSG->DoPreLineNow(false);
	mOSG->DoPreLineNow3(false);
}

//������Ƶ�ط�
void replyPerson(bool isStartPerson)
{
	mOSG->clearFlyLine();
	mOSG->clearCarLine();
	mOSG->clearPersonLine();
	mOSG->drawPersonLine();
	isStartPerson = !isStartPerson;
	mOSG->DoPreLineNow3(isStartPerson);
	mOSG->DoPreLineNow(false);
	mOSG->DoPreLineNow2(false);
}

void drawFlyLine()
{
	mOSG->drawFlyLine();
}

void clearFlyLine() {
	mOSG->clearFlyLine();
}

void drawCarLine() {
	mOSG->drawCarLine();
}

void clearCarLine() {
	mOSG->clearCarLine();
}

void drawPersonLine() {
	mOSG->drawPersonLine();
}

void clearPersonLine() {
	mOSG->clearPersonLine();
}

void DoPreLineNow(bool isStart) {
	mOSG->DoPreLineNow(isStart);
}

void DoPreLineNow2(bool isStart) {
	mOSG->DoPreLineNow2(isStart);
}

void DoPreLineNow3(bool isStart) {
	mOSG->DoPreLineNow3(isStart);
}

void readFlyCoords(char * filename) {
	mOSG->readFlyCoords(filename);
}

void readCarCoords(char * filename) {
	mOSG->readCarCoords(filename);
}

void readPersonCoords(char * filename) {
	mOSG->readPersonCoords(filename);
}

void addFLyAndMove(char * filename, bool start) {
	mOSG->addFLyAndMove(filename, start);
}

void addCarAndMove(char * filename, bool start) {
	mOSG->addCarAndMove(filename, start);
}

void addPersonAndMove(char * filename, bool start) {
	mOSG->addPersonAndMove(filename, start);
}

void drawPollution() {
	mOSG->drawPollution();
}

void drawLink()
{
	mOSG->drawLink();
}

void hideLink()
{
	mOSG->hideLink();
}

void showImageLayer2015() {
	mOSG->showImageLayer2015();
}
void hideImageLayer2015() {
	mOSG->hideImageLayer2015();
}

void showImageLayer2017() {
	mOSG->showImageLayer2017();
}
void hideImageLayer2017() {
	mOSG->hideImageLayer2017();
}

void showCliassificationImageLayer2015() {
	mOSG->showCliassificationImageLayer2015();
}
void hideCliassificationImageLayer2015() {
	mOSG->hideCliassificationImageLayer2015();
}

void showCliassificationImageLayer2017() {
	mOSG->showCliassificationImageLayer2017();
}
void hideCliassificationImageLayer2017() {
	mOSG->hideCliassificationImageLayer2017();
}

void showTransferImage() {
	mOSG->showTransferImage();
}
void hideTransferImage() {
	mOSG->hideTransferImage();
}

void showXinJiangImage() {
	mOSG->showXinJiangImage();
}
void hideXinJiangImage() {
	mOSG->hideXinJiangImage();
}

void showSlopeImage() {
	mOSG->showSlopeImage();
}
void hideSlopeImage() {
	mOSG->hideSlopeImage();
}

void showAspectImage() {
	mOSG->showAspectImage();
}
void hideAspectImage() {
	mOSG->hideAspectImage();
}

void showPollutionImage() {
	mOSG->showPollutionImage();
}
void hidePollutionImage() {
	mOSG->hidePollutionImage();
}
void showClassLabel()
{
	mOSG->showClassLabel();
}

void showSpectrumImage2018() {
	mOSG->showSpectrumImage2018();
}
void hideSpectrumImage2018() {
	mOSG->hideSpectrumImage2018();
}

void showSpectrumImage2019() {
	mOSG->showSpectrumImage2019();
}
void hideSpectrumImage2019() {
	mOSG->hideSpectrumImage2019();
}

void showSpectrumClassificationImage2018() {
	mOSG->showSpectrumClassificationImage2018();
}
void hideSpectrumClassificationImage2018(){
	mOSG->hideSpectrumClassificationImage2018();
}
void showSpectrumClassificationImage2019() {
	mOSG->showSpectrumClassificationImage2019();
}

void hideSpectrumClassificationImage2019(){
	mOSG->hideSpectrumClassificationImage2019();
}

void showSpectrumTransferImage() {
	mOSG->showSpectrumTransferImage();
}
void hideSpectrumTransferImage() {
	mOSG->hideSpectrumTransferImage();
}

void addTerrain() {
	mOSG->addTerrain();
}

void addPersonPoint() {
	mOSG->addPersonPoint();
}

void modifyPerson(int label) {
	mOSG->modifyPerson(label);
}

//��ʾ����������
void addSensorNetwork()
{
	mOSG->addSensorNetwork();
}

//���ش���������
void hideSensorNetwork()
{
	mOSG->hideSensorNetwork();
}