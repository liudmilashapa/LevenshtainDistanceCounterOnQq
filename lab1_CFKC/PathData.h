#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>


enum class ActionType
{
    RemainTheSame = 0,
    Erase = 1,
    Add = 2,
    AddOrErase = 3,
    Substitute = 4,
    Count = 5

};

//using PathData = std::vector< std::vector<ActionType> >;

//---------------------------------------------------------------------------

struct PathData
{
    //---------------------------------------------------------------------------

    struct Branch
    {
        void pushBackOtherBranch(Branch& other)
        {
            int branchSize = other.m_actions.size();
            for (int i = 0; i < branchSize; ++i)
            {
                m_actions.push_back(other.m_actions[i]);
            }
        }
        bool isRemainTheSameTrue(int& firstPos, int& secondPos, std::string _baseWord, std::string _resultWord)
        {
            if (_baseWord.front() == _resultWord.front())
            {
                return true;
            }
            else
            {
                size_t foundIndF = _baseWord.find_first_of(_resultWord);
                size_t foundIndS = _resultWord.find_first_of(_baseWord);
                if ((foundIndF != std::string::npos) && (foundIndS != std::string::npos))
                {
                    firstPos = foundIndF;
                    secondPos = foundIndS;
                    return true;
                }
                else return false;
            }
        }
        bool isValidBranch(std::string _baseWord, std::string _resultWord)
        {
            int basePos = 0;
            int resPos = 0;
            if ((m_actions.size() < 1)
                || (m_actions.size() > (_baseWord.size() + _resultWord.size())))
            {
                return false;
            }
            if (m_actions.front() == ActionType::RemainTheSame)
            {
                if (!isRemainTheSameTrue(basePos, resPos, _baseWord, _resultWord))
                {
                    return false;
                }
            }

           // if ((m_actions.size() < _resultWord.size())
           //     || (m_actions.size() > (_baseWord.size()+ _resultWord.size()))
           //     )
           // {
           //     return false;
           // }
            int resW = 0;
            int baseW =0;
            for (auto action : m_actions)
            {
               
                switch (action)
                {
                case ActionType::Add:
                {
                    ++resW;
                    break; 
                }
                case ActionType::Erase:
                {
                    ++baseW;
                    break; 
                }
                case ActionType::Substitute:
                {
                    ++resW;
                    ++baseW;
                    break; 
                }
                case ActionType::RemainTheSame:
                {
                    ++resW;
                    ++baseW;
                    break;
                }
                default:
                    break;
                }
            }
            return ((baseW + basePos) == _baseWord.size() && ((resW+resPos)==_resultWord.size()));
           //    // (resW > _resultWord.size() || baseW > _resultWord.size()) ?  false : true;
           // bool res1 = resW <= _resultWord.size();
           // bool res2 = baseW <= _resultWord.size();
           // return res1 || res2;
        }

        void addAction(ActionType action)
        {
            m_actions.push_back(action);
        }
      
            void printBranch( std::string& output)
        {
            static const std::string sc_lut[static_cast<int>(ActionType::Count)] = { "=", "-", "+", "+-", "#" };

            int branchSize = m_actions.size();
            for (int i = 0; i < branchSize; ++i)
            {

               // std::cout << "|" << sc_lut[static_cast<int>(m_actions[i])] << "|";
                output += "|";
                output += sc_lut[static_cast<int>(m_actions[i])];
                output += "|";
            }

            //std::cout << "\n";
            output+= "\n";
        }
        //void printBranch()
        //{
        //    static const std::string sc_lut[static_cast<int>(ActionType::Count)] = { "=", "-", "+", "+-", "#" };

        //    int branchSize = m_actions.size();
        //    for (int i = 0; i < branchSize; ++i)
        //    {

        //         std::cout << "|" << sc_lut[static_cast<int>(m_actions[i])] << "|";
        //    }

        //    std::cout << "\n";
        //}

        std::vector<ActionType> m_actions;
    };

    //---------------------------------------------------------------------------

    struct Branches
    {
        Branches()
        {
        }

