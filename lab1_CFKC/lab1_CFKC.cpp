#include "lab1_CFKC.h"
#include "LevenCounter.h"
lab1_CFKC::lab1_CFKC(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_widget = new  QWidget();
	setCentralWidget(m_widget);
	createMainBox();
}

void lab1_CFKC::createInputBox(QBoxLayout& _mainBoxLayout)
{
	m_inputBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	_mainBoxLayout.addLayout(m_inputBoxLayout);
	m_word1 = new QLineEdit();
	m_word2 = new QLineEdit();
	m_inputBoxLayout->addWidget(m_word1);
	m_inputBoxLayout->addWidget(m_word2);
}

void lab1_CFKC::createResultBox(QBoxLayout& _mainBoxLayout)
{
	m_resultBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	_mainBoxLayout.addLayout(m_resultBoxLayout);

	m_difLbl = new QLabel();
	m_simLbl = new QLabel();
	QFont font = m_difLbl->font();
	font.setPointSize(20);
	m_difLbl->setFont(font);
	m_simLbl->setFont(font);

	m_resultButtton = new QPushButton(("Calculate"));

	m_constDifLbl = new QLabel("Difference");
	m_constSimLbl = new QLabel("Similarity");

	m_resultBoxLayout->addWidget(m_resultButtton);
	m_resultBoxLayout->addWidget(m_constDifLbl);
	m_resultBoxLayout->addWidget(m_difLbl);
	m_difLbl->setContentsMargins(35, 10, 20, 10);
	m_constDifLbl->setContentsMargins(20, 0, 20, 0);
	m_resultBoxLayout->addWidget(m_constSimLbl);
	m_resultBoxLayout->addWidget(m_simLbl);
	m_simLbl->setContentsMargins(35, 10, 20, 10);
	m_constSimLbl->setContentsMargins(20, 0, 20, 0);

}

void lab1_CFKC::createDataBox(QBoxLayout & _mainBoxLayout)
{
	m_dataBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	_mainBoxLayout.addLayout(m_dataBoxLayout);
	createInputBox(*m_dataBoxLayout);
	createResultBox(*m_dataBoxLayout);
}

void lab1_CFKC::createTableBox(QBoxLayout & _mainBoxLayout)
{
	m_tableBoxLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	_mainBoxLayout.addLayout(m_tableBoxLayout);
}

void lab1_CFKC::createMainBox()
{
	m_mainBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	m_widget->setLayout(m_mainBoxLayout);
	createDataBox(* m_mainBoxLayout);
	createTableBox(* m_mainBoxLayout);
}

void lab1_CFKC::addDisplatInfoTable(DisplayInfo & _displayInfo, int row)
{
	for (int i = 0; i < _displayInfo.m_symvolBase.size(); i++)
	{
		QColor color;
		std::string string1(1, _displayInfo.m_symvolBase[i]);
		std::string string2(1, _displayInfo.m_symvolNew[i]);
		m_table->setItem(row, i, new QTableWidgetItem(QString::fromStdString(string1)));
		m_table->setItem(row+1, i, new QTableWidgetItem(QString::fromStdString(string2)));
		switch (_displayInfo.m_action[i])
		{
		case ActionType::Add:
		{
			color = QColor(174, 214, 241);
			break;
		}
		case ActionType::Substitute:
		{
			color = QColor(252, 243, 207);
			break;
		}
		case ActionType::Erase:
		{
			color = QColor(232, 218, 239);
			break;
		}
		case ActionType::RemainTheSame:
		{
			color = QColor(171, 235, 198);
			break;
		}
		default:
			color = Qt::white;
			break;
		}
		m_table->item(row, i)->setBackground(color);
		m_table->item(row+1, i)->setBackground(color);
	}
}

void lab1_CFKC::displayTable(QVector<DisplayInfo> & _displayInfo)
{
	if (!m_table)
	{
		m_table = new QTableWidget;
		
	}
	m_table->setRowCount(0);
	//m_table->setSizePolicy( QtGui->QSizePolicy->Minimum, QtGui->QSizePolicy->Minimum);
	m_table->setMaximumHeight(500);
//	m_table->setMaximumWidth(100);
	m_table->setMinimumHeight(100);
	m_table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	m_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	m_tableBoxLayout->addWidget(m_table);
	int maxsize = m_word1->text().size()+m_word2->text().size();
	int rowSize =  (_displayInfo.size() * 3-1);
	m_table->setRowCount(rowSize);
	m_table->setColumnCount(maxsize);
	m_table->setMinimumWidth(10* maxsize);
	m_table->horizontalHeader()->setDefaultSectionSize(40);
	int row = 0;
	for (int i = 0; i < _displayInfo.size(); i++)
	{
		addDisplatInfoTable(_displayInfo[i], row);
		row +=2;
		if (i != _displayInfo.size() - 1)
		{
			++row;
		}
	}
}
//void lab1_CFKC::clickResult1()
//{
//	QString fileName1 = QFileDialog::getOpenFileName(
//		this,
//		"Open Document",
//		QDir::currentPath(),
//		"All files (*.*) ");
//}

