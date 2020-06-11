#pragma once

#include <QObject>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include "PathData.h"


enum class SymvolAction
{
    Insertion,
    Substitution,
    Deletion,
    Equal
};

enum class IndxType
{
    Left, 
    Up,
    Diagonal
};

struct NeighborhoodIndx
{
    NeighborhoodIndx(int _indx, int _firstWordSize)
    :m_indx(_indx)
    {
        int indxtemp = m_indx - 1;
        m_indxLeft = ((isIndxValid(indxtemp,_firstWordSize)) ? (indxtemp) : -1);
        indxtemp = _indx - _firstWordSize - 1;
        m_indxUp = ((isIndxValid(indxtemp, _firstWordSize)) ? (indxtemp) : -1);
        indxtemp = _indx - _firstWordSize - 2;
        m_indxDioganal = ((isIndxValid(indxtemp, _firstWordSize)) ? (indxtemp) : -1);
    }
    bool isIndxValid(int indx, int m_firstMaxInd)
    {
        //return ((indx > m_firstMaxInd) && (indx % m_firstMaxInd != 0));
        return ((indx > -1) );
    }

    void setMin(std::vector<int> & m_matrix)
    {
        int temp1 = (m_indxDioganal != -1)?(m_matrix.at(m_indxDioganal)):INT16_MAX;
        int temp2 = (m_indxUp != -1) ? (m_matrix.at(m_indxUp)) : INT16_MAX;
        int temp3 = (m_indxLeft!= -1) ? (m_matrix.at(m_indxLeft)) : INT16_MAX;

        m_min = std::min({ temp1, temp2, temp3 });
    }

    bool isIndxMin(std::vector<int> & m_matrix, IndxType _indxType)
    {
        switch (_indxType)
        {
        case IndxType::Diagonal:
        {
         if (m_indxDioganal!= -1)
         {
             if (m_min == m_matrix.at(m_indxDioganal))
             {
                 return true;
             }
         }
         return false; 
        }
        case IndxType::Up:
        {
            if (m_indxUp != -1)
            {
                if (m_min == m_matrix.at(m_indxUp))
                {
                    return true;
                }
            }
            return false;
        }
        case IndxType::Left:
        {
            if (m_indxLeft != -1)
            {
                if (m_min == m_matrix.at(m_indxLeft))
                {
                    return true;
                }
            }
            return false;
        }
        
        default:
            break;
        }

    }

    int m_min;
    int m_indxLeft;
    int m_indxUp;
    int m_indxDioganal;
    int m_indx;

};

struct DisplayInfo
{
    /*DisplayInfo(char _symvolBase, SymvolAction _action, char _symvolNew)
        :m_action(_action)
    {
        switch (m_action)
        {
        case SymvolAction::Equal:
        {
            m_symvolBase = _symvolBase;
            m_symvolNew = _symvolNew;
            break;
        }
        case SymvolAction::Substitution:
        {
            m_symvolBase = _symvolBase;
            m_symvolNew = _symvolNew;
            break;
        }
        case SymvolAction::Deletion:
        {
            m_symvolBase = _symvolBase;
            m_symvolNew = ' ';
            break;
        }
        case SymvolAction::Insertion:
        {
            m_symvolBase = ' ';
            m_symvolNew = _symvolNew;
            break;
        }?

        default:
            break;
        }
    }*/
    
    std::string m_symvolBase;
    std::vector<ActionType> m_action;
    std::string m_symvolNew;

    DisplayInfo() {}