        Branch& getBestBranch(int size)
        {
            int index;
            int min=-1;
            for (int i = 0; i < m_branches.size(); i++)
            {
                if (m_branches[i].m_actions.size() != size)
                {
                    continue;
                }
                int tempMin = 0;
                for (int j = 0; j < m_branches[i].m_actions.size(); j++)
                {
                    switch (m_branches[i].m_actions[j])
                    {
                        {   case ActionType::Add:
                            tempMin += 3;
                            break;
                        }
                        {   case ActionType::Substitute:
                            tempMin += 2;
                            break;
                        }
                        {   case ActionType::Erase:
                            tempMin += 3;
                            break;
                        }
                        {   case ActionType::RemainTheSame:
                            tempMin += 1;
                            break;
                        }
                    default:
                        break;
                    }
                }
                if (tempMin < min || min == -1)
                {
                    min = tempMin;
                    index = i;
                }
            }
            return m_branches[index];
        }

        Branch & getBranch(int _idx)
        {
            return m_branches[_idx];
        }

        int getBranchesCount()
        {
            return m_branches.size();
        }

        //void addActionToAllBranches(ActionType action)
        //{
        //    if (getBranchesCount() == 0)
        //    {
        //        addBranch();
        //    }

        //    int branchesCount = getBranchesCount();

        //    for (int i = 0; i < branchesCount; ++i)
        //    {
        //        m_branches[i].addAction(action);
        //    }
        //}

        void copyBranchToAllBranches(Branch& branch)
        {
            int branchesCount = getBranchesCount();

            for (int i = 0; i < branchesCount; ++i)
            {
                m_branches[i].pushBackOtherBranch(branch);
            }
        }

        void addBranch()
        {
            m_branches.emplace_back(Branch());
        }

   /*     void printPath()
        {
            int branchesCount = getBranchesCount();

            std::cout << "\nValid paths:\n";
        
            for (int i = 0; i < branchesCount; ++i)
            {
                std::cout << "\nPath #" << i << ":\n\n";
               
                m_branches[i].printBranch();
            }
        }

        std::vector< Branch > m_branches;
    };*/

    std::string printPath()
    {
        std::string output;
        int branchesCount = getBranchesCount();
     //   std::cout << "\nValid paths:\n";
        output+=  "\nValid paths:\n";

        for (int i = 0; i < branchesCount; ++i)
        {
            //std::cout << "\nPath #" << i << ":\n\n";
            output += "\nPath #";
            output += i;
            output += ":\n\n";

            m_branches[i].printBranch( output);
        }
        return output;
    }

    std::vector< Branch > m_branches;
    };

    //---------------------------------------------------------------------------
    PathData() {};
    PathData(int height, int width)
        : m_height(height), m_width(width)
    {
        m_pathData.resize(m_height * m_width);
    }

    //void addActionTo(int i, ActionType action)
    //{
    //    m_pathData[i].addActionToAllBranches(action);
    //}

    //void copyBranches(int srcCellIdx, int dstCellIdx)
    //{
    //    int srcBranchesCount = m_pathData[srcCellIdx].getBranchesCount();

    //    for (int i = 0; i < srcBranchesCount; ++i)
    //    {
    //        Branch& srcBranch = m_pathData[srcCellIdx].getBranch(i);
    //        m_pathData[dstCellIdx].copyBranchToAllBranches(srcBranch);
    //    }
    //}

    Branches& getBranches(int cellIdx)
    {
        return m_pathData[cellIdx];
    }

    //---------------------------------------------------------------------------

    using PathDataStruct = std::vector< Branches >;
    PathDataStruct m_pathData;
    int m_height;
    int m_width;
};

