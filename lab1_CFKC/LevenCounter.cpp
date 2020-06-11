#include "LevenCounter.h"

//template<typename T>
//typename T::size_type LevenshteinDistance(const T& source,
//    const T& target) 
//{
//    if (source.size() > target.size()) {
//        return LevenshteinDistance(target, source);
//    }
//
//    using TSizeType = typename T::size_type;
//    const TSizeType min_size = source.size(), max_size = target.size();
//    std::vector<TSizeType> lev_dist(min_size + 1);
//
//    for (TSizeType i = 0; i <= min_size; ++i) {
//        lev_dist[i] = i;
//    }
//
//    for (TSizeType j = 1; j <= max_size; ++j) {
//        TSizeType previous_diagonal = lev_dist[0], previous_diagonal_save;
//        ++lev_dist[0];
//
//        for (TSizeType i = 1; i <= min_size; ++i) {
//            previous_diagonal_save = lev_dist[i];
//            if (source[i - 1] == target[j - 1]) {
//                lev_dist[i] = previous_diagonal;
//            }
//            else {
//                lev_dist[i] = std::min(std::min(lev_dist[i - 1], lev_dist[i]), previous_diagonal) + 1;
//            }
//            previous_diagonal = previous_diagonal_save;
//        }
//    }
//
//    return lev_dist[min_size];
//}
//



Levenshtein::Levenshtein() 
:m_LevenshteinDiff(-1){}


int Levenshtein::returnIndex(int less, int lenght, bool isFirst, int i)
{
 if (isFirst)
    {
        return (less + (lenght * i));
    }
    else 
    {
        return (less * lenght + i);
    }
}

void Levenshtein::findAllMin(std::vector<int>& line1, int & min,  int less1, int less2, int lenght1, int lenght2, bool isFirst)
{

    for (int i = less2; i < lenght2; i++)
    {   
        int index = returnIndex(less1, lenght1, isFirst, i);
        if (m_matrix.at(index) < min || min == -1)
        {
            min = m_matrix.at(index);
        }
    }
    for (int i = less2; i < lenght2; i++)
    {
        int index = returnIndex(less1, lenght1, isFirst, i);
        if (m_matrix.at(index) == min)
        {
            line1.push_back(i);
        }
    }
}


//void Levenshtein::addWordInfo(  const int min1, const int min2,
//                                const std::vector<int> & line1, const int line2,
//                                const  int col1, const std::vector<int> & col2,
//                                int & nextFirstLess, int & nextSecondLess
//                             )
//{
//    SymvolAction action;
//
//    //for (auto lineEl : line1)
//    //{
//    //    for (auto colEl : col2)
//    //    {
//    //        if (m_firstWord.at(lineEl - 1) == m_secondWord.at(colEl - 1))
//    //        {
//    //            if (lineEl == line2 && colEl == col1)
//    //            {
//    //                action = SymvolAction::Equal;
//    //                ++nextFirstLess; ++nextSecondLess;
//    //            }
//    //            else if (lineEl > line2 && colEl == col1)
//    //            {
//    //                action = SymvolAction::Insertion;
//    //                nextFirstLess; ++nextSecondLess;
//    //            }
//    //            else if (lineEl == line2 && colEl > col1)
//    //            {
//    //                action = SymvolAction::Deletion;
//    //                ++nextFirstLess; nextSecondLess;
//    //            }
//    //        }
//    //        else if (lineEl == line2 && colEl == col1 )
//    //        {
//    //            action = SymvolAction::Substitution;
//    //            ++nextFirstLess; ++nextSecondLess
//    //                ;
//    //        }
//    //    }
//    //}
//    if (line1.size() == 1 && (col2.size() == 1))
//    {
//        if (m_firstWord.at(col2.front()-1) == m_secondWord.at(line1.front()-1))
//        {
//            action = SymvolAction::Equal;
//        }
//        else
//        {
//            action = SymvolAction::Substitution;
//        }
//        ++nextFirstLess; ++nextSecondLess;
//    }
//    else if (line1.size() > 1)
//    {
//        action = SymvolAction::Insertion;
//        nextFirstLess; ++nextSecondLess;
//   
//    }
//    else if (col2.size() > 1)
//    {
//     action = SymvolAction::Deletion;
//     ++nextFirstLess; nextSecondLess;
//    }
//    m_firstWordInfo.push_back(DisplayInfo({m_firstWord.at(col1-1) ,action, m_secondWord.at(line2-1)}));
//}

