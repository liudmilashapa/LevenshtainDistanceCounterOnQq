#pragma once

#include <QtWidgets>
#include "ui_lab1_CFKC.h"

struct DisplayInfo;

class lab1_CFKC : public QMainWindow
{
	Q_OBJECT

public:
	lab1_CFKC(QWidget *parent = Q_NULLPTR);
	QWidget* m_widget;
	QLineEdit* m_word1; 
	QLineEdit* m_word2; 
	QLabel* m_constDifLbl;
	QLabel* m_constSimLbl;
	QLabel* m_difLbl; 
	QLabel* m_simLbl;
	QPushButton* m_resultButtton;
	QTableWidget* m_table=nullptr;

	QBoxLayout* m_mainBoxLayout;
	QBoxLayout* m_dataBoxLayout;
	QBoxLayout* m_tableBoxLayout;
	QBoxLayout* m_inputBoxLayout;
	QBoxLayout* m_resultBoxLayout;
	
	//QGroupBox* gridGroupBox;
	QVector<QLabel> m_displayLabels;
	//QVBoxLayout* mainLayout;

public slots:

	void addDisplatInfoTable(DisplayInfo & _displayInfo, int row);
	void displayTable(QVector<DisplayInfo>&);
//	void clickResult1();

private:
	
	void createMainBox();
	void createTableBox(QBoxLayout & m_mainBoxLayout);
	void createDataBox(QBoxLayout & m_mainBoxLayout);
	void createInputBox(QBoxLayout & m_mainBoxLayout);
	void createResultBox(QBoxLayout & m_mainBoxLayout);

	Ui::lab1_CFKCClass ui;
};
