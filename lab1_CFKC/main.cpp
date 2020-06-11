#include "lab1_CFKC.h"
#include "LevenCounter.h"

#include <QtWidgets>

int main(int argc, char *argv[])
{
	
    QApplication app(argc, argv);
    lab1_CFKC * window = new lab1_CFKC();
  //  QMainWindow* window = new QMainWindow();
    ////QWidget* wgt = new QWidget();

    //QPushButton* pcmdA = new QPushButton("A");
    //QPushButton* pcmdB = new QPushButton("B");
    //QPushButton* pcmdC = new QPushButton("C");

    ////Layout setup
    //QVBoxLayout* phbxLayout = new QVBoxLayout;
    //phbxLayout->setContentsMargins(10, 10, 10, 10);
    //phbxLayout->setSpacing(20);
    //phbxLayout->addWidget(pcmdA);
    //phbxLayout->addWidget(pcmdB);
    //phbxLayout->addWidget(pcmdC);
    //window->setLayout(phbxLayout);

 
  

   Levenshtein levenCounter;
 
  
    QObject::connect(window->m_resultButtton, SIGNAL(clicked()),
        &levenCounter, SLOT(clickResult())
    );

    //QObject::connect(window->m_resultButtton, SIGNAL(clicked()),
    //    window, SLOT(clickResult1())
    //);

    QObject::connect(&levenCounter, SIGNAL(differenceChanged(int)),
        window->m_difLbl, SLOT(setNum(int))
    );

    QObject::connect(&levenCounter, SIGNAL(similarityChanged(int)),
        window->m_simLbl, SLOT(setNum(int))
    );

    QObject::connect(&levenCounter, SIGNAL(readyToDisplay(QVector<DisplayInfo>&)),
        window, SLOT(displayTable(QVector<DisplayInfo>&))
    );

    QObject::connect(window->m_word1, SIGNAL(textChanged(const QString&)),
        &levenCounter, SLOT(slotSecondWord(const QString&))
    );  
    
    QObject::connect(window->m_word2, SIGNAL(textChanged(const QString&)),
        &levenCounter, SLOT(slotFirstWord(const QString&))
    );

    window->show();
    //QDebug(QtDebugMsg) << "text";

    return app.exec();
}