//void Levenshtein::addDisplayInfo(int j, int i, int temp1, int temp2, int temp3, int equal)
//{
//    int min = std::min({temp1,temp2,temp3});
//    SymvolAction action;
//
//    if (equal == 0)
//    {
//        action = SymvolAction::Equal;
//    }
//    else    
//        if (min == temp1)
//        {
//            action = SymvolAction::Insertion;
//        }
//        else  
//            if (min == temp2)
//            {
//                action = SymvolAction::Deletion;
//            }
//            else 
//            {
//                action = SymvolAction::Substitution;
//            }
//
//    m_firstWordInfo.push_back(DisplayInfo({ m_firstWord[j-1], action , m_secondWord[i-1]}));
//}

//void Levenshtein::addDisplayInfo(int firstWordless , int secondWordless )
//{
//    int lenght1 = m_firstWord.size() + 1;
//    int lenght2 = m_secondWord.size() + 1;
//    int min1 = -1;
//    int min2 = -1;
//    
//    int nextFirstLess = firstWordless;
//    int nextSecondLess = secondWordless;
//    int col1 = firstWordless;
//    int line2 = secondWordless;
//    std::vector<int> line1;
//    std::vector<int> col2;
//    findAllMin(line1, min1, firstWordless, secondWordless, lenght1, lenght2, true);
//    findAllMin(col2, min2, secondWordless, firstWordless,  lenght1, lenght1, false);
//    addWordInfo(min1, min2, line1, line2, col1, col2, nextFirstLess, nextSecondLess);
//
//    if (firstWordless == m_firstWord.size() && secondWordless == m_secondWord.size())
//    {
//        return;
//    }
//    else if (firstWordless == m_firstWord.size() && secondWordless != m_secondWord.size())
//    {
//        for (int i=secondWordless+1; i < lenght2; i++)
//        {
//            m_firstWordInfo.push_back(DisplayInfo({ ' ', SymvolAction::Insertion, m_secondWord.at(i-1) }));
//        }
//        return;
//    }
//    else if (firstWordless != m_firstWord.size() && secondWordless == m_secondWord.size())
//    {
//        for (int i = firstWordless + 1; i < lenght1; i++)
//        {
//            m_firstWordInfo.push_back(DisplayInfo({ m_firstWord.at(i-1), SymvolAction::Deletion, ' ' }));
//        }
//        return;
//    }
//
//    addDisplayInfo(nextFirstLess, nextSecondLess);
//}

//bool Levenshtein::isIndxValid(int indx, int m_firstMaxInd)
//{
//    return ((indx > m_firstMaxInd) && (indx % m_firstMaxInd != 0));
//}

//void Levenshtein::addDisplayInfo(int i)
//{
//    int currentIndfirst = m_firstWord.size();
//    int currentIndsecond = m_secondWord.size();
//    std::vector<int> oldQueue;
//    std::vector<int> yangQueue;
//    std::vector<int>tempInd;
//    oldQueue.push_back((m_firstWord.size() + 1) * (m_secondWord.size() + 1) - 1);
//    tempInd.push_back((m_firstWord.size() + 1) * (m_secondWord.size() + 1) - 1);
//    while(!oldQueue.empty())
//    {
//        int up = oldQueue.front() - m_firstWord.size();
//        int left = oldQueue.front() - 1;
//        int diagonal = oldQueue.front() - 1 - m_firstWord.size();
//        yangQueue.push_back(up);
//        yangQueue.push_back(left);
//        yangQueue.push_back(diagonal);
//
//
//    }
//}