//---------------------------------------------------------------------------

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
//void matrixFirstsLineFilling(int lenght1, int lenght2, std::vector<int>& matrix, PathData& data)
//{
//    for (int i = 1; i < std::max(lenght1, lenght2); i++)
//    {
//
//        if (i < lenght1)
//        {
//            matrix[i] = i;
//            //            data.addActionTo(i, ActionType::Erase);
//        }
//        if (i < lenght2)
//        {
//            matrix[i * lenght1] = i;
//            //            data.addActionTo(i * lenght1, ActionType::Add);
//        }
//    }
//}
//
//int countLevenshtein(std::string& firstWord, std::string& secondWord, std::vector<int>& matrix, PathData& data)
//{
//    int length1 = firstWord.size() + 1;
//    int length2 = secondWord.size() + 1;
//    matrix.clear();
//    matrix.resize((length1 + 1) * (length2 + 1), 0);
//
//    matrixFirstsLineFilling(length1, length2, matrix, data);
//
//    std::unordered_map<ActionType, int> branchSplit;
//
//    for (int i = 1; i < length2; i++)
//        for (int j = 1; j < length1; j++)
//        {
//            int equal = ((firstWord.at(j - 1) == secondWord.at(i - 1)) ? 0 : 1);
//            int insertionPath = matrix.at((i)*length1 + j - 1) + 1;
//            int deletionPath = matrix.at((i - 1) * length1 + j) + 1;
//            int substitutionPath = matrix.at((i - 1) * length1 + j - 1) + equal;
//            int min = std::min({ insertionPath, deletionPath, substitutionPath });
//
//            matrix[i * (length1)+j] = min;
//            //matrix.erase(matrix.begin() + i * (length1)+j);
//            //matrix.insert(matrix.begin() + i * (length1)+j, 1, min);
//
//            branchSplit.clear();
//
//            if (min == insertionPath)
//            {
//                //                data.copyBranches(i*length1 + j - 1, i*length1 + j);
//                //                data.addActionTo(i*length1 + j, ActionType::Add);
//                branchSplit[ActionType::Add] = i * length1 + j - 1;
//            }
//            if (min == deletionPath)
//            {
//                //data.copyBranches((i-1)*length1 + j, i*length1 + j);
//                //data.addActionTo(i*length1 + j, ActionType::Erase);
//                branchSplit[ActionType::Erase] = (i - 1) * length1 + j;
//            }
//            if (min == substitutionPath)
//            {
//                //data.copyBranches((i - 1)*length1 + j - 1, i*length1 + j);
//                //data.addActionTo(i*length1 + j, equal == 0 ? ActionType::RemainTheSame : ActionType::Substitute);
//                branchSplit[equal == 0 ? ActionType::RemainTheSame : ActionType::Substitute] = (i - 1) * length1 + j - 1;
//            }
//
//            PathData::Branches& currentCellBranches = data.getBranches(i * length1 + j);
//
//            auto it = branchSplit.begin();
//            for (int i = 0; i < branchSplit.size(); ++i, ++it)
//            {
//                PathData::Branches& otherBranches = data.getBranches(it->second);
//                if (otherBranches.getBranchesCount() != 0)
//                {
//                    for (int j = 0; j < otherBranches.getBranchesCount(); ++j)
//                    {
//                        currentCellBranches.addBranch();
//                        currentCellBranches.getBranch(i + j).pushBackOtherBranch(otherBranches.getBranch(j));
//                        currentCellBranches.getBranch(i + j).addAction(it->first);
//                    }
//                }
//                else
//                {
//                    if (currentCellBranches.getBranchesCount() < i + 1)
//                    {
//                        currentCellBranches.addBranch();
//                    }
//                    currentCellBranches.getBranch(i).addAction(it->first);
//                }
//            }
//
//        }
//
//    return matrix.back();
//}
//
//void matrixPrint(std::string& firstWord, std::string& secondWord, std::vector<int>& matrix)
//{
//    //  std::string first = "  " + firstWord;
//    //  std::string second = " " + secondWord;
//    for (int i = 0; i < (firstWord.size() + 1) * (secondWord.size() + 1); i++)
//    {
//        if ((i % (firstWord.size() + 1) == 0) && i != 0)
//        {
//            std::cout << std::endl;
//        }
//        std::cout << " " << matrix.at(i);
//
//    }
//}
//
//int main()
//{
//    std::string firstWord = "HYUNDAI";
//    std::string secondWord = "HONDA";
//    std::vector<int> matrix;
//
//    PathData data(firstWord.size() + 1, secondWord.size() + 1);
//
//    int dif = countLevenshtein(firstWord, secondWord, matrix, data);
//    matrixPrint(firstWord, secondWord, matrix);
//
//    data.getBranches((firstWord.size() + 1) * (secondWord.size() + 1) - 1).printPath();
//
//    std::string source = ("ALISIA");
//    std::string dest("GOALS");
//
//    PathData anotherData(source.size() + 1, dest.size() + 1);
//    int distance = countLevenshtein(source, dest, matrix, anotherData);
//    matrixPrint(source, dest, matrix);
//
//    anotherData.getBranches((source.size() + 1) * (dest.size() + 1) - 1).printPath();
//
//    // std::cout << distance;
//   // std::cout << source;
//   // std::cout << dest;
//}