    DisplayInfo(PathData::Branch & branch, std::string _firstWord, std::string _secondWord)
    {
        int i = 0;
        while (_secondWord.size() != 0 || _firstWord.size() != 0)
        {
           /* if (i >= branch.m_actions.size())
            {*/
                if (_secondWord.size() == 0)
                { 

                    m_symvolBase.push_back(_firstWord.front());
                    m_symvolNew.push_back(' ');
                    _firstWord.erase(0, 1);
                    m_action.push_back(ActionType::Erase);
                    ++i; 
                    continue;
                }
                else if (_firstWord.size() == 0)
                {

                    m_symvolBase.push_back(' ');
                    m_symvolNew.push_back(_secondWord.front());
                    _secondWord.erase(0, 1);
                    m_action.push_back(ActionType::Add);
                    ++i;
                    continue;
                }
               
         //   }

            switch (branch.m_actions[i])
            {
            case ActionType::RemainTheSame:
            {
                if (_firstWord.front() != _secondWord.front())
                {
                    int foundInd = _firstWord.find_first_of(_secondWord);
                    char symvol = _firstWord.at(foundInd);
                    while (_firstWord.front() != _secondWord.front())
                    {
                        if (_firstWord.front() != symvol)
                        {
                            m_symvolBase.push_back(_firstWord.front());
                            m_symvolNew.push_back(' ');
                            _firstWord.erase(0, 1);
                            m_action.push_back(ActionType::Erase);
                        }
                        else 
                        {
                            m_symvolBase.push_back(' ');
                            m_symvolNew.push_back(_secondWord.front());
                            _secondWord.erase(0, 1);
                            m_action.push_back(ActionType::Add);
                        }
                        
                        if (_secondWord.size() == 0 || _firstWord.size() == 0)
                        {
                            return;
                        }
                    }
                }
                    m_symvolBase.push_back(_firstWord.front());
                    _firstWord.erase(0,1);
                    m_symvolNew.push_back(_secondWord.front());
                    _secondWord.erase(0,1);
                    m_action.push_back(ActionType::RemainTheSame);
                break;
            }
            case ActionType::Add:
            {
                m_symvolBase.push_back(' ');
                m_symvolNew.push_back(_secondWord.front());
                _secondWord.erase(0,1);
                m_action.push_back(ActionType::Add);
                break;
            }
            case ActionType::Erase:
            {
                m_symvolBase.push_back(_firstWord.front());
                _firstWord.erase(0,1);
                m_symvolNew.push_back(' ');
                m_action.push_back(ActionType::Erase);
                break;
            }
            case ActionType::Substitute:
            {
                m_symvolBase.push_back(_firstWord.front());
                m_symvolNew.push_back(_secondWord.front());
                _secondWord.erase(0,1);
                _firstWord.erase(0,1);
                m_action.push_back(ActionType::Substitute);
                break;
            }

            default:
                break;
            }
            i++;
        }
    };
};

class Levenshtein : public QObject {
    Q_OBJECT 
public:

    Levenshtein();
    
    int returnIndex(int less, int lendht, bool isFirst, int i);
    bool isIndxValid(int indx, int m_firstMaxInd);
    void addWordInfo(   const int min1, const int min2, 
                        const std::vector<int> & line1, const int line2, 
                        const int col1, const std::vector<int> & col2, 
                        int & nextFirstLess, int & nextSecondLess
                    );

    void findAllMin(std::vector<int>& line1, int& min, int less1, int less2, int lenght1, int lenght2, bool i);

    void addDisplayInfo(int j, int i, int temp1, int temp2, int temp3, int equal);
    //void addDisplayInfo(int firstWordless = 1, int secondWordless = 1);
    void addDisplayInfo(int i);
    void addDisplayInfo();

	void matrixFirstsLineFilling(int lenght1, int lenght2);
    void matrixFilling();
    
    void countLevenshteinDiff();
    void countMaxSimilarity();

    int getLevenshteinDiff();
    int getLevenshteinSim();
    void matrixPrint();

private:
    std::string m_firstWord;
    QVector<DisplayInfo> m_WordInfo;
  
    PathData m_pathData;
    std::string m_secondWord;
    std::vector<int> m_matrix;
    int m_LevenshteinDiff;
    int m_LevenshteinSim;

public slots:

    void slotFirstWord(const QString& text);
    void slotSecondWord(const QString& text);
    void clickResult();

signals:

    void differenceChanged(int);
    void similarityChanged(int);
  //  void readyToDisplay(std::vector<DisplayInfo> &);
    void readyToDisplay(QVector<DisplayInfo>&);


};