//void Levenshtein::addDisplayInfo()
//{
//    m_firstWordInfo.clear();
//    SymvolAction action;
//    int lenghtMax = std::max({m_firstWord.size(), m_secondWord.size()});
//    int currentIndfirst = m_firstWord.size();
//    int currentIndsecond = m_secondWord.size();
//    int nextIndfirst;
//    int nextIndsecond;
//    
//    for (int i = lenghtMax; i > 0; --i)
//    {
//        int LetterIndFirstWorld = currentIndfirst - 1;
//        int LetterIndSecondWorld = currentIndsecond - 1;
//        int indx = (m_firstWord.size() + 1) * currentIndsecond + currentIndfirst;
//        NeighborhoodIndx neighborhoodIndx(indx, (int)(m_firstWord.size()));
//        neighborhoodIndx.setMin(m_matrix);
//        if (neighborhoodIndx.isIndxMin( m_matrix, IndxType::Diagonal))
//        {
//            if (m_firstWord.at(LetterIndFirstWorld) == m_secondWord.at(LetterIndSecondWorld))
//            {
//                action = SymvolAction::Equal;
//            }
//            else 
//            {
//                action = SymvolAction::Substitution;
//            }
//
//            nextIndfirst = --currentIndfirst;
//            nextIndsecond= --currentIndsecond;
//        }
//        else 
//            if (neighborhoodIndx.isIndxMin(m_matrix, IndxType::Left))
//            {
//                action = SymvolAction::Deletion;
//                nextIndfirst = --currentIndfirst;
//                nextIndsecond = currentIndsecond;
//            }
//            else if (neighborhoodIndx.isIndxMin(m_matrix, IndxType::Up))
//            {
//                action = SymvolAction::Insertion;
//                nextIndfirst = currentIndfirst;
//                nextIndsecond = --currentIndsecond;
//            }
//  
//        m_firstWordInfo.insert(m_firstWordInfo.begin(), DisplayInfo({ m_firstWord.at(LetterIndFirstWorld), action, m_secondWord.at(LetterIndSecondWorld) }));
//        if (currentIndfirst == 0 )
//        {
//            for (int i = currentIndsecond ; i > 0; --i)
//            {
//            m_firstWordInfo.insert(m_firstWordInfo.begin(), DisplayInfo({ m_firstWord.at(i-1), SymvolAction::Deletion, ' ' }));
//            }
//            return;
//        }
//        if (currentIndsecond == 0)
//        {
//            for (int i = currentIndfirst; i > 0 ; --i)
//            {
//                m_firstWordInfo.insert(m_firstWordInfo.begin(), DisplayInfo({ m_firstWord.at(i - 1), SymvolAction::Deletion, ' ' }));
//            }
//            return;
//        }
//        currentIndfirst = nextIndfirst;
//        currentIndsecond = nextIndsecond;
//    }
//
//}


void Levenshtein::matrixFirstsLineFilling(int lenght1, int lenght2)
{
    for (int i = 1; i < std::max(lenght1, lenght2); i++)
    {
        if (i < lenght1)
        {
            m_matrix[i] = i;
          /*  m_matrix.erase(m_matrix.begin() + i);
            m_matrix.insert(m_matrix.begin() + i, 1, i);*/
        }
        if (i < lenght2)
        {
            m_matrix[i * lenght1] = i;
           /* int j = i * lenght1;
            m_matrix.erase(m_matrix.begin() + j);
            m_matrix.insert(m_matrix.begin() + j, 1, i);*/
        }
    }
}

void Levenshtein::matrixFilling()
{
    int lenght1 = m_firstWord.size() + 1;
    int lenght2 = m_secondWord.size() + 1;
    m_matrix.reserve((lenght1) * (lenght2));
    m_matrix.insert(m_matrix.begin(), (lenght1) * (lenght2), 0);
    matrixFirstsLineFilling(lenght1, lenght2);

    for (int j = 1; j < lenght1; j++)
        for (int i = 1; i < lenght2; i++)
        {
            int equal = (m_firstWord.at(j - 1) == m_secondWord.at(i - 1) ? 0 : 1);//equal

            int temp1 = m_matrix.at((i)*lenght1 + j - 1) + 1;//insertion
            int temp2 = m_matrix.at((i - 1) * lenght1 + j) + 1;//deletion
            int temp3 = m_matrix.at((i - 1) * lenght1 + j - 1) + equal;//substitution

            int min = std::min({ temp1, temp2, temp3 });
         //   addDisplayInfo(j, i, temp1, temp2, temp3, equal);
            m_matrix.erase(m_matrix.begin() + i * (lenght1)+j);
            m_matrix.insert(m_matrix.begin() + i * (lenght1)+j, 1, min);
        }
}

