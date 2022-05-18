#include <iostream>
#include <string>

#include "../Src/Log.hpp"
#include "../Src/MarkdownIndex.hpp"

void logList(const md::TitleList& list){
    LOGE("md::TitleList{\n");
    for(const auto& e : list)
    {
        LOGE("\t"<<e<<"\n");
    }
    LOGE("}\n");
}


int test_file(const auto& filePath,const md::TitleList& expected){
    auto optContent{md::readRaw(filePath)};
    if(!optContent)
    {
        LOGE("Cannot read <" << filePath << ">\n");
        return 1;
    }

    auto titleList{md::ram::titlesFromContent(optContent.value())};

    if(titleList != expected)
    {
        if(size(titleList) != size(expected))
        {
            LOGEL("ERROR : Not same titles count");
            LOGEL("\tDIFF : GOT<"<<size(titleList)<<">   EXPECTED<"<<size(expected)<<">");

            LOGEL(" -- EXPECTED --\n"<<expected);
            LOGEL(" -- GOT --\n" << titleList);
        }
        else
        {
            auto maxIter{std::min(size(titleList),size(expected))};
            for(size_t i{}; i < maxIter;++i)
            {
                if(titleList[i] != expected[i])
                    LOGEL("\tDIFF : GOT<"<<titleList[i]<<">   EXPECTED<"<<expected[i]<<">");
            }
        }

        return 1;
    }
    return 0;
}

int main(int argc,char* argv[]){
    auto constexpr testFile_basic{"../../Tests/Inputs/Test_0.md"};
    auto constexpr testFile_complex{"../../Tests/Inputs/Test_complex_0.md"};

    md::TitleList expected_basic{{1,"Gros fichier"},{.level=2,.text="Et un sous-titre ! -TEst## \"é\"<[0]>, est\'^ important & (pas_que) 10% pour20$*+10-\'3\'"},{3,"Et un sous-sous titre"},{3,"Parce qu'il faut bien plusieurs parties"}};
    
    md::TitleList expected_complex{
        {1,"s7a_STM32_VSCode"},
        {1,"Solution rapide (Compter 5-10min)"},
        {2,"1 - Installer le SDK_eled"},
        {3,"Méthode 1"},
        {3,"Méthode 2"},
        {2,"2 - Installer les extensions VSCode"},
        {3,"1 -> Extension essentielle"},
        {3,"2 -> Extensions conseillées"},
        {2,"3 - Initialiser le dossier du projet"},
        {2,"4 - Ouvrir le dossier du projet avec VSCode"},
        {1,"Utilisation"},
        {2,"1 - Compilation"},
        {2,"2 - Lancement du programme"},
        {2,"3 - En cas de problème"},
        {3,"En rédaction "},
        {1,"Procédure manuelle détaillée"},
        {2,"Pré-requis"}
    };

    return test_file(testFile_basic,expected_basic) || test_file(testFile_complex,expected_complex);
}