//void Levenshtein::countLevenshteinDiff()
//{
//    m_matrix.clear();
//    m_LevenshteinDiff = -1;
//    if (m_firstWord.empty() || m_secondWord.empty())
//    {
//        m_LevenshteinDiff = -1;
//    }
//    else
//    {
//        matrixFilling();
//       m_LevenshteinDiff = m_matrix.back();
//    }
//}
void Levenshtein::countLevenshteinDiff()
    //std::string& firstWord, std::string& secondWord, std::vector<int>& matrix, PathData& data)
{
    int length1 = m_firstWord.size() + 1;
    int length2 = m_secondWord.size() + 1;
    m_matrix.clear();
    m_matrix.resize((length1 + 1) * (length2 + 1), 0);

    matrixFirstsLineFilling(length1, length2);

    std::unordered_map<ActionType, int> branchSplit;

    for (int i = 1; i < length2; i++)
        for (int j = 1; j < length1; j++)
        {
            int equal = ((m_firstWord.at(j - 1) == m_secondWord.at(i - 1)) ? 0 : 1);
            int insertionPath = m_matrix.at((i)*length1 + j - 1) + 1;
            int deletionPath = m_matrix.at((i - 1) * length1 + j) + 1;
            int substitutionPath = m_matrix.at((i - 1) * length1 + j - 1) + equal;
            int min = std::min({ insertionPath, deletionPath, substitutionPath });

            m_matrix[i * (length1)+j] = min;
            //matrix.erase(matrix.begin() + i * (length1)+j);
            //matrix.insert(matrix.begin() + i * (length1)+j, 1, min);

            branchSplit.clear();

            if (min == insertionPath)
            {
                //                data.copyBranches(i*length1 + j - 1, i*length1 + j);
                //                data.addActionTo(i*length1 + j, ActionType::Add);
                branchSplit[ActionType::Add] = i * length1 + j - 1;
            }
            if (min == deletionPath)
            {
                //data.copyBranches((i-1)*length1 + j, i*length1 + j);
                //data.addActionTo(i*length1 + j, ActionType::Erase);
                branchSplit[ActionType::Erase] = (i - 1) * length1 + j;
            }
            if (min == substitutionPath)
            {
                //data.copyBranches((i - 1)*length1 + j - 1, i*length1 + j);
                //data.addActionTo(i*length1 + j, equal == 0 ? ActionType::RemainTheSame : ActionType::Substitute);
                branchSplit[equal == 0 ? ActionType::RemainTheSame : ActionType::Substitute] = (i - 1) * length1 + j - 1;
            }

            PathData::Branches& currentCellBranches = m_pathData.getBranches(i * length1 + j);

            auto it = branchSplit.begin();
            for (int i = 0; i < branchSplit.size(); ++i, ++it)
            {
                PathData::Branches& otherBranches = m_pathData.getBranches(it->second);
                if (otherBranches.getBranchesCount() != 0)
                {
                    for (int j = 0; j < otherBranches.getBranchesCount(); ++j)
                    {
                        currentCellBranches.addBranch();
                        currentCellBranches.getBranch(i + j).pushBackOtherBranch(otherBranches.getBranch(j));
                        currentCellBranches.getBranch(i + j).addAction(it->first);
                    }
                }
                else
                {
                    if (currentCellBranches.getBranchesCount() < i + 1)
                    {
                        currentCellBranches.addBranch();
                    }
                    currentCellBranches.getBranch(i).addAction(it->first);
                }
            }

        }

    m_LevenshteinDiff = m_matrix.at(length1*length2-1);
}

void Levenshtein::countMaxSimilarity()
{
    if (!m_WordInfo.isEmpty())
    {
        int maxSimilarity = 0;
        for (int i = 0; i < m_WordInfo.size(); i++)
        {
            int temp = m_WordInfo.at(i).m_action.size() - m_LevenshteinDiff;
            if (temp > maxSimilarity)
            {
                maxSimilarity = temp;
            }
        }
        m_LevenshteinSim = maxSimilarity;
    }
    else m_LevenshteinSim = 0;
}

int Levenshtein::getLevenshteinDiff()
{
    return m_LevenshteinDiff;
}

int Levenshtein::getLevenshteinSim()
{
    return m_LevenshteinSim;
}

void Levenshtein::slotFirstWord(const QString& text)
{
    m_firstWord = text.toStdString();
}

void Levenshtein::slotSecondWord(const QString& text)
{
    m_secondWord = text.toStdString();
}

void Levenshtein::clickResult()
{
    m_pathData = PathData(m_firstWord.size() + 1, m_secondWord.size() + 1);
    countLevenshteinDiff();
    int diff = getLevenshteinDiff();
    if (diff != -1)
    {   
        m_WordInfo.clear();
//        emit resultChanged(temp);
        int ind = (m_firstWord.size() + 1) * (m_secondWord.size() + 1) - 1;     
        for (int i = 0; i < m_pathData.getBranches(ind).getBranchesCount(); i++)
        {
            /*int actionSize = m_pathData.getBranches(ind).getBranch(i).m_actions.size();
            if (actionSize<m_firstWord.size() || actionSize>(m_firstWord.size() + m_secondWord.size()))
            {
                continue;
            }*/
            if (m_pathData.getBranches(ind).getBranch(i).isValidBranch(m_secondWord, m_firstWord))
            {
                m_WordInfo.push_back(DisplayInfo(m_pathData.getBranches(ind).getBranch(i), m_secondWord, m_firstWord));
            }
        }
        countMaxSimilarity();
        emit differenceChanged(diff);
        emit similarityChanged(getLevenshteinSim());
        emit readyToDisplay(m_WordInfo);
    }
    else
    {
        emit differenceChanged(0);
        emit similarityChanged(0);
    }
}

//void matrixPrint(std::string & firstWord, std::string & secondWord, std::vector<int> & matrix)
//{
//    std::string first = "  " + firstWord;
//    std::string second = " " + secondWord;
//    for (int i = 0; i < (firstWord.size() + 2) * (secondWord.size() + 2); i++)
//    {
//
//        if ((i % (firstWord.size() + 2) == 0) && i != 0)
//        {
//            std::cout << std::endl << " " << second.at(i%(firstWord.size()+2));
//        }
//        if (i < firstWord.size() + 2)
//        {
//            std::cout << " " << first.at(i);
//        }
//        else
//        {
//            std::cout << " " << matrix.at(i);
//        }
//    }
//}
//};
//int main()
//{
//    std::string firstWord = "HYUNDAY";
//    std::string secondWord = "HONDA";
//    std::vector<int> matrix;
//    int dif = countLevenshtein(firstWord, secondWord, matrix);
//    matrixPrint(firstWord, secondWord, matrix);
//
//    // std::string source = ("GOALS");
//    // std::string dest("ALISIA");
//    // int distance = LevenshteinDistance(source, dest);
//    // std::cout << distance;
//    // std::cout << source;
//    // std::cout << dest;
//}

void Levenshtein::matrixPrint()
    //std::string& firstWord, std::string& secondWord, std::vector<int>& matrix)
{
    //  std::string first = "  " + firstWord;
    //  std::string second = " " + secondWord;
    for (int i = 0; i < (m_firstWord.size() + 1) * (m_secondWord.size() + 1); i++)
    {
        if ((i % (m_firstWord.size() + 1) == 0) && i != 0)
        {
            std::cout << std::endl;
        }
        std::cout << " " << m_matrix.at(i);

    }
